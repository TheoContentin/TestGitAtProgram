#include "map.h"
using namespace Imagine;

map::map(std::string backgroud_path, char* physics_path){

    if(! load(background, srcPath( backgroud_path ))) {
        std::cout << "Echec de lecture d'image de fond" << std::endl;
    }
    if(! load(physics,srcPath(physics_path))){
        std::cout<<"Echec de de lecture de l'image physique"<<std::endl;
    }

    center = DoublePoint3(0,0,0);
    axe1 = FloatVector3(1,0,0);
    axe2 = FloatVector3(0,1,0);
    axe3 = FloatVector3(0,0,1);

    Plane = Mesh::Plane(center,axe1,axe2);
    generateWalls();

}
