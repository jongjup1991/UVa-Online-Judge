#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

long collatz(long a, long limit, long callCount) {
	if (a > limit) {
		return callCount;
	}
	else if (a == 1) {
		return callCount + 1;
	}
	else {
		if ((a % 2) == 0) {
			return collatz((a >> 1), limit, callCount + 1);
		}
		else {
			return collatz(((a * 3) + 1), limit, callCount + 1);
		}
	}
}

int main(int argc, char** argv) {
	long initial, limit;
	int lineCount = 1;
	while (scanf("%ld%ld", &initial, &limit) == 2) {
		if ((initial < 0) || (limit < 0)) {
			break;
		}
	    long callCount = collatz(initial, limit, 0);
		printf ("Case %d: A = %ld, limit = %ld, number of terms = %ld\n", lineCount, initial, limit, callCount);
		lineCount++;
	}
	return 0;	
}