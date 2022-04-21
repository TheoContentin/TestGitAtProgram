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
    std::vector<Mesh> walls;
    FloatVector3 axe1, axe2, axe3;

    void initialize();
    void makeAxes();
    void generateWalls();
    void set_start();


public:
    map(char const * background_path,char const * texture_path,char const *physics);
    DoublePoint3 start_position;
    FloatVector3 start_direction;
    void draw();
};


//Classe pour construire les murs du terrain
struct PointClasse{
public:
    PointClasse(int val0, DoublePoint3 dp0): val(val0), p(dp0){}
    int val;
    DoublePoint3 p;

    bool operator>(PointClasse p2){
        return val > p2.val;
    }
};



class FilePriorite {
    std::vector<PointClasse> v;
public:
    FilePriorite(){
        v = std::vector<PointClasse>();
        v.push_back(PointClasse(-1,DoublePoint3(0,0,0)));
    }

    bool empty();

    void push(PointClasse d);

    PointDist pop();

};
