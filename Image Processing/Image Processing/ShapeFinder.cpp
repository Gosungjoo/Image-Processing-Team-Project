#include <opencv2/core/matx.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

#include "ShapeFinder.h"
#include "Color.h"

ShapeFinder::ShapeFinder(std::string file_path)
	: _file_path{ file_path }, _image{ cv::imread(_file_path, cv::IMREAD_COLOR) }
{
	if (_image.empty()) {
		std::cout << "Could not open or find the image: " << _file_path << std::endl;
		throw std::runtime_error{ "Could not open or find the image: " + _file_path };
	}

	for (int y = 0; y < _image.rows; y++) {
		std::vector<Color> row{};
		for (int x = 0; x < _image.cols; x++) {
			Color pixel_color{ _image.at<cv::Vec3b>(x, y) };
			row.emplace_back(pixel_color);
		}
		_map.emplace_back(row);
	}
}

void ShapeFinder::find()
{
	int masks[4][3][3] = {
		{ { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } },
		{ { 1, 0, -1 }, { 2, 0, -2 }, { 1, 0, -1 } },
		{ { 0, -1, -2 }, { 1, 0, -1 }, { 2, 1, 0 } },
		{ { 2, 1, 0 }, { 1, 0, -1 }, { 0, -1, -2 } }
	};

	//for (int x = 0; x < _image.rows; x++) {
	//	for (int y = 0; y < _image.cols; y++) {
	//		cv::Vec3b &vcolor = _image.at<cv::Vec3b>(x, y);
	//		Color color(vcolor);

	//		std::cout << "Color: " << color.r << " " << color.g << " " << color.b << std::endl;
	//	}
	//}
}

decltype(ShapeFinder::_map) ShapeFinder::apply_mask()
{
	decltype(_map) map{};

	for (int y = 1; y < _image.rows - 1; y++) {
		for (int x = 1; x < _image.cols - 1; x++) {
			for (int y2 = 0; y2 < 3; y2++)
				for (int x2 = 0; x2 < 3; x++) {
					
				}
		}
	}
	return _map;
}