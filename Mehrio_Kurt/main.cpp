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
    int nplayers = 1;
    Window W=openComplexWindow(200,500,"Mehrio Kurt",1,0,0,800,100);


    fillRect(10,10,180,100,RED);
    drawString(30,70,"1  Joueur",BLACK,24);

    fillRect(10,170,180,100,YELLOW);
    drawString(30,240,"2 Joueurs",BLACK,24);

    fillRect(10,330,180,100,GREEN);
    drawString(30,400,"Départ",BLACK,24);

    int x,y;
    getMouse(x,y);

    if ((y<270)&&(y>170)){
        nplayers = 2;
    }

    if(nplayers==2){
        map carte("SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3_physics.png");
        std::cout<<"Genere la carte correctement"<<std::endl;
        Kart kart1(carte,1);
        Kart kart2(carte,2);
        Window FirstPlayerWindow = openWindow3D(500, 500, "Joueur 1",290,140);
        Window SecondPlayerWindow = openWindow3D(500, 500, "Joueur 2",1012,140);

        setActiveWindow(FirstPlayerWindow);
        setBackGround(Color(0,0,0));
        carte.draw();
        kart1.showKart();
        kart2.showKart();
        setActiveWindow(SecondPlayerWindow);
        setBackGround(Color(0,0,0));
        carte.draw();
        kart1.showKart();
        kart2.showKart();
        anyClick();  //Waiting for click to start

        for(int i=0;i<25000;i++){
            milliSleep(1);
            updateKeys(kart1,kart2);
            run_physics(kart1,carte);
            run_physics(kart2,carte);
            setActiveWindow(FirstPlayerWindow);
            kart1.MoveCamera();
            setActiveWindow(SecondPlayerWindow);
            kart2.MoveCamera();
            setActiveWindow(W);
        }
        anyClick();
        closeWindow(FirstPlayerWindow);
        closeWindow(SecondPlayerWindow);
        closeWindow(W);
        endGraphics();



    }
    else{
        map carte("SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3_physics.png");
        std::cout<<"Genere la carte correctement"<<std::endl;
        Kart kart1(carte,1);
        Window FirstPlayerWindow = openWindow3D(500, 500, "Joueur 1",290,140);
        setActiveWindow(FirstPlayerWindow);
        setBackGround(Color(0,0,0));
        carte.draw();
        kart1.showKart();

        anyClick();  //Waiting for click to start

        for(int i=0;i<25000;i++){
            milliSleep(10);
            updateKeys(kart1);
            run_physics(kart1,carte);
            kart1.MoveCamera();
            }
        anyClick();
        closeWindow(FirstPlayerWindow);
        closeWindow(W);
        endGraphics();
    }
    return 0;
}
