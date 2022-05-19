#include "physics.h"

#include "Imagine/LinAlg.h"

using namespace Imagine;

bool collided(FloatPoint3 corner, FVector<double,6> seg){

    DoublePoint3 seg0(seg[0],seg[1],seg[2]);
    DoublePoint3 seg1(seg[3],seg[4],seg[5]);

    //On regarde si un point est dans le carré à droite du segemnt orienté donné
    DoublePoint3 v = seg1-seg0;
    float len = sqrt(pow(v.x(),2)+ pow(v.y(),2));

    // On projette alors sur le vecteur directeur du segment.

    DoublePoint3 vect = corner - seg0;
    DoublePoint3 normalvector = DoublePoint3((seg1-seg0).y(),-(seg1-seg0).x(),0);
    float scal =  (vect.x()*v.x() +vect.y()*v.y())/len;
    if (scal/len<1 && scal/len>0){
        float nscal = (vect.x()*normalvector.x() +vect.y()*normalvector.y())/len;
        if(nscal/len <1 && nscal/len>0){
            return true;
        }
    }
    return false;
}

void run_physics(Kart &kart,map carte){
    //Traitement des collisions
    for(int j=0; j< carte.compute_walls.size();j++){
        //std::cout<<"Mur testé: "<<j<<std::endl;
        for(int i=0;i<4;i++){
            if(collided(kart.Hitbox[i],carte.compute_walls[j])){
             //Traiter les collisions
                }
            }
        }

    std::cout<<"Getting Keys"<<std::endl;
    kart.updateKeys();
    kart.depl();
    std::cout<<"Moving Camera"<<std::endl;
    kart.MoveCamera();
    std::cout<<kart.pos<<std::endl;
}


