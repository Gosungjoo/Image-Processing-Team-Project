#include <string>

class FormFinder {
private:
	std::string _file_path{ "" };

public:
	FormFinder(std::string file_path);
	FormFinder(const FormFinder&) = delete;
	FormFinder& operator=(const FormFinder&) = delete;

	void find(void);
};
