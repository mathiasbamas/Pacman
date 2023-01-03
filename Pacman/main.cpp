#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"

using namespace std;
using namespace nsGraphics;
using namespace nsEvent;
using namespace nsShape;
using namespace chrono;


int main()
{
    MinGL window("Pacman", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    microseconds frameTime = microseconds::zero();

    while (window.isOpen())
    {
        time_point<steady_clock> start = steady_clock::now();


        window.clearScreen();
        window.finishFrame();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
