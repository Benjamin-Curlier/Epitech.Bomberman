/*
** GameEngine.cpp for cpp_bomberman in /home/camila/rendu/cpp_bomberman
**
** Made by 
** Login  <@epitech.eu>
**
** Started on  lun. mai 18 19:48:08 2015 
** Last update dim. juin 14 21:00:59 2015 
*/

#pragma once

#include "AObject.hpp"
#include "Player_2.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Wall.hpp"
#include "Bonus.hpp"
#include "Cube.hpp"
#include <SFML/Audio.hpp>

class GameEngine : public gdl::Game
{
public:
	GameEngine() {}

	bool initialize() {
    if (!_context.start(1920, 1080, "My bomberman!")) // on cree une fenetre
    	return false;
    glEnable(GL_DEPTH_TEST);
    if (!_shader.load("LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER)
    	|| !_shader.load("LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER)
	|| !_shader.build()) // il faut ensuite compiler son shader
    	return false;

    glm::mat4 projection;
    glm::mat4 transformation;
    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    transformation = glm::lookAt(glm::vec3(0, 20, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); //10
    _shader.bind();
    _shader.setUniform("view", transformation);
    _shader.setUniform("projection", projection);
    CreateMenu();
    //CreateMap(10, 10);
    return true;
}

bool update() {
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
		return false;
	_context.updateClock(_clock);
	_context.updateInputs(_input);
	bool a = false;
	for (size_t i = 0; i < _objects.size(); ++i)
	{
	  if (_objects[i]->getId() == 1)
	    a = true;
		if (_objects[i]->isAlive())
			_objects[i]->update(_clock, _input);
		else
		{
			if (_objects[i]->getId() == 2)
				explosion(i);
			_objects.erase(_objects.begin() + i);
		}
	}
	if (a == false)
	  GameOver();
	return true;
}

bool updatemenu() {
	if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
		exit(EXIT_SUCCESS);
	_context.updateClock(_clock);
	_context.updateInputs(_input);
	for (size_t i = 0; i < _objects.size(); ++i)
	{
		_objects[i]->update(_clock, _input);
		if (_objects[i]->getNbr() == 1)
			return false;
		if (_objects[i]->getNbr() == 2)
			exit(EXIT_SUCCESS);
	}
	return true;
}

int xrandom(int i)
{
	struct timeval usec;

	gettimeofday(&usec, NULL);
	srand((long int)usec.tv_usec);
	return (random() % i);
}

void explosion(int i)
{
	AObject *bonus;
	Flame *flame = new Flame(_objects[i]->getPos().x, _objects[i]->getPos().y,_objects[i]->getPos().z, true, &_objects);
	Flame *secondflame = new Flame(_objects[i]->getPos().x, _objects[i]->getPos().y,_objects[i]->getPos().z, false, &_objects);
	flame->initialize();
	secondflame->initialize();
	_objects.push_back(flame);
	_objects.push_back(secondflame);
	float w;
	int a = 0;
	std::vector<bool> _mesbools;
	_mesbools.push_back(true);
	_mesbools.push_back(true);
	_mesbools.push_back(true);
	_mesbools.push_back(true);
	for (w = 1; w <= _objects[i]->getEx(); w++)
	{
		if (_mesbools[0] == true)
		{
			Flame *flame1 = new Flame(_objects[i]->getPos().x + w / 2, _objects[i]->getPos().y,_objects[i]->getPos().z, false, &_objects);
			flame1->initialize();
			int v;
			while ((v = flame1->collision()) != -1 && _mesbools[0] == true)
			{
				_mesbools[0] = false;
				if (_objects[v]->getId() == 0)
					break;
				else if (_objects[v]->getId() == 2)
					_objects[v]->setLife(false);
				else
				{
					if (_objects[v]->getId() == 4 && (a = xrandom(7)) > 3)
					{
						if (a == 4)
							bonus = new Bonus(_objects[v]->getPos(), 10);
						else if (a == 5)
							bonus = new Bonus(_objects[v]->getPos(), 11);
						else
							bonus = new Bonus(_objects[v]->getPos(), 12);
					}
					delete *(_objects.begin() + v);
					_objects.erase(_objects.begin() + v);
					if (a > 3)
					{
						bonus->initialize();
						_objects.push_back(bonus);
					}
				}
			}
			_objects.push_back(flame1);
		}
		if (_mesbools[1] == true)
		{
			Flame *flame2 = new Flame(_objects[i]->getPos().x - w / 2, _objects[i]->getPos().y,_objects[i]->getPos().z, false, &_objects);
			flame2->initialize();
			int v;
			while ((v = flame2->collision()) != -1 && _mesbools[1] == true)
			{
				_mesbools[1] = false;
				if (_objects[v]->getId() == 0)
					break;
				else if (_objects[v]->getId() == 2)
					_objects[v]->setLife(false);
				else
				{
					if (_objects[v]->getId() == 4)
					{
						a = xrandom(7);
						if (a == 4)
							bonus = new Bonus(_objects[v]->getPos(), 10);
						else if (a == 5)
							bonus = new Bonus(_objects[v]->getPos(), 11);
						else
							bonus = new Bonus(_objects[v]->getPos(), 12);
					}
					delete *(_objects.begin() + v);
					_objects.erase(_objects.begin() + v);
					if (a > 3)
					{
						bonus->initialize();
						_objects.push_back(bonus);
					}
				}
			}
			_objects.push_back(flame2);
		}
		if (_mesbools[2] == true)
		{
			Flame *flame3 = new Flame(_objects[i]->getPos().x, _objects[i]->getPos().y,_objects[i]->getPos().z + w / 2, true, &_objects);
			flame3->initialize();
			int v;
			while ((v = flame3->collision()) != -1 && _mesbools[2] == true)
			{
				_mesbools[2] = false;
				if (_objects[v]->getId() == 0)
					break;
				if (_objects[v]->getId() == 2)
					_objects[v]->setLife(false);
				else
				{
					if (_objects[v]->getId() == 4)
					{
						a = xrandom(7);
						if (a == 4)
							bonus = new Bonus(_objects[v]->getPos(), 10);
						else if (a == 5)
							bonus = new Bonus(_objects[v]->getPos(), 11);
						else
							bonus = new Bonus(_objects[v]->getPos(), 12);
					}
					delete *(_objects.begin() + v);
					_objects.erase(_objects.begin() + v);
					if (a > 3)
					{
						bonus->initialize();
						_objects.push_back(bonus);
					}
				}
			}
			_objects.push_back(flame3);
		}
		if (_mesbools[3] == true)
		{
			Flame *flame4 = new Flame(_objects[i]->getPos().x, _objects[i]->getPos().y,_objects[i]->getPos().z - w / 2, true, &_objects);
			flame4->initialize();
			int v;
			while ((v = flame4->collision()) != -1 && _mesbools[3] == true)
			{
				_mesbools[3] = false;
				if (_objects[v]->getId() == 0)
					break;
				else if (_objects[v]->getId() == 2)
					_objects[v]->setLife(false);
				else
				{
					if (_objects[v]->getId() == 4)
					{
						a = xrandom(7);
						if (a == 4)
							bonus = new Bonus(_objects[v]->getPos(), 10);
						else if (a == 5)
							bonus = new Bonus(_objects[v]->getPos(), 11);
						else
							bonus = new Bonus(_objects[v]->getPos(), 12);
					}
					delete *(_objects.begin() + v);
					_objects.erase(_objects.begin() + v);
					if (a > 3)
					{
						bonus->initialize();
						_objects.push_back(bonus);
					}
				}
			}
			_objects.push_back(flame4);
		}
	}
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.bind();
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->draw(_shader, _clock);
	_context.flush();
}

void	put_wall(float xmax, float zmax)
{
	AObject *wall;
	
	int x;
	int z;
	for (z = zmax / 2 - 1; z >= -(zmax / 2 - 1); z--)
	{
		if (z == (zmax / 2 - 1) || z == -(zmax / 2 - 1))
		{
			for (x = xmax / 2 - 3; x >= -(xmax / 2 - 3); x--)
			{
				wall = new Wall(x, 0, z);
				wall->initialize();
				_objects.push_back(wall);
			}
		}
		else if (z == (zmax / 2 - 2) || z == -(zmax / 2 - 2))
		{
			for (x = xmax / 2 - 2; x >= -(xmax / 2 - 2); x--)
			{
				if (x % 2 != 0)
				{
					wall = new Wall(x, 0, z);
					wall->initialize();
					_objects.push_back(wall);
				}
			}
		}
		else
		{
			for (x = xmax / 2 - 1; x >= -(xmax / 2 - 1); x--)
			{
				if (z % 2 != 0)
				{
					if (x % 2 == 0)
					{
						wall = new Wall(x, 0, z);
						wall->initialize();
						_objects.push_back(wall);
					}
				}
				else
				{
					wall = new Wall(x, 0, z);
					wall->initialize();
					_objects.push_back(wall);
				}
			}
		}
	}

	for (z = zmax / 2 - 1; z >= -(zmax / 2 - 1); z--)
	{
		if (z == (zmax / 2 - 1) || z == -(zmax / 2 - 1))
		{
		}
		else if (z == (zmax / 2 - 2) || z == -(zmax / 2 - 2))
		{
			for (x = xmax / 2 - 2; x >= -(xmax / 2 - 2); x--)
			{
				if (x % 2 == 0)
				{
					wall = new Unbreakable_wall(x, z,1,1);
					wall->initialize();
					_objects.push_back(wall);
				}
			}
		}
		else
		{
			for (x = xmax / 2 - 1; x >= -(xmax / 2 - 1); x--)
			{
				if (z % 2 != 0)
				{
					if (x % 2 != 0)
					{
						wall = new Unbreakable_wall(x, z,1,1);
						wall->initialize();
						_objects.push_back(wall);
					}
				}
			}
		}
	}	
}

bool CreateMap(int x, int z) 
{
	AObject *menu = new OnlyCube(true, glm::vec3(0, 0, 0), glm::vec3(50, 50, 50), glm::vec3(-30, 0, 0), "./Textures/blue.tga");
	_objects.push_back(menu);
	menu->initialize();
	AObject *sol = new Sol(x, z);
	_objects.push_back(sol);
	sol->initialize();
	AObject *unbreakable_wall = new Unbreakable_wall(x / 2, 0, 1, z + 1);
	_objects.push_back(unbreakable_wall);
	unbreakable_wall->initialize();
	unbreakable_wall = new Unbreakable_wall((x / 2) * -1, 0, 1, z + 1);
	_objects.push_back(unbreakable_wall);
	unbreakable_wall->initialize();
	unbreakable_wall = new Unbreakable_wall(0, z / 2, x - 1, 1);
	_objects.push_back(unbreakable_wall);
	unbreakable_wall->initialize();
	unbreakable_wall = new Unbreakable_wall(0, (z / 2) * - 1, x - 1, 1);
	_objects.push_back(unbreakable_wall);
	unbreakable_wall->initialize();

	put_wall(x, z);

	AObject *player = new Player(&_objects, x / 2 - 1 , z / 2 - 1);
	player->initialize();
	_objects.push_back(player);
	AObject *player2 = new Player2(&_objects, -(x / 2 - 1) , -(z / 2 - 1));
	player2->initialize();
	_objects.push_back(player2);
}

bool CreateMenu()
{
	AObject *menu = new OnlyCube(true, glm::vec3(0, -0.5, 0), glm::vec3(15, 15, 15), glm::vec3(0, 90, 0), "./Textures/bomber.tga");
	_objects.push_back(menu);
	menu->initialize();
	AObject *cube = new LittleMovingCube(glm::vec3(4, 10, 0));
	_objects.push_back(cube);
	cube->initialize();
}

void GameOver() {
   int j;
   j = _objects.size();
  for (size_t i = 0; i < j; ++i)
  {
    delete _objects[i];
    _objects.pop_back();
  }
   AObject *menu = new OnlyCube(true, glm::vec3(0, -0.5, 0), glm::vec3(15, 15, 15), glm::vec3(-30, 90, 0), "./Textures/gameover.tga");
  _objects.push_back(menu);
  menu->initialize();
 }

void InitGame() {
	int j;
	j = _objects.size();
	for (size_t i = 0; i < j; ++i)
	{
		delete _objects[i];
		_objects.pop_back();
	}
	CreateMap(10, 10);}

	~GameEngine() {
		for (size_t i = 0; i < _objects.size(); ++i)
			delete _objects[i];
	}

private:
	gdl::SdlContext _context;
	gdl::Clock _clock;
	gdl::Input _input;
	gdl::BasicShader _shader;
	std::vector<AObject *> _objects;
};

