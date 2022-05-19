#pragma once
#include <Imagine/Graphics.h>
#include "map.h"
#include "mesh_3D.h"
#include <cmath>

using namespace Imagine;

class Kart{
public:
     FVector<float, 3> pos;
     FVector<float, 2> vit;
     int dir; //-1 si il tourne à gauche, 1 à droite, 0 tout droit
     int moteur; //1 si en marche, 0 sinon, -1 marche arriere
     Kart(map map);
     Mesh bunny;
     FVector<double,3> Hitbox[4];
     void showKart();
     void depl();
     void updateKeys();
     void MoveCamera();
};
