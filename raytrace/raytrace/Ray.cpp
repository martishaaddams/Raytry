#include "Ray.h"
Ray::Ray()
{
	for (int i = 0; i < 3; i++)
	{
		direction[i] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		dot[i] = 0;
	}
}
Ray::Ray(std::array<float, 3> a, std::array<float, 3> b)
{
	direction = a;
	dot = b;
}
Ray::Ray(std::array<float,6> a)
{
	if (a.size() != 6)
	{
		std::cout << "Wrong data, ray can't be created";
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			direction[i] = a[i];
		}
		for (int i = 0; i < 3; i++)
		{
			dot[i] = a[3 + i];
		}
	}

}
void Ray::out()
{
	std::cout << "direction (";
	for (int i = 0; i < 3; i++)
	{
		std::cout << direction[i] << ", ";
	}
	std::cout << ")" << std::endl;
	std::cout << "dot (";
	for (int i = 0; i < 3; i++)
	{
		std::cout << dot[i] << ", ";
	}
	std::cout << ")" << std::endl;
}