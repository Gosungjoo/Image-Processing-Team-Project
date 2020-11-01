#include <iostream>
#include <string>

#include "ShapeFinder.h"

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++) {
        std::string file_path = "C:\\" + std::string{ argv[i] };
        ShapeFinder shapefinder(file_path);
        try {
            shapefinder.find();
        } catch (std::exception) {

        }
    }
}
