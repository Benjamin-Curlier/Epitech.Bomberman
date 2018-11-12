/*
** Bomb.hpp for cpp_bomberman in /home/camila/Music/cpp_bomberman
**
** Made by 
** Login  <@epitech.eu>
**
** Started on  dim. juin 14 19:54:47 2015 
** Last update dim. juin 14 19:55:28 2015 
*/

#ifndef BOMB_H_
# define BOMB_H_

#include "AObject.hpp"

class Bomb : public AObject
{
private:
  gdl::Texture _texture;
  gdl::Geometry _geometry;
  float _speed = 3;
  clock_t _time;
  std::vector<AObject *> *_objects;

public:
  Bomb(glm::vec3 position, std::vector<AObject *> *objects, int explosion) {
    _position = position;
    this->scale(glm::vec3(0.5, 0.5, 0.5));
    _time = clock();
    _objects = objects;
    _id = 2;
    _explosion = explosion;
  }
  virtual ~Bomb() { }
  virtual bool initialize()
  {
    if (_texture.load("./Textures/bomb.tga") == false)
      {
        std::cerr << "Cannot load the cube texture" << std::endl;
        return (false);
      }
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.setColor(glm::vec4(1, 1, 1, 1));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.build();
    return (true);
  }
  virtual void update(gdl::Clock const &clockl, gdl::Input &input)
  {
    if (_is_push == true)
      {
	if (_direction == 0)
	  {
	    if (test_collid2(glm::vec3(0, 0, -1) * static_cast<float>(clockl.getElapsed()) * _speed) == false)
	      translate(glm::vec3(0, 0, -1) * static_cast<float>(clockl.getElapsed()) * _speed);
	  }
	else if (_direction == 1)
	  {
	    if (test_collid2(glm::vec3(0, 0, 1) * static_cast<float>(clockl.getElapsed()) * _speed) == false)
	      translate(glm::vec3(0, 0, 1) * static_cast<float>(clockl.getElapsed()) * _speed);
	  }
	else if (_direction == 2)
	  {
	    if (test_collid2(glm::vec3(-1, 0, 0) * static_cast<float>(clockl.getElapsed()) * _speed) == false)
	      translate(glm::vec3(-1, 0, 0) * static_cast<float>(clockl.getElapsed()) * _speed);
	  }
	else if(_direction == 3)
	  {
	    if (test_collid2(glm::vec3(1, 0, 0) * static_cast<float>(clockl.getElapsed()) * _speed) == false)
	      translate(glm::vec3(1, 0, 0) * static_cast<float>(clockl.getElapsed()) * _speed);
	  }
	  }
    if ((((float)clock() - _time)/CLOCKS_PER_SEC) >= 1.5)
      this->_alive = false;
  }
  bool	test_collid2(glm::vec3 const &test)
  {
    glm::vec3 fpos = _position + test;
    for (auto it : *(this->_objects))
      if (it->getPos().x != this->_position.x && it->getPos().y != this->_position .y && it->getPos().z != this->_position.z && it->getSol() != true)
	{
	  glm::vec3 a1 = fpos + glm::vec3(this->getScal().x / 2, 0, this->getScal().z / 2);
	  glm::vec3 b1 = fpos + glm::vec3(this->getScal().x / 2, 0, -this->getScal().z / 2);
	  glm::vec3 c1 = fpos + glm::vec3(-this->getScal().x / 2, 0, this->getScal().z / 2);
	  glm::vec3 d1 = fpos + glm::vec3(-this->getScal().x / 2, 0, -this->getScal().z / 2);
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
	      _is_push = false;
	      return true;
	    }
	}
    return false;
  } 
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock)
  {
    (void)clock;
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
};
#endif /* !BOMB_H_ */
