#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_LIMIT 1000

int main(int argc, char** argv) {
	char line[LINE_LIMIT];
	while (fgets(line, LINE_LIMIT, stdin)) {
		int lineOffset;

		/* 
		   It is previously known that I will always receive lines with the newline char.
		   If empty, print newline, as required by the problem, and skip. 
		*/
		if (line[0] == '\n') {
			printf("\n");
		}
		else {
			int whereNewline = 2;

			/* 
			   It is previously known that all lines will have the newline char at the end.
			   If the line is not empty, then due to the specification of the problem,
			   the newline will always be the third character or later, and occur exactly once.
		       If it occurs later, iteratively find where it is.
		    */
			while (line[whereNewline] != '\n') {
				whereNewline++;
			}
			int actualLineLimit = whereNewline + 1;
			int iterationLimit = 0;
			char command;
			for (lineOffset = 0; lineOffset < actualLineLimit; lineOffset++) {

				/* 
				   For any given character, it is either a digit, exclamation point,
				   or a character to be printed,
				   where for numbers with more than one digit, you take the sum of the digits;
				   for example, "10" is really the same as 1, and "11" is really to be
				   interpreted as 1 + 1 = 2.
				*/ 
				if (isdigit(line[lineOffset])) {
					iterationLimit += (line[lineOffset] - '0');
				}

				/* 
				   If it is not a digit, then it is either an exclamation point or a
				   character to be printed. 
				   If an exclamation point, then a newline is to be printed;
				   if a 'b', then a blank space is to be printed;
				   otherwise, print the character as-is on the screen,
				   as many times as the sum of the digits preceding the character
				   (e.g. the correct action for "101b" is to sum up 1 + 0 + 1 = 2,
				   and thus print "  "- two blank spaces)
				*/
				else {
					command = line[lineOffset];
					if (command == '!') {
						printf("\n");
					}
					else {
						int i;
						for (i = 0; i < iterationLimit; i++) {
							if (command == 'b') {
								printf(" ");
							}
							else {
								printf("%c", command);
							}
						}
					}
					iterationLimit = 0;
				}

			}

			/*
			    If the second last character within the current line of input being processed
			    is in fact an exclamation point,
			    then our current line of output will have a newline,
			    and no further action is required;
			    otherwise, we need to manually add a newline
			    because the problem requires that.
			*/

			if (line[whereNewline - 1] != '!') {
				printf("\n");
			}

		}
	}
	return 0;
}