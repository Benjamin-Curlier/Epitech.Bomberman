/*
** main.cpp for cpp_bomberman in /home/camila/rendu/cpp_bomberman
**
** Made by 
** Login  <@epitech.eu>
**
** Started on  lun. mai 18 19:49:12 2015 
// Last update Sun Jun 14 20:55:11 2015 Océane Adamowski
*/

#include <unistd.h>
#include <cstdlib>
#include "GameEngine.hpp"
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <SFML/Audio.hpp>

int main(void)
{
  sf::SoundBuffer Buffer;
  if (!Buffer.loadFromFile("./Textures/sic2.wav"))
    std::cout << "ERROR!" << std::endl;
  sf::Sound Sound(Buffer);
  Sound.play();

  GameEngine engine;
  if (engine.initialize() == false)
    return (EXIT_FAILURE);

  while (engine.updatemenu() == true)
  {
    usleep(50);
    engine.draw();
    Sound.getStatus();
  }
  engine.InitGame();
  while (engine.update() == true)
  {
    usleep(50);
    engine.draw();
  }
  return EXIT_SUCCESS;
}
