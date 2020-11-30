#include <iostream>
#include <string>

#include "Video.h"

int main(int argc, char** argv)
{
    std::string video_path = "C:\\" + std::string{ argv[1] };
    Video video{ video_path };

    try {
        video.double_fps();
        video.save();
    }
    catch (std::exception err) {
        std::cerr << "Unexcepted error occured: " << err.what() << std::endl;
        return -1;
    }

    return 0;
}
