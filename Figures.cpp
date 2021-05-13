#include "Figures.h"

/* ======== Constructors & Destructors ======== */

figure::figure() {}
figure::~figure() {}
sphere::~sphere() {}
box::~box()
{
    v1.clear(); edge_1.clear();
    v2.clear(); edge_2.clear();
    v3.clear(); edge_3.clear();
    v4.clear(); edge_4.clear();
    v5.clear(); edge_5.clear();
    v6.clear(); edge_6.clear();
    v7.clear(); v8.clear();
}

tetra::~tetra()
{
    v1.clear(); edge_1.clear();
    v2.clear(); edge_2.clear();
    v3.clear(); edge_3.clear();
    v4.clear(); edge_4.clear();
}

sphere::sphere(double x, double y, double z, double Rad, int R, int G, int B, int surface)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->Rad = Rad;
    this->R = static_cast<uint8_t>(R);
    this->G = static_cast<uint8_t>(G);
    this->B = static_cast<uint8_t>(B);
    this->surface = static_cast<uint8_t>(surface);
}

box::box(double x1, double y1, double z1,
    double x8, double y8, double z8,
    int R, int G, int B, int surface)
{
    this->R = static_cast<uint8_t>(R);
    this->G = static_cast<uint8_t>(G);
    this->B = static_cast<uint8_t>(B);#include "Figures.h"

/* ======== Constructors & Destructors ======== */

figure::figure() {}
figure::~figure() {}
sphere::~sphere() {}
box::~box()
{
    v1.clear(); edge_1.clear();
    v2.clear(); edge_2.clear();
    v3.clear(); edge_3.clear();
    v4.clear(); edge_4.clear();
    v5.clear(); edge_5.clear();
    v6.clear(); edge_6.clear();
    v7.clear(); v8.clear();
}

tetra::~tetra()
{
    v1.clear(); edge_1.clear();
    v2.clear(); edge_2.clear();
    v3.clear(); edge_3.clear();
    v4.clear(); edge_4.clear();
}

sphere::sphere(double x, double y, double z, double Rad, int R, int G, int B, int surface)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->Rad = Rad;
    this->R = static_cast<uint8_t>(R);
    this->G = static_cast<uint8_t>(G);
    this->B = static_cast<uint8_t>(B);
    this->surface = static_cast<uint8_t>(surface);
}

box::box(double x1, double y1, double z1,
    double x8, double y8, double z8,
    int R, int G, int B, int surface)
{
    this->R = static_cast<uint8_t>(R);
    this->G = static_cast<uint8_t>(G);
    this->B = static_cast<uint8_t>(B);
    this->surface = static_cast<uint8_t>(surface);
    double dx = x8 - x1, dy = y8 - y1, dz = z8 - z1;

    v1 = { x1, y1, z1 };
    v8 = { x8, y8, z8 };
    v2 = { x1 + dx, y1, z1 };
    v3 = { x1, y1 + dy, z1 };
    v4 = { x1 + dx, y1 + dy, z1 };
    v5 = { x1, y1, z1 + dz };
    v6 = { x1 + dx, y1, z1 + dz };
    v7 = { x1, y1 + dy, z1 + dz };

    half_diag_quad = 0.5 * dist_quad(v1, v8);

    edge_1 = { v1, v2, v4, v3 }; edge_2 = { v1, v5, v7, v3 };
    edge_3 = { v1, v5, v6, v2 }; edge_4 = { v3, v7, v8, v4 };
    edge_5 = { v2, v6, v8, v4 }; edge_6 = { v5, v6, v8, v7 };

    /* edge_1 = 1, 2, 4, 3
       edge_2 = 1, 5, 7, 3
       edge_3 = 1, 5, 6, 2
       edge_4 = 3, 7, 8, 4
       edge_5 = 2, 6, 8, 4
       edge_6 = 5, 6, 8, 7 */
}

tetra::tetra(double x1, double y1, double z1,
    double x2, double y2, double z2,
    double x3, double y3, double z3,
    double x4, double y4, double z4,
    int R, int G, int B, int surface)
{
    this->R = static_cast<uint8_t>(R);
    this->G = static_cast<uint8_t>(G);
    this->B = static_cast<uint8_t>(B);
    this->surface = static_cast<uint8_t>(surface);

    v1 = { x1, y1, z1 };
    v2 = { x2, y2, z2 };
    v3 = { x3, y3, z3 };
    v4 = { x4, y4, z4 };

    /* edge_1 = 1, 2, 3
       edge_2 = 1, 4, 3
       edge_3 = 2, 3, 4
       edge_4 = 1,2,4   */

    edge_1 = { v1, v2, v3 };
    edge_2 = { v1, v4, v3 };
    edge_3 = { v2, v3, v4 };
    edge_4 = { v1, v2, v4 };

    // Calculating circumscribed sphere center
    vector<double> v_1 = { (x4 * x4 - x1 * x1 + y4 * y4 - y1 * y1 + z4 * z4 - z1 * z1), y4 - y1, z4 - z1 };
    vector<double> v_2 = { (x4 * x4 - x2 * x2 + y4 * y4 - y2 * y2 + z4 * z4 - z2 * z2), y4 - y2, z4 - z2 };
    vector<double> v_3 = { (x4 * x4 - x3 * x3 + y4 * y4 - y3 * y3 + z4 * z4 - z3 * z3), y4 - y3, z4 - z3 };
    vector<double> v_1_ = { x4 - x1, y4 - y1, z4 - z1 };
    vector<double> v_2_ = { x4 - x2, y4 - y2, z4 - z2 };
    vector<double> v_3_ = { x4 - x3, y4 - y3, z4 - z3 };

    double denominator = 2 * volume_vect(v_1_, v_2_, v_3_);

    double x0 = volume_vect(v_1, v_2, v_3) / denominator;
    v_1 = { x4 - x1, (x4 * x4 - x1 * x1 + y4 * y4 - y1 * y1 + z4 * z4 - z1 * z1), z4 - z1 };
    v_2 = { x4 - x2, (x4 * x4 - x2 * x2 + y4 * y4 - y2 * y2 + z4 * z4 - z2 * z2), z4 - z2 };
    v_3 = { x4 - x3, (x4 * x4 - x3 * x3 + y4 * y4 - y3 * y3 + z4 * z4 - z3 * z3), z4 - z3 };
    double y0 = volume_vect(v_1, v_2, v_3) / denominator;
    v_1 = { x4 - x1, y4 - y1, (x4 * x4 - x1 * x1 + y4 * y4 - y1 * y1 + z4 * z4 - z1 * z1) };
    v_2 = { x4 - x2, y4 - y2, (x4 * x4 - x2 * x2 + y4 * y4 - y2 * y2 + z4 * z4 - z2 * z2) };
    v_3 = { x4 - x3, y4 - y3, (x4 * x4 - x3 * x3 + y4 * y4 - y3 * y3 + z4 * z4 - z3 * z3) };
    double z0 = volume_vect(v_1, v_2, v_3) / denominator;

    optimize_center = { x0, y0, z0 };
    circumscribed_RAD = dist_quad(optimize_center, v1);
}

/* ======== Ray Tracing ======== */

bool sphere::traceback(const vector<double>& s_point,
    const vector<double>& trace_ray,
    vector<double>& res_v,
    int trace_mode)
{
    double coef_a = pow(trace_ray[0], 2) + pow(trace_ray[1], 2) + pow(trace_ray[2], 2);
    double coef_b = 2 * (s_point[0] * trace_ray[0] + s_point[1] * trace_ray[1] +
        s_point[2] * trace_ray[2] - trace_ray[0] * x - trace_ray[1] * y - trace_ray[2] * z);
    double coef_c = pow(s_point[0] - x, 2) + pow(s_point[1] - y, 2) + pow(s_point[2] - z, 2) - pow(Rad, 2);
    double discriminant = pow(coef_b, 2) - 4 * coef_a * coef_c;
    if (discriminant <= 0)
    {
        return false;
    }
    double parameter_1 = (-coef_b - pow(discriminant, 0.5)) / (2 * coef_a);
    double parameter_2 = (-coef_b + pow(discriminant, 0.5)) / (2 * coef_a);
    if (trace_mode == 2)
    {
        if (parameter_1 > 0 && parameter_2 > 0) return true;
        return false;
    }
    vector<double> intersection;
    if (parameter_1 > parameter_2)
    {
        intersection = s_point + trace_ray * parameter_2;
    }
    else
    {
        intersection = s_point + trace_ray * parameter_1;
    }
    vector<double> sphere_center = { x, y, z };
    vector<double> surface_normal = intersection - sphere_center;

    res_v[0] = intersection[0]; res_v[1] = intersection[1]; res_v[2] = intersection[2];
    res_v[3] = R; res_v[4] = G; res_v[5] = B;
    res_v[6] = surface_normal[0]; res_v[7] = surface_normal[1]; res_v[8] = surface_normal[2];
    res_v[9] = surface; res_v[10] = 1;

    return true;
}

bool box::internal_point(vector<double> point, int edge_number) const
{
    // edge_1 = 1, 2, 4, 3; edge_2 = 1, 5, 7, 3; edge_3 = 1, 5, 6, 2; edge_4 = 3, 7, 8, 4; edge_5 = 2, 6, 8, 4; edge_6 = 5, 6, 8, 7;
    try
    {
        switch (edge_number)
        {
        case 1:
            if (point[0] >= v1[0] &&
                point[0] <= v2[0] &&
                point[1] >= v1[1] &&
                point[1] <= v3[1])
            {
                return true;
            }
            return false;
        case 2:
            if (point[1] >= v1[1] &&
                point[1] <= v3[1] &&
                point[2] >= v1[2] &&
                point[2] <= v7[2])
            {
                return true;
            }
            return false;
        case 3:
            if (point[0] >= v1[0] &&
                point[0] <= v2[0] &&
                point[2] >= v1[2] &&
                point[2] <= v5[2])
            {
                return true;
            }
            return false;
        case 4:
            if (point[0] >= v3[0] &&
                point[0] <= v4[0] &&
                point[2] >= v3[2] &&
                point[2] <= v8[2])
            {
                return true;
            }
            return false;
        case 5:
            if (point[1] >= v2[1] &&
                point[1] <= v4[1] &&
                point[2] >= v2[2] &&
                point[2] <= v8[2])
            {
                return true;
            }
            return false;
        case 6:
            if (point[0] >= v5[0] &&
                point[0] <= v6[0] &&
                point[1] >= v5[1] &&
                point[1] <= v7[1])
            {
                return true;
            }
            return false;
        default:
            throw raytrace_exception("Error occured while tried to calculate internal dot: box.");
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
    return false;
}

bool box::traceback(const vector<double>& s_point,
    const vector<double>& trace_ray,
    vector<double>& res_v,
    int trace_mode)
{
    std::vector<std::vector<double>> intersections;
    std::vector<std::vector<double>> normals;
    std::vector<double> params;
    double alpha = trace_ray[0], beta = trace_ray[1], gamma = trace_ray[2];
    bool inner = false;
    // edge_1 = 1, 2, 4, 3; edge_2 = 1, 5, 7, 3; edge_3 = 1, 5, 6, 2; edge_4 = 3, 7, 8, 4; edge_5 = 2, 6, 8, 4; edge_6 = 5, 6, 8, 7;

    // Edge 1:
    if (gamma != 0)
    {
        double parameter = (v1[2] - s_point[2]) / gamma;
        if (parameter == 0) inner = true;
        double x = s_point[0] + alpha * parameter;
        double y = s_point[1] + beta * parameter;
        std::vector<double> point = { x,y,v1[2] };
        if (internal_point(point, 1) == true)
        {
            intersections.push_back(point);
            normals.push_back({ 0,0,-1 });
            params.push_back(parameter);
        }
    }
    // Edge 2:
    if (alpha != 0)
    {
        double parameter = (v1[0] - s_point[0]) / alpha;
        if (parameter == 0) inner = true;
        double y = s_point[1] + beta * parameter;
        double z = s_point[2] + gamma * parameter;
        std::vector<double> point = { v1[0], y, z };
        if (internal_point(point, 2) == true)
        {
            intersections.push_back(point);
            normals.push_back({ -1, 0, 0 });
            params.push_back(parameter);
        }
    }
    // Edge 3:
    if (beta != 0)
    {
        double parameter = (v1[1] - s_point[1]) / beta;
        if (parameter == 0) inner = true;
        double x = s_point[0] + alpha * parameter;
        double z = s_point[2] + gamma * parameter;
        std::vector<double> point = { x, v1[1], z };
        if (internal_point(point, 3) == true)
        {
            intersections.push_back(point);
            normals.push_back({ 0, -1, 0 });
            params.push_back(parameter);
        }
    }
    // Edge 4:
    if (beta != 0)
    {
        double parameter = (v3[1] - s_point[1]) / beta;
        if (parameter == 0) inner = true;
        double x = s_point[0] + alpha * parameter;
        double z = s_point[2] + gamma * parameter;
        std::vector<double> point = { x, v3[1], z };
        if (internal_point(point, 4) == true)
        {
            intersections.push_back(point);
            normals.push_back({ 0,1,0 });
            params.push_back(parameter);
        }
    }
    // Edge 5:
    if (alpha != 0)
    {
        double parameter = (v2[0] - s_point[0]) / alpha;
        if (parameter == 0) inner = true;
        double y = s_point[1] + beta * parameter;
        double z = s_point[2] + gamma * parameter;
        std::vector<double> point = { v2[0], y, z };
        if (internal_point(point, 5) == true)
        {
            intersections.push_back(point);
            normals.push_back({ 1,0,0 });
            params.push_back(parameter);
        }
    }
    // Edge 6:
    if (gamma != 0)
    {
        double parameter = (v8[2] - s_point[2]) / gamma;
        if (parameter == 0) inner = true;
        double x = s_point[0] + alpha * parameter;
        double y = s_point[1] + beta * parameter;
        std::vector<double> point = { x, y, v8[2] };
        if (internal_point(point, 6) == true)
        {
            intersections.push_back(point);
            normals.push_back({0,0,1});
            params.push_back(parameter);
        }
    }
    if (trace_mode == 2)
    {
        if (intersections.size() > 0 && inner == false)
        {
            for (auto p : params) if (p <= 0) return false;
            return true;
        }
        return false;
    }
    // res_v = {x, y, z, R, G, B, Nx, Ny, Nz, Surface, Otype}
    if (intersections.size() == 2)
    {
        double D1 = dist_quad(intersections[0], s_point);
        double D2 = dist_quad(intersections[1], s_point);
        res_v[3] = R; res_v[4] = G; res_v[5] = B;
        res_v[9] = surface; res_v[10] = 2;
        if (D1 <= D2)
        {
            res_v[0] = intersections[0][0]; res_v[1] = intersections[0][1]; res_v[2] = intersections[0][2];
            res_v[6] = normals[0][0]; res_v[7] = normals[0][1]; res_v[8] = normals[0][2];
        }
        else
        {
            res_v[0] = intersections[1][0]; res_v[1] = intersections[1][1]; res_v[2] = intersections[1][2];
            res_v[6] = normals[1][0]; res_v[7] = normals[1][1]; res_v[8] = normals[1][2];
        }
        return true;
    }
    return false;
}

bool tetra::internal_point(vector<double> point, vector<vector<double>> edge) const
{
    vector<double> sign;
    sign.push_back(vectmul_area(edge[1] - edge[0], point - edge[0]));
    sign.push_back(vectmul_area(edge[2] - edge[1], point - edge[1]));
    sign.push_back(vectmul_area(edge[0] - edge[2], point - edge[2]));
    size_t positive = 0, negative = 0, zero = 0;
    for (auto s : sign)
    {
        if (s > 0) positive++;
        if (s == 0) zero++;
        if (s < 0) negative++;
    }
    if ((zero + positive == sign.size()) || (zero + negative == sign.size()))
    {
        return true;
    }
    return false;
}

bool tetra::traceback(const vector<double>& s_point,
    const vector<double>& trace_ray,
    vector<double>& res_v,
    int trace_mode)
{
    vector<vector<double>> intersections;
    vector<vector<double>> Ns;
    vector<double> v_1, v_2, N, point;
    double D, param, x, y, z;
    // Calculating distance to mass center:
    vector<double> center_vect = optimize_center - s_point;
    double dist = scalmul(center_vect, center_vect) - pow(scalmul(center_vect, trace_ray), 2) / scalmul(trace_ray, trace_ray);
    if (dist > circumscribed_RAD) /// !
    {
        return false;
    }
    // edge_1:
    v_1 = edge_1[1] - edge_1[0];
    v_2 = edge_1[2] - edge_1[0];
    N = vectmul(v_1, v_2);
    if (scalmul(N, trace_ray) != 0)
    {
        D = N[0] * edge_1[0][0] + N[1] * edge_1[0][1] + N[2] * edge_1[0][2];
        param = (D - N[0] * s_point[0] - N[1] * s_point[1] -
            N[2] * s_point[2]) / (N[0] * trace_ray[0] + N[1] * trace_ray[1] + N[2] * trace_ray[2]);
        x = s_point[0] + trace_ray[0] * param, y = s_point[1] + trace_ray[1] * param, z = s_point[2] + trace_ray[2] * param;
        point = { x,y,z };
        if (internal_point(point, edge_1) == true)
        {
            intersections.push_back(point);
            Ns.push_back(N);
        }
    }
    // edge_2:
    v_1 = edge_2[1] - edge_2[0];
    v_2 = edge_2[2] - edge_2[0];
    N = vectmul(v_1, v_2);
    if (scalmul(N, trace_ray) != 0)
    {
        D = N[0] * edge_2[0][0] + N[1] * edge_2[0][1] + N[2] * edge_2[0][2];
        param = (D - N[0] * s_point[0] - N[1] * s_point[1] -
            N[2] * s_point[2]) / (N[0] * trace_ray[0] + N[1] * trace_ray[1] + N[2] * trace_ray[2]);
        x = s_point[0] + trace_ray[0] * param, y = s_point[1] + trace_ray[1] * param, z = s_point[2] + trace_ray[2] * param;
        point = { x,y,z };
        if (internal_point(point, edge_2) == true)
        {
            intersections.push_back(point);
            Ns.push_back(N);
        }
    }
    // edge_3:
    v_1 = edge_3[1] - edge_3[0];
    v_2 = edge_3[2] - edge_3[0];
    N = vectmul(v_1, v_2);
    if (scalmul(N, trace_ray) != 0)
    {
        D = N[0] * edge_3[0][0] + N[1] * edge_3[0][1] + N[2] * edge_3[0][2];
        param = (D - N[0] * s_point[0] - N[1] * s_point[1] -
            N[2] * s_point[2]) / (N[0] * trace_ray[0] + N[1] * trace_ray[1] + N[2] * trace_ray[2]);
        x = s_point[0] + trace_ray[0] * param, y = s_point[1] + trace_ray[1] * param, z = s_point[2] + trace_ray[2] * param;
        point = { x,y,z };
        if (internal_point(point, edge_3) == true)
        {
            intersections.push_back(point);
            Ns.push_back(N);
        }
    }
    // edge_4:
    v_1 = edge_4[1] - edge_4[0];
    v_2 = edge_4[2] - edge_4[0];
    N = vectmul(v_1, v_2);
    if (scalmul(N, trace_ray) != 0)
    {
        D = N[0] * edge_4[0][0] + N[1] * edge_4[0][1] + N[2] * edge_4[0][2];
        param = (D - N[0] * s_point[0] - N[1] * s_point[1] -
            N[2] * s_point[2]) / (N[0] * trace_ray[0] + N[1] * trace_ray[1] + N[2] * trace_ray[2]);
        x = s_point[0] + trace_ray[0] * param, y = s_point[1] + trace_ray[1] * param, z = s_point[2] + trace_ray[2] * param;
        point = { x,y,z };
        if (internal_point(point, edge_4) == true)
        {
            intersections.push_back(point);
            Ns.push_back(N);
        }
    }
    if (intersections.size() != 0 && intersections.size() != 2)
    {
        return false;
    }
    if (intersections.size() == 0)
    {
        return false;
    }
    vector<double> screen_point = s_point + trace_ray;
    vector<double> ans, Nans;
    if (intersections.size() == 2)
    {
        double distance_1 = dist_quad(screen_point, intersections[0]), distance_2 = dist_quad(screen_point, intersections[1]);
        if (distance_1 <= distance_2)
        {
            ans = intersections[0];
            Nans = Ns[0];
        }
        else
        {
            ans = intersections[1];
            Nans = Ns[1];
        }
    }
    vector<double> check_n = ans - optimize_center;
    if (scalmul(check_n, Nans) < 0)
    {
        Nans[0] = -Nans[0];
        Nans[1] = -Nans[1];
        Nans[2] = -Nans[2];
    }
    res_v[0] = ans[0]; res_v[1] = ans[1]; res_v[2] = ans[2];
    res_v[3] = R; res_v[4] = G; res_v[5] = B; res_v[6] = Nans[0];
    res_v[7] = Nans[1]; res_v[8] = Nans[2]; res_v[9] = surface;
    res_v[10] = 3;
    return true;
}
    this->surface = static_cast<uint8_t>(surface);
    double dx = x8 - x1, dy = y8 - y1, dz = z8 - z1;

    v1 = { x1, y1, z1 };
    v8 = { x8, y8, z8 };
    v2 = { x1 + dx, y1, z1 };
    v3 = { x1, y1 + dy, z1 };
    v4 = { x1 + dx, y1 + dy, z1 };
    v5 = { x1, y1, z1 + dz };
    v6 = { x1 + dx, y1, z1 + dz };
    v7 = { x1, y1 + dy, z1 + dz };

    half_diag_quad = 0.5 * dist_quad(v1, v8);

    edge_1 = { v1, v2, v4, v3 }; edge_2 = { v1, v5, v7, v3 };
    edge_3 = { v1, v5, v6, v2 }; edge_4 = { v3, v7, v8, v4 };
    edge_5 = { v2, v6, v8, v4 }; edge_6 = { v5, v6, v8, v7 };

    /* edge_1 = 1, 2, 4, 3
       edge_2 = 1, 5, 7, 3
       edge_3 = 1, 5, 6, 2
       edge_4 = 3, 7, 8, 4
       edge_5 = 2, 6, 8, 4
       edge_6 = 5, 6, 8, 7 */
}

tetra::tetra(double x1, double y1, double z1,
    double x2, double y2, double z2,
    double x3, double y3, double z3,
    double x4, double y4, double z4,
    int R, int G, int B, int surface)
{
    this->R = static_cast<uint8_t>(R);
    this->G = static_cast<uint8_t>(G);
    this->B = static_cast<uint8_t>(B);
    this->surface = static_cast<uint8_t>(surface);

    v1 = { x1, y1, z1 };
    v2 = { x2, y2, z2 };
    v3 = { x3, y3, z3 };
    v4 = { x4, y4, z4 };

    /* edge_1 = 1, 2, 3
       edge_2 = 1, 4, 3
       edge_3 = 2, 3, 4
       edge_4 = 1,2,4   */

    edge_1 = { v1, v2, v3 };
    edge_2 = { v1, v4, v3 };
    edge_3 = { v2, v3, v4 };
    edge_4 = { v1, v2, v4 };

    // Calculating circumscribed sphere center
    vector<double> v_1 = { (x4 * x4 - x1 * x1 + y4 * y4 - y1 * y1 + z4 * z4 - z1 * z1), y4 - y1, z4 - z1 };
    vector<double> v_2 = { (x4 * x4 - x2 * x2 + y4 * y4 - y2 * y2 + z4 * z4 - z2 * z2), y4 - y2, z4 - z2 };
    vector<double> v_3 = { (x4 * x4 - x3 * x3 + y4 * y4 - y3 * y3 + z4 * z4 - z3 * z3), y4 - y3, z4 - z3 };
    vector<double> v_1_ = { x4 - x1, y4 - y1, z4 - z1 };
    vector<double> v_2_ = { x4 - x2, y4 - y2, z4 - z2 };
    vector<double> v_3_ = { x4 - x3, y4 - y3, z4 - z3 };

    double denominator = 2 * volume_vect(v_1_, v_2_, v_3_);

    double x0 = volume_vect(v_1, v_2, v_3) / denominator;
    v_1 = { x4 - x1, (x4 * x4 - x1 * x1 + y4 * y4 - y1 * y1 + z4 * z4 - z1 * z1), z4 - z1 };
    v_2 = { x4 - x2, (x4 * x4 - x2 * x2 + y4 * y4 - y2 * y2 + z4 * z4 - z2 * z2), z4 - z2 };
    v_3 = { x4 - x3, (x4 * x4 - x3 * x3 + y4 * y4 - y3 * y3 + z4 * z4 - z3 * z3), z4 - z3 };
    double y0 = volume_vect(v_1, v_2, v_3) / denominator;
    v_1 = { x4 - x1, y4 - y1, (x4 * x4 - x1 * x1 + y4 * y4 - y1 * y1 + z4 * z4 - z1 * z1) };
    v_2 = { x4 - x2, y4 - y2, (x4 * x4 - x2 * x2 + y4 * y4 - y2 * y2 + z4 * z4 - z2 * z2) };
    v_3 = { x4 - x3, y4 - y3, (x4 * x4 - x3 * x3 + y4 * y4 - y3 * y3 + z4 * z4 - z3 * z3) };
    double z0 = volume_vect(v_1, v_2, v_3) / denominator;

    optimize_center = { x0, y0, z0 };
    circumscribed_RAD = dist_quad(optimize_center, v1);
}

/* ======== Ray Tracing ======== */

bool sphere::traceback(const vector<double>& s_point,
    const vector<double>& trace_ray,
    vector<double>& res_v,
    int trace_mode)
{
    double coef_a = pow(trace_ray[0], 2) + pow(trace_ray[1], 2) + pow(trace_ray[2], 2);
    double coef_b = 2 * (s_point[0] * trace_ray[0] + s_point[1] * trace_ray[1] +
        s_point[2] * trace_ray[2] - trace_ray[0] * x - trace_ray[1] * y - trace_ray[2] * z);
    double coef_c = pow(s_point[0] - x, 2) + pow(s_point[1] - y, 2) + pow(s_point[2] - z, 2) - pow(Rad, 2);
    double discriminant = pow(coef_b, 2) - 4 * coef_a * coef_c;
    if (discriminant <= 0)
    {
        return false;
    }
    double parameter_1 = (-coef_b - pow(discriminant, 0.5)) / (2 * coef_a);
    double parameter_2 = (-coef_b + pow(discriminant, 0.5)) / (2 * coef_a);
    if (trace_mode != 1)
    {
        if (parameter_1 > 0 && parameter_2 > 0)
        {
            return true;
        }
        return false;
    }
    vector<double> intersection;
    if (parameter_1 > parameter_2)
    {
        intersection = s_point + trace_ray * parameter_2;
    }
    else
    {
        intersection = s_point + trace_ray * parameter_1;
    }
    vector<double> sphere_center = { x, y, z };
    vector<double> surface_normal = intersection - sphere_center;

    res_v[0] = intersection[0]; res_v[1] = intersection[1]; res_v[2] = intersection[2];
    res_v[3] = R; res_v[4] = G; res_v[5] = B;
    res_v[6] = surface_normal[0]; res_v[7] = surface_normal[1]; res_v[8] = surface_normal[2];
    res_v[9] = surface; res_v[10] = 1;

    return true;
}

bool box::internal_point(vector<double> point, int edge_number) const
{
    // edge_1 = 1, 2, 4, 3; edge_2 = 1, 5, 7, 3; edge_3 = 1, 5, 6, 2; edge_4 = 3, 7, 8, 4; edge_5 = 2, 6, 8, 4; edge_6 = 5, 6, 8, 7;
    try
    {
        switch (edge_number)
        {
        case 1:
            if (point[0] >= v1[0] &&
                point[0] <= v2[0] &&
                point[1] >= v1[1] &&
                point[1] <= v3[1])
            {
                return true;
            }
            return false;
        case 2:
            if (point[1] >= v1[1] &&
                point[1] <= v3[1] &&
                point[2] >= v1[2] &&
                point[2] <= v7[2])
            {
                return true;
            }
            return false;
        case 3:
            if (point[0] >= v1[0] &&
                point[0] <= v2[0] &&
                point[2] >= v1[2] &&
                point[2] <= v5[2])
            {
                return true;
            }
            return false;
        case 4:
            if (point[0] >= v3[0] &&
                point[0] <= v4[0] &&
                point[2] >= v3[2] &&
                point[2] <= v8[2])
            {
                return true;
            }
            return false;
        case 5:
            if (point[1] >= v2[1] &&
                point[1] <= v4[1] &&
                point[2] >= v2[2] &&
                point[2] <= v8[2])
            {
                return true;
            }
            return false;
        case 6:
            if (point[0] >= v5[0] &&
                point[0] <= v6[0] &&
                point[1] >= v5[1] &&
                point[1] <= v7[1])
            {
                return true;
            }
            return false;
        default:
            throw raytrace_exception("Error occured while tried to calculate internal dot: box.");
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
    return false;
}

bool box::traceback(const vector<double>& s_point,
    const vector<double>& trace_ray,
    vector<double>& res_v,
    int trace_mode)
{
    std::vector<std::vector<double>> intersections;
    std::vector<std::vector<double>> normals;
    double alpha = trace_ray[0], beta = trace_ray[1], gamma = trace_ray[2];
    bool inner = false;
    // edge_1 = 1, 2, 4, 3; edge_2 = 1, 5, 7, 3; edge_3 = 1, 5, 6, 2; edge_4 = 3, 7, 8, 4; edge_5 = 2, 6, 8, 4; edge_6 = 5, 6, 8, 7;

    // Edge 1:
    if (gamma != 0)
    {
        double parameter = (v1[2] - s_point[2]) / gamma;
        if (parameter == 0) inner = true;
        double x = s_point[0] + alpha * parameter;
        double y = s_point[1] + beta * parameter;
        std::vector<double> point = { x,y,v1[2] };
        if (internal_point(point, 1) == true)
        {
            intersections.push_back(point);
            normals.push_back({ 0,0,-1 });
        }
    }
    // Edge 2:
    if (alpha != 0)
    {
        double parameter = (v1[0] - s_point[0]) / alpha;
        if (parameter == 0) inner = true;
        double y = s_point[1] + beta * parameter;
        double z = s_point[2] + gamma * parameter;
        std::vector<double> point = { v1[0], y, z };
        if (internal_point(point, 2) == true)
        {
            intersections.push_back(point);
            normals.push_back({ -1, 0, 0 });
        }
    }
    // Edge 3:
    if (beta != 0)
    {
        double parameter = (v1[1] - s_point[1]) / beta;
        if (parameter == 0) inner = true;
        double x = s_point[0] + alpha * parameter;
        double z = s_point[2] + gamma * parameter;
        std::vector<double> point = { x, v1[1], z };
        if (internal_point(point, 3) == true)
        {
            intersections.push_back(point);
            normals.push_back({ 0, -1, 0 });
        }
    }
    // Edge 4:
    if (beta != 0)
    {
        double parameter = (v3[1] - s_point[1]) / beta;
        if (parameter == 0) inner = true;
        double x = s_point[0] + alpha * parameter;
        double z = s_point[2] + gamma * parameter;
        std::vector<double> point = { x, v3[1], z };
        if (internal_point(point, 4) == true)
        {
            intersections.push_back(point);
            normals.push_back({ 0,1,0 });
        }
    }
    // Edge 5:
    if (alpha != 0)
    {
        double parameter = (v2[0] - s_point[0]) / alpha;
        if (parameter == 0) inner = true;
        double y = s_point[1] + beta * parameter;
        double z = s_point[2] + gamma * parameter;
        std::vector<double> point = { v2[0], y, z };
        if (internal_point(point, 5) == true)
        {
            intersections.push_back(point);
            normals.push_back({ 1,0,0 });
        }
    }
    // Edge 6:
    if (gamma != 0)
    {
        double parameter = (v8[2] - s_point[2]) / gamma;
        if (parameter == 0) inner = true;
        double x = s_point[0] + alpha * parameter;
        double y = s_point[1] + beta * parameter;
        std::vector<double> point = { x, y, v8[2] };
        if (internal_point(point, 6) == true)
        {
            intersections.push_back(point);
            normals.push_back({0,0,1});
        }
    }
    if (trace_mode == 2)
    {
        if (intersections.size() > 0 && inner == false) return true;
        return false;
    }
    // res_v = {x, y, z, R, G, B, Nx, Ny, Nz, Surface, Otype}
    if (intersections.size() == 2)
    {
        double D1 = dist_quad(intersections[0], s_point);
        double D2 = dist_quad(intersections[1], s_point);
        res_v[3] = R; res_v[4] = G; res_v[5] = B;
        res_v[9] = surface; res_v[10] = 2;
        if (D1 <= D2)
        {
            res_v[0] = intersections[0][0]; res_v[1] = intersections[0][1]; res_v[2] = intersections[0][2];
            res_v[6] = normals[0][0]; res_v[7] = normals[0][1]; res_v[8] = normals[0][2];
        }
        else
        {
            res_v[0] = intersections[1][0]; res_v[1] = intersections[1][1]; res_v[2] = intersections[1][2];
            res_v[6] = normals[1][0]; res_v[7] = normals[1][1]; res_v[8] = normals[1][2];
        }
        return true;
    }
    return false;
}

bool tetra::internal_point(vector<double> point, vector<vector<double>> edge) const
{
    vector<double> sign;
    sign.push_back(vectmul_area(edge[1] - edge[0], point - edge[0]));
    sign.push_back(vectmul_area(edge[2] - edge[1], point - edge[1]));
    sign.push_back(vectmul_area(edge[0] - edge[2], point - edge[2]));
    size_t positive = 0, negative = 0, zero = 0;
    for (auto s : sign)
    {
        if (s > 0) positive++;
        if (s == 0) zero++;
        if (s < 0) negative++;
    }
    if ((zero + positive == sign.size()) || (zero + negative == sign.size()))
    {
        return true;
    }
    return false;
}

bool tetra::traceback(const vector<double>& s_point,
    const vector<double>& trace_ray,
    vector<double>& res_v,
    int trace_mode)
{
    vector<vector<double>> intersections;
    vector<vector<double>> Ns;
    vector<double> v_1, v_2, N, point;
    double D, param, x, y, z;
    // Calculating distance to mass center:
    vector<double> center_vect = optimize_center - s_point;
    double dist = scalmul(center_vect, center_vect) - pow(scalmul(center_vect, trace_ray), 2) / scalmul(trace_ray, trace_ray);
    if (dist > circumscribed_RAD) /// !
    {
        return false;
    }
    // edge_1:
    v_1 = edge_1[1] - edge_1[0];
    v_2 = edge_1[2] - edge_1[0];
    N = vectmul(v_1, v_2);
    if (scalmul(N, trace_ray) != 0)
    {
        D = N[0] * edge_1[0][0] + N[1] * edge_1[0][1] + N[2] * edge_1[0][2];
        param = (D - N[0] * s_point[0] - N[1] * s_point[1] -
            N[2] * s_point[2]) / (N[0] * trace_ray[0] + N[1] * trace_ray[1] + N[2] * trace_ray[2]);
        x = s_point[0] + trace_ray[0] * param, y = s_point[1] + trace_ray[1] * param, z = s_point[2] + trace_ray[2] * param;
        point = { x,y,z };
        if (internal_point(point, edge_1) == true)
        {
            intersections.push_back(point);
            Ns.push_back(N);
        }
    }
    // edge_2:
    v_1 = edge_2[1] - edge_2[0];
    v_2 = edge_2[2] - edge_2[0];
    N = vectmul(v_1, v_2);
    if (scalmul(N, trace_ray) != 0)
    {
        D = N[0] * edge_2[0][0] + N[1] * edge_2[0][1] + N[2] * edge_2[0][2];
        param = (D - N[0] * s_point[0] - N[1] * s_point[1] -
            N[2] * s_point[2]) / (N[0] * trace_ray[0] + N[1] * trace_ray[1] + N[2] * trace_ray[2]);
        x = s_point[0] + trace_ray[0] * param, y = s_point[1] + trace_ray[1] * param, z = s_point[2] + trace_ray[2] * param;
        point = { x,y,z };
        if (internal_point(point, edge_2) == true)
        {
            intersections.push_back(point);
            Ns.push_back(N);
        }
    }
    // edge_3:
    v_1 = edge_3[1] - edge_3[0];
    v_2 = edge_3[2] - edge_3[0];
    N = vectmul(v_1, v_2);
    if (scalmul(N, trace_ray) != 0)
    {
        D = N[0] * edge_3[0][0] + N[1] * edge_3[0][1] + N[2] * edge_3[0][2];
        param = (D - N[0] * s_point[0] - N[1] * s_point[1] -
            N[2] * s_point[2]) / (N[0] * trace_ray[0] + N[1] * trace_ray[1] + N[2] * trace_ray[2]);
        x = s_point[0] + trace_ray[0] * param, y = s_point[1] + trace_ray[1] * param, z = s_point[2] + trace_ray[2] * param;
        point = { x,y,z };
        if (internal_point(point, edge_3) == true)
        {
            intersections.push_back(point);
            Ns.push_back(N);
        }
    }
    // edge_4:
    v_1 = edge_4[1] - edge_4[0];
    v_2 = edge_4[2] - edge_4[0];
    N = vectmul(v_1, v_2);
    if (scalmul(N, trace_ray) != 0)
    {
        D = N[0] * edge_4[0][0] + N[1] * edge_4[0][1] + N[2] * edge_4[0][2];
        param = (D - N[0] * s_point[0] - N[1] * s_point[1] -
            N[2] * s_point[2]) / (N[0] * trace_ray[0] + N[1] * trace_ray[1] + N[2] * trace_ray[2]);
        x = s_point[0] + trace_ray[0] * param, y = s_point[1] + trace_ray[1] * param, z = s_point[2] + trace_ray[2] * param;
        point = { x,y,z };
        if (internal_point(point, edge_4) == true)
        {
            intersections.push_back(point);
            Ns.push_back(N);
        }
    }
    if (intersections.size() != 0 && intersections.size() != 2)
    {
        return false;
    }
    if (intersections.size() == 0)
    {
        return false;
    }
    vector<double> screen_point = s_point + trace_ray;
    vector<double> ans, Nans;
    if (intersections.size() == 2)
    {
        double distance_1 = dist_quad(screen_point, intersections[0]), distance_2 = dist_quad(screen_point, intersections[1]);
        if (distance_1 <= distance_2)
        {
            ans = intersections[0];
            Nans = Ns[0];
        }
        else
        {
            ans = intersections[1];
            Nans = Ns[1];
        }
    }
    vector<double> check_n = ans - optimize_center;
    if (scalmul(check_n, Nans) < 0)
    {
        Nans[0] = -Nans[0];
        Nans[1] = -Nans[1];
        Nans[2] = -Nans[2];
    }
    res_v[0] = ans[0]; res_v[1] = ans[1]; res_v[2] = ans[2];
    res_v[3] = R; res_v[4] = G; res_v[5] = B; res_v[6] = Nans[0];
    res_v[7] = Nans[1]; res_v[8] = Nans[2]; res_v[9] = surface;
    res_v[10] = 3;
    return true;
}
