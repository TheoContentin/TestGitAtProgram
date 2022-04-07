// Author: 

#include "fastMarching.h"
#include <iostream>

const int w=256, h=256;

int main() {
    openWindow(w,h);
    Image<float> W(w,h);
    W.fill(1.0f);
    vector<PointDist> v;
    cout << "Cliquez des points origine, clic droit pour terminer" << endl;
    PointDist p(0,0,0);
    while(getMouse(p.i,p.j)==1) {
        v.push_back(p);
        fillCircle(p.i,p.j,2,BLUE);
    }
    Image<float> D = fastMarching(W,v);
    affiche(D);
    endGraphics();
    return 0;
}
