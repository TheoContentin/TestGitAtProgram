#include "map.h"
#include <queue>
#include <vector>

using namespace Imagine;


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

    // Generation de la texture du sol;
    int h=texture.size(0);
    int w=texture.size(1);
    DoublePoint3 *P=new DoublePoint3[(w+1)*(h+1)];
    for (int j=0;j<=w;j++)
        for (int i=0;i<=h;i++)
            P[i+(h+1)*j]=DoublePoint3(100*double(i)/h,100*double(j)/w,0);   // A flat surface to texture
    Triangle *T=new Triangle[2*(h)*(w)];
    for (int j=0;j<w;j++) {
        for (int i=0;i<h;i++) {
            T[2*(i+(h)*j)]=Triangle(i+(h+1)*j,i+1+(h+1)*j,i+(h+1)*(j+1));
            T[2*(i+(h)*j)+1]=Triangle(i+1+(h+1)*j,i+1+(h+1)*(j+1),i+(h+1)*(j+1));
        }
    }
    std::cout<<"Triangle Ok"<<std::endl;

    std::cout<<"Quad Ok"<<std::endl;

    Plane = Mesh(P,(w+1)*(h+1),T,2*h*w,0,0,FACE_COLOR,SMOOTH_SHADING);
    std::cout<<"Mesh Ok"<<std::endl;

    Color *col=new Color[2*w*h];
    for (int j=0;j<w;j++) {
        for (int i=0;i<h;i++) {
            col[2*(i+(h*j))]=texture(i,j);
            col[2*(i+h*j)+1]=texture(i,j);
        }
    }

    Plane.setColors(TRIANGLE,col);

    std::cout<<"Colors Ok"<<std::endl;
    generateWalls();
    set_start();

}

void map::draw(){
    showMesh(Plane);
}

void map::generateWalls(){
    //Genere les murs codés en rouge, Fait une boucle fermée
    int h=physics.size(0);
    int w=physics.size(1);
    FilePriorite Q;
    int r,g,b;
    for (int j=0;j<w;j++) {
        for (int i=0;i<h;i++) {
            r,g,b = physics(i,j);
            if((b==0) &&(g==0)){
                Q.push(PointClasse(r,DoublePoint3(100*double(i+0.5)/h,100*double(j+0.5)/w,0)));
            }
        }
    }

    int last = 256;
    std::vector<DoublePoint3> mur;

    while(!Q.empty()){
     PointClasse p1 = Q.pop();
     if (p1.val==last-1){
         mur.push_back(p1.p);
     }
     if (p1.val == last-2){
         //On termine le mur précédent
         int len = mur.size();
         DoublePoint3 MurTab[2*len];
         for(int i=0;i<len;i++){
             MurTab[i]=mur[i];
             MurTab[(2*len)-1-i] = mur[i] + DoubleVector3(0,0,1); //Mettre un attribut quelque part pour la taille des murs
         }
         Triangle T[2*(len-1)];
         //Pas fini


     }
    }
}

void map::set_start(){
    //Cherche le pixel vert avec un code 0 248 0 pour definir le point de départ, et points dans la direction du pixel vert 0 128 0;
    int h=physics.size(0);
    int w=physics.size(1);
    DoublePoint3 Lookat;
    for (int j=0;j<w;j++) {
        for (int i=0;i<h;i++) {
            if(physics(i,j)==Color(0,248,0)){
                start_position=DoublePoint3(100*double(i+0.5)/h,100*double(j+0.5)/w,0);
            }
            if(physics(i,j)==Color(0,128,0)){
                Lookat=DoublePoint3(100*double(i+0.5)/h,100*double(j+0.5)/w,0);
            }
        }
    }
    start_direction = Lookat-start_position;
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
