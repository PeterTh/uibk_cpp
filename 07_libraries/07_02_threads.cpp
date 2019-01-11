#include <iostream>
#include <string>
#include <thread>
#include <mutex>

void replace_string_thread(std::string& target, std::mutex& target_mutex,
		const std::string to_replace, const std::string replacement) {
	std::lock_guard lock(target_mutex);
	//             ^ in C++17 we can omit the template parameter (deduction guides)
	//               in earlier versions we need to explicitly write "<std::mutex>"
	// lock_guard is a *scoped lock*
	target.replace(target.find(to_replace), to_replace.size(), replacement);
}

int main() {

	std::string message{ "Hello World" };
	std::mutex message_mutex;

	std::cout << message << std::endl;

	/// Create two threads to manipulate the message string

	std::thread replace_world(replace_string_thread,
		std::ref(message), std::ref(message_mutex), "World", "Program");
	std::thread replace_hello(replace_string_thread,
		std::ref(message), std::ref(message_mutex), "Hello", "Goodbye");

	// NOTE the usage of std::ref to pass references to
	// the replace_string_thread function
	// (std::thread tries to move or copy its arguments)

	/// Wait for thread completion

	replace_world.join();
	replace_hello.join();

	std::cout << message << std::endl;
}
