//#pragma once
#ifndef BOX_H
#define BOX_H
#include "Figure.h"
#include <iostream>
#include <array>
#include <cstdint>
#include"geometry.hpp"
class box : public Figure
{
public:
	//std::array<float, 3> min_point ;
	//std::array<float, 3> max_point;
	Vec3f min_point;
	Vec3f max_point;
	Vec3i color;
	box(Vec3f& min, Vec3f& max, Vec3i& col);
	//sf::Color color;
	bool ray_intersect( const Vec3f& orig, const Vec3f& dir, float* t0   );
	box();

	//~box();
};
#endif // !BOX_H



