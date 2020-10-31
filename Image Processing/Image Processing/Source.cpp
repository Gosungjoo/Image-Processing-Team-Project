
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

#include "FormFinder.h"

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++) {
        std::string file_path = "C:\\" + std::string{ argv[i] };
        FormFinder formfinder(file_path);

        formfinder.find();
    }
}