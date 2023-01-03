#ifndef BGTEXT_H
#define BGTEXT_H

// On inclut l'en-tête de IDrawable
#include "mingl/graphics/idrawable.h"

// Ici, les autres en-têtes utiles
#include "mingl/gui/text.h"
#include "mingl/shape/rectangle.h"

// La classe hérite de IDrawable
class BgText: public nsGraphics::IDrawable
{

public:
    // Le constructeur de la classe, prenant les paramètres lors de l'instanciation
    BgText(const nsGraphics::Vec2D& position, const std::string& content, const nsGraphics::RGBAcolor& textColor, const nsGraphics::RGBAcolor& backgroundColor);

    // Ne pas oublier le destructeur virtuel
    virtual ~BgText() = default;

    // On surcharge la fonction draw() qui est appelée lors de l'affichage de notre objet
    virtual void draw(MinGL& window) const override;

private:
    // On met les variables membres ici
    nsGui::Text m_text;
    nsShape::Rectangle m_background;

};

#endif // BGTEXT_H
