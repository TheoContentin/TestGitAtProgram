#include "physics.h"

#include "Imagine/LinAlg.h"

using namespace Imagine;

bool collided(FVector<FVector<double,3>,4> Hitbox, FVector<DoublePoint3,2> seg){

    FVector<double,3> tangent = (seg[1]-seg[0]).normalize();
    FVector<double,3> normal = {tangent.y(),-tangent.x(),0};


    //std::cout<<"Computing tangents for points " <<Hitbox[0]<<Hitbox[1]<<Hitbox[2]<<Hitbox[3]<<seg<<std::endl;


    int sign = 0;
    bool crossing = false;
    for(int i = 0;i<4;i++){
        DoublePoint3 v =  Hitbox[i]-seg[0];
        double dot_product = v.x()*normal.x() + v.y()*normal.y();
        if(dot_product*sign>=0){
            sign = (dot_product > 0) - (dot_product < 0);
        }
        else{
            crossing =true;
        }
    }

    double seg_len = sqrt(pow(seg[1].x()-seg[0].x(),2)+pow(seg[1].y()-seg[0].y(),2));

    if (crossing){
        int count = 0;
        for(int i = 0;i<4;i++){
            DoublePoint3 v =  Hitbox[i]-seg[0];
            double dot_product = v.x()*tangent.x() + v.y()*tangent.y();
            if((dot_product<=seg_len)&&(dot_product>=0)){
                count +=1;
            }
        }
        if(count>1){
            return true;
        }

    }
    return false;
}

void run_physics(Kart &kart,map carte){
    //Traitement des collisions
    for(int j=0; j< carte.compute_walls.size();j++){
        //std::cout<<"Mur testé: "<<j<<std::endl;
        if(collided(kart.Hitbox,carte.compute_walls[j])){
                double angle;
                angle = 2*(atan2((carte.compute_walls[j][1]-carte.compute_walls[j][0]).y(),(carte.compute_walls[j][1]-carte.compute_walls[j][0]).x())+(2*M_PI) - kart.vit[1]);
                while(angle <M_PI){
                    angle += 2*M_PI;
                }
                while(angle >M_PI){
                    angle += -2*M_PI;
                }
                kart.vit[1] =  kart.vit[1] + angle;
            std::cout<<"Collided with wall "<<j<<std::endl;
        }
    }

    //std::cout<<"Getting Keys"<<std::endl;
    kart.updateKeys();
    kart.depl();
    //std::cout<<"Moving Camera"<<std::endl;
    kart.MoveCamera();
    std::cout<<kart.pos<<std::endl;
}


