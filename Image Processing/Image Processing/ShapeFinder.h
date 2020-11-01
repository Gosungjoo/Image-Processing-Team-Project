#pragma once

#include <opencv2/core.hpp>

#include <string>
#include <list>

#include "Color.h"

class ShapeFinder {
private:
	std::string _file_path{ "" };
	cv::Mat _image{};

	std::vector<std::vector<Color>> _map{};

public:
	ShapeFinder(std::string file_path);
	ShapeFinder(const ShapeFinder&) = delete;
	ShapeFinder& operator=(const ShapeFinder&) = delete;

	void find(void);
	decltype(_map) apply_mask();
};
