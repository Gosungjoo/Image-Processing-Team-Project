#include "Color.h"

Color::Color()
	: r{0}, g{0}, b{0}
{}

Color::Color(int red, int green, int blue)
	: r{ red }, g{ green }, b{ blue }
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

cv::Vec3b Color::toVec3b()
{
	return cv::Vec3b{ uchar(r), uchar(g), uchar(b) };
}

bool Color::operator!=(const Color& color) const
{
	return r != color.r || g != color.g || b != color.b;
}