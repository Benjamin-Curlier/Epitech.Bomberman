/*
** Player.cpp for cpp_bomberman in /home/camila/Music/cpp_bomberman
**
** Made by 
** Login  <@epitech.eu>
**
** Started on  dim. juin 14 19:49:03 2015 
// Last update Sun Jun 14 20:19:56 2015 Océane Adamowski
*/

#include "AObject.hpp"
#include "Bomb.hpp"

class Player : public AObject
{

private:

  float _speed;
  gdl::Model _model;
  std::vector<AObject *> *_objects;
  clock_t _time;
  char _bombpack = 1;
  char _bombpackmax = 1;
  bool _test = false;

public:

  Player(std::vector<AObject *> *objects, int x, int z)
  {
    _objects = objects;
    _position.x = x;
    _position.y = -0.25;
    _position.z = z;
    _id = 1;
    _speed = 3.0f;
  };

  virtual ~Player() { }

  virtual bool initialize()
  {
    this->scale(glm::vec3(0.0015, 0.0015, 0.0015));
    if (_model.load("LibBomberman_linux_x64/assets/marvin.fbx") == false)
      {
	std::cerr << "Cannot load the model" << std::endl;
	return false;
      }
    if (_model.createSubAnim(0, "A1", 0, 20) == false)
      std::cout << "Error while cutting" << std::endl;  
    if (_model.createSubAnim(0, "A2", 40, 80) == false)
      std::cout << "Error while cutting" << std::endl;   
    if (_model.createSubAnim(0, "A3", 100, 130) == false)
      std::cout << "Error while cutting" << std::endl;    
   _model.setCurrentAnim(0);
    return (true);
  }

  virtual void update(gdl::Clock const &clockl, gdl::Input &input)
  {
    if (_test == true)
      {
	if ((((float)clock() - _time)/CLOCKS_PER_SEC) >= 1.5)
	  {
	    _bombpack = _bombpackmax;
	    _test = false;
	  }
      }
    if (input.getKey(SDLK_DOWN) && test_collid(glm::vec3(0, 0, -1) * static_cast<float>(clockl.getElapsed()) * _speed, 0) == false)
      {
	translate(glm::vec3(0, 0, -1) * static_cast<float>(clockl.getElapsed()) * _speed);
	test_collide_bonus();
	_rotation = glm::vec3(0, 180, 0);
	_direction = 0;
      }
    if (input.getKey(SDLK_UP) && test_collid(glm::vec3(0, 0, 1) * static_cast<float>(clockl.getElapsed()) * _speed, 1) == false)
      {
	translate(glm::vec3(0, 0, 1) * static_cast<float>(clockl.getElapsed()) * _speed);
	test_collide_bonus();
	_rotation = glm::vec3(0, 0, 0);
	_direction = 1;
      }
    if (input.getKey(SDLK_RIGHT) && test_collid(glm::vec3(-1, 0, 0) * static_cast<float>(clockl.getElapsed()) * _speed, 2) == false)
      {
	translate(glm::vec3(-1, 0, 0) * static_cast<float>(clockl.getElapsed()) * _speed);
	test_collide_bonus();
	_rotation = glm::vec3(0, -90, 0);
	_direction = 2;
      }
    if (input.getKey(SDLK_LEFT) && test_collid(glm::vec3(1, 0, 0) * static_cast<float>(clockl.getElapsed()) * _speed, 3) == false)
      {
	translate(glm::vec3(1, 0, 0) * static_cast<float>(clockl.getElapsed()) * _speed);
	test_collide_bonus();
	_rotation = glm::vec3(0, 90, 0);
	_direction = 3;
      }
    if (input.getKey(SDLK_SPACE))
      {
	if (test_collid_bomb() == false && _bombpack > 0)
	  {
	    _test = true;
	    _time = clock();
	    _bombpack--;
	    Bomb* bomb;
	    if (_direction == 0) 
	      bomb = new Bomb(_position + glm::vec3(0, 0, -0.6), _objects, _explosion);
	    if (_direction == 1) 
	      bomb = new Bomb(_position + glm::vec3(0, 0, 0.6), _objects, _explosion);
	    if (_direction == 2) 
	      bomb = new Bomb(_position + glm::vec3(-0.6, 0, 0), _objects, _explosion);
	    if (_direction == 3) 
	      bomb = new Bomb(_position + glm::vec3(0.6, 0, 0), _objects, _explosion);
	    if (bomb->initialize())
	      _objects->push_back(bomb);
	    else
	      delete bomb;
	  }
      }
  }
  
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock)
  {
    _model.draw(shader, getTransformation(), clock.getElapsed());
  }
  
  void test_collide_bonus()
  {
    int i = 0;
    for (auto it : *(this->_objects))
      {
	if (it->getId() > 9)
	  {
	    glm::vec3 a1 = _position + glm::vec3(0.3, 0, 0.3);
	    glm::vec3 b1 = _position + glm::vec3(0.3, 0, -0.3);
	    glm::vec3 c1 = _position + glm::vec3(-0.3, 0, 0.3);
	    glm::vec3 d1 = _position + glm::vec3(-0.3, 0, -0.3);
	    glm::vec3 a2 = it->getPos() + glm::vec3(it->getScal().x / 2, 0, it->getScal().z / 2);
	    glm::vec3 b2 = it->getPos() + glm::vec3(it->getScal().x / 2, 0, -it->getScal().z / 2);
	    glm::vec3 c2 = it->getPos() + glm::vec3(-it->getScal().x / 2, 0, it->getScal().z / 2);
	    glm::vec3 d2 = it->getPos() + glm::vec3(-it->getScal().x / 2, 0, -it->getScal().z / 2);
	    float rax1 = my_max4(a1.x, b1.x, c1.x, d1.x);
	    float rax2 = my_min4(a1.x, b1.x, c1.x, d1.x);
	    float raz1 = my_max4(a1.z, b1.z, c1.z, d1.z);
	    float raz2 = my_min4(a1.z, b1.z, c1.z, d1.z);
	    float rbx1 = my_max4(a2.x, b2.x, c2.x, d2.x);
	    float rbx2 = my_min4(a2.x, b2.x, c2.x, d2.x);
	    float rbz1 = my_max4(a2.z, b2.z, c2.z, d2.z);
	    float rbz2 = my_min4(a2.z, b2.z, c2.z, d2.z);
	    if (raz2 >= rbz1 || rax2 >= rbx1 || rax1 <= rbx2 || raz1 <= rbz2)
	      rax1 = rax1;
	    else
	      {
		if (it->getId() == 10)
		  _speed += 1;
		else if (it->getId() == 11)
		  _explosion += 1;
		else
		{
		  _bombpack += 1;
		  _bombpackmax += 1;
		}
		delete *(_objects->begin() + i);
		_objects->erase(_objects->begin() + i);
		return;
	      }
	  }
	i++;
      }
  }

  bool	test_collid_bomb()
  {
    glm::vec3 fpos;
    if (_direction == 0)
      fpos = _position + glm::vec3(0, 0, -0.6);
    if (_direction == 1)
      fpos = _position + glm::vec3(0, 0, 0.6);
    if (_direction == 2)
      fpos = _position + glm::vec3(-0.6, 0, 0);
    if (_direction == 3)
      fpos = _position + glm::vec3(0.6, 0, 0);
    for (auto it : *(this->_objects))
      if (it->getId() != this->_id && it->getSol() != true)
	{
	  glm::vec3 a1 = fpos + glm::vec3(0.25, 0, 0.25);
	  glm::vec3 b1 = fpos + glm::vec3(0.25, 0, -0.25);
	  glm::vec3 c1 = fpos + glm::vec3(-0.25, 0, 0.25);
	  glm::vec3 d1 = fpos + glm::vec3(-0.25, 0, -0.25);
	  glm::vec3 a2 = it->getPos() + glm::vec3(it->getScal().x / 2, 0, it->getScal().z / 2);
	  glm::vec3 b2 = it->getPos() + glm::vec3(it->getScal().x / 2, 0, -it->getScal().z / 2);
	  glm::vec3 c2 = it->getPos() + glm::vec3(-it->getScal().x / 2, 0, it->getScal().z / 2);
	  glm::vec3 d2 = it->getPos() + glm::vec3(-it->getScal().x / 2, 0, -it->getScal().z / 2);
	  float rax1 = my_max4(a1.x, b1.x, c1.x, d1.x);
	  float rax2 = my_min4(a1.x, b1.x, c1.x, d1.x);
	  float raz1 = my_max4(a1.z, b1.z, c1.z, d1.z);
	  float raz2 = my_min4(a1.z, b1.z, c1.z, d1.z);
	  float rbx1 = my_max4(a2.x, b2.x, c2.x, d2.x);
	  float rbx2 = my_min4(a2.x, b2.x, c2.x, d2.x);
	  float rbz1 = my_max4(a2.z, b2.z, c2.z, d2.z);
	  float rbz2 = my_min4(a2.z, b2.z, c2.z, d2.z);
	  if (raz2 >= rbz1 || rax2 >= rbx1 || rax1 <= rbx2 || raz1 <= rbz2)
	    rax1 = rax1;
	  else 	  
	    return true;
	}
    return false;
  }
  
  bool	test_collid(glm::vec3 const &test, char a)
  {
    glm::vec3 fpos = _position + test;
    for (auto it : *(this->_objects))
      if (it->getId() != this->_id && it->getSol() != true)
	{
	  glm::vec3 a1 = fpos + glm::vec3(0.3, 0, 0.3);
	  glm::vec3 b1 = fpos + glm::vec3(0.3, 0, -0.3);
	  glm::vec3 c1 = fpos + glm::vec3(-0.3, 0, 0.3);
	  glm::vec3 d1 = fpos + glm::vec3(-0.3, 0, -0.3);
	  glm::vec3 a2 = it->getPos() + glm::vec3(it->getScal().x / 2, 0, it->getScal().z / 2);
	  glm::vec3 b2 = it->getPos() + glm::vec3(it->getScal().x / 2, 0, -it->getScal().z / 2);
	  glm::vec3 c2 = it->getPos() + glm::vec3(-it->getScal().x / 2, 0, it->getScal().z / 2);
	  glm::vec3 d2 = it->getPos() + glm::vec3(-it->getScal().x / 2, 0, -it->getScal().z / 2);
	  float rax1 = my_max4(a1.x, b1.x, c1.x, d1.x);
	  float rax2 = my_min4(a1.x, b1.x, c1.x, d1.x);
	  float raz1 = my_max4(a1.z, b1.z, c1.z, d1.z);
	  float raz2 = my_min4(a1.z, b1.z, c1.z, d1.z);
	  float rbx1 = my_max4(a2.x, b2.x, c2.x, d2.x);
	  float rbx2 = my_min4(a2.x, b2.x, c2.x, d2.x);
	  float rbz1 = my_max4(a2.z, b2.z, c2.z, d2.z);
	  float rbz2 = my_min4(a2.z, b2.z, c2.z, d2.z);
	  if (raz2 >= rbz1 || rax2 >= rbx1 || rax1 <= rbx2 || raz1 <= rbz2)
	    rax1 = rax1;
	  else
	    {
	      if (it->getId() == 2)
		{
		  it->setIs_push(true);
		  it->setDir(a);
		}
	      return true;
	    }
	}
    return false;
  } 
};
