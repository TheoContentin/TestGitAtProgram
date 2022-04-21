//MehrioKurt Théo Contentin Steven Arulpragasam


#include <Imagine/Graphics.h>
#include "map.h"
using namespace Imagine;


int main(int argc, char** argv)
{
    map carte("texture.jpeg","texture.jpeg","texture.jpeg");
    Window glWindow = openWindow3D(512, 512, "3D Window");
    setActiveWindow(glWindow);
    setBackGround(Color(0,0,0));
    carte.draw();
    anyClick();
    closeWindow(glWindow);
    endGraphics();
    return 0;
}
