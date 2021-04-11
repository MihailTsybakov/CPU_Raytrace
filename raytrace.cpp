#include "raytrace.h"

/* ======== Raytracer ======== */

raytracer::raytracer(string src_scene, string src_obj, string saveto, int thread_number)
{
    this->src_scene = src_scene;
    this->src_obj = src_obj;
    this->saveto = saveto;
    this->thread_number = thread_number;
}

bool raytracer::calc_shadow(vector<double> point, vector<double> light_src, vector<figure*> shapes) const
{
    double light_dist = dist_quad(light_src, point);
    for (auto shape : shapes)
    {
        vector<double> t_result = { 0,0,0, 0,0,0, 0,0,0, 0,0 };
        if (shape->traceback(point, light_src - point, t_result, 2))
        {
            vector<double> intersection = { t_result[0], t_result[1], t_result[2] };
            if (light_dist < dist_quad(point, intersection)) return true;
        }
    }
    return false;
}

double raytracer::calc_light(vector<double> surface_normal, vector<double> light_ray, int stype, int otype, bool shadow) const
{
    if (shadow == true) return 0;
    surface_normal = to_length(surface_normal, 1.0);
    light_ray = to_length(light_ray, 1.0);
    double cos_alpha = scalmul(surface_normal, light_ray);
    if (stype == 0) // Diffuse
    {
        if (cos_alpha <= 0) return 0;
        return cos_alpha;
    }
    switch (otype)
    {
    case 1: // sphere
        if (cos_alpha + 0.25 <= 0) return 0;
        return pow(cos_alpha + 0.25, 3);

    case 2: // box
        if (cos_alpha + 0.6 <= 0) return 0;
        return pow(cos_alpha + 0.6, 5);

    case 3: // tetra
        if (cos_alpha + 0.6 <= 0) return 0;
        return pow(cos_alpha + 0.6, 6);

    default:
        return 0;
    }
}

void raytracer::stripe_trace(int h_start, int h_end,
    int width, Canvas& frame,
    vector<double> lu_corner, // left upper corner
    vector<double> camera,
    vector<double> upvector,
    vector<double> normal,
    vector<double> ortsup,
    vector<double> light_source,
    vector<figure*> shapes,
    double view_depth) const
{
    vector<double> curr_p;
    vector<vector<double>> intersections;
    for (int i = h_start; i < h_end; ++i)
    {
        curr_p = lu_corner;
        for (int j = 0; j < width; ++j)
        {
            intersections.clear();
            vector<double> t_result = { 0,0,0, 0,0,0, 0,0,0, 0,0 }; // 11
            vector<double> trace_ray = curr_p - camera;
            for (auto shape : shapes)
            {
                if (shape->traceback(camera, trace_ray, t_result, 1)) intersections.push_back(t_result);
            }
            if (intersections.size() > 0)
            {
                vector<double> closest_intersection = intersections[0];
                if (intersections.size() > 1) closest_intersection = intersections[closest_point(intersections, trace_ray)];

                vector<double> point = { closest_intersection[0], closest_intersection[1], closest_intersection[2] };
                vector<double> surf_normal = { closest_intersection[6], closest_intersection[7], closest_intersection[8] };
                vector<double> light_ray = light_source - point;

                double light_coef = calc_light(surf_normal, light_ray,
                    closest_intersection[9],
                    closest_intersection[10],
                    calc_shadow(point, light_source, shapes));

                if (dist_quad(point, curr_p) > view_depth * view_depth) light_coef = 0;

                int R = static_cast<int>(light_coef * closest_intersection[3]); if (R > 255) R = 255;
                int G = static_cast<int>(light_coef * closest_intersection[4]); if (G > 255) G = 255;
                int B = static_cast<int>(light_coef * closest_intersection[5]); if (B > 255) B = 255;
                frame.put_pixel(j, i, R, G, B); /* !!! */
            }
            curr_p = curr_p - ortsup;
        }
        lu_corner = lu_corner - upvector;
    }
}

void raytracer::raytrace() const
{
    try
    {
        if (saveto.find(".bmp") == string::npos)
        {
            throw raytrace_exception("Error: unsupported image format encountered.");
        }
        vector<double> camera, normal, upvector, light;
        int screen_height, screen_width;
        double screen_distance, view_depth;
        vector<figure*> shapes;

        reader so_reader(src_scene, src_obj); //scene & objects reader
        so_reader.read_scene(camera, normal, light, upvector, screen_distance, screen_height, screen_width, view_depth);
        so_reader.read_objects(shapes);

        vector<double> ort_sup = vectmul(upvector, normal);
        upvector = to_length(upvector, screen_height / 2);
        ort_sup = to_length(ort_sup, screen_width / 2);
        normal = to_length(normal, screen_distance);

        vector<double> lu_corner = camera + normal + upvector + ort_sup; //left upper corner
        upvector = to_length(upvector, 1);
        ort_sup = to_length(ort_sup, 1);

        Canvas frame(screen_width, screen_height);
        frame.fill_canvas(0, 0, 0);

        if (screen_height % thread_number != 0) throw raytrace_exception("Error: screen_height % thread_number must be 0.");
        vector<vector<double>> pivot_points = { lu_corner };
        for (int i = 0; i < thread_number - 1; ++i) pivot_points.push_back(lu_corner - upvector * (i + 1) * (screen_height / thread_number));
        vector<thread> thread_pool;

        int h = screen_height / thread_number;
        for (int i = 0; i < thread_number; ++i)
        {
            thread_pool.push_back(thread(&raytracer::stripe_trace, this, h * i, (i + 1) * h, screen_width, ref(frame), pivot_points[i], camera,
                upvector, normal, ort_sup, light, shapes, view_depth));
        }
        for (auto thread_iter = thread_pool.begin(); thread_iter != thread_pool.end(); ++thread_iter) thread_iter->join();
        frame.save(saveto);
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

/* ======== Renderer ======== */

renderer::renderer(string scene_template, string obj_template, string save_template, int thread_number)
{
    this->scene_template = scene_template;
    this->obj_template = obj_template;
    this->save_template = save_template;
    this->thread_number = thread_number;
}

string renderer::gettime() const
{
    time_t raw_time;
    tm* timeinfo;
    time(&raw_time);
    timeinfo = localtime(&raw_time);
    stringstream ss;
    ss << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec;
    return ss.str();
}

void renderer::render_scope(int scope_start, int scope_end, bool logs, spinlock& slock) const
{
    try
    {
        if (scope_start >= scope_end) throw render_exception("Error: wrong scope render borders.");
        for (int i = scope_start; i < scope_end; ++i)
        {
            stringstream ss;
            ss << i;
            raytracer rtracer(scene_template + ss.str() + ".txt", obj_template + ss.str() + ".txt", save_template + ss.str() + ".bmp", 1);
            rtracer.raytrace();
            if (logs)
            {
                slock.lock();
                cout << "thread <" << this_thread::get_id() << ">: rendered frame " << i << endl;
                slock.unlock();
            }
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

void renderer::render(int frame_number, bool logs) const
{
    try
    {
        if (logs)
        {
            cout << "render started: " << gettime() << endl;
        }
        vector<thread> thread_pool;
        if (frame_number % thread_number != 0)
        {
            throw render_exception("Error: frame_number % thread_number must be 0.");
        }
        int N = frame_number / thread_number;
        spinlock s_lock;
        for (int i = 0; i < thread_number; ++i)
        {
            thread_pool.push_back(thread(&renderer::render_scope, this, i * N + 1, (i + 1) * N + 1, logs, ref(s_lock)));
        }
        for (auto thread_iter = thread_pool.begin(); thread_iter != thread_pool.end(); ++thread_iter) thread_iter->join();
        if (logs)
        {
            cout << "render ended: " << gettime() << endl;
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

void renderer::join_to_video(string frame_template, string video_name, int framerate, int quality) const
{
    stringstream ss;
    ss << "ffmepg -framerate " << framerate << " -i " << frame_template << " -q " << quality << " " << video_name;
    system((ss.str()).c_str());
}