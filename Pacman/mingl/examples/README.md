# Exemples minGL 2
Ce répertoire contient divers exemples dont le but est de vous aider a utiliser minGL 2.  
Il est conseillé de **bien** lire les commentaires qui sont éparpillés dans le code de ces exemples, et de lire la documentation des différentes classes qui vous sont introduites en même temps.

## ``00-Boilerplate/``
L'exemple n°00 Boilerplate contient le strict minimum pour démarrer un projet sous minGL 2.

Si vous voulez démarrer un projet avec l'aide de cet exemple, il vous est vivement conseillé de le placer dans un répertoire séparé de minGL 2, de placer le répertoire de minGL 2 dans votre nouveau répertoire de travail et de mettre a jour le fichier de projet ``00-Boilerplate.pro`` en accord avec vos changements.

## ``01-Shapes/``
L'exemple n°01 Shapes vous montre comment dessiner des formes géométriques sur la fenêtre avec minGL 2.

Vous y verrez certaines classes utilisées très souvent lors de l'utilisation de la bibliothèque, ainsi que les mécanismes d'affichage.

## ``02-Texte/``
L'exemple n°02 Texte vous montre comment afficher du texte a l'utilisateur directement sur la fenêtre.

Les différents paramètres pour afficher le texte vous y seront montrés.

## ``03-Clavier/``
L'exemple n°03 Clavier vous montre comment récupérer l'état d'une touche du clavier.

La carré bleu peut être déplacé a l'aide des touches ZQSD du clavier.

## ``04-Souris/``
L'exemple n°4 Souris vous montre comment se servir du gestionnaire d'évènements pour récupérer des évènements souris.

Le carré bleu peut être déplacé a l'aide du curseur de la souris. Sa couleur est changé au clic de souris.  
**Attention:** Comme nous nous servons du gestionnaire d'évènements, la ligne suivante, provenant du Boilerplate, et permettant de vider le gestionnaire d'évènement périodiquement, a été commentée:
```C++
window.getEventManager().clearEvents();
```

## ``05-Transition/``
L'exemple n°5 Transition vous montre comment se servir du gestionnaire de transition.

Plusieurs formes géométriques ont des transitions qui sont appliquées sur leur différentes propriétés, avec des paramètres qui diffèrent afin que vous puissiez voir ses possibilités.

## ``06-Sprite/``
L'exemple n°6 Sprite vous montre comment charger une image externe au format .si2 dans votre programme.

Cet exemple stocke les ressources dans le répertoire ``res/``, qui comprend actuellement une unique image.  
Afin que le programme puisse retrouver ses ressources, ce répertoire doit **impérativement** être copié dans le même répertoire où se trouve l'exécutable.

## ``07-Audio/``
L'exemple n°7 Audio vous montre comment utiliser le sous-système audio afin de jouer de la musique et des effets sonores.

Même remarque que l'exemple précédent, le répertoire ``res/`` doit être copié dans le même répertoire que celui où se trouve l'exécutable.

### Remerciements
- **music.wav**  
    The Entertainer by Kevin MacLeod  
    Link: https://incompetech.filmmusic.io/song/5765-the-entertainer  
    License: http://creativecommons.org/licenses/by/4.0/  

- **sound1.wav**  
    snr_bod.wav by DWSD  
    Link: https://freesound.org/people/DWSD/sounds/183111  
    License: https://creativecommons.org/licenses/by/3.0/

- **sound2.wav**  
    metalbang0.wav by SamsterBirdies  
    Link: https://freesound.org/people/SamsterBirdies/sounds/435699  
    License: https://creativecommons.org/publicdomain/zero/1.0/  

## ``08-CustomDrawable/``
L'exemple n°8 Custom Drawable vous montre comment créer vos propres objets affichables.

Une classe d'exemple ``BgText``, affichant un texte avec une couleur de fond, est créé comme exemple.

## ``09-CustomTransitionable/``
L'exemple n°9 Custom Transitionable vous montre comment créer vos propres objets compatible avec le gestionnaire de transition.

Cet exemple reprend la classe ``BgText`` créé lors de l'exemple précédent, afin de lui ajouter le support de la transition pour sa couleur de texte et de fond.