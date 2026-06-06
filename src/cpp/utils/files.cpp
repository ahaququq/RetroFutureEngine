#include "utils/files.hpp"

#include <fstream>
#include <sstream>

#include "utils/log.hpp"

std::string load_file(const std::string& name) {
	std::ifstream file{name};
	
	if (!file.is_open()) {
		warn(std::string{"Failed to open: "} + name);
		return "";
	}
	ok("Read: " + name);
	
	std::ostringstream output;
	
	file.get(*output.rdbuf(), '\0');
	
	return output.str();
}