#include "Item.h"
#include <iostream>

Item::Item(float x, float y)
{
    _sprite.setPosition(x, y);
    _sprite.setScale(0.15,0.15);
    _vida=30;
}

int Item::getVida()
{
    return _vida;
}

void Item::update()
{
    _texture.loadFromFile("imagenes/Sprites/Manzana/Manzana.png");
    _sprite.setTexture(_texture);
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
sf::FloatRect Item::getBounds() const
{
    return _sprite.getGlobalBounds();
}
