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
                while(angle <-M_PI){
                    angle += 2*M_PI;
                }
                while(angle >+M_PI){
                    angle += -2*M_PI;
                }
                kart.vit[1] =  kart.vit[1] + kart.moteur*angle;
            //std::cout<<"Collided with wall "<<j<<std::endl;
        }
    }
    kart.maxvit = carte.get_vit(kart.pos);
    //std::cout<<"Getting Keys"<<std::endl;
    kart.depl(carte.start_position);
    kart.MoveCamera();
    //std::cout<<kart.pos<<std::endl;
}

void updateKeys(Kart &kart1){
    Event ev;
    do{
    getEvent(0,ev);
    //std::cout<<"Got event: "<<ev.type<<ev.key<<std::endl;
    if(ev.type==EVT_KEY_ON){
        //std::cout<<"On detecte une touche allumé"<<std::endl;
        if(ev.key == 'z'){
            kart1.moteur=1;
        }
        if(ev.key == 's'){
            kart1.moteur=-1;
        }
        if(ev.key == 'q'){
            kart1.dir = -1;
        }
        if(ev.key == 'd'){
            kart1.dir = 1;
        }
    }

    if(ev.type==EVT_KEY_OFF){
        //std::cout<<"On detecte une touche off"<<std::endl;
        if((ev.key == 'z')&&(kart1.moteur==1)){
            kart1.moteur=0;
        }
        if((ev.key == 's')&&(kart1.moteur==-1)){
            kart1.moteur=0;
        }
        if((ev.key == 'q')&&(kart1.dir==-1)){
            kart1.dir = 0;
        }
        if((ev.key == 'd')&&(kart1.dir==1)){
            kart1.dir = 0;
        }
    }

    }while(ev.type!=EVT_NONE);
}

void updateKeys(Kart &kart1,Kart &kart2){
    Event ev;
    do{
    getEvent(0,ev);
    //std::cout<<"Got event: "<<ev.type<<ev.key<<std::endl;
    if(ev.type==EVT_KEY_ON){
        //std::cout<<"On detecte une touche allumé"<<std::endl;
        if(ev.key == 'z'){
            kart1.moteur=1;
        }
        if(ev.key == 's'){
            kart1.moteur=-1;
        }
        if(ev.key == 'q'){
            kart1.dir = -1;
        }
        if(ev.key == 'd'){
            kart1.dir = 1;
        }
        //Joueur 2
        if(ev.key == 'i'){
            kart2.moteur=1;
        }
        if(ev.key == 'k'){
            kart2.moteur=-1;
        }
        if(ev.key == 'j'){
            kart2.dir = -1;
        }
        if(ev.key == 'l'){
            kart2.dir = 1;
        }
    }

    if(ev.type==EVT_KEY_OFF){
        //std::cout<<"On detecte une touche off"<<std::endl;
        if((ev.key == 'z')&&(kart1.moteur==1)){
            kart1.moteur=0;
        }
        if((ev.key == 's')&&(kart1.moteur==-1)){
            kart1.moteur=0;
        }
        if((ev.key == 'q')&&(kart1.dir==-1)){
            kart1.dir = 0;
        }
        if((ev.key == 'd')&&(kart1.dir==1)){
            kart1.dir = 0;
        }
        //Joueur 2
        if((ev.key == 'i')&&(kart2.moteur==1)){
            kart2.moteur=0;
        }
        if((ev.key == 'k')&&(kart2.moteur==-1)){
            kart2.moteur=0;
        }
        if((ev.key == 'j')&&(kart2.dir==-1)){
            kart2.dir = 0;
        }
        if((ev.key == 'l')&&(kart2.dir==1)){
            kart2.dir = 0;
        }
    }

    }while(ev.type!=EVT_NONE);
}

void compute_collisions(Kart &kart1,Kart &kart2){  // Set collision between the two karts : We don't handle long collisions

    bool collision=false;

    DoublePoint3 v1 = (kart1.Hitbox[1]-kart1.Hitbox[0]);
    DoublePoint3 v2 = (kart1.Hitbox[3]-kart1.Hitbox[0]);

    for(int i =0;i<4;i++){
        DoublePoint3 v3 = kart2.Hitbox[i]-kart1.Hitbox[0];
        double scal1 = (v1.x()*v3.x() + v1.y()*v3.y())/(pow(v1.x(),2)+pow(v1.y(),2));
        double scal2 = (v2.x()*v3.x() + v2.y()*v3.y())/(pow(v2.x(),2)+pow(v2.y(),2));

        if((scal1>0)&&(scal1<1)&&(scal2>0)&&(scal2<1)){
            collision = true;
        }
    }

    v1 = (kart2.Hitbox[1]-kart2.Hitbox[0]);
    v2 = (kart2.Hitbox[3]-kart2.Hitbox[0]);

    for(int i =0;i<4;i++){
        DoublePoint3 v3 = kart1.Hitbox[i]-kart2.Hitbox[0];
        double scal1 = (v1.x()*v3.x() + v1.y()*v3.y())/(pow(v1.x(),2)+pow(v1.y(),2));
        double scal2 = (v2.x()*v3.x() + v2.y()*v3.y())/(pow(v2.x(),2)+pow(v2.y(),2));

        if((scal1>0)&&(scal1<1)&&(scal2>0)&&(scal2<1)){
            collision = true;
        }
    }

    if(collision&&!(kart1.incollision)){

        kart1.incollision=true;
//        Window W = openWindow(1000,1000);
//        setActiveWindow(W);
//        drawCircle(kart1.Hitbox[0].x()*10,kart1.Hitbox[0].y()*10,3,BLUE);
//        drawCircle(kart1.Hitbox[1].x()*10,kart1.Hitbox[1].y()*10,3,BLUE);
//        drawCircle(kart1.Hitbox[2].x()*10,kart1.Hitbox[2].y()*10,3,BLUE);
//        drawCircle(kart1.Hitbox[3].x()*10,kart1.Hitbox[3].y()*10,3,BLUE);
//        drawCircle(kart1.pos.x()*10,kart1.pos.y()*10,3,BLUE);

//        drawCircle(kart2.Hitbox[0].x()*10,kart2.Hitbox[0].y()*10,3,RED);
//        drawCircle(kart2.Hitbox[1].x()*10,kart2.Hitbox[1].y()*10,3,RED);
//        drawCircle(kart2.Hitbox[2].x()*10,kart2.Hitbox[2].y()*10,3,RED);
//        drawCircle(kart2.Hitbox[3].x()*10,kart2.Hitbox[3].y()*10,3,RED);
//        drawCircle(kart2.pos.x()*10,kart2.pos.y()*10,3,RED);
//        click();
//        closeWindow(W);

        //std::cout<<"Collision !!"<<std::endl;

        float angle = kart2.vit[1] - kart1.vit[1];
        while(angle <-M_PI){
            angle += 2*M_PI;
        }
        while(angle >=M_PI){
            angle += -2*M_PI;
        }

        double swapvar = kart1.vit[0];
        kart1.vit[0] = kart2.vit[0];
        kart2.vit[0] = swapvar;

        kart1.vit[1]+= 0.5*angle;
        kart2.vit[1]-= 0.5*angle;

    }
    if((!collision)&&kart1.incollision){
        kart1.incollision = false;
    }
}
