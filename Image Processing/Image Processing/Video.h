#pragma once

#include <string>
#include <vector>

#include "Color.h"

using ImageType = std::vector<std::vector<Color>>;
using VideoType = std::vector<ImageType>;

class Video {
private:
	const std::string _file_path{};
	VideoType _video{};
	double _fps{};

	ImageType _merge_images(const ImageType&, const ImageType&);


public:
	Video(decltype(_file_path));

	void double_fps(void);
	void save();
};
