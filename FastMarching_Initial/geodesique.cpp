// Author: 

#include "fastMarching.h"
#include <iostream>

typedef FVector<float,2> FloatPoint2; // point avec coordonnees float

const float EPSILON=10.0f; // Spatial length parameter
const float TAU=0.8f; // Increment dans la direction opposee au gradient
const size_t MAX_LENGTH=1000; // Max length of a geodesic

// Remplis l'image des poids, fonction croissante de la distance en couleur
// du point courant a I(p).
Image<float> remplisPoids(const Image<Color>& I, const IntPoint2& p) {
    float r = I(p.x(),p.y()).r() ,g = I(p.x(),p.y()).g(),b = I(p.x(),p.y()).b();

    Image<float> W(I.width(), I.height());
    for(int i = 0; i< I.width();i++){
        for(int j = 0; j< I.height(); j++){
            float R =I(i,j).r(),G=I(i,j).g(),B=I(i,j).b();
            W(i,j) = EPSILON + (abs(R-r)+abs(G-g)+abs(B-b))/3.;
        }
    }
    return W;
}

IntPoint2 arrondi(const FloatPoint2& p) {
    return IntPoint2((int)(p[0]+0.5f), (int)(p[1]+0.5f));
}

// Calcule la geodesique de p1 a p2.
vector<FloatPoint2> geodesique(const Image<float>& D,
                               FloatPoint2 p1, FloatPoint2 p2) {
    vector<FloatPoint2> v;
    v.push_back(p2);

    for(int i=0;i<MAX_LENGTH;i++){
        FloatPoint2 current = v.back();
        FloatPoint2 grad = gradient(D,Coords<2>(current));

        FloatPoint2 next = current - TAU*grad.normalize();

        //std::cout<<dist(p1,next)<<endl;

        if(dist(p1,next)>1){
            v.push_back(next);
            if(i==MAX_LENGTH-1){
                std::cout<<"Le chemin est trop long";
                break;
            }

        }
        else{
            v.push_back(p1);
            break;
        }


    }
    return v;
}

int main() {
    Image<Color> I;
    if(! load(I, argc>1? argv[1]: srcPath("map.png"))) {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 1;
    }
    openWindow(I.width(), I.height());
    display(I);

    cout << "Cliquez les points de depart et d'arrivee" << endl;
    IntPoint2 p1, p2;
    while(getMouse(p1)==1) {
        display(I);
        p2=p1;
        fillCircle(p2,2,BLUE);

    }

    Image<float> W = remplisPoids(I,p2);
    affiche(W);
    click();
    std::vector<PointDist> v;
    PointDist p(p2.x(),p2.y(),0);
    v.push_back(p);

    Image<float> D = fastMarching(W,v);

    affiche(D);
    click();

    vector<FloatPoint2> geo = geodesique(D,p2,p1);

    display(I);
    fillCircle(p2,2,BLUE);
    fillCircle(p1,2,BLUE);

    for(int i = 0; i<geo.size();i++){
        drawPoint(geo[i].x(),geo[i].y(),RED);
    }

    click();


    endGraphics();
    return 0;
}
