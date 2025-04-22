#include <iostream>
#include <cmath>
#include "Minotauro.h"

sf::Texture Minotauro::_texture;
Minotauro::Minotauro(float x, float y) : Enemigo("imagenes/Sprites/Minotauro/Minotauro.png", {1.8,1.8}, 600, 50)
{
    _sprite.setTextureRect({991, 654, 93, 78});
    _max_health=600;
    _health=_max_health;
    _attack=false;
    _dead=false;
    _primera_deteccion=false;
    _sprite.setPosition(x, y);
    _attack_frame=0;
    _dead_frame=0;
    _barraVidaFondo.setSize(sf::Vector2f(50, 5));
    _barraVidaFondo.setFillColor(sf::Color::Red);
    _barraVidaFrente.setSize(sf::Vector2f(50, 5));
    _barraVidaFrente.setFillColor(sf::Color::Green);
    configurar_Tam_Pos_Hitbox();
}
void Minotauro::configurar_Tam_Pos_Hitbox()
{
    float hitboxWidth = 30.0f;
    float hitboxHeight = 36.0f;
    _hitbox.setSize(sf::Vector2f(hitboxWidth,hitboxHeight));
    _hitbox.setFillColor(sf::Color::Red);
    updateHitboxPos();
}
void Minotauro::updateHitboxPos()
{
    sf::FloatRect hitbox_bounds = _sprite.getGlobalBounds();
    _hitbox.setPosition(hitbox_bounds.left+15, hitbox_bounds.top + 37);
}
void Minotauro::colision_mapa(sf::Vector2f vectorPosicionesEsqueletos[], int pos)
{
    _sprite.setPosition(vectorPosicionesEsqueletos[pos].x,vectorPosicionesEsqueletos[pos].y);
}
sf::Vector2f Minotauro::returnPosition()
{
    return _sprite.getPosition();
}
sf::FloatRect Minotauro::getHitbox()
{
    return _hitbox.getGlobalBounds();
}
int Minotauro::getDanio()
{
    if(_attack)
    {
        return _damage;
    }
}
bool Minotauro::getFrameAttack()
{
    return _attack;
}
void Minotauro::actualizarBarraVida()
{
    float porcentajeVida = static_cast<float>(_health) / _max_health;
    _barraVidaFrente.setSize(sf::Vector2f(50 * porcentajeVida, 5));
}
void Minotauro::disminuir_vida(int danio)
{
    _health -= danio;
    if(_health<0)
    {
        _health=0;
    }
    actualizarBarraVida();
}
bool Minotauro::detectar_jugador(sf::Vector2f posicion_jugador)
{
    sf::Vector2f distancia = _sprite.getPosition() - posicion_jugador;
    float distancia_total = std::sqrt(distancia.x * distancia.x + distancia.y * distancia.y);
    float rango_deteccion = 380.0f;
    if (distancia_total <= rango_deteccion)
    {
        return true;
    }
    return false;
}
bool Minotauro::isDead()
{
    return _dead;
}
void Minotauro::update(sf::Vector2f posicion_caballero)
{
    if(_health>0)
    {
        sf::Vector2f posicion = _sprite.getPosition();
        _barraVidaFondo.setPosition(posicion.x - 10, posicion.y - 10);
        _barraVidaFrente.setPosition(posicion.x - 10, posicion.y - 10);
        _attack=false;
        if (detectar_jugador(posicion_caballero))
        {
            _primera_deteccion=true;
            _sprite.setTextureRect({871, 23, 86, 86});
            _distancia = posicion_caballero - _sprite.getPosition();
            float magnitud = std::sqrt(_distancia.x * _distancia.x + _distancia.y * _distancia.y);

            // Distancia mínima antes de detener el esqueleto
            float distancia_minima = 5; // Ajusta esta distancia según sea necesario

            if (magnitud > distancia_minima)
            {
                _attack_frame = 0;
                if (magnitud != 0)
                {
                    _distancia /= magnitud;
                }
                _movePosition = sf::Vector2f(_distancia.x * _velocity.x, _distancia.y * _velocity.y);
                _sprite.setTextureRect({488, 23, 98, 98});
                if (_movePosition.x < 0)
                {
                    _sprite.setScale(1, 1);
                }
                else if (_movePosition.x > 0)
                {
                    _sprite.setScale(-1, 1);
                }
                _sprite.move(_movePosition);
            }
            else
            {
                _attack_frame += 0.1;
                if (_attack_frame >= 7 )
                {
                    _attack_frame = 0;
                    _attack = true;
                }
                switch((int)_attack_frame)
                {
                case 0:
                    _sprite.setTextureRect({ 369, 25, 93, 87});
                    break;
                case 1:
                    _sprite.setTextureRect({ 1, 145, 121, 96});
                    break;
                case 2:
                    _sprite.setTextureRect({ 122, 146, 123, 97});
                    break;
                case 3:
                    _sprite.setTextureRect({244, 149, 124, 97});
                    break;
                case 4:
                    _sprite.setTextureRect({ 388, 121, 88, 111});
                    break;
                case 5:
                    _sprite.setTextureRect({ 488, 123, 93, 113});
                    break;
                case 6:
                    _sprite.setTextureRect({ 610, 148, 93, 88});
                    break;
                }
                if (_movePosition.x < 0)
                {
                    _sprite.setScale(1, 1);
                }
                else if (_movePosition.x > 0)
                {
                    _sprite.setScale(-1, 1);
                }
            }
        }
        else
        {
            if(_primera_deteccion)
            {
                _sprite.setTextureRect({871, 23, 86, 86});
            }
        }
    }
    else
    {
        _attack=false;
        _dead_frame+=0.1;
        if(_dead_frame>=13)
        {
            _dead=true;
        }
        switch((int)_dead_frame)
        {
        case 0:
            _sprite.setTextureRect({254, 510, 90, 89});
            break;
        case 1:
            _sprite.setTextureRect({370, 514, 93, 87});
            break;
        case 2:
            _sprite.setTextureRect({254, 510, 90, 89});
            break;
        case 3:
            _sprite.setTextureRect({370, 514, 93, 87});
            break;
        case 4:
            _sprite.setTextureRect({4, 383, 99, 94});
            break;
        case 5:
            _sprite.setTextureRect({991, 655, 95, 78});
            break;
        }
    }
    updateHitboxPos();
}
void Minotauro::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    target.draw(_barraVidaFondo, states);
    target.draw(_barraVidaFrente, states);
}


