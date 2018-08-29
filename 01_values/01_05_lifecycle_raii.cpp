#include <iostream>
#include <fstream>


int main() {
	bool doWorld = false;

	// block that deals with file writing
	{
		std::ofstream file("out.txt");
		file << "Hello ";
		if(!doWorld) return 0;
		file << "World" << std::endl;
	}
	// file is now closed
}


/// C-style (and many other languages) comparison
int badMain() {
	bool doWorld = false;

	// block that deals with file writing
	{
		FILE* f = fopen("out.txt", "w");
		fprintf(f, "Hello ");
		if(!doWorld) return 0;
		fprintf(f, "World\n");
		fclose(f);
	}
	// ???
}
