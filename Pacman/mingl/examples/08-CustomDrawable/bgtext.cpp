#include "bgtext.h"

BgText::BgText(const nsGraphics::Vec2D& position, const std::string& content, const nsGraphics::RGBAcolor& textColor, const nsGraphics::RGBAcolor& backgroundColor)
    : m_text(position, content, textColor)
    , m_background(m_text.computeVisiblePosition(), m_text.computeVisibleEndPosition(), backgroundColor)
{} // BgText()

void BgText::draw(MinGL& window) const
{
    // Affiche le fond puis le texte
    window << m_background << m_text;
} // draw()
