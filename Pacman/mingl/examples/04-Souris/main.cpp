#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"

using namespace std;

nsGraphics::Vec2D rectPos;
nsGraphics::RGBAcolor rectColor = nsGraphics::KCyan;

void events(MinGL &window)
{
    // On vérifie chaque évènement de la queue d'évènements
    while (window.getEventManager().hasEvent())
    {
        const nsEvent::Event_t actualEvent = window.getEventManager().pullEvent();

        // On regarde le type d'évènement
        switch (actualEvent.eventType)
        {
            case nsEvent::EventType_t::MouseMove:
                // Il s'agit d'un mouvement de souris
                rectPos.setX(actualEvent.eventData.moveData.x);
                rectPos.setY(actualEvent.eventData.moveData.y);

                break;

            case nsEvent::EventType_t::MouseClick:
                // Il s'agit d'un click de souris
                rectColor = (actualEvent.eventData.clickData.state ? nsGraphics::KCyan : nsGraphics::KPurple);

                break;

            default:
                // L'évènement ne nous intéresse pas
                break;
        }
    }
}

void dessiner(MinGL &window)
{
    // On dessine le rectangle
    window << nsShape::Rectangle(rectPos, rectPos + nsGraphics::Vec2D(20, 20), rectColor);
}

int main()
{
    // Initialise le système
    MinGL window("04 - Souris", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
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
        events(window);
        dessiner(window);

        // On finit la frame en cours
        window.finishFrame();

        // /!\ On NE vide PAS la queue d'évènements car on s'en sert /!\
        // window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
