

int global1;
// global1: static storage duration, external linkage
static int global2;
// global2: static storage duration, internal linkage

const int global3 = 4;
// global3: static storage duration, *internal* linkage (must be initialized)
extern const int global3;
// global3: static storage duration, external linkage

thread_local int thread1;
// thread1: thread storage duration, external linkage
thread_local static int thread2;
// thread2: thread storage duration, internal linkage

// unnamed namespace
namespace {
	int in_unnamed1;
	// in_unnamed1: static storage duration, internal linkage
	extern int in_unnamed2;
	// in_unnamed2: static storage duration, **internal** linkage
}

void foo1() {}
// foo1: external linkage
static void foo2() {}
// foo2: internal linkage


void test() {
	int local1;
	// local1: automatic storage duration, no linkage
	static int local2;
	// local2: static storage duration, *no* linkage

	extern int local3;
	// local3: declares that there is a static storage duration, external linkage variable "local3" provided *somewhere*
	//local3 += 1;
}

int main() {
}
