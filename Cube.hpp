/*
** Cube.hpp for cpp_bomberman in /home/camila/Music/cpp_bomberman
**
** Made by 
** Login  <@epitech.eu>
**
** Started on  dim. juin 14 19:58:51 2015 
** Last update dim. juin 14 19:59:30 2015 
*/

#ifndef CUBE_H_
# define CUBE_H_

#include "AObject.hpp"

class Flame : public AObject
{
private:
  gdl::Texture _texture;
  gdl::Geometry _geometry;
  float _speed;
  std::vector<AObject *> *_objects;
  clock_t _time;

public:
  Flame(float x, float y, float z, bool up, std::vector<AObject *> *objects) 
  {
    _objects = objects;
    _position = glm::vec3(x, y, z);
    if (up == false)
      this->scale(glm::vec3(0.5, 0.5, 0.25));
    else
      this->scale(glm::vec3(0.25, 0.5, 0.5));
    this->_id = 3;
  }
  virtual ~Flame() { }
  virtual bool initialize()
  {
    if (_texture.load("LibBomberman_linux_x64/assets/Fire.tga") == false)
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
    _time = clock();
    return (true);
  }

  int collision()
  {
    int i = 0;
    for (auto it : *(this->_objects))
      {
	if (it->getId() != this->_id && it->getSol() != true && it->isAlive())
	  {
	    glm::vec3 a1 = _position + glm::vec3(this->getScal().x / 2, 0, this->getScal().z / 2);
	    glm::vec3 b1 = _position + glm::vec3(this->getScal().x / 2, 0, -this->getScal().z / 2);
	    glm::vec3 c1 = _position + glm::vec3(-this->getScal().x / 2, 0, this->getScal().z / 2);
	    glm::vec3 d1 = _position + glm::vec3(-this->getScal().x / 2, 0, -this->getScal().z / 2);
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
	      return i;
	  }
	i++;
      }
    return -1;
  }

  virtual void update(gdl::Clock const &clockl, gdl::Input &input)
  {
    (void)input;
    (void)clockl;
    if ((((float)clock() - _time)/CLOCKS_PER_SEC) >= 0.5)
      this->_alive = false;
  }
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock)
  {
    (void)clock;
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
};

class OnlyCube : public AObject
{
  private:
    gdl::Texture _texture;
    gdl::Geometry _geometry;
    float _speed;
    std::basic_string<char> _path;
    clock_t _time;
    std::vector<AObject*> *_objects;

  public:
    OnlyCube(bool sol, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, std::basic_string<char> ca) {
      _scale = scale;
      _position = position;
      _path = ca;
      _rotation = rotate;
      _objects = _objects;
      _sol = sol;
    }
    virtual ~OnlyCube() {}
    virtual bool initialize()
    {
      if (_texture.load(_path) == false)
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
      (void)input;
      (void)clockl;
      if ((((float)clock() - _time)/CLOCKS_PER_SEC) >= 1.5)
        this->_alive = false;
    }

    virtual void draw(gdl::AShader &shader, gdl::Clock const &clock)
    {
      (void)clock;
      _texture.bind();
      _geometry.draw(shader, getTransformation(), GL_QUADS);
    }
  };

class	LittleMovingCube : public AObject
{
private:
  gdl::Texture _texture;
  gdl::Geometry _geometry;
  float _speed;

public:
  LittleMovingCube(glm::vec3 x) {_position = x; _scale = glm::vec3(0.5, 0.5, 0.5); _rotation = glm::vec3(0, 0, 0);}
  virtual ~LittleMovingCube() { }
  virtual bool initialize()
  {
    _speed = 10.0f;
    if (_texture.load("./Textures/space.tga") == false)
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
 virtual void update(gdl::Clock const &clock, gdl::Input &input)
 {
   if (input.getKey(SDLK_RETURN))
   {
     if (_position.z >= -1.40 && _position.z <= 1.90)
       _nbr = 1;
     if (_position.z <= -5.50 && _position.z >= -6.50)
     _nbr = 2;
//     std::cout << "ici : " << glm::to_string(_position) << std::endl;
   }
if (input.getKey(SDLK_DOWN))
translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
if (input.getKey(SDLK_UP))
translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
 }
virtual void draw(gdl::AShader &shader, gdl::Clock const &clock)
{
(void)clock;
_texture.bind();
_geometry.draw(shader, getTransformation(), GL_QUADS);
}
};

#endif /* !CUBE_H_ */
