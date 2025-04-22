#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED
#include <SFML/Graphics.hpp>
class Mapa: public sf::Drawable
{
    sf::Sprite _sprite;
    sf::Texture _texture;
public:
    Mapa();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // MAPA_H_INCLUDED
