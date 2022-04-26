#include "physics.h"

using namespace Imagine;

bool collided(FloatPoint3 corner, DoublePoint3 seg[2]){
    //On regarde si un point est dans le carré à droite du segemnt orienté donné
    DoublePoint3 v = seg[1]-seg[0];
    float len = sqrt(pow(v.x(),2)+ pow(v.y(),2));

    // On projette alors sur le vecteur directeur du segment.

    DoublePoint3 vect = corner - seg[0];
    DoublePoint3 normalvector = DoublePoint3((seg[1]-seg[0]).y(),-(seg[1]-seg[0]).x());
    float scal =  (vect.x()*v.x() +vect.y()*v.y())/len;
    if (scal/len<1 && scal/len>0){
        float nscal = (vect.x()*normalvector.x() +vect.y()*normalvector.y())/len;
        if(nscal/len <1 && nscal/len>0){
            return true;
        }
    }
    return false;
}

void run_physics(Kart kart,map carte){
    //Traitement des collisions
    for(int j; j< carte.compute_walls.size();j++){
        for(int i=0;i<4;i++){
            if(collided(kart.fP[i],carte.compute_walls[j])){
             //Traiter les collisions
            }
        }
    }
}
