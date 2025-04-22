#include "Mapa.h"
#include <iostream>
Mapa::Mapa()
{
    _texture.loadFromFile("imagenes/Mapa/Mapa.png");
    _sprite.setTexture(_texture);
}

void Mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}



