#include "priorite.h"

// Ajoute un element
void FilePriorite::push(PointDist d) {
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
PointDist FilePriorite::pop() {
    PointDist p = v[1];
    v[1] = v.back();
    v.pop_back();
    double dc1,dc2; //Distance de l'enfant 1 et puis de l'enfant 2
    int i=1;
    while(true){

        if(2*i<v.size()){
            dc1 = v[2*i].dist;
        }
        else{
            dc1 = __DBL_MIN__;
        }

        if((2*i)+1<v.size()){
            dc2 = v[(2*i) + 1].dist;
        }
        else{
            dc2 = __DBL_MIN__;
        }

        if(dc1>dc2){
            if((v[i].dist<dc1)&&(2*i<v.size())){
                std::swap(v[i],v[2*i]);
                i = 2*i;
            }
            else{
                break;
            }
        }
        else{
            if((v[i].dist<dc2)&&(2*i+1<v.size())){
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
