#pragma once
#include <Imagine/Graphics.h>
#include "map.h"
#include "mesh_3D.h"
#include <cmath>

using namespace Imagine;

class Kart{
public:
     float maxvit;
     FVector<float, 3> pos;
     FVector<float, 2> vit; //vitesse en polaire
     FVector<float, 2> targ_vit; //Vitesse voulue en polaire
     FVector<float, 2> orient; //Orientation du kart en polaire
     float prevangle;
     int dir; //-1 si il tourne à gauche, 1 à droite, 0 tout droit
     int moteur; //1 si en marche, 0 sinon, -1 marche arriere

     bool incollision;

     Kart(map map);
     Kart(map map,int number);
     Mesh bunny;
     FVector<FVector<float,3>,4> Hitbox;
     void showKart();
     void depl();
     void updateKeys();
     void MoveCamera();
     void VitTurn();
     void accel();
};
