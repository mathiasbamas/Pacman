#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/gui/text.h"
#include "mingl/shape/line.h"

using namespace std;

void dessiner(MinGL &window)
{
    // MinGL 2 supporte l'affichage de texte sur la fenêtre assez simplement.
    window << nsGui::Text(nsGraphics::Vec2D(20, 20), "Hello, World!", nsGraphics::KWhite);

    // Vous pouvez aussi changer la police (parmi un choix assez limité, malheureusement).
    window << nsGui::Text(nsGraphics::Vec2D(20, 40), "Hello, World! mais plus grand", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15);
    window << nsGui::Text(nsGraphics::Vec2D(20, 60), "Hello, World! mais en Helvetica 18", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);

    // L'alignement vertical et horizontal peut aussi être changé.
    window << nsShape::Line(nsGraphics::Vec2D(320, 120), nsGraphics::Vec2D(320, 220), nsGraphics::KRed);
    window << nsShape::Line(nsGraphics::Vec2D(10, 310), nsGraphics::Vec2D(630, 310), nsGraphics::KRed);

    window << nsGui::Text(nsGraphics::Vec2D(320, 135), "Gauche horizontalement", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15);
    window << nsGui::Text(nsGraphics::Vec2D(320, 160), "Centre horizontalement", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15,
                          nsGui::Text::HorizontalAlignment::ALIGNH_CENTER);
    window << nsGui::Text(nsGraphics::Vec2D(320, 185), "Droite horizontalement", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15,
                          nsGui::Text::HorizontalAlignment::ALIGNH_RIGHT);

    window << nsGui::Text(nsGraphics::Vec2D(15, 310), "Bas verticalement", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15,
                          nsGui::Text::HorizontalAlignment::ALIGNH_LEFT, nsGui::Text::VerticalAlignment::ALIGNV_BOTTOM);
    window << nsGui::Text(nsGraphics::Vec2D(200, 310), "Centre verticalement", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15,
                          nsGui::Text::HorizontalAlignment::ALIGNH_LEFT, nsGui::Text::VerticalAlignment::ALIGNV_CENTER);
    window << nsGui::Text(nsGraphics::Vec2D(400, 310), "Haut verticalement", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_9_BY_15,
                          nsGui::Text::HorizontalAlignment::ALIGNH_LEFT, nsGui::Text::VerticalAlignment::ALIGNV_TOP);

    // N'hésitez pas a lire la doc pour plus de détails.
}

int main()
{
    // Initialise le système
    MinGL window("02 - Texte", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
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

        // On dessine le texte
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
