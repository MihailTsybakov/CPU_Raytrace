#ifndef FUNCS
#define FUNCS

#include <vector>
#include <string>
#include <cmath>
#include <thread>
#include <iostream>
#include <atomic>
using namespace std;

vector<string> split_by_space(string src);

vector<double> vectmul(vector<double> v1, vector<double> v2);

double scalmul(vector<double> v1, vector<double> v2);

double dist_quad(vector<double> point_1, vector<double> point_2);

double volume_vect(vector<double> v1, vector<double> v2, vector<double> v3);

vector<double> operator*(vector<double> v, double multiplier);

vector<double> operator+(vector<double> v1, vector<double> v2);

vector<double> operator-(vector<double> v1, vector<double> v2);

double vectmul_area(vector<double> v1, vector<double> v2);

int closest_point(vector<vector<double>> points, vector<double> point);

vector<double> to_length(vector<double> src, double new_len);

void check_system_cores();

class spinlock
{
private:
    atomic<bool> lock_f{ false };
public:
    spinlock();
    void lock() noexcept;
    void unlock() noexcept;
};

#endif // FUNCS
