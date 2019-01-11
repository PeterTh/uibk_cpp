#include <iostream>
#include <string>
#include <future>
#include <chrono>

#include <filesystem>
namespace fs = std::filesystem;

// Note: needs to be linked with -lstdc++fs (in GCC 8.2)
// experimental in earlier compilers

int main() {
	using namespace std::chrono_literals;

	auto largest_future = std::async([]() {
		// find largest file in working directory
		decltype(fs::file_size(std::declval<fs::path>())) largest_size = 0;
		fs::path largest;
		try {
			for(auto& p : fs::recursive_directory_iterator("R:/")) {
				if(p.is_regular_file()) {
					auto path = p.path();
					auto s = fs::file_size(path);
					if(s > largest_size) {
						largest_size = s;
						largest = path;
					}
				}
			}
		}
		// when dealing with files, getting an exception isn't unlikely
		catch(std::exception& e) {
			std::cerr << std::endl << "Exception: " << e.what() << std::endl;
		}
		return largest;
	});

	std::cout << "Searching for largest file...";

	// ... other work / progress bar / etc
	while(largest_future.wait_for(250ms) != std::future_status::ready) {
		std::cout << ".";
	}

	std::cout << std::endl << "Largest file: " << largest_future.get().generic_string() << std::endl;
}
