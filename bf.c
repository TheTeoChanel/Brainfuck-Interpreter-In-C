#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	bool debugMode = false;
	bool traceMode = false;

	if (argc == 1) {
		printf("fatal error: no input file\n");
		printf("use --help to get help\n");
		return 1;
	}
	// VERSION
	if (strcmp(argv[1], "--version")==0) {
		printf("BrainF*ck Interpreter by TheTeoChannel\nVersion 0.12 // 2026\n");
		return 0;
	}
	// HELP
	if (strcmp(argv[1], "--help")==0) {
		printf("BRAINF*CK Interpreter by TheTeoChanel\n");
		printf("\n");
		printf("Syntax:\n\n");
		printf("bf FILENAME.BF -OPTIONS\n");
		printf("or\n");
		printf("bf -OPTION\n");
		printf("\n");
		printf("Options:\n\n");
		printf("--help		open this page (not a self reference)\n");
		printf("-t			TRACE MODE: Tracking every command in logs.txt\n");
		printf("-d			DEBUG MODE: Printing only important actions ([ ] . ,)\n");
		printf("--version	Show version of this program\n");
		printf("\nHad fun making this, TheTeoChanel 2026\n");
		return 0;
	}
	if (argc > 2 && strcmp(argv[2], "-d")==0)
		debugMode = true;
	else if (argc > 2) {
		printf("fatal error: unrecognized option '%s'.", argv[2]);
		return 1;
	}

	if (argc > 2 && strcmp(argv[2], "-t")==0)
		traceMode = true;
	else if (argc > 2) {
		printf("fatal error: unrecognized option '%s'.", argv[2]);
		return 1;
	}

	FILE *logs;
	logs = fopen("logs.txt", "w");
	fprintf(logs, "THETEOCHANNEL BRAINF*CK INTERPRETER LOGS\n");
	fprintf(logs, "COMMAND, cell:CELL NUM, val:CELL VALUE\n");
	fprintf(logs, "!PRINT!, cell:CELL NUM, val:CELL VALUE, char:CELL VALUE CHAR\n");
	fprintf(logs, "-------------------------------------------------\n");

	int stack[30000] = {0};
	int ptr = 0;
	int depth = 1;
	char program[1024];
	char buf[2];

	//INIT FILE
	FILE *fptr;
	fptr = fopen(argv[1], "r");

	if (fptr == NULL) {
		printf("fatal error: couldnt open the input file\n");
		return 1;
	}

	//READ BF FILE
	int programLen = fread(program, 1, sizeof(program) - 1, fptr);
	program[programLen] = '\0';
	fclose(fptr);

	for (int i = 0; i < programLen; i++) {
		switch (program[i]) {
		case '+':
			stack[ptr]++;
			if (stack[ptr] > 255) stack[ptr] = 0;
			if (traceMode) fprintf(logs, "+, cell:%d, val:%d\n", ptr, stack[ptr]);
			break;
		
		case '-':
			stack[ptr]--;
			if (stack[ptr] < 0) stack[ptr] = 255;
			if (traceMode) fprintf(logs, "-, cell:%d, val:%d\n", ptr, stack[ptr]);
			break;
		
		case '<':
			ptr--;
			if (ptr < 0) ptr = 29999;
			if (traceMode) fprintf(logs, "<, cell:%d, val:%d\n", ptr, stack[ptr]);
			break;
		
		case '>':
			ptr++;
			if (ptr > 29999) ptr = 0;
			if (traceMode) fprintf(logs, ">, cell:%d, val:%d\n", ptr, stack[ptr]);
			break;
		
		case '.':
			printf("%c", stack[ptr]);
			if (debugMode) printf("!PRINT! cell:%d, val:%d, CHAR=\"%c\"\n", ptr, stack[ptr], stack[ptr]);
			if (traceMode) fprintf(logs, "!PRINT! cell:%d, val:%d, CHAR=\"%c\"\n", ptr, stack[ptr], stack[ptr]);
			break;
		
		case ',':
			printf("USER INPUT> ");
			fgets(buf, sizeof(buf), stdin);
			stack[ptr] = (int)buf[0];
			break;

		case '[':
			if (stack[ptr] == 0) {
				while (depth > 0) {
					i++;
					if (program[i]=='[') depth++;
					if (program[i]==']') depth--;
				}
				depth = 1;
			}
			if (debugMode) printf("[, cell:%d, val:%d\n", ptr, stack[ptr]);
			if (traceMode) fprintf(logs, "!PRINT! cell:%d, val:%d, CHAR=\"%c\"\n", ptr, stack[ptr], stack[ptr]);			
			break;
		
		case ']':
			if (stack[ptr] != 0) {
				while (depth > 0) {
					i--;
					if (program[i]==']') depth++;
					if (program[i]=='[') depth--;
				}
				depth = 1;
			}
			if (debugMode) printf("], cell:%d, val:%d\n", ptr, stack[ptr]);
			if (traceMode) fprintf(logs, "!PRINT! cell:%d, val:%d, CHAR=\"%c\"\n", ptr, stack[ptr], stack[ptr]);			
			break;
		}
	}
	fclose(logs);
	return 0;
}
