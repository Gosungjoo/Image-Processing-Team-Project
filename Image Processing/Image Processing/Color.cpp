#include "Color.h"

Color::Color(cv::Vec3b &color)
: r{(int)color[0]}, g{(int)color[1]}, b{(int)color[2]}
{}

cv::Vec3b& Color::toVec3b() {
	cv::Vec3b vec;

	vec.val[0] = r;
	vec.val[1] = g;
	vec.val[2] = b;

	return vec;
}