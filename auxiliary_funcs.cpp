#include "auxiliary_funcs.h"

vector<string> split_by_space(string src)
{
    vector<string> res_v;
    string curr_piece = "";
    for (size_t i = 0; i < src.size(); ++i)
    {
        if (src[i] == ' ')
        {
            res_v.push_back(curr_piece);
            curr_piece = "";
        }
        else
        {
            curr_piece += src[i];
        }
    }
    res_v.push_back(curr_piece);
    return res_v;
}

vector<double> vectmul(vector<double> v1, vector<double> v2)
{
    vector<double> res_v = { 0,0,0 };
    res_v[0] = v1[1] * v2[2] - v1[2] * v2[1];
    res_v[1] = v1[2] * v2[0] - v1[0] * v2[2];
    res_v[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return res_v;
}

double scalmul(vector<double> v1, vector<double> v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

double dist_quad(vector<double> point_1, vector<double> point_2)
{
    return pow((point_1[0] - point_2[0]), 2) + pow((point_1[1] - point_2[1]), 2) + pow((point_1[2] - point_2[2]), 2);
}

double volume_vect(vector<double> v1, vector<double> v2, vector<double> v3)
{
    return (v1[0] * (v2[1] * v3[2] - v2[2] * v3[1]) + v1[1] * (v2[2] * v3[0] - v2[0] * v3[2]) + v1[2] * (v2[0] * v3[1] - v2[1] * v3[0]));
}

vector<double> operator*(vector<double> v, double multiplier)
{
    vector<double> res_v;
    for (auto coord : v)
    {
        res_v.push_back(coord * multiplier);
    }
    return res_v;
}

vector<double> operator+(vector<double> v1, vector<double> v2)
{
    vector<double> res_v;
    for (size_t i = 0; i < v1.size(); ++i)
    {
        res_v.push_back(v1[i] + v2[i]);
    }
    return res_v;
}

vector<double> operator-(vector<double> v1, vector<double> v2)
{
    vector<double> res_v;
    for (size_t i = 0; i < v1.size(); ++i)
    {
        res_v.push_back(v1[i] - v2[i]);
    }
    return res_v;
}

double vectmul_area(vector<double> v1, vector<double> v2)
{
    return (v1[1] * v2[2] - v1[2] * v2[1]) + (v1[2] * v2[0] - v1[0] * v2[2]) + (v1[0] * v2[1] - v1[1] * v2[0]);
}

int closest_point(vector<vector<double>> points, vector<double> point)
{
    double min_d = 10e10;
    int closest_ind;
    for (size_t i = 0; i < points.size(); ++i)
    {
        vector<double> p_ = { points[i][0], points[i][1], points[i][2] };
        double curr_d = dist_quad(p_, point);
        if (curr_d < min_d) min_d = curr_d, closest_ind = i;
    }
    return closest_ind;
}

vector<double> to_length(vector<double> src, double new_len)
{
    vector<double> res_v;
    double coef = pow(new_len * new_len / (scalmul(src, src)), 0.5);
    for (auto coord : src)
    {
        res_v.push_back(coord * coef);
    }
    return res_v;
}

void check_system_cores()
{
    cout << "Supported thread number: " << std::thread::hardware_concurrency() << endl;
}

spinlock::spinlock() {}

void spinlock::lock() noexcept
{
    while (lock_f.load(std::memory_order_relaxed)) {}
    lock_f.store(true, std::memory_order_relaxed);
}

void spinlock::unlock() noexcept
{
    lock_f.store(false, std::memory_order_relaxed);
}