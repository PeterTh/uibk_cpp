#include <iostream>
#include <string>
#include <future>

#include <filesystem>
namespace fs = std::filesystem;

// Note: needs to be linked with -lstdc++fs (in GCC)

int main() {

	auto largest_future = std::async([]() {
		// find largest file in working directory
		decltype(fs::file_size(std::declval<fs::path>())) largest_size = 0;
		fs::path largest;
		for(auto& p : fs::directory_iterator(".")) {
			auto path = p.path();
			auto s = fs::file_size(path);
			if(s > largest_size) {
				largest_size = s;
				largest = path;
			}
		}
		return largest;
	});

	std::cout << "Searching for largest file..." << std::endl;

	// ... other work / progress bar / etc

	std::cout << "Largest file: " << largest_future.get() << std::endl;
}
