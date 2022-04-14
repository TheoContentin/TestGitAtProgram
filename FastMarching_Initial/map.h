#include <Imagine/Images.h>

using namespace Imagine;

class map{
private:
    Image<Color> background;
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
    map(char* background_path,char*physics)

public:
    void draw();
};
