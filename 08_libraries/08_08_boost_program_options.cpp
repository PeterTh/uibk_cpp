#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char **argv) {

	int opt;

	// Declare the supported options.
	po::options_description desc("Program options");
	desc.add_options()
		("help", "produce help message")
		("optimization", po::value<int>(&opt)->default_value(10), "optimization level")
		("include-path,I", po::value<std::vector<std::string>>()->multitoken(), "include path")
		("input-file", po::value<std::vector<std::string>>(), "input file")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}

	if(vm.count("include-path")) {
		auto paths = vm["include-path"].as<std::vector<std::string>>();
		std::cout << "Number of include paths: " << paths.size() << std::endl;
		for(auto p : paths) {
			std::cout << "  " << p << std::endl;
		}
	}
}
