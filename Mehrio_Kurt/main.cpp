//MehrioKurt Théo Contentin Steven Arulpragasam


#include <Imagine/Graphics.h>
#include "map.h"
using namespace Imagine;


int main(int argc, char** argv)
{
    map carte("texture.jpeg","texture.jpeg","texture.jpeg");
    std::cout<<"Genéré la carte correctement"<<std::endl;
    Window glWindow = openWindow3D(512, 512, "3D Window");
    setActiveWindow(glWindow);
    setBackGround(Color(0,0,0));
    anyClick();
    std::cout<<"On rentre dans draw"<<std::endl;
    carte.draw();
    std::cout<<"On sort de draw"<<std::endl;
    anyClick();
    closeWindow(glWindow);
    endGraphics();
    return 0;
}
