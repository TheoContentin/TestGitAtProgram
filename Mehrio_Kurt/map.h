#pragma once
#include <Imagine/Images.h>

using namespace Imagine;

class map{
private:
    Image<Color> background;
    Image<Color> texture;
    Image<Color> physics;
    float size;
    DoublePoint3 center;
    Mesh Plane;
    bool active;
    Mesh* walls;
    FloatVector3 axe1, axe2, axe3;

    void initialize();
    void makeAxes();
    void generateWalls();


public:
    map(char const * background_path,char const * texture_path,char const *physics);
    DoublePoint3 start_position;
    FloatVector3 start_direction;
    void draw();
};
