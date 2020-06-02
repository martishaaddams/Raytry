#ifndef RAY_H
#define RAY_H
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
class Ray
{
public:
	std::array<float, 3> direction;
	std::array<float, 3> dot;
	sf::Color color=sf::Color::White;
	float t=INFINITY;
	Ray();
	Ray(std::array<float,3> a, std::array<float, 3> b);
	Ray(std::array<float,6> a);
	void out();
	~Ray() {};

};
#endif

