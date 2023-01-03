#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"

using namespace std;

nsGraphics::Vec2D rectPos;

void clavier(MinGL &window)
{
    // On vérifie si ZQSD est pressé, et met a jour la position
    if (window.isPressed({'z', false}))
        rectPos.setY(rectPos.getY() - 1);
    if (window.isPressed({'s', false}))
        rectPos.setY(rectPos.getY() + 1);
    if (window.isPressed({'q', false}))
        rectPos.setX(rectPos.getX() - 1);
    if (window.isPressed({'d', false}))
        rectPos.setX(rectPos.getX() + 1);
}

void dessiner(MinGL &window)
{
    // On dessine le rectangle
    window << nsShape::Rectangle(rectPos, rectPos + nsGraphics::Vec2D(20, 20), nsGraphics::KCyan);
}

int main()
{
    // Initialise le système
    MinGL window("03 - Clavier", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On fait tourner les procédures
        clavier(window);
        dessiner(window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
