#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/triangle.h"
#include "mingl/transition/transition_engine.h"

using namespace std;

int main()
{
    // Initialise le système
    MinGL window("05 - Transition", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // On instantie quelques objets transitionables
    nsShape::Circle circle(nsGraphics::Vec2D(64, 64), 16, nsGraphics::KRed);
    nsShape::Rectangle rect(nsGraphics::Vec2D(128, 64), nsGraphics::Vec2D(512, 192), nsGraphics::KBlue);
    nsShape::Triangle tri(nsGraphics::Vec2D(256, 256), nsGraphics::Vec2D(256, 384), nsGraphics::Vec2D(512, 384), nsGraphics::KPurple);
    nsShape::Line line(nsGraphics::Vec2D(64, 512), nsGraphics::Vec2D(576, 512), nsGraphics::KNavy);

    // Instantie un gestionnaire de transition
    nsTransition::TransitionEngine transitionEngine;

    // On démarre une premiere transition simple, qui change le rayon du cercle a 48 pixels pendant 10 secondes
    transitionEngine.startContract(nsTransition::TransitionContract(circle, circle.TRANSITION_RADIUS, chrono::seconds(10), {48}));

    // On peut définir une fonction a appeler quand une transition se termine
    nsTransition::TransitionContract rectTransitionContract(rect, rect.TRANSITION_FILL_COLOR_ALPHA, chrono::seconds(5), {64});
    rectTransitionContract.setDestinationCallback([&] {
        // On définit ici ce qu'il se passe quand la transition est terminée
        std::cout << "Transition sur rectangle terminé!" << std::endl;
        rect.setFillColor(nsGraphics::RGBAcolor(255, 0, 0, 64));
        rect.setBorderColor(nsGraphics::KGreen);
    });

    transitionEngine.startContract(rectTransitionContract);

    // On peut aussi définir plusieurs transition en même temps sur un seul objet
    transitionEngine.startContract(nsTransition::TransitionContract(tri, tri.TRANSITION_THIRD_POSITION, chrono::seconds(2), {512, 256}));
    transitionEngine.startContract(nsTransition::TransitionContract(tri, tri.TRANSITION_SECOND_POSITION, chrono::seconds(2), {512, 384}));

    // Enfin, il existe aussi plusieurs mode de transitions (ici, nous voyons une transition infinie)
    transitionEngine.startContract(nsTransition::TransitionContract(line, line.TRANSITION_FIRST_POSITION, chrono::seconds(6), {288, 512},
                                                                    chrono::seconds::zero(), nsTransition::Transition::TransitionMode::MODE_LOOP_SMOOTH));
    transitionEngine.startContract(nsTransition::TransitionContract(line, line.TRANSITION_SECOND_POSITION, chrono::seconds(6), {352, 512},
                                                                    chrono::seconds::zero(), nsTransition::Transition::TransitionMode::MODE_LOOP_SMOOTH));
    transitionEngine.startContract(nsTransition::TransitionContract(line, line.TRANSITION_LINE_WIDTH, chrono::seconds(6), {20},
                                                                    chrono::seconds::zero(), nsTransition::Transition::TransitionMode::MODE_LOOP_SMOOTH));

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

        // On affiche tout les objets
        window << circle << rect << tri << line;

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
