#include <opencv2/core/matx.hpp>

class Color {
public:
	int r{ 0 };
	int g{ 0 };
	int b{ 0 };

	Color(cv::Vec3b &color);
	cv::Vec3b& toVec3b();
};
