#include "process.h"

HANDLE hstdout;
BitMap* bitMap = nullptr;
int main()
{
	Run(Init());
	return 0;
}