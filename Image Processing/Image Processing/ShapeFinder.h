#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <string>
#include <list>

#include "Color.h"

#define NOT_NEG(X) ((X) > 0) ? X : (-X)

using Map = std::vector<std::vector<Color>>;

class ShapeFinder {
private:
	std::string _file_path{ "" };
	cv::Mat _image{};

	Map _map{};

public:
	ShapeFinder(std::string file_path);
	ShapeFinder(const ShapeFinder&) = delete;
	ShapeFinder& operator=(const ShapeFinder&) = delete;

	void find(void);
	decltype(_map) apply_mask(int mask[3][3]);
	cv::Mat image_from_map(Map map);
};
