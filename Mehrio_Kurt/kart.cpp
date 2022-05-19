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

    Mymesh.setVertices(depl);
    delete[] depl;
}

Kart::Kart(map map){
    vit = {map.start_direction[0],map.start_direction[1]};
    pos = map.start_position;
    moteur = 0;
    dir = 0;
    std::string fileName = srcPath("bunny.obj");
    readMesh(bunny, fileName);

    DoublePoint3 axis(1,0,0);
    rotate_mesh3d(bunny,axis,-M_PI/2);

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
    double angle = dir*0.5;
    vit.x() = vit.x()*cos(angle)-1*sin(angle)*vit.y();
    vit.y() = vit.x()*sin(angle) + vit.y()*cos(angle);

    FloatPoint3* depl=new FloatPoint3[bunny.vertices().size()];
    for (int i=0; i<bunny.vertices().size(); i++){
        depl[i] = bunny.vertices()[i];
        depl[i].x() += vit.x()*moteur;
        depl[i].y() += vit.y()*moteur;
    }
    for(int i =0;i<4;i++){
        Hitbox[i].x() += vit.x()*moteur;
        Hitbox[i].y() += vit.y()*moteur;
    }
    std::cout<<"Moving position: "<< pos ;
    pos.x() += vit.x()*moteur;
    pos.y() += vit.y()*moteur;
    std::cout<<" "<<pos<<std::endl;
    bunny.setVertices(depl);
    bunny.setColor(Color(0,100,254));
    delete[] depl;

}

void Kart::updateKeys(){
    Event ev;
    do{
    getEvent(0,ev);
    std::cout<<"Got event: "<<ev.type<<ev.key<<std::endl;
    if(ev.type==EVT_KEY_ON){
        std::cout<<"On detecte une touche allumé"<<std::endl;
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
        std::cout<<"On detecte une touche eteinte"<<std::endl;
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
    std::cout<<pos<<std::endl;
    DoubleVector3 dir(vit.normalize().x(),vit.normalize().y(),-0.3);
    setCamera(pos,-20*dir,DoubleVector3(0,0,1));
}



