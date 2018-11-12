/*
** test.cpp for Music in /home/camila/Music
**
** Made by 
** Login  <@epitech.eu>
**
** Started on  dim. juin 14 20:11:35 2015 
// Last update Sun Jun 14 20:35:10 2015 Océane Adamowski
*/

#include <iostream>
#include <SFML/Audio.hpp>

void playSound()
{
  sf::SoundBuffer Buffer;
  if (!Buffer.loadFromFile("Spintronic_-_Firecrackers_Niveau_1_.wav"))
    std::cout << "ERROR!" << std::endl;
  sf::Sound Sound(Buffer);
  Sound.play();

  while (Sound.getStatus() == sf::Sound::Playing)
;
}

int main()
{
  playSound();
  std::cout << "Done" << std::endl;
  return EXIT_SUCCESS;
}
