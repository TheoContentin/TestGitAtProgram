//MehrioKurt Théo Contentin Steven Arulpragasam


#include <Imagine/Graphics.h>
#include "map.h"
#include "kart.h"
using namespace Imagine;


int main(int argc, char** argv)
{
    map carte("texture.jpeg","texture.jpeg","texture.jpeg");
    std::cout<<"Genéré la carte correctement"<<std::endl;
    Kart kart(carte);
    Window glWindow = openWindow3D(512, 512, "3D Window");
    setActiveWindow(glWindow);
    setBackGround(Color(0,0,0));
    anyClick();
    std::cout<<"On rentre dans draw"<<std::endl;
    carte.draw();
    kart.showCube();
    std::cout<<"On sort de draw"<<std::endl;
    anyClick();
    closeWindow(glWindow);
    endGraphics();
    return 0;
}
