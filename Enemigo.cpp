#include "Enemigo.h"
#include <iostream>
Enemigo::Enemigo(const char* archivoTextura, sf::Vector2f vel, int h, int d)
{
    _health=h;
    _velocity=vel;
    _damage=d;
    _texture.loadFromFile(archivoTextura);
    _sprite.setTexture(_texture);
}
void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    target.draw(_hitbox, states);
}
sf::FloatRect Enemigo::getBounds()const
{
    return _sprite.getGlobalBounds();

}
