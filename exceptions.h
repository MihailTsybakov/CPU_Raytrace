#ifndef EXCEPT
#define EXCEPT

#include <iostream>
#include <string>
using namespace std;

class reader_error : public exception
{
private:
    string error_msg;
public:
    reader_error(string error_msg)
    {
        this->error_msg = error_msg;
    }
    const char* what() const noexcept override
    {
        return error_msg.c_str();
    }
};

class raytrace_exception : public exception
{
private:
    string error_msg;
public:
    raytrace_exception(string error_msg)
    {
        this->error_msg = error_msg;
    }
    const char* what() const noexcept override
    {
        return error_msg.c_str();
    }
};

class render_exception : public exception
{
private:
    string error_msg;
public:
    render_exception(string error_msg)
    {
        this->error_msg = error_msg;
    }
    const char* what() const noexcept override
    {
        return error_msg.c_str();
    }
};

#endif // EXCEPT
