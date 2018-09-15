
#ifndef _CONSTANTS
#define _CONSTANTS

#include "../geometry/vec3d.hpp"
#include "../geometry/vec3f.hpp"

const double PI = 3.1415926535897932384;
const double TWO_PI = 6.2831853071795864769;
const double PI_ON_180 = 0.0174532925199432957;
const double invPI = 0.3183098861837906715;
const double invTWO_PI = 0.1591549430918953358;

const float EPS = 1e-6;
const double D_EPS = 1e-12;

const Vec3d X_AXIS = Vec3d(1.,0.,0.);
const Vec3d Y_AXIS = Vec3d(0.,1.,0.);
const Vec3d Z_AXIS = Vec3d(0.,0.,1.);
const Vec3d XY_VEC = Vec3d(1.,1.,0.);
const Vec3d YZ_VEC = Vec3d(0.,1.,1.);
const Vec3d ZX_VEC = Vec3d(1.,0.,1.);
const Vec3d XYZ_VEC = Vec3d(1.,1.,1.);

const Vec3d BLACK = Vec3d(0.);
const Vec3d WHITE = Vec3d(1.);
const Vec3d GREY = Vec3d(.5, .5, .5);
const Vec3d RED = Vec3d(1., 0., 0.);
const Vec3d MATTE_RED = Vec3d(1., .25, .25);
const Vec3d GREEN = Vec3d(0., 1., 0.);
const Vec3d MATTE_GREEN = Vec3d(0., 1., .25);
const Vec3d BLUE = Vec3d(0., 0., 1.);
const Vec3d MATTE_BLUE = Vec3d(.25, .25, 1.);
const Vec3d YELLOW = Vec3d(1., 1., 0.);
const Vec3d MATTE_YELLOW = Vec3d(1., 1., .25);
const Vec3d MAGENTA = Vec3d(1., 0., 1.);
const Vec3d MATTE_MAGENTA = Vec3d(1., .25, 1.);
const Vec3d CYAN = Vec3d(0., 1., 1.);
const Vec3d MATTE_CYAN = Vec3d(.25, 1., 1.);
const Vec3d ORANGE = Vec3d(1., .5, 0.);
const Vec3d MATTE_ORANGE = Vec3d(1., .5, .25);

#endif
