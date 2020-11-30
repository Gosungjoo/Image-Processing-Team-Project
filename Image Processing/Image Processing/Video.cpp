#include <opencv2/opencv.hpp>

#include <exception>
#include <iostream>

#include "Video.h"

Video::Video(decltype(Video::_file_path) file_path)
	: _file_path{file_path}
{
	int i = 0;

	cv::VideoCapture capture(_file_path);
	if (!capture.isOpened()) {
		throw std::runtime_error{ "Error opening video stream or file" };
	}

	_fps = capture.get(cv::CAP_PROP_FPS);

	while (true) {
		cv::Mat frame{};

		capture >> frame;
		if (frame.empty()) {
			break;
		}

		ImageType image_map{};
		for (int y = 0; y < frame.rows; y++) {
			std::vector<Color> row{};
			for (int x = 0; x < frame.cols; x++) {
				Color pixel_color{ frame.at<cv::Vec3b>(cv::Point(x, y)) };
				row.emplace_back(pixel_color);
			}
			image_map.emplace_back(row);
		}
		_video.emplace_back(image_map);

		// Only get the x first frames
		//if (i == 60)
		//	break;
	}

	capture.release();
}

void Video::double_fps(void)
{
	decltype(_video) doubled_video{};

	for (int i = 0; i < _video.size() - 1; i++) {
		doubled_video.emplace_back(_video[i]);
		doubled_video.emplace_back(_merge_images(_video[i], _video[i + 1]));
	}
	doubled_video.emplace_back(_video[_video.size() - 1]);

	_video = VideoType{};
	for (const auto& image : doubled_video) {
		_video.emplace_back(image);
	}
}

ImageType Video::_merge_images(const ImageType& image1, const ImageType& image2)
{
	ImageType image{};
	for (int y = 0; y < image1.size(); y++) {
		std::vector<Color> row{}	;
		for (int x = 0; x < image1[y].size(); x++) {

			// Do the calcul here

			// Change those values with the finals values (R, G, B) of the pixel.
			Color pixel_color{ 255, 0, 0 };
			row.emplace_back(pixel_color);
		}
		image.emplace_back(row);
	}
	return image;
}

void Video::save(void)
{
	std::vector<cv::Mat> video{};

	cv::VideoWriter output("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), _fps * 2, cv::Size(_video[0][0].size(), _video[0].size()));

	for (const auto &image : _video) {
		std::cout << image[0].size() << " " << image.size() << std::endl;
		cv::Mat frame{cv::Size(image[0].size(), image.size()), 16};

		for (int y = 0; y < image.size(); y++) {
			for (int x = 0; x < image[y].size(); x++) {
				frame.at<cv::Vec3b>(cv::Point(x, y)) = image[y][x].toVec3b();
			}
		}
		video.emplace_back(frame);
	}

	for (cv::Mat frame : video) {
		output.write(frame);
	}
	output.release();
}