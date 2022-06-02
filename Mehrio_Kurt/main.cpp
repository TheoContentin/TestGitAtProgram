//MehrioKurt Théo Contentin Steven Arulpragasam


#include <Imagine/Graphics.h>
#include "map.h"
#include "kart.h"
#include "physics.h"

using namespace Imagine;


void events() {
    // Basics
    Window W=openComplexWindow(500,500,"events",2);
                                               // ...
    // Advanced
    std::cout << "Generate events, press 'q' key done" << std::endl;              // manually process events
    Event ev;
    do {
        getEvent(500,ev);
        switch (ev.type) {
        case EVT_NONE:
            std::cout << "No event for 500ms" << std::endl;
            break;
        case EVT_MOTION:
            std::cout << "Motion" << std::endl;
            break;
        case EVT_KEY_ON:
            std::cout << "Key " << ev.key << " pressed"<< std::endl;
            break;
        case EVT_KEY_OFF:
            std::cout << "Key " << ev.key << " released"<< std::endl;
            break;
        case EVT_BUT_ON:
            std::cout << "Button " << ev.button << " pressed"<< std::endl;
            break;
        case EVT_BUT_OFF:
            std::cout << "Button " << ev.button << " released"<< std::endl;
            break;
        }
        if (ev.type!=EVT_NONE)
            std::cout << " Mouse=[" << ev.pix.x() <<','<<ev.pix.y() << "] ,State="<< ev.state
                 << ",Win=" << ev.win << ",SubWin=" << ev.subWin << std::endl;
    } while (ev.type!=EVT_KEY_ON || ev.key!='q'); // ...
    unGetEvent(ev);         // unget event
    flushEvents();          // flush events

    std::cout << "Please click" << std::endl;
    anyClick();
    //closeWindow(W);
}


int main(int argc, char** argv)
{
    map carte("SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3_physics.png");
    std::cout<<"Genere la carte correctement"<<std::endl;
    Kart kart(carte);
    Window glWindow = openWindow3D(512, 512, "3D Window");
    Window W=openComplexWindow(15,15,"events",1);
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
    for(int i=0;i<25000;i++){
        milliSleep(50);
        run_physics(kart,carte);
    }
    anyClick();
    closeWindow(glWindow);
    endGraphics();
    return 0;
}
