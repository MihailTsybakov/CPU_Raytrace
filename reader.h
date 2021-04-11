#ifndef READER
#define READER

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "exceptions.h"
#include "auxiliary_funcs.h"
#include "Figures.h"

/* ==== Instructions ====:

camera x y z
normal_ x y z
upvector x y z
light x y z
...
light x y z
screen_dist d
screen_height h
screen_width w
view_depth vd

  ==== Objects ====:
sphere R G B X Y Z RAD SURFACE
box R G B X1 Y1 Z1 X8 Y8 Z8 SURFACE
tetra R G B X1 ... Z4 SURFACE(16)

*/


using namespace std;
class reader
{
private:
    string scene_file, obj_file;
public:
    reader(string scene_file, string obj_file);

    void read_scene(vector<double>& camera,
        vector<double>& normal,
        vector<double>& light_source,
        vector<double>& upvector,
        double& screen_distance,
        int& screen_height,
        int& screen_width,
        double& view_depth) const;

    void read_objects(vector<figure*>& figures) const;
};
#endif // READER
