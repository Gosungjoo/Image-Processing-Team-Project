#include "Color.h"

Color::Color()
	: r{0}, g{0}, b{0}
{}

Color::Color(cv::Vec3b &color)
: r{(int)color[0]}, g{(int)color[1]}, b{(int)color[2]}
{}

Color &Color::operator=(const Color& color)
{
	Color _color;
	_color.r = color.r;
	_color.g = color.b;
	_color.b = color.b;

	return _color;
}

cv::Vec3b& Color::toVec3b()
{
	cv::Vec3b vec;

	vec.val[0] = r;
	vec.val[1] = g;
	vec.val[2] = b;

	return vec;
}