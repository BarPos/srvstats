#include "index.h"

static std::string pageCache = "";

std::string getIndexPage() {
	if (pageCache != "") return pageCache;

	std::string line;
	std::ifstream fs("index.html");
	std::ostringstream oss;

	if (!fs) return "Error! No 'index.html'";
	while (std::getline(fs, line)) {
		oss << line << "\n";
	}

	pageCache = oss.str();
	return oss.str();
}