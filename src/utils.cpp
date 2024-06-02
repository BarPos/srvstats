#include "utils.h"


unsigned int getCpuCores(){
	return std::thread::hardware_concurrency();
}

using namespace get_system_usage_linux;

static double ussageCache = 0.0f;
static std::thread cacheThread;
static double memoryUssageCache = 0.0f;
static double swapUssageCache = 0.0f;
static std::string uptimeCache = "";

std::string _getUptime() {
	std::string line;
	std::ifstream("/proc/uptime", std::ifstream::in) >> line;
	std::ostringstream oss;

	const uint32_t time = stoul(line);
	std::map<std::string, uint16_t> timeStorage;

	if ((timeStorage["days"] = time / 86400) > 0)
	{
		if (timeStorage["days"] == 1)
			oss << timeStorage["days"] << " day ";
		if (timeStorage["days"] > 1)
			oss << timeStorage["days"] << " days ";
	}
	if ((timeStorage["hours"] = time / 3600 % 24) > 0)
	{
		if (timeStorage["hours"] == 1)
			oss << timeStorage["hours"] << " hour ";
		if (timeStorage["hours"] > 1)
			oss << timeStorage["hours"] << " hours ";
	}
	if ((timeStorage["minutes"] = time / 60 % 60) > 0)
	{
		if (timeStorage["minutes"] == 1)
			oss << timeStorage["minutes"] << " minute ";
		if (timeStorage["minutes"] > 1)
			oss << timeStorage["minutes"] << " minutes ";
	}
	if ((timeStorage["seconds"] = time % 60) > 0)
	{
		if (timeStorage["seconds"] == 1)
		{
			oss << timeStorage["seconds"] << " second";
		}

		if (timeStorage["seconds"] > 1)
		{
			oss << timeStorage["seconds"] << " seconds";
		}
	}

	return oss.str();
}


void startCacheThread() {
	cacheThread = std::thread([]() {
		while (true) {
			CPU_stats t1 = read_cpu_data();

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			CPU_stats t2 = read_cpu_data();
			ussageCache = (100.0f * get_cpu_usage(t1, t2));
			
			auto memory_data = read_memory_data();
			memoryUssageCache = (100.0f * memory_data.get_memory_usage());
			swapUssageCache = (100.0f * memory_data.get_swap_usage());

			uptimeCache = _getUptime();
		}
		});
}

double getCpuUssage() {
	return ussageCache;
}

double getMemUssage() {
	return memoryUssageCache;
}
double getSwapUssage() {
	return swapUssageCache;
}

std::string getUptime() {
	return uptimeCache;
}