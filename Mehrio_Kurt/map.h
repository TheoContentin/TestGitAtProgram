#pragma once
#include <Imagine/Images.h>
#include "Imagine/LinAlg.h"


using namespace Imagine;

class map{
private:
    Image<Color> background;
    Image<Color> texture;
    Image<Color> physics;
    float size;

    DoublePoint3 center;
    Mesh Plane;
    Mesh Sky;
    Mesh Sol;
    bool active;
    std::vector<Mesh> walls; // La liste des objets Mesh à afficher.
    FloatVector3 axe1, axe2, axe3;

    float wallheight;

    void initialize();
    void makeAxes();
    void generateWalls();
    void set_start();


public:
    map(char const * background_path,char const * texture_path,char const *physics);
    DoublePoint3 start_position;
    FloatVector3 start_direction;
    float dt;
    std::vector<FVector<DoublePoint3,2>> compute_walls; // Liste des segments pour verifier les collisions. DoublePoint3[2] marche pas
    float get_vit(DoublePoint3 pos);
    float kart_size;
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

    PointClasse pop();

};
