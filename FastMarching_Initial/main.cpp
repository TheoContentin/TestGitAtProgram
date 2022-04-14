//MehrioKurt Théo Contentin Steven Arupalgrasam


#include <Imagine/Graphics.h>
using namespace Imagine;


int main(int argc, char** argv)
{
    Window glWindow = openWindow3D(512, 512, "3D Window");
    setActiveWindow(glWindow);
    setBackGround(Color(0,0,0));
    std::string fileName = srcPath("bunny.obj");
    Mesh mesh;
    readMeshFromObjFile(mesh, fileName);
    mesh.setColor(Color(255,100,0));
    showMesh(mesh);
    animateCamera();
    Particle particles1; // creates particles
    particles1.start();

    for (int i=0;i<200;i++)
    {
        particles1.draw();
        milliSleep(20);
    }
    anyClick();
    particles1.stop();
    closeWindow(glWindow);
    endGraphics();
    return 0;
}
