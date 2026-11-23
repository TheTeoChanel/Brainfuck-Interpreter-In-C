#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	//INIT STACK
	unsigned char stack[30000] = {0};
	int stackLimit = 29999; // CELL COUNT, CAN BE CHANGED
	int pointer = 0;
	char buf[2];

	char program[2048];

	bool debugMode = false;
	bool traceMode = false;
	//char input[128];
	//int inputIdx = 0;

	if (argc == 1) {
		printf("fatal error: no input file\n");
		printf("use --help to get help\n");
		return 1;
	}
	// VERSION
	if (strcmp(argv[1], "--version") == 0 && argc == 2) {
		printf("BrainF*ck Interpreter by TheTeoChannel\nVersion 0.22 // 2026\n");
		return 0;
	}
	// SHOW HELP
	if (strcmp(argv[1], "--help") == 0 && argc == 2) {
		printf("BRAINF*CK Interpreter by TheTeoChanel\n");
		printf("\n");
		printf("Syntax:\n\n");
		printf("bf FILENAME.BF --OPTIONS\n");
		printf("or\n");
		printf("bf -OPTION\n");
		printf("\n");
		printf("Options:\n\n");
		printf("--help		open this page (not a self reference)\n");
		printf("-trace		TRACE MODE: Tracking every command in logs.txt\n");
		printf("-debug		DEBUG MODE: Printing only important actions ([ ] . ,)\n");
		printf("--version	Show version of this program\n");
		printf("\nHad fun making this, TheTeoChanel 2026\n");
		return 0;
	} 
	if (argc == 3 && strcmp(argv[2], "-debug") == 0) {
		debugMode = true;
	} else if (argc == 3 && strcmp(argv[2], "-trace") == 0) {
		 traceMode = true;
	}

	//if (argc > 3 && strcmp(argv[2], "-input")==0)	
	//	strcpy(input, argv[3]);
	//printf("%s", input);

	FILE *logsPTR;
	logsPTR = fopen("logs.txt", "w");
	fprintf(logsPTR, "THETEOCHANNEL BF INTERPRETER LOG FILE\n");
	fprintf(logsPTR, "COMMAND, cell:CELL NUM, val:CELL VALUE\n");
	fprintf(logsPTR, "-------------------------------------------------\n");
	
	//INIT INPUT FILE
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

	for (int pc = 0; pc < programLen; pc++) { //PC=PROGRAM COUNTER
		switch (program[pc]) {
		case '+':
			stack[pointer]++;
			if (traceMode) fprintf(logsPTR, "+, cell:%d, val:%d\n", pointer, stack[pointer]);
			break;

		case '-':
			stack[pointer]--;
			if (traceMode) fprintf(logsPTR, "-, cell:%d, val:%d\n", pointer, stack[pointer]);
			break;

		case '<':
			pointer--;
			if (pointer < 0) pointer = stackLimit;
			if (traceMode) fprintf(logsPTR, "<, cell:%d, val:%d\n", pointer, stack[pointer]);
			break;
		
		case '>':
			pointer++;
			if (pointer > stackLimit) pointer = 0;
			if (traceMode) fprintf(logsPTR, ">, cell:%d, val:%d\n", pointer, stack[pointer]);
			break;
		
		case '.':
			printf("%c", stack[pointer]);
			if (debugMode) printf("!PRINT! cell:%d, val:%d, CHAR=\"%c\"\n", pointer, stack[pointer], stack[pointer]);
			if (traceMode) fprintf(logsPTR, "!PRINT! cell:%d, val:%d, CHAR=\"%c\"\n", pointer, stack[pointer], stack[pointer]);
			break;
		
		case ',':
			printf("USER INPUT> ");
			fgets(buf, sizeof(buf), stdin);
			stack[pointer] = (int)buf[0];

			//stack[ptr] = input[inputIdx];
			//printf("%c", input[inputIdx]);
			//inputIdx++;
			break;

		case '[':
			if (stack[pointer] == 0) {
				int depth = 1;
				while (depth > 0) {
					pc++;
					if (program[pc]=='[') depth++;
					if (program[pc]==']') depth--;
				}
			}
			if (debugMode) printf("[, cell:%d, val:%d\n", pointer, stack[pointer]);
			if (traceMode) fprintf(logsPTR, "[, cell:%d, val:%d\n", pointer, stack[pointer], stack[pointer]);			
			break;
		
		case ']':
			if (stack[pointer] != 0) {
				int depth = 1;
				while (depth > 0) {
					pc--;
					if (program[pc]==']') depth++;
					if (program[pc]=='[') depth--;
				}
			}
			if (debugMode) printf("], cell:%d, val:%d\n", pointer, stack[pointer]);
			if (traceMode) fprintf(logsPTR, "], cell:%d, val:%d\n", pointer, stack[pointer], stack[pointer]);			
			break;
		}
	}
	fclose(logsPTR);
	return 0;
}
