#include "kart.h"

void rotate_mesh3d(Mesh &Mymesh, DoublePoint3 Axis, double angle){
    DoublePoint3 axe = Axis.normalize();
    float c = cos(angle);
    float s = sin(angle);

    FloatPoint3* depl=new FloatPoint3[Mymesh.vertices().size()];
    for(int i = 0; i< Mymesh.vertices().size();i++){
        depl[i].x() = (axe.x()*axe.x()*(1-c) + c)*Mymesh.vertices()[i].x() + ((axe.x()*axe.y()*(1-c)) - s*axe.z())*Mymesh.vertices()[i].y() + (axe.x()*axe.z()*(1-c) + s*axe.y())*Mymesh.vertices()[i].z();
        depl[i].y() = (axe.x()*axe.y()*(1-c) + axe.z()*s)*Mymesh.vertices()[i].x() + ((axe.y()*axe.y()*(1-c)) + c)*Mymesh.vertices()[i].y() + (axe.y()*axe.z()*(1-c) - s*axe.x())*Mymesh.vertices()[i].z();
        depl[i].z() = (axe.x()*axe.z()*(1-c) - axe.y()*s)*Mymesh.vertices()[i].x() + ((axe.z()*axe.y()*(1-c)) - s*axe.x())*Mymesh.vertices()[i].y() + (axe.z()*axe.z()*(1-c) + c)*Mymesh.vertices()[i].z();
    }

    std::cout<<depl<<std::endl;

    Mymesh.setVertices(depl);
    delete[] depl;
}

void rotate_mesh2d(Mesh &Mymesh, FVector<float,3> pos,float angle){
    FloatPoint3* depl = new FloatPoint3[Mymesh.vertices().size()];
    for(int i=0; i<Mymesh.vertices().size(); i++){
        depl[i].x() = pos[0] + cos(angle)*(Mymesh.vertices()[i].x()-pos[0]) - sin(angle)*(Mymesh.vertices()[i].y()-pos[1]);
        depl[i].y() = pos[1] + sin(angle)*(Mymesh.vertices()[i].x()-pos[0]) + cos(angle)*(Mymesh.vertices()[i].y()-pos[1]);
        depl[i].z() = Mymesh.vertices()[i].z();
    }

    Mymesh.setVertices(depl);
    delete[] depl;
}

Kart::Kart(map map){
    vit = {0,float(atan2(map.start_direction[1],map.start_direction[0]))};
    maxvit = 1;
    pos = map.start_position;
    orient = {1/map.dt,float(atan2(map.start_direction[1],map.start_direction[0]))};
    prevangle = orient[1];
    targ_vit = {0,0};
    moteur = 0;
    dir = 0;
    std::string fileName = srcPath("bunny.obj");
    readMesh(bunny, fileName);

    DoublePoint3 axis(1,0,0);
    rotate_mesh3d(bunny,axis,-M_PI/2);

    bunny.setColor(Color(0,100,254));
    FloatPoint3 dist = bunny.vertices()[0] - map.start_position;

    FloatPoint3* depl=new FloatPoint3[bunny.vertices().size()];
    for (int i=0; i<bunny.vertices().size(); i++){
        depl[i] = bunny.vertices()[i];
        depl[i] = depl[i] - dist;
    }
    bunny.setVertices(depl);
    delete[] depl;

    double xmax=-1000,xmin=+1000,ymax=-1000,ymin=+1000;
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

        Hitbox[0] = FVector<double,3>(xmin,ymin,0);
        Hitbox[1] = FVector<double,3>(xmax,ymin,0);
        Hitbox[2] = FVector<double,3>(xmax,ymax,0);
        Hitbox[3] = FVector<double,3>(xmin,ymax,0);
    }
}

void Kart::showKart(){
    showMesh(bunny);
}

void Kart::depl(){

    if(moteur == 1){
        targ_vit[0] = maxvit*orient[0];
        targ_vit[1] = orient[1];
    }
    if(moteur ==-1){
        targ_vit[0] = -maxvit*orient[0];
        targ_vit[1] =  orient[1];
    }
    if(moteur == 0 ){
        targ_vit[0] = 0;
        targ_vit[1] = orient[1];
    }

    double angle = -dir*0.7; //L'angle est en radians ca fait 40 degres
    targ_vit[1] += angle;

    VitTurn();
    accel();

    FloatPoint3* depl=new FloatPoint3[bunny.vertices().size()];
    for (int i=0; i<bunny.vertices().size(); i++){
        depl[i] = bunny.vertices()[i];
        depl[i].x() += vit[0]*cos(vit[1]);
        depl[i].y() += vit[0]*sin(vit[1]);
    }
    for(int i =0;i<4;i++){
        Hitbox[i].x() += vit[0]*cos(vit[1]);
        Hitbox[i].y() += vit[0]*sin(vit[1]);
    }
    pos.x() += vit[0]*cos(vit[1]);
    pos.y() += vit[0]*sin(vit[1]);


    bunny.setVertices(depl);
    bunny.setColor(Color(0,100,254));
    delete[] depl;

    rotate_mesh2d(bunny,pos,orient[1]-prevangle);
    prevangle = orient[1];

}

void Kart::updateKeys(){
    Event ev;
    do{
    getEvent(0,ev);
    //std::cout<<"Got event: "<<ev.type<<ev.key<<std::endl;
    if(ev.type==EVT_KEY_ON){
        //std::cout<<"On detecte une touche allumé"<<std::endl;
        if(ev.key == 'i'){
            moteur=1;
        }
        if(ev.key == 'k'){
            moteur=-1;
        }
        if(ev.key == 'j'){
            dir = -1;
        }
        if(ev.key == 'l'){
            dir = 1;
        }
    }

    if(ev.type==EVT_KEY_OFF){
        //std::cout<<"On detecte une touche off"<<std::endl;
        if((ev.key == 'i')&&(moteur==1)){
            moteur=0;
        }
        if((ev.key == 'k')&&(moteur==-1)){
            moteur=0;
        }
        if((ev.key == 'j')&&(dir==-1)){
            dir = 0;
        }
        if((ev.key == 'l')&&(dir==1)){
            dir = 0;
        }
    }

    }while(ev.type!=EVT_NONE);
}

void Kart::MoveCamera(){
    //std::cout<<pos<<std::endl;
    DoubleVector3 cam(cos(orient[1]),sin(orient[1]),-0.3);
    setCamera(pos,-20*cam,DoubleVector3(0,0,1));
}


void Kart::VitTurn(){

    vit[1] += (targ_vit[1]-vit[1])/10;
    orient[1] += (vit[1]-orient[1])/11;
}
void Kart::accel(){

    vit[0] += 0.4*(targ_vit[0]-vit[0]);
}
