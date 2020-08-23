#include "check.h"
// 8 9 8/9 digits
// 10 <=10 chars
// 7 double
// 1 M/W

int check(const char* text, int fmt)
{
	int c = 0 , i = 0;
	const char* pc = text;
	double d = 0.0;

	switch (fmt) {
	case 1: case 7: case 8:
	case 9: case 10:
		break;
	default:
		fprintf(stderr, "check format error ! must in (1,7,8,9,10)\n");
		return 0;
	}

	for (;;) {
		c = *pc;
		if (!c)
			return 0;
		if (!isspace(c))
			break;
		++pc;
	}

	switch (fmt) {
	case 10:
		for (i = 0; i < 10; ++i) {
			c = *pc;
			if (!c)
				return 1;
			if (isspace(c))
				break;
			++pc;
		}
		break;
	case 8: case 9:
		for (i = 0; i < fmt; ++i) {
			c = *pc;
			if (!isdigit(c))
				return 0;
			++pc;
		}
		break;
	case 7:
		if (sscanf(pc, "%lf%n", &d, &i) < 1 || !(0.0 <= d && d <= 100.0))
			return 0;
		printf("i=%d\n", i);
		pc += i;
		break;
	case 1:
		c = *pc++;
		if (c != 'M' && c != 'W')
			return 0;
		break;
	}

	for (;;) {
		c = *pc;
		if (!c)
			return 1;
		if (!isspace(c))
			return 0;
		++pc;
	}
}
