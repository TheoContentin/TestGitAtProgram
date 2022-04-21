#pragma once
#include <Imagine/Images.h>

using namespace Imagine;

class kart{
     FVector<float, 3> pos;
     FVector<float, 2> vit;
     int dir; //-1 si il tourne à gauche, 1 à droite, 0 tout droit
     kart();
};
