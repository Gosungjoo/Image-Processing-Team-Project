#include <opencv2/core/matx.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

#include "ShapeFinder.h"
#include "Color.h"

ShapeFinder::ShapeFinder(std::string file_path)
	: _file_path{file_path}
{}

void ShapeFinder::find()
{
	std::cout << "Searching form for file " << _file_path << std::endl;

	cv::Mat image;
	image = cv::imread(_file_path, cv::IMREAD_COLOR);
	if (image.empty()) {
		std::cout << "Could not open or find the image: " << _file_path << std::endl;
		throw std::runtime_error{ "Could not open or find the image: " + _file_path };
	}

	cv::Vec3b &vcolor = image.at<cv::Vec3b>(50, 50);
	Color color(vcolor);

	std::cout << "Color: " << color.r << " " << color.g << " " << color.b << std::endl;
}
