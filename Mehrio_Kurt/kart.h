#pragma once
#include <Imagine/Images.h>
#include "map.h"
#include <cmath>

using namespace Imagine;

class kart{
     FVector<float, 3> pos;
     FVector<float, 2> vit;
     int dir; //-1 si il tourne à gauche, 1 à droite, 0 tout droit
     int moteur; //1 si en marche, 0 sinon, -1 marche arriere
     kart(map map);
     FloatPoint3* fP;
     void showCube();
     void depl();
     void updateKeys();
};
