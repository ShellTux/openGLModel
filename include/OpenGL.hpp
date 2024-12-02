#ifndef INCLUDE_INCLUDE_OPENGL_HPP_
#define INCLUDE_INCLUDE_OPENGL_HPP_

#include "Vec3.hpp"
#include "types.hpp"

void Perspective(const f32 theta, const f32 alpha, const f32 beta);
void LookAt(const Vec3 &camera, const Vec3 &target, const Vec3 &up);

#endif // INCLUDE_INCLUDE_OPENGL_HPP_
