#include <iostream>

#include "FormFinder.h"

FormFinder::FormFinder(std::string file_path)
	: _file_path{file_path}
{}

void FormFinder::find()
{
	std::cout << "Searching form for file " << _file_path << std::endl;
}