#include "kart.h"

Kart::Kart(map map){
    vit = {map.start_direction[0],map.start_direction[1]};
    pos = map.start_position;
    moteur = 0;
    dir = 0;
    FloatPoint3 fB[8]={FloatPoint3(pos.x(),pos.y(),0),FloatPoint3(pos.x()+map.kart_size,pos.y(),0),FloatPoint3(pos.x()+map.kart_size,pos.y()+map.kart_size,0),FloatPoint3(pos.x(),pos.y()+map.kart_size,0),   // constructor (float)
                       FloatPoint3(pos.x(),pos.y(),map.kart_size),FloatPoint3(pos.x()+map.kart_size,pos.y(),map.kart_size),FloatPoint3(pos.x()+map.kart_size,pos.y()+map.kart_size,map.kart_size),FloatPoint3(pos.x(),pos.y()+map.kart_size,map.kart_size)
                      };
    for (int i=0;i<8;i++)
        fP[i] = fB[i];
}

void Kart::showCube(){
    Triangle fT[12]={Triangle(0,2,1),Triangle(2,0,3),Triangle(4,5,6),Triangle(6,7,4),   // A cube
                     Triangle(0,1,5),Triangle(5,4,0),Triangle(1,2,6),Triangle(6,5,1),
                     Triangle(2,3,7),Triangle(7,6,2),Triangle(3,0,4),Triangle(4,7,3)
                    };
    Mesh fM(fP,8,fT,12);
    showMesh(fM);
}

void Kart::depl(){
    double angle = dir*0.5;
    vit.x() = vit.x()*cos(angle)-1*sin(angle)*vit.y();
    vit.y() = vit.x()*sin(angle) + vit.y()*cos(angle);

    for (int i=0; i<8;i++){
        fP[i].x() += vit.x()*moteur;
        fP[i].y() += vit.y()*moteur;
    }
}

void Kart::updateKeys(){

}

