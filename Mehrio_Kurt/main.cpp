//MehrioKurt Théo Contentin Steven Arulpragasam


#include <Imagine/Graphics.h>
#include "map.h"
#include "kart.h"
#include "physics.h"

using namespace Imagine;

int main(int argc, char** argv)
{
    int nplayers = 0;
    bool started =false;
    Window W=openComplexWindow(200,500,"Mehrio Kurt",1,0,0,800,100);
    Image<Color> menu;
    load(menu,srcPath("menu.png"));
    display(menu,0,0);

    //selecting mode

    int x,y;
    while(nplayers ==0){
        getMouse(x,y);
        if ((y<160)&&(y>96)){
            display(menu,0,0);
            drawLine(33,147,174,147,YELLOW,3);
            nplayers = 1;
        }
        if ((y<250)&&(y>190)){
            display(menu,0,0);
            drawLine(33,239,174,239,YELLOW,3);
            nplayers = 2;
        }
    }

    if(nplayers==2){
        map carte("SuperMarioKartMapFlowerCup3.png","SuperMarioKartMapFlowerCup3_low.png","SuperMarioKartMapFlowerCup3_physics.png");
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

        setActiveWindow(W);
        while(!started){
            getMouse(x,y);
            if ((y<330)&&(y>270)){
                started = true;
            }
        }
        drawString(15,450, "1/3",BLACK,20);
        drawString(135,450, "1/3",BLACK,20);
        for(int i=0;i<25000;i++){
            milliSleep(5);
            updateKeys(kart1,kart2);
            compute_collisions(kart1,kart2);
            run_physics(kart1,carte);
            run_physics(kart2,carte);
            compute_collisions(kart1,kart2);
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

        setActiveWindow(W);
        while(!started){
            getMouse(x,y);
            if ((y<330)&&(y>270)){
                started = true;
            }
        }
        drawString(15,450, "1/3",BLACK,20);
        for(int i=0;i<25000;i++){
            milliSleep(15);
            setActiveWindow(W);
            updateKeys(kart1);
            run_physics(kart1,carte);
            setActiveWindow(FirstPlayerWindow);
            kart1.MoveCamera();

        }
        anyClick();
        closeWindow(FirstPlayerWindow);
        closeWindow(W);
        endGraphics();
    }
    return 0;
}
