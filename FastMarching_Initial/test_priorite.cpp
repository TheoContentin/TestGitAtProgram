#include "priorite.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

const int n=20;

int main() {
    std::srand((unsigned int)std::time(0));
    std::vector<PointDist> v;
    FilePriorite F;
    for(int i=0; i<n; i++)
        v.push_back( PointDist(i,0, (double)i) );
    for(int i=0;i<n;i++){
        std::swap(v[i],v[rand()%n]);
    }

    for(int i = 0;i<n;i++){
    std::cout<<v[i].dist<<" ";
    }
    std::cout<<std::endl;

    for(int i=0;i<n;i++){
        F.push(v[i]);
    }
    for(int i=0;i<n;i++){
        std::cout<<F.pop().dist<<" ";
    }
    std::cout<<std::endl;
}
