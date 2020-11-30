#pragma once

#include <opencv2/core/matx.hpp>

class Color {
public:
	int r{ 0 };
	int g{ 0 };
	int b{ 0 };

	Color();
	Color(cv::Vec3b &color);
	Color(int r, int g, int b);
	Color& operator=(const Color& color);

	bool operator!=(const Color& color) const;
	cv::Vec3b toVec3b() const;
};
