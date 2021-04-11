#ifndef RAYTRACE
#define RAYTRACE

#define _CRT_SECURE_NO_WARNINGS

#include "Figures.h"
//#include <mutex>
#include <thread>
#include "canvas.h"
#include "reader.h"
#include <ctime>
#include <sstream>
#include <cstdlib>
#include "auxiliary_funcs.h"

class raytracer
{
private:
    string src_scene, src_obj, saveto;
    int thread_number;
    bool calc_shadow(vector<double> point, vector<double> light_src, vector<figure*> shapes) const;
    double calc_light(vector<double> surface_normal, vector<double> light_ray, int stype, int otype, bool shadow) const;
public:
    raytracer(string src_scene, string src_obj, string saveto, int thread_number);
    void raytrace() const;
    void stripe_trace(int h_start, int h_end,
        int width, Canvas& frame,
        vector<double> lu_corner,
        vector<double> camera,
        vector<double> upvector,
        vector<double> normal,
        vector<double> ortsup,
        vector<double> light_source,
        vector<figure*> shapes,
        double view_depth) const;
};

class renderer
{
private:
    string scene_template, obj_template, save_template;
    int thread_number;
    string gettime() const;
public:
    renderer(string scene_template, string obj_template, string save_template, int thread_number);
    void render(int frame_number, bool logs) const;
    void render_scope(int scope_start, int scope_end, bool logs, spinlock& slock) const;
    void join_to_video(string frame_template, string video_name, int framerate, int quality) const;
};

#endif // RAYTRACE
