#include "map.h"
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
            P[i+(h+1)*j]=DoublePoint3(double(i)/h,double(j)/w,0);   // A flat surface to texture
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
            std::cout<<"texture(i,j)"<<std::endl;
        }
    }

    Plane.setColors(TRIANGLE,col);

    std::cout<<"Colors Ok"<<std::endl;
    generateWalls();

}

void map::draw(){
    showMesh(Plane);
}

void map::generateWalls(){
    return;
}
