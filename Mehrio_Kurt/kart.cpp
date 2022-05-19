#include "kart.h"


Kart::Kart(map map){
    vit = {map.start_direction[0],map.start_direction[1]};
    pos = map.start_position;
    moteur = 0;
    dir = 0;
    std::string fileName = srcPath("bunny.obj");
    readMesh(bunny, fileName);
    FloatPoint3 dist = bunny.vertices()[0] - map.start_position;

    FloatPoint3* depl=new FloatPoint3[bunny.vertices().size()];
    for (int i=0; i<bunny.vertices().size(); i++){
        depl[i] = bunny.vertices()[i];
        depl[i] = depl[i] - dist;
    }
    bunny.setVertices(depl);
    delete[] depl;

    double xmax=0,xmin=0,ymax=0,ymin=0;
    for(int i=0;i<bunny.vertices().size();i++){
        DoublePoint3 p = bunny.vertices()[i];
        if (p.x()>xmax){
            xmax=p.x();
        }
        if (p.x()<xmin){
            xmin=p.x();
        }
        if (p.y()>ymax){
            ymax=p.y();
        }
        if (p.y()<ymin){
            ymin=p.y();
        }

    }
}


void Kart::showKart(){
    showMesh(bunny);
}

void Kart::depl(){
    double angle = dir*0.5;
    vit.x() = vit.x()*cos(angle)-1*sin(angle)*vit.y();
    vit.y() = vit.x()*sin(angle) + vit.y()*cos(angle);

    FloatPoint3* depl=new FloatPoint3[bunny.vertices().size()];
    for (int i=0; i<bunny.vertices().size(); i++){
        depl[i] = bunny.vertices()[i];
        depl[i].x() += vit.x()*moteur;
        depl[i].y() += vit.y()*moteur;
    }
    bunny.setVertices(depl);
    bunny.setColor(Color(0,100,254));
    showMesh(bunny,false); //false : pas de reset camera
    delete[] depl;

}

void Kart::updateKeys(){
    Event ev;
    do{
    getEvent(500,ev);
    if(ev.type==EVT_KEY_ON){
        if(ev.key == 'I'){
            moteur=1;
        }
        if(ev.key == 'K'){
            moteur=-1;
        }
        if(ev.key == 'J'){
            dir = -1;
        }
        if(ev.key == 'L'){
            dir = 1;
        }
    }

    if(ev.type==EVT_KEY_OFF){
        if((ev.key == 'I')&&(moteur==1)){
            moteur=0;
        }
        if((ev.key == 'K')&&(moteur==-1)){
            moteur=0;
        }
        if((ev.key == 'J')&&(dir==-1)){
            dir = 0;
        }
        if((ev.key == 'L')&&(dir==1)){
            dir = 0;
        }
    }

    }while(ev.type!=EVT_NONE);
}

