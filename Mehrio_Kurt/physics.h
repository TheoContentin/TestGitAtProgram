// Les fonctions 2D pour faire marcher le jeux en 2D, les objets utilisés et leurs hitboxes sont générées en même temps que la map.

#pragma once
#include <Imagine/Images.h>
#include "map.h"
#include "kart.h"
#include <cmath>

void run_physics(Kart kart,map carte);
