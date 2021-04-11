#include "reader.h"

reader::reader(string scene_file, string obj_file)
{
    this->scene_file = scene_file;
    this->obj_file = obj_file;
}

void reader::read_scene(vector<double>& camera,
    vector<double>& normal,
    vector<double>& light_source,
    vector<double>& upvector,
    double& screen_distance,
    int& screen_height,
    int& screen_width,
    double& view_depth) const
{
    try
    {
        ifstream scene_stream(scene_file);
        if (!scene_stream.is_open())
        {
            throw reader_error("Error: cannot open scene instructions file: " + scene_file);
        }
        string row;
        while (getline(scene_stream, row))
        {
            vector<string> scene_row = split_by_space(row);
            string title = scene_row[0];
            switch (title.size())
            {
            case 6: //camera
                camera.push_back(stod(scene_row[1]));
                camera.push_back(stod(scene_row[2]));
                camera.push_back(stod(scene_row[3]));
                break;
            case 5: // light
            {
                light_source.push_back(stod(scene_row[1]));
                light_source.push_back(stod(scene_row[2]));
                light_source.push_back(stod(scene_row[3]));
                break;
            }
            case 7: // normal_
                normal.push_back(stod(scene_row[1]));
                normal.push_back(stod(scene_row[2]));
                normal.push_back(stod(scene_row[3]));
                break;
            case 8: // upvector
                upvector.push_back(stod(scene_row[1]));
                upvector.push_back(stod(scene_row[2]));
                upvector.push_back(stod(scene_row[3]));
                break;
            case 11: // screen_dist
                screen_distance = stod(scene_row[1]);
                break;
            case 12: // screen_width
                screen_width = stoi(scene_row[1]);
                break;
            case 10: // view_depth
                view_depth = stod(scene_row[1]);
                break;
            case 13: // screen_height
                screen_height = stoi(scene_row[1]);
                break;
            default:
                throw reader_error("Error: unknown instruction encountered.");
            }
        }
        scene_stream.close();
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

void reader::read_objects(vector<figure*>& figures) const
{
    try
    {
        ifstream obj_stream(obj_file);
        if (!obj_stream.is_open())
        {
            throw reader_error("Error: cannor open objects file: " + obj_file);
        }
        string obj_row;

        while (getline(obj_stream, obj_row))
        {
            vector<string> obj_v = split_by_space(obj_row);
            switch (obj_v[0].size())
            {
            case 6: // sphere
                figures.push_back(new sphere(stod(obj_v[4]), stod(obj_v[5]), stod(obj_v[6]),
                    stod(obj_v[7]), stoi(obj_v[1]), stoi(obj_v[2]),
                    stoi(obj_v[3]), stoi(obj_v[8])));
                break;
            case 3: // box
                figures.push_back(new box(stod(obj_v[4]), stod(obj_v[5]), stod(obj_v[6]),
                    stod(obj_v[7]), stod(obj_v[8]), stod(obj_v[9]),
                    stoi(obj_v[1]), stoi(obj_v[2]), stoi(obj_v[3]),
                    stoi(obj_v[10])));
                break;
            case 5: //tetra
                figures.push_back(new tetra(stod(obj_v[4]), stod(obj_v[5]), stod(obj_v[6]),
                    stod(obj_v[7]), stod(obj_v[8]), stod(obj_v[9]),
                    stod(obj_v[10]), stod(obj_v[11]), stod(obj_v[12]),
                    stod(obj_v[13]), stod(obj_v[14]), stod(obj_v[15]),
                    stoi(obj_v[1]), stoi(obj_v[2]), stoi(obj_v[3]),
                    stoi(obj_v[16])));
                break;
            default:
                throw reader_error("Error: unknown object type encountered.");
            }
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}