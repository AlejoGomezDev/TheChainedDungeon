#ifndef ITEM_H
#define ITEM_H
#include "Colisionable.h"
#include <SFML/Graphics.hpp>

class Item: public sf::Drawable, public Colisionable
{
protected:
    sf::Texture _texture;
    sf::Sprite _sprite;
    int _vida;
public:
    Item(float x, float y);
    int getVida();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
};
#endif // ITEM_H
