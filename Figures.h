#ifndef FIGURE
#define FIGURE

#include <vector>
#include <string>
#include "auxiliary_funcs.h"
#include "exceptions.h"
using namespace std;

class figure
{
protected:
    uint8_t R, G, B;
    uint8_t surface; // 0 = diffuse, 1 = glossy
public:
    virtual bool traceback(const vector<double>& s_point,
        const vector<double>& trace_ray,
        vector<double>& res_v,
        int trace_mode) = 0;
    // res_v: [x, y, z, R, G, B, Nx, Ny, Nz, Stype, ObjType (sphere = 1, box = 2, tetra= 3)]
    figure();
    virtual ~figure();
};

class sphere : public figure
{
private:
    double x, y, z, Rad;
public:
    sphere(double x, double y, double z, double Rad, int R, int G, int B, int surface);
    virtual bool traceback(const vector<double>& s_point,
        const vector<double>& trace_ray,
        vector<double>& res_v,
        int trace_mode) override;
    ~sphere();
};

class box : public figure
{
private:
    vector<double> v1, v2, v3, v4, v5, v6, v7, v8;
    vector<vector<double>> edge_1, edge_2, edge_3, edge_4, edge_5, edge_6;

    /* edge_1 = 1, 2, 4, 3
    edge_2 = 1, 5, 7, 3
    edge_3 = 1, 5, 6, 2
    edge_4 = 3, 7, 8, 4
    edge_5 = 2, 6, 8, 4
    edge_6 = 5, 6, 8, 7 */

    double half_diag_quad;

    bool internal_point(vector<double> point, int edge_number) const;
public:
    box(double x1, double y1, double z1,
        double x8, double y8, double z8,
        int R, int G, int B, int surface);
    virtual bool traceback(const vector<double>& s_point,
        const vector<double>& trace_ray,
        vector<double>& res_v,
        int trace_mode) override;
    ~box();
};

class tetra : public figure
{
private:
    vector<double> v1, v2, v3, v4;
    vector<vector<double>> edge_1, edge_2, edge_3, edge_4;
    vector<double> optimize_center; // Circumscribed sphere center
    double circumscribed_RAD;

    bool internal_point(vector<double> point, vector<vector<double>> edge) const;
public:
    tetra(double x1, double y1, double z1,
        double x2, double y2, double z2,
        double x3, double y3, double z3,
        double x4, double y4, double z4,
        int R, int G, int B, int surface);
    virtual bool traceback(const vector<double>& s_point,
        const vector<double>& trace_ray,
        vector<double>& res_v,
        int trace_mode) override;
    ~tetra();
};

#endif // FIGURE
