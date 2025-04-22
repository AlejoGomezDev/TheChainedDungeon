#ifndef COLISIONABLE_H
#define COLISIONABLE_H
#include <SFML/Graphics.hpp>

class Colisionable
{
public:
    virtual sf::FloatRect getBounds() const=0;
    bool hayColision(Colisionable &obj)const;
};

#endif // COLISIONABLE_H
