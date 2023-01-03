#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/transition/transition_engine.h"

// On inclut l'en-tête de notre objet custom
#include "bgtext.h"

using namespace std;

int main()
{
    // Initialise le système
    MinGL window("09 - Custom Transitionable", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Instantie notre objet custom
    BgText customObject(nsGraphics::Vec2D(64, 64), "Hello, World!", nsGraphics::KBlue, nsGraphics::KRed);

    // Instantie un gestionnaire de transition
    nsTransition::TransitionEngine transitionEngine;

    // On démarre les transitions sur notre objet custom
    transitionEngine.startContract(nsTransition::TransitionContract(customObject, customObject.TRANSITION_TEXT_COLOR, chrono::seconds(2), {255, 0, 0},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));
    transitionEngine.startContract(nsTransition::TransitionContract(customObject, customObject.TRANSITION_BACKGROUND_COLOR, chrono::seconds(2), {0, 0, 255},
                                                                    chrono::seconds::zero(), nsTransition::Transition::MODE_LOOP_SMOOTH));

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On met a jour le gestionnaire de transition
        transitionEngine.update(frameTime);

        // On affiche notre objet
        window << customObject;

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
