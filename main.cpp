#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"
#include "Enemigo.h"
#include "Esqueleto_1.h"
#include "Esqueleto_2.h"
#include "Minotauro.h"
#include "Jefe_Final.h"
#include "Mapa.h"
#include "Colisionable.h"
#include "item.h"

bool isInRoom(const sf::Vector2f& position, const sf::FloatRect& roomBounds)
{
    return roomBounds.contains(position);
}
bool isInRoom_music(const sf::Vector2f& position, const sf::FloatRect& roomBounds)
{
    return roomBounds.contains(position);
}

int main()
{
    ///Inicializacion de la ventana
    sf::RenderWindow window(sf::VideoMode(1000, 600), "The Chained Dungeon");
    window.setFramerateLimit(60);

    bool _play=true;


    //Game loop
    while (window.isOpen())
    {
        ///CABALLERO
        Personaje caballero;

        ///DECLARACION DE LOS VECTORES PARA LAS POSICIONES DE LOS ENEMIGOS
        sf::Vector2f posicion_valida;
        sf::Vector2f vectorPosicionesEsqueletos[13];
        sf::Vector2f vectorPosicionesEsqueletos_2[13];
        sf::Vector2f vectorPosicionMiniboss[1];
        sf::Vector2f vectorPosicionfinalboss[1];

        ///ESQUELETO 1
        std::vector<Esqueleto_1> esqueletos;

        ///ESQUELETO 2
        std::vector<Esqueleto_2> esqueletos_2;

        ///MINOTAURO
        Minotauro miniboss(6650, 3700);
        bool nivel_minotauro=false;
        bool nivel2_minotauro=false;
        bool nivel3_minotauro=false;

        ///JEFE FINAL
        Jefe_Final finalboss(9250, 5350);

        ///MANZANAS
        std::vector<Item> manzanas;
        manzanas.emplace_back(4110,715);
        manzanas.emplace_back(275,3850);
        manzanas.emplace_back(1930,3850);
        manzanas.emplace_back(3550, 3350);
        manzanas.emplace_back(7380, 3730);
        manzanas.emplace_back(7630, 3730);
        manzanas.emplace_back(7380, 3820);
        manzanas.emplace_back(7630, 3820);
        manzanas.emplace_back(9255, 4175);

        ///MAPA
        Mapa fondo;


        ///CAPA DE COLISIONES
        sf::Image imagen;
        imagen.loadFromFile("imagenes/Mapa/Capa_Colisiones.png");
        const sf::Color color=imagen.getPixel(1580,530);

        ///ESTATUAS
        sf::Texture estatuas;
        estatuas.loadFromFile("imagenes/Mapa/Estatuas.png");
        sf::Sprite estatuas_sprite;
        estatuas_sprite.setTexture(estatuas);

        ///VISTA
        sf::View vista(sf::FloatRect(1184, 268, 1000, 600));

        ///RADIO DE VISION
        sf::Texture RadioVision;
        RadioVision.loadFromFile("imagenes/Degradado/Radio_Vision.png");
        sf::Sprite Radio_Vision_sprite;
        Radio_Vision_sprite.setTexture(RadioVision);

        ///SALAS SPAWN
        std::map<std::string, sf::FloatRect> rooms =
        {
            {"sala1", sf::FloatRect(2765, 128, 770, 840)},
            {"sala2", sf::FloatRect(4065, 1155, 930, 835)},
            {"pasillo", sf::FloatRect(2236, 1152, 1475, 840)},
            {"sala3", sf::FloatRect(1441, 2337, 1000, 1060)},
            {"miniboss", sf::FloatRect(5632, 2912, 1215, 1183)},
            {"sala4", sf::FloatRect(8830, 3040, 870, 1000)},
            {"bossfinal", sf::FloatRect(8576, 4890, 1375, 709)}
        };
        bool b_r1=false, b_r2=false, b_ps=false, b_r3=false, b_mb=false, b_r4=false, b_fb=false;

        ///MUSICA
        sf::Music music;
        if (!music.openFromFile("OST/Gameplay_Song.wav"))
        {
            std::cerr << "Error al cargar el archivo de música" << std::endl;
            return -1;
        }
        music.setLoop(true);
        music.setVolume(1);
        music.play();

        std::map<std::string, sf::FloatRect> rooms_music =
        {
            {"miniboss", sf::FloatRect(5632, 2912, 1215, 1183)},
            {"bossfinal", sf::FloatRect(8576, 4890, 1375, 709)}
        };
        std::string currentRoomMusic = "gameplay";
        std::map<std::string, std::string> roomMusic =
        {
            {"gameplay", "OST/Gameplay_Song.wav"},
            {"miniboss", "OST/Minotauro_Song.wav"},
            {"bossfinal", "OST/FinalBoss_Song.wav"}
        };

        int esqueletos_muertos=0;

        bool lvl_up=false;
        sf::Clock lvlUpClock;
        //ReadInput (Act los estados de los perifericos de entrada)
        //Leer la cola de mensajes

        while(_play)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            ///CMD
            caballero.cmd();

            ///Update
            if(!caballero.isDead())
            {
                if(esqueletos_muertos==3)
                {
                    lvl_up=true;
                    caballero.aumentar_stats();
                    esqueletos_muertos=0;

                }
                else if(esqueletos_muertos>3)
                {
                    lvl_up=true;
                    caballero.aumentar_stats();
                    esqueletos_muertos-=3;
                }
                caballero.aumentarXp(esqueletos_muertos);
                caballero.update();

            }
            else
            {
                _play=false;
            }

            ///COMPROBAR COLISIONES DEL CABALLERO CON EL MAPA Y ENEMIGOS
            bool colisionDetectada = false;
            sf::Vector2f posicion_caballero = caballero.returnPosition();
            sf::FloatRect hitbox = caballero.getHitbox();
            for (int x = hitbox.left; x < hitbox.left + hitbox.width; ++x)
            {
                for (int y = hitbox.top; y < hitbox.top + hitbox.height; ++y)
                {

                    if (color==imagen.getPixel(x,y))
                    {
                        caballero.colision_mapa(posicion_valida);
                        colisionDetectada = true;
                        break;
                    }
                }
                if (colisionDetectada)
                {
                    break;
                }
            }
            if (!colisionDetectada)
            {
                posicion_valida = posicion_caballero;
            }

            ///DETERMINAR LA HABITACION PARA SPAWNEAR NPCS
            int contador_salas=0;
            for (const auto& room : rooms)
            {
                if(isInRoom(posicion_caballero, room.second))
                {
                    switch(contador_salas)
                    {
                    case 3:
                        if(!b_r1)
                        {
                            esqueletos.emplace_back(3200, 650);
                            esqueletos.emplace_back(3330, 800);
                            esqueletos.emplace_back(3450, 650);
                            b_r1=true;
                        }
                        break;
                    case 4:
                        if(!b_r2)
                        {
                            esqueletos.emplace_back(4205, 1650);
                            esqueletos.emplace_back(4850, 1650);
                            esqueletos.emplace_back(4205, 1860);
                            esqueletos.emplace_back(4850, 1860);
                            esqueletos_2.emplace_back(4525, 1710);
                            b_r2=true;
                        }
                        break;
                    case 2:
                        if(!b_ps)
                        {
                            esqueletos.emplace_back(3280, 1750);
                            esqueletos.emplace_back(2530, 1750);
                            b_ps=true;
                        }
                        break;
                    case 5:
                        if(!b_r3)
                        {
                            esqueletos.emplace_back(1580, 2890);
                            esqueletos.emplace_back(2285, 2890);
                            esqueletos.emplace_back(1580, 3250);
                            esqueletos.emplace_back(2285, 3250);
                            esqueletos_2.emplace_back(1545, 2890);
                            esqueletos_2.emplace_back(2320, 2890);
                            esqueletos_2.emplace_back(1545, 3250);
                            esqueletos_2.emplace_back(2320, 3250);
                            b_r3=true;
                        }
                        break;
                    case 6:
                        if(!b_r4)
                        {
                            esqueletos_2.emplace_back(9040, 3780);
                            esqueletos_2.emplace_back(9075, 3780);
                            esqueletos_2.emplace_back(9415, 3780);
                            esqueletos_2.emplace_back(9450, 3780);
                            esqueletos_2.emplace_back(8890, 3950);
                            esqueletos_2.emplace_back(8925, 3950);
                            esqueletos_2.emplace_back(9540, 3950);
                            esqueletos_2.emplace_back(9575, 3950);
                            b_r4=true;
                        }
                        break;
                    }
                }
                contador_salas++;
            }

            //COLISION CON ESQUELETOS TIPO 1
            for (auto& esqueleto : esqueletos)
            {
                if(caballero.hayColision(esqueleto))
                {
                    if(esqueleto.getFrameAttack())
                    {
                        caballero.disminuirVida(esqueleto.getDanio());
                    }
                    if(caballero.getFrameAttack())
                    {
                        esqueleto.disminuir_vida(caballero.getDanio());
                    }
                }
            }

            //COLISION CON ESQUELETOS TIPO 2
            for (auto& esqueleto_2 : esqueletos_2)
            {
                if(caballero.hayColision(esqueleto_2))
                {
                    if(esqueleto_2.getFrameAttack())
                    {
                        caballero.disminuirVida(esqueleto_2.getDanio());
                    }
                    if(caballero.getFrameAttack())
                    {
                        esqueleto_2.disminuir_vida(caballero.getDanio());
                    }
                }
            }

            //COLISION CON MINOTAURO
            if(caballero.hayColision(miniboss))
            {
                if(miniboss.getFrameAttack())
                {
                    caballero.disminuirVida(miniboss.getDanio());
                }
                if(caballero.getFrameAttack())
                {
                    miniboss.disminuir_vida(caballero.getDanio());
                }
            }

            //COLISION CON JEFE FINAL
            if(caballero.hayColision(finalboss))
            {
                if(finalboss.getFrameAttack())
                {
                    caballero.disminuirVida(finalboss.getDanio());
                }
                if(caballero.getFrameAttack())
                {
                    finalboss.disminuir_vida(caballero.getDanio());
                }
            }

            //COLISION CON MANZANAS
            for (auto m = manzanas.begin(); m != manzanas.end(); )
            {
                if (caballero.hayColision(*m))
                {
                    caballero.aumentarVida(m->getVida());
                    m = manzanas.erase(m);
                }
                else
                {
                    ++m;
                }
            }

            ///DETERMINAR LA HABITACION DEL CABALLERO Y ACTUALIZAR LA MUSICA
            std::string newRoomMusic = "gameplay";
            for (const auto& room_music : rooms_music)
            {
                if (isInRoom_music(posicion_caballero, room_music.second))
                {
                    newRoomMusic = room_music.first;
                    break;
                }
            }
            if (newRoomMusic != currentRoomMusic)
            {
                currentRoomMusic = newRoomMusic;
                if (!music.openFromFile(roomMusic[currentRoomMusic]))
                {
                    std::cerr << "Error al cargar el archivo de música" << std::endl;
                }
                else
                {
                    music.play();
                }
            }

            ///ACTUALIZAR LA VISTA
            window.setView(vista);
            vista.setCenter(caballero.returnPosition());
            Radio_Vision_sprite.setPosition(vista.getCenter().x - vista.getSize().x / 2,vista.getCenter().y - vista.getSize().y/ 2);
            window.clear();

            ///DRAW
            window.draw(fondo);
            window.draw(caballero);

            //DIBUJAR MANZANAS
            for(auto& manzana : manzanas)
            {
                manzana.update();
                window.draw(manzana);
            }

            //DIBUJAR ESQUELETOS TIPO 1
            int pos = 0;
            for (auto i = esqueletos.begin(); i != esqueletos.end(); )
            {
                if(pos>13)
                {
                    pos=0;
                }
                if (!i->isDead())
                {
                    bool colisionEsqueleto = false;
                    i->update({posicion_caballero.x, posicion_caballero.y-5});
                    sf::Vector2f posicion_esqueleto = i->returnPosition();
                    sf::FloatRect hitbox_esqueleto = i->getHitbox();
                    for (int x = hitbox_esqueleto.left; x < hitbox_esqueleto.left + hitbox_esqueleto.width; ++x)
                    {
                        for (int y = hitbox_esqueleto.top; y < hitbox_esqueleto.top + hitbox_esqueleto.height; ++y)
                        {

                            if (color==imagen.getPixel(x,y))
                            {
                                i->colision_mapa(vectorPosicionesEsqueletos,pos);
                                colisionEsqueleto = true;
                                break;
                            }
                        }
                        if (colisionEsqueleto)
                        {
                            break;
                        }
                    }
                    if (!colisionEsqueleto)
                    {
                        vectorPosicionesEsqueletos[pos]=posicion_esqueleto;
                    }
                    window.draw(*i);
                    ++i;  // Avanzar al siguiente esqueleto
                }
                else
                {
                    // Si el esqueleto está muerto, eliminarlo del vector
                    esqueletos_muertos++;
                    i = esqueletos.erase(i);
                }
                pos++;
            }

            //DIBUJAR ESQUELETOS TIPO 2
            int pos_2=0;
            for (auto i = esqueletos_2.begin(); i != esqueletos_2.end(); )
            {
                if(pos_2>13)
                {
                    pos_2=0;
                }
                if (!i->isDead())
                {
                    bool colisionEsqueleto_2 = false;
                    i->update({posicion_caballero.x, posicion_caballero.y-5});
                    sf::Vector2f posicion_esqueleto_2 = i->returnPosition();
                    sf::FloatRect hitbox_esqueleto_2 = i->getHitbox();
                    for (int x = hitbox_esqueleto_2.left; x < hitbox_esqueleto_2.left + hitbox_esqueleto_2.width; ++x)
                    {
                        for (int y = hitbox_esqueleto_2.top; y < hitbox_esqueleto_2.top + hitbox_esqueleto_2.height; ++y)
                        {

                            if (color==imagen.getPixel(x,y))
                            {
                                i->colision_mapa(vectorPosicionesEsqueletos_2,pos_2);
                                colisionEsqueleto_2 = true;
                                break;
                            }
                        }
                        if (colisionEsqueleto_2)
                        {
                            break;
                        }
                    }
                    if (!colisionEsqueleto_2)
                    {
                        vectorPosicionesEsqueletos_2[pos_2]=posicion_esqueleto_2;
                    }
                    window.draw(*i);
                    ++i;  // Avanzar al siguiente esqueleto
                }
                else
                {
                    // Si el esqueleto está muerto, eliminarlo del vector
                    esqueletos_muertos+=2;
                    i = esqueletos_2.erase(i);
                }
                pos_2++;
            }


            //DIBUJAR MINI BOSS
            if (!miniboss.isDead())
            {
                bool colisionMiniboss = false;
                miniboss.update({posicion_caballero.x, posicion_caballero.y-25});
                sf::Vector2f posicion_miniboss = miniboss.returnPosition();
                sf::FloatRect hitbox_miniboss = miniboss.getHitbox();
                for (int x = hitbox_miniboss.left; x < hitbox_miniboss.left + hitbox_miniboss.width; ++x)
                {
                    for (int y = hitbox_miniboss.top; y < hitbox_miniboss.top + hitbox_miniboss.height; ++y)
                    {

                        if (color==imagen.getPixel(x,y))
                        {
                            miniboss.colision_mapa(vectorPosicionMiniboss,0);
                            colisionMiniboss = true;
                            break;
                        }
                    }
                    if (colisionMiniboss)
                    {
                        break;
                    }
                }
                if (!colisionMiniboss)
                {
                    vectorPosicionMiniboss[0]=posicion_miniboss;
                }
                window.draw(miniboss);
            }
            else
            {
                if(nivel3_minotauro)
                {
                    esqueletos_muertos+=3;
                    nivel3_minotauro=false;
                }
                if(nivel2_minotauro)
                {
                    esqueletos_muertos+=3;
                    nivel2_minotauro=false;
                    nivel_minotauro=true;
                    nivel3_minotauro=true;
                }
                if(!nivel_minotauro)
                {
                    esqueletos_muertos+=3;
                    nivel2_minotauro=true;
                }
            }

            //DIBUJAR BOSS
            if (!finalboss.isDead())
            {
                bool colisionfinalboss = false;
                finalboss.update({posicion_caballero.x, posicion_caballero.y-5});
                sf::Vector2f posicion_finalboss = finalboss.returnPosition();
                sf::FloatRect hitbox_finalboss = finalboss.getHitbox();
                for (int x = hitbox_finalboss.left; x < hitbox_finalboss.left + hitbox_finalboss.width; ++x)
                {
                    for (int y = hitbox_finalboss.top; y < hitbox_finalboss.top + hitbox_finalboss.height; ++y)
                    {

                        if (color==imagen.getPixel(x,y))
                        {
                            finalboss.colision_mapa(vectorPosicionfinalboss,0);
                            colisionfinalboss = true;
                            break;
                        }
                    }
                    if (colisionfinalboss)
                    {
                        break;
                    }
                }
                if (!colisionfinalboss)
                {
                    vectorPosicionfinalboss[0]=posicion_finalboss;
                }
                window.draw(finalboss);
            }

            window.draw(estatuas_sprite);
            Radio_Vision_sprite.setPosition(caballero.returnPosition().x - 1020 / 2,caballero.returnPosition().y - 612 / 2); ///EL GOAT EL CABRA);
            window.draw(Radio_Vision_sprite);
            window.draw(caballero.getBarraVidaBorde());
            window.draw(caballero.getBarraVidaFondo());
            window.draw(caballero.getBarraVidaFrente());
            window.draw(caballero.getBarraXpBorde());
            window.draw(caballero.getBarraXpFondo());
            window.draw(caballero.getBarraXpFrente());
            window.draw(caballero.getTextVida());
            window.draw(caballero.getTextXp());
            if (lvl_up)
            {
                sf::Time elapsed = lvlUpClock.getElapsedTime();
                if (elapsed.asSeconds() < 15)
                {
                        sf::Font _font_lv;
                        sf::Text _text_lv;
                        _font_lv.loadFromFile("Roboto-Regular.ttf");
                        _text_lv.setFont(_font_lv);
                        _text_lv.setFillColor(sf::Color::Magenta);
                        _text_lv.setCharacterSize(50);
                        _text_lv.setString("¡Has subido de nivel!");
                        _text_lv.setPosition({posicion_caballero.x-200, posicion_caballero.y+150});
                        window.draw(_text_lv);
                }
                else
                {
                    lvl_up = false;
                    lvlUpClock.restart();
                }
            }
            ///Display
            window.display();
        }





        while(!_play)
        {
            sf::View new_vista(sf::FloatRect(0, 0, 1000, 600));
            window.setView(new_vista);
            music.stop();
            sf::Font font;
            font.loadFromFile("Roboto-Regular.ttf");
            sf::Text text;
            text.setFont(font);
            text.setFillColor(sf::Color::White);
            text.setCharacterSize(40);
            text.setPosition(120, 280);
            text.setString("Has muerto. Presione Espacio para reiniciar");
            window.clear(sf::Color::Black);
            window.draw(text);
            window.display();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                _play=true;
            }
        }
    }
    return 0;
}
