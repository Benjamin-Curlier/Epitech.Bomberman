/*
** coucou.cpp for cpp_bomberman in /home/camila/rendu/cpp_bomberman
**
** Made by 
** Login  <@epitech.eu>
**
** Started on  lun. mai 18 19:45:59 2015 
** Last update dim. juin 14 20:03:41 2015 
*/

#pragma once
#include <Texture.hh>
#include <Game.hh>
#include <SdlContext.hh>
#include <BasicShader.hh>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <sys/time.h>
#include <stdlib.h>
#include <Geometry.hh>
#include <AShader.hh>
#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <Model.hh>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

class AObject
{
public:
  AObject() :
    _position(0, 0, 0), // On initialise la position a 0
    _rotation(0, 0, 0), // pareil pour la rotation
    _scale(1, 1, 1) // l'echelle est mise a 1
  {}
  virtual ~AObject(){}

  glm::vec3	getPos() const {return _position;};
  glm::vec3	getRot() const {return _rotation;};
  glm::vec3	getScal() const {return _scale;};
  bool		getSol() const {return _sol;};
  int		getId() const {return _id;};
  int		getNbr() const {return _nbr;};
  int		getEx() const {return _explosion;};
  char		getDir() const {return _direction;};
  bool		getIs_push() const {return _is_push;};
  bool    isAlive() const {return _alive;};
  bool    setLife(bool life) {_alive = life;};
  bool    setIs_push(bool a) {_is_push = a;};
  bool    setDir(char a) {_direction = a;};

  virtual bool initialize() {return (true);}
  virtual void update(gdl::Clock const &clock, gdl::Input &input){}
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
  void translate(glm::vec3 const &v) {_position += v;}
  void rotate(glm::vec3 const& axis, float angle){_rotation += axis * angle;}
  void scale(glm::vec3 const& scale) {_scale *= scale;}

  float my_max4(float a, float b, float c, float d)
  {
    return (my_max(my_max(my_max(a, b), c), d));
  }
  float my_min4(float a, float b, float c, float d)
  {
    return (my_min(my_min(my_min(a, b), c), d));
  }
  float my_max(float a, float b)
  {
    if (a >= b)
      return a;
    return b;
  }
  float my_min(float a, float b)
  {
    if (a <= b)
      return a;
    return b;
  }

  glm::mat4 getTransformation()
  {
    glm::mat4 transform(1);
    transform = glm::translate(transform, _position);
    transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
    transform = glm::scale(transform, _scale);
    return (transform);
  }

protected:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;
  bool _sol = false;
  bool _alive = true;
  bool _is_push = false;
  char _direction = 3;
  int	_nbr = 0;
  int	_id = 0;
  struct timeval _time;
  int _explosion = 2;
};
