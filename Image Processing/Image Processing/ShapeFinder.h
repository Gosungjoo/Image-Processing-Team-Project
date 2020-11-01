#include <string>

class ShapeFinder {
private:
	std::string _file_path{ "" };

public:
	ShapeFinder(std::string file_path);
	ShapeFinder(const ShapeFinder&) = delete;
	ShapeFinder& operator=(const ShapeFinder&) = delete;

	void find(void);
};
