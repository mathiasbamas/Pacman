#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/audio/audioengine.h"
#include "mingl/gui/text.h"

using namespace std;

int main()
{
    // Initialise le système
    MinGL window("07 - Audio", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Initialise le sous-système audio
    nsAudio::AudioEngine audioEngine;

    // On définit la musique du sous-système, et on la joue
    audioEngine.setMusic("res/music.wav");
    audioEngine.startMusicFromBeginning();

    // On charge les effets sonores
    audioEngine.loadSound("res/sound1.wav");
    audioEngine.loadSound("res/sound2.wav");

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        window << nsGui::Text(nsGraphics::Vec2D(16, 24), "Appuyez sur ESPACE pour mettre en pause/lecture la musique.", nsGraphics::KPurple);
        window << nsGui::Text(nsGraphics::Vec2D(16, 40), "Appuyez sur S pour jouer un effet sonore.", nsGraphics::KPurple);

        window << nsGui::Text(nsGraphics::Vec2D(320, 320), audioEngine.isMusicPlaying() ? "LECTURE" : "PAUSE", audioEngine.isMusicPlaying() ? nsGraphics::KLime : nsGraphics::KRed,
                              nsGui::GlutFont::BITMAP_9_BY_15, nsGui::Text::HorizontalAlignment::ALIGNH_CENTER);

        // On vérifie les touches
        if (window.isPressed({' ', false}))
        {
            // Espace a été pressé, on bascule la musique
            window.resetKey({' ', false});
            audioEngine.toggleMusicPlaying();
        }
        if (window.isPressed({'s', false}))
        {
            // S a été pressé, on joue un effet sonore
            window.resetKey({'s', false});
            const uint8_t soundToPlay = rand() % 2 + 1;
            audioEngine.playSoundFromBuffer("res/sound" + std::to_string(soundToPlay) + ".wav");
        }

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
