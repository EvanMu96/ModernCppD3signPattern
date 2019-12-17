/*
the decorator pattern allow us to enchance
existing types without either modifying the
original types or causing an explosion of 
the number of derived types
*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* abstract class shape*/
struct Shape
{
    virtual string _str() = 0;
};

struct Circle : Shape
{
    int radius;
    Circle(const int radius) : radius{radius} {}
    Circle() : radius{1} {};
    void resize(int factor) {radius *= factor;}

    string _str() override
    {/*return (string("A circle of radius ") + radius + string("\n"));*/
        ostringstream s;
        s << "A circle of radius " << radius << "\n";
        return s.str();
    }
};

/* template decorator */
template <typename T> struct ColoredShape: T
{
    static_assert(is_base_of<Shape, T>::value,
                 "Type t must be a Shape");
    string color;
    ColoredShape(string color) : color{color} {}
    string _str() override
    {
        ostringstream s;
        s << "A circle of radius " << color << "\n";
        return T::_str() + s.str();
    }
};

int main()
{
    Circle c(10);
    ColoredShape<Circle> d = {"blue"};
    d.radius = 10;
    cout << d._str();
    return 0;
}


