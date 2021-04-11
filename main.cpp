#include "raytrace.h"

int main(int argc, char* argv[])
{
    renderer R("C:\\Users\\mihai\\Desktop\\progy\\C & C++\\Traceback\\Series_1\\tetra_1_instructions_",
        "C:\\Users\\mihai\\Desktop\\progy\\C & C++\\Traceback\\Series_1\\tetra_1_objects_",
        "C:\\Users\\mihai\\Desktop\\progy\\C & C++\\Traceback\\Frames_3\\trace3_test_", 4);
    //R.render(12, true);
    raytracer rtracer("instructions.txt", "objects.txt", "trace_vs.bmp", 4);
    rtracer.raytrace();
    //check_system_cores();
    
    /*
    R.join_to_video("frame_%d.bmp",
        "video.avi", 
        24,      // framerate
        1,       // quality 1 = best, 30 = worst 
        "ffmpeg" /*ffmpeg path*/);
    */
    
    return 0;
}
