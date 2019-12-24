#include <iostream>

using namespace std;

/*
* we assume that rendering can happen in vector and raster form
*/

/* renderer based class */
struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;
};


/* inherented from base class Renderer */
/* two different render methods*/
struct VectorRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        cout << "Rasterizing circle of radius" << radius << endl;
    }
};

struct RasterRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        cout << "Rasterizing circle of radius" << radius << endl;
    }
};

/* the base class Shape will keep a reference to the renderer
the shape will support self-rendering with the draw()
member function, and will support the resize() operation*/

struct Shape
{
virtual void draw() = 0;
virtual void resize(float factor) = 0;    
protected:
    Renderer& renderer;
    Shape(Renderer& renderer) : renderer{renderer} {}

};

struct Circle : Shape
{
    float x, y, radius;

    void draw() override
    {
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override
    {
        radius *= factor;
    }

    Circle(Renderer& renderer, float x, float y, float radius)
    : Shape{renderer}, x{x}, y{y}, radius{radius} {}
};

/* the Circle class is compatible with two different low level renderer */

void test()
{
    RasterRenderer rr;
    Circle raster_c{rr, 5,5,5};
    raster_c.draw();
    raster_c.resize(0.5);
    raster_c.draw();
}

int main()
{
    test();
    return 0;
}