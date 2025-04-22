#include "Colisionable.h"
bool Colisionable::hayColision(Colisionable &obj)const
{
    return getBounds().intersects(obj.getBounds());
}
