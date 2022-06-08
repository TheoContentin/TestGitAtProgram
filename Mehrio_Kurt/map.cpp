#include "map.h"
#include <queue>
#include <vector>

using namespace Imagine;

const Color myrainbow[4] = {YELLOW,GREEN,RED,BLUE};

map::map(char const *background_path,char const *texture_path, char const *physics_path){

    if(! load(background, stringSrcPath( background_path ))){
        std::cout << "Echec de lecture d'image de fond" << std::endl;
    }
    if(! load(texture, stringSrcPath( texture_path ))){
        std::cout << "Echec de lecture d'image de fond" << std::endl;
    }
    if(! load(physics,stringSrcPath(physics_path))){
        std::cout<<"Echec de de lecture de l'image physique"<<std::endl;
    }

    center = DoublePoint3(0,0,0);
    axe1 = FloatVector3(1,0,0);
    axe2 = FloatVector3(0,1,0);
    axe3 = FloatVector3(0,0,1);

    wallheight = 1;
    kart_size =1;
    dt = 3;

    // Generation de la texture du sol;
    int h=texture.size(0);
    int w=texture.size(1);
    DoublePoint3 *P=new DoublePoint3[(w+1)*(h+1)];
    for (int j=0;j<=w;j++)
        for (int i=0;i<=h;i++)
            P[i+(h+1)*j]=DoublePoint3(100*double(j)/w,100*double(i)/h,0);   // A flat surface to texture
    Quad *T=new Quad[(h)*(w)];
    for (int j=0;j<w;j++) {
        for (int i=0;i<h;i++) {
            T[(i+(h)*j)]=Quad(i+(h+1)*j,i+1+(h+1)*j,i+1+(h+1)*(j+1),i+(h+1)*(j+1));
            //T[2*(i+(h)*j)+1]=Triangle(i+1+(h+1)*j,i+1+(h+1)*(j+1),i+(h+1)*(j+1));
        }
    }
    std::cout<<"Triangle Ok"<<std::endl;

    std::cout<<"Quad Ok"<<std::endl;

    Plane = Mesh(P,(w+1)*(h+1),0,0,T,w*h,FACE_COLOR,FLAT_SHADING);
    std::cout<<"Mesh Ok"<<std::endl;

    Color *col=new Color[w*h];
    for (int j=0;j<w;j++) {
        for (int i=0;i<h;i++) {
            col[(i+(h*j))]=texture(i,j);
            //col[2*(i+h*j)+1]=texture(i,j);
        }
    }

    Plane.setColors(QUAD,col);

    std::cout<<"Colors Ok"<<std::endl;
    generateWalls();
    set_start();

    // Generation ciel
    DoublePoint3 *P_sky=new DoublePoint3[8];
    P_sky[0] = {500,500,10};
    P_sky[1] = {500,-500,10};
    P_sky[2] = {-500,-500,10};
    P_sky[3] = {-500,500,10};
    for (int i=0; i<4; i++)
        P_sky[4+i] = {P_sky[i].x(),P_sky[i].y(), P_sky[i].z()-50};

    Quad *Q_sky = new Quad[5];
    Q_sky[0] = Quad(0,1,2,3);
    Q_sky[1] = Quad(0,4,7,3);
    Q_sky[2] = Quad(0,4,5,1);
    Q_sky[3] = Quad(1,5,6,2);
    Q_sky[4] = Quad(2,6,7,3);

    Sky = Mesh(P_sky,8,0,0,Q_sky,5,CONSTANT_COLOR,FLAT_SHADING);
    Color *col_sky = new Color[5];
    for (int i=0; i<5; i++)
        col_sky[i] = BLUE;
    Sky.setColors(QUAD,col_sky);

    // Generation fond
    DoublePoint3 *P_sol=new DoublePoint3[4];
    for (int i=0; i<4; i++)
        P_sol[i] = P_sky[i+4];


    Quad *Q_sol = new Quad[1];
    Q_sol[0] = Quad(0,1,2,3);
    Sol = Mesh(P_sol,4,0,0,Q_sol,1,CONSTANT_COLOR,FLAT_SHADING);
    Sol.setColor(GREEN);

}

void map::draw(){
    showMesh(Plane);
    for(int i = 0;i<walls.size();i++){
        showMesh(walls[i]);
    }
    showMesh(Sky);
    showMesh(Sol);
}

void map::generateWalls(){
    //Genere les murs codés en rouge; extraits de petits segments d'une boucle orienté la partie accessible est à gauche de la courbe.
    int h=physics.size(0);
    int w=physics.size(1);
    FilePriorite Q;
    int r,g,b;

    for (int j=0;j<w;j++) {
        for (int i=0;i<h;i++) {
            r = physics(i,j).r();
            g = physics(i,j).g();
            b = physics(i,j).b();
            if(r!=0){
                //std::cout<<"Premier point : "<<r<<std::endl;
                Q.push(PointClasse(r,DoublePoint3(100*double(j+0.5)/w,100*double(i+0.5)/h,0)));
            }
        }
    }

    int last = 255;
    std::vector<DoublePoint3> mur;
    DoublePoint3 ptemp;
    DoublePoint3 firstp;
    DoublePoint3 pinter2;

    while(!Q.empty()){
     PointClasse p1 = Q.pop();

     if (p1.val == last){
         firstp = p1.p;
         mur.push_back(p1.p);
     }

     if (p1.val==last-1){
         //std::cout<<p1.val<<" "<<last-1<<std::endl;
         mur.push_back(p1.p);

         FVector<DoublePoint3,2> seg = {ptemp,p1.p};
         compute_walls.push_back(seg);
         }
     if (p1.val == last-2){
         FVector<DoublePoint3,2> seg = {firstp,ptemp};
         compute_walls.push_back(seg);
         //On genere le mesh à afficher
         int len = mur.size();
         DoublePoint3 MurTab[2*len];
         for(int i=0;i<len;i++){
             MurTab[i]=mur[i];
             MurTab[(2*len)-1-i] = mur[i] + DoubleVector3(0,0,wallheight);
         }

         Quad *Qua=new Quad[len-1];
         Color *Cols = new Color[len-1];
         for(int i = 0; i<len-1;i++){
             Qua[i] = Quad(i,i+1,(2*len)-2-i,(2*len)-1-i);
             Cols[i] = myrainbow[i%4];

         }
         Mesh tempmesh = Mesh(MurTab,2*len,0,0,Qua,len-1,FACE_COLOR);
         tempmesh.setColors(QUAD,Cols);
         walls.push_back(tempmesh);

         while(!mur.empty()){
             mur.pop_back();
         }
         firstp = p1.p;
         mur.push_back(p1.p);
       }
     ptemp = p1.p;
     last = p1.val;
    }

    //Generation du dernier mur;

    int len = mur.size();
    DoublePoint3 MurTab[2*len];
    for(int i=0;i<len;i++){
        MurTab[i]=mur[i];
        MurTab[(2*len)-1-i] = mur[i] + DoubleVector3(0,0,wallheight);
    }

    Quad *Qua=new Quad[len-1];
    Color *Cols = new Color[len-1];
    for(int i = 0; i<len-1;i++){
        Qua[i] = Quad(i,i+1,(2*len)-2-i,(2*len)-1-i);
        Cols[i] = myrainbow[i%4];

    }
    Mesh tempmesh = Mesh(MurTab,2*len,0,0,Qua,len-1,FACE_COLOR);
    tempmesh.setColors(QUAD,Cols);
    walls.push_back(tempmesh);


    //std::cout<<"In generateWalls() got : "<<walls.size()<<std::endl;
}

void map::set_start(){
    //Cherche le pixel vert avec un code 0 248 0 pour definir le point de départ, et points dans la direction du pixel vert 0 128 0;
    int h=physics.size(0);
    int w=physics.size(1);
    DoublePoint3 Lookat;
    for (int j=0;j<w;j++) {
        for (int i=0;i<h;i++) {
            if(physics(i,j)==Color(0,248,255)){
                start_position=DoublePoint3(100*double(j+0.5)/w,100*double(i+0.5)/h,0);
            }
            if(physics(i,j)==Color(0,128,255)){
                Lookat=DoublePoint3(100*double(j+0.5)/w,100*double(i+0.5)/h,0);
            }
        }
    }
    start_direction = (Lookat-start_position).normalize();
}

float map::get_vit(DoublePoint3 pos){
    int h=physics.size(0);
    int w=physics.size(1);
    if(int((w*(pos.y()-0.5)/100<w)&&(int(h*(pos.x()-0.5)/100)<h)&&(w*(pos.y()-0.5)/100>-1)&&(int(h*(pos.x()-0.5)/100)>-1))){
            return 2*physics(int(w*(pos.y()-0.5)/100),int(h*(pos.x()-0.5)/100)).b()/255.;

    }else{
        return 1;
    }
}


// Recuperation du Tp d'algo Fastmarching
void FilePriorite::push(PointClasse d) {
            int i = v.size();
            v.push_back(d);
            while(i!=1){
                int par = i/2;
                if(v[i]>v[par]){
                    std::swap(v[i],v[par]);
                    i = par;
                }
                else{
                    break;
                }
            }
}

// Retire un element
PointClasse FilePriorite::pop() {
    PointClasse p = v[1];
    v[1] = v.back();
    v.pop_back();
    double dc1,dc2; //Distance de l'enfant 1 et puis de l'enfant 2
    int i=1;
    while(true){

        if(2*i<v.size()){
            dc1 = v[2*i].val;
        }
        else{
            dc1 = __DBL_MIN__;
        }

        if((2*i)+1<v.size()){
            dc2 = v[(2*i) + 1].val;
        }
        else{
            dc2 = __DBL_MIN__;
        }

        if(dc1>dc2){
            if((v[i].val<dc1)&&(2*i<v.size())){
                std::swap(v[i],v[2*i]);
                i = 2*i;
            }
            else{
                break;
            }
        }
        else{
            if((v[i].val<dc2)&&(2*i+1<v.size())){
                std::swap(v[i],v[2*i+1]);
                i = 2*i +1;
            }
            else{
                break;
            }
        }

    }
    return p;

}

bool FilePriorite::empty(){
         return(v.size()==1);

}
