#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

/// linking:
// -lboost_log
// -DBOOST_LOG_DYN_LINK

namespace logging = boost::log;

/// setup example

void log_init() {
	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::debug);
	// ^ globally filter out log messages of lower importance than "debug"

	logging::add_common_attributes();
	// ^ enable common log message attributes such as timestamps

	logging::add_console_log(std::cout,
		logging::keywords::format = "%Message% (%TimeStamp%)",
		logging::keywords::filter = logging::trivial::severity >= logging::trivial::warning
	);
	// ^ log all messages of "warning" level or higher to std::cout in the given format

	logging::add_file_log(
		logging::keywords::file_name = "test.log",
		logging::keywords::rotation_size = 10 * 1024 * 1024,
		logging::keywords::format = "[%TimeStamp%]: %Message%"
	);
	// ^ log all messages not globally filtered out to "test.log"
	//   keep a maximum of 10 MiB of logging information
}

/// usage

int main() {
	log_init();

	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

	return 0;
}
