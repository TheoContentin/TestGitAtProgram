#define _USE_MATH_DEFINES
#include <cmath>
#include "fastMarching.h"
#include "priorite.h"
#include <algorithm>


const int voisin[4][2] = { {-1,0}, {+1,0}, {0,-1}, {0,+1} };

// Met dans dx et dy les plus petites valeurs des voisins du pixel (x,y).
void minVoisins(const Image<float>& D, int x, int y, float& dx, float& dy) {

    dx = INF, dy = INF;

    for(int i=0;i<4;i++){
        int k = x+voisin[i][0], l = y+voisin[i][1];
        if(((-1<k) && (k<D.width())) && ((-1<l) && (l<D.height()))){ //Condition pour ne pas sortir du cadre
            if(i<2){
                dx = min(dx,D(k,l));
            }
            else{
                dy = min(dy,D(k,l));
            }
        }
    }
}

// Met a jour et renvoie la distance D(x,y) en fonction des voisins.
float calcDistance(Image<float>& D, const Image<float>& W, int x, int y){
    float d1,d2;
    minVoisins(D,x,y,d1,d2);
    if((d1 == INF)||(d2==INF)){
        if((min(d1,d2)+W(x,y) == INF)){
        }
            return min(d1,d2)+W(x,y);
    }else{
        if ((2*pow(W(x,y),2) -pow(d1-d2,2))<0){
            return min(d1,d2)+W(x,y);
        }
        else{
            return (d1 + d2 + sqrt(2*pow(W(x,y),2) -pow(d1-d2,2)))/2;
        }
    }
}

// Fast Marching: carte de distance a partir des points de niv0, qui sont a
// distance 0 par definition.
Image<float> fastMarching(const Image<float>& W, const vector<PointDist>& niv0){
    const int w=W.width(), h=W.height();

    // Initialisation
    Image<float> D(w,h); D.fill(INF);
    Image<bool>  E(w,h); E.fill(false);
    FilePriorite F;
    for(int i = 0;i<niv0.size();i++){
        D(niv0[i].i,niv0[i].j) = 0;
        E(niv0[i].i,niv0[i].j) = true;
        F.push(niv0[i]);
    }
    while(!F.empty()){
        PointDist p = F.pop();
        for(int i =0;i<4;i++){
            int k = p.i + voisin[i][0], l=p.j + voisin[i][1];
            if(((-1<k) && (k<w)) && ((-1<l) && (l<h)) ){ //Condition pour ne pas sortir du cadre
                if(!E(k,l)){
                    D(k,l) = calcDistance(D,W,k,l);
                    E(k,l) = true;
                    F.push(PointDist(k,l,-D(k,l)));
                }
            }
        }
    }

    return D;
}

// Affiche en couleur l'image des distances.
// bleu=0, rouge=maximum, vert=infini
void affiche(const Image<float>& I) {
    Image<float> D=I.clone();
    for(int i=0; i<D.height(); i++){
        for(int j=0; j<D.width(); j++){
            if(D(j,i)==INF){
                D(j,i)=-1.0f;
            }
        }
    }

    float M = *max_element(D.begin(), D.end());
    M = max(1.0f,M);
    Image<Color> B(D.width(), D.height());
    for(int i=0; i<D.height(); i++){
        for(int j=0; j<D.width(); j++) {
            if(D(j,i)>=0) {
                float angle=M_PI/2*D(j,i)/M;
                B(j,i) = Color(char(255*sin(angle)), 0, char(255*cos(angle)));
            }
            else B(j,i) = GREEN;
        }
    }
    display(B);
}
// salut theo
