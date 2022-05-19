//MehrioKurt Théo Contentin Steven Arulpragasam


#include <Imagine/Graphics.h>
#include "map.h"
#include "kart.h"
#include "physics.h"

using namespace Imagine;


int main(int argc, char** argv)
{
    map carte("SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3_physics.png");
    std::cout<<"Genere la carte correctement"<<std::endl;
    Kart kart(carte);
    Window glWindow = openWindow3D(512, 512, "3D Window");
    setActiveWindow(glWindow);
    setBackGround(Color(0,0,0));
    anyClick();
    std::cout<<"On rentre dans draw"<<std::endl;
    carte.draw();
    std::cout<<carte.start_position<<" ,"<<carte.start_direction <<std::endl;
    run_physics(kart,carte);
    kart.showKart();
    kart.MoveCamera();
    std::cout<<"On sort de draw"<<std::endl;
    for(int i=0;i<500;i++){
        milliSleep(1000);
        run_physics(kart,carte);
        std::cout<<kart.pos<<std::endl;
    }
    anyClick();
    closeWindow(glWindow);
    endGraphics();
    return 0;
}
