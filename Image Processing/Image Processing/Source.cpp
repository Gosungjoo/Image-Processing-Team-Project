#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++) {
        std::string file_path = "C:\\" + std::string{ argv[i] };

        std::cout << file_path << std::endl;

        cv::Mat image;
        image = cv::imread(file_path, cv::IMREAD_COLOR); // Read the file

        if (image.empty()) // Check for invalid input
        {
            std::cout << "Could not open or find the image" << std::endl;
            return -1;
        }

        cv::namedWindow(file_path, cv::WINDOW_AUTOSIZE); // Create a window for display.
        imshow(file_path, image); // Show our image inside it.

    }
    cv::waitKey(0);
}
