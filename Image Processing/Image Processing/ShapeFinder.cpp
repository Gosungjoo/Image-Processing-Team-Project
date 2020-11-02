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

	_map.reserve(_image.rows);
	for (int y = 0; y < _image.rows; y++) {
		std::vector<Color> row{};
		for (int x = 0; x < _image.cols; x++) {
			Color pixel_color{ _image.at<cv::Vec3b>(x, y) };
			row.emplace_back(pixel_color);
		}
		_map.emplace_back(row);
	}
}


void ShapeFinder::edge_finder_line(Map map, int basex, int basey, int incrementx, int incrementy)
{
	for (int y = basey; y < map.size() && y > 0; y += incrementy) {
		for (int x = basex; x < map[0].size() && x > 0; x += incrementx) {
			cv::Point point = cv::Point(x, y);
			if (map[y][x] != Color(0, 0, 0)) {
				bool to_add = true;
				for (const auto& elem : _edges) {
					if (elem.x < point.x + 50 && elem.x > point.x - 50 && elem.y < point.y + 50 && elem.y > point.y - 50) {
						to_add = false;
						break;
					}
				}

				if (to_add) 
					_edges.push_back(cv::Point(x, y));
				return;
			}
		}
	}
}

void ShapeFinder::edge_finder_column(Map map, int basex, int basey, int incrementx, int incrementy)
{
	for (int x = basex; x < map[0].size() && x > 0; x += incrementx) {
		for (int y = basey; y < map.size() && y > 0; y += incrementy) {
			cv::Point point = cv::Point(x, y);
			if (map[y][x] != Color(0, 0, 0)) {
				bool to_add = true;
				for (const auto& elem : _edges) {
					if (elem.x < point.x + 50 && elem.x > point.x - 50 && elem.y < point.y + 50 && elem.y > point.y - 50) {
						to_add = false;
						break;
					}
				}

				if (to_add)
					_edges.push_back(cv::Point(x, y));
				return;
			}
		}
	}
}

void ShapeFinder::find()
{
	static int masks[4][3][3] = {
		{ { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } },
		{ { 1, 0, -1 }, { 2, 0, -2 }, { 1, 0, -1 } },
		{ { 0, -1, -2 }, { 1, 0, -1 }, { 2, 1, 0 } },
		{ { 2, 1, 0 }, { 1, 0, -1 }, { 0, -1, -2 } }
	};

	for (auto i = 0; i < 4; i++) {
		std::stringstream ss{};

		Map map = apply_mask(masks[i]);

		edge_finder_line(map, 1, 1, 1, 1);
		edge_finder_line(map, 1, map.size() - 1, 1, -1);
		edge_finder_line(map, map[0].size() - 1, 1, -1, 1);
		edge_finder_line(map, map[0].size() - 1, map.size() - 1, -1, -1);

		edge_finder_column(map, 1, 1, 1, 1);
		edge_finder_column(map, 1, map.size() - 1, 1, -1);
		edge_finder_column(map, map[0].size() - 1, 1, -1, 1);
		edge_finder_column(map, map[0].size() - 1, map.size() - 1, -1, -1);
	}

	if (_edges.size() == 4)
		std::cout << "The shape is a square." << std::endl;
	else if (_edges.size() == 3)
		std::cout << "The shape is a triangle." << std::endl;
	else
		std::cout << "Unknow shapes (" << _edges.size() << " edges)." << std::endl;
}


cv::Mat ShapeFinder::image_from_map(Map map) {
	auto img = _image.clone();

	for (uint y = 0; y < map.size(); y++) {
		for (uint x = 0; x < map[y].size(); x++) {
			img.at<cv::Vec3b>(cv::Point(x, y)) = map[y][x].toVec3b();
		}
	}

	return img;
}

decltype(ShapeFinder::_map) ShapeFinder::apply_mask(int mask[3][3])
{
	decltype(_map) map{};

	map.reserve(_image.rows - 1);
	for (int y = 1; y < _image.rows - 1; y++) {
		std::vector<Color> colors{};
		colors.reserve(_image.cols - 1);
		for (int x = 1; x < _image.cols - 1; x++) {
			int64 r{ 0 }, g{ 0 }, b{ 0 };
			for (int y2 = 0; y2 < 3; y2++) {
				for (int x2 = 0; x2 < 3; x2++) {
					r = r + _map[y + y2 - 1][x + x2 - 1].r * mask[y2][x2];
					g = g + _map[y + y2 - 1][x + x2 - 1].g * mask[y2][x2];
					b = b + _map[y + y2 - 1][x + x2 - 1].b * mask[y2][x2];
				}
			}

			const auto col = Color{
				int(MIN(NOT_NEG(r), 255)),
				int(MIN(NOT_NEG(g), 255)),
				int(MIN(NOT_NEG(b), 255)),
			};
			colors.emplace_back(col);
		}
		map.emplace_back(colors);
	}

	return map;
}