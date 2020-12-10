#include <iostream>
#include <string>
#include <regex>

int main() {
	std::string s = R"(
		Some people, when confronted with a problem, think
		"I know, I'll use regular expressions."
		Now they have two problems.)";

	// ^ Note: raw string syntax

	/// check for a single match

	std::regex self_regex("REGULAR EXPRESSIONS?",
		std::regex_constants::ECMAScript | std::regex_constants::icase);
	// ^ equivalent to just std::regex_constants::icase (ECMAScript is the default)

	if(std::regex_search(s, self_regex)) {
		std::cout << "Text contains the phrase 'regular expression[s]'\n";
	}

	/// iterate over all matches using a regex_iterator

	std::regex word_regex(R"(['\w]+)");
	auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), word_regex);
	auto words_end = std::sregex_iterator();

	std::cout << "Found "
		<< std::distance(words_begin, words_end)
		<< " words\n";

	const int N = 6;
	std::cout << "Words longer than " << N << " characters:\n";
	for(auto i = words_begin; i != words_end; ++i) {
		std::string match_str = i->str();
		if(match_str.size() > N) {
			std::cout << "  " << match_str << '\n';
		}
	}

	/// find words with 6 or more characters and put the first character in brackets

	std::regex long_word_regex(R"((\w)(\w{5,}))");
	std::string new_s = std::regex_replace(s, long_word_regex, "[$1]$2");
	std::cout << new_s << '\n';
}
