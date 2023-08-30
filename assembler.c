// assembler.c
// This code assembles a file and computes its binary representation

// Author: Colin Ruiz and Zach Kratz
// Partnering method: Worked on methods together

// Date 3/1/2023
// Version 2.0






#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "atranslate.h"
#include "ctranslate.h"
#include "map.h"

#define MAX_LEN 100

map varvals;
//getatranslate aidentify;

// this method removes the spaces and comments for each line passed into it
// and passes it to line2
void removeSpaceComments(char* line, char* line2){
	int index = 0;
	int line2index = 0;
	// while the line is still being read
	while (line[index]!='\0'){
		if(line[index]=='/'){
			line2[line2index] = '\0';
			break;
		}
		else if(!isspace(line[index])){
			line2[line2index] = line[index];
			line2index++;
		}

		index++;


	}
	line2[line2index] = '\0';
}

// this method deals with the first pass of the program putting 
// values and variables into the varvals map.
void firstpass(FILE *firstfile, char fp[], char outfp[]){
	varvals = createMap(1000);
	insertKey(varvals, "SCREEN", "16384");
	insertKey(varvals, "KBD", "24576");
	insertKey(varvals, "SP", "0");
	insertKey(varvals, "LCL", "1");
	insertKey(varvals, "ARG", "2");
	insertKey(varvals, "THIS", "3");
	insertKey(varvals, "THAT", "4");
	insertKey(varvals, "R0", "0");
	insertKey(varvals, "R1", "1");
	insertKey(varvals, "R2", "2");
	insertKey(varvals, "R3", "3");
	insertKey(varvals, "R4", "4");
	insertKey(varvals, "R5", "5");
	insertKey(varvals, "R6", "6");
	insertKey(varvals, "R7", "7");
	insertKey(varvals, "R8", "8");
	insertKey(varvals, "R9", "9");
	insertKey(varvals, "R10", "10");
	insertKey(varvals, "R11", "11");
	insertKey(varvals, "R12", "12");
	insertKey(varvals, "R13", "13");
	insertKey(varvals, "R14", "14");
	insertKey(varvals, "R15", "15");


	int line_num = 0;
	char cleanstr[MAX_LEN];
	while(!feof(firstfile)){
		removeSpaceComments(fp, outfp);
		//puts(outfp);
		if (outfp[0] !='\0'){
			if(outfp[0] == '('){
				int index = 1;
				int subindex = 0;


				while(outfp[index] != ')'){
					cleanstr[subindex] = outfp[index];
					index++;
					subindex++;
				}
				cleanstr[subindex] = '\0';

				char num[MAX_LEN];
				sprintf(num, "%d", line_num);
//				puts(cleanstr);
	//			puts(num);
			//int val;
			//val = containsKey(varvals, cleanstr);
			//if (val != -1){
			//}
				insertKey(varvals, cleanstr, num);
			//if(outfp[0] =='@'){
			//	getsubstring(fp, outfp);
			//	int val = atoi(outfp[0]);
			//	if(!isdigit(val)){
			//		insertKey(varvals, outfp,
			//	}
			//}

				line_num--;
			}
			line_num++;
		}
		//line_num++;
		fgets(fp, MAX_LEN, firstfile);
	}

}

int main(int argc, char** argv){
	if(argc > 3){
		puts("no good");
		return 1;
	}
	// creating variables
	//const char* A_C = "A_COMMAND\n";
	//const char* C_C = "C_COMMAND\n";
	//const char* L_C = "L_COMMAND\n";
	// loading in the files
	char *inputfilename = argv[1];
	char *outputfilename = argv[2];

	FILE *firstfile = fopen(inputfilename, "r");
	FILE *file = fopen(outputfilename, "w");
	char infirstpass[MAX_LEN];
	char outfp[MAX_LEN];

	fgets(infirstpass, MAX_LEN, firstfile);

	firstpass(firstfile, infirstpass, outfp);

	fclose(firstfile);
	fclose(file);

	FILE *myfile = fopen(inputfilename, "r");

	FILE *outputfile = fopen(outputfilename, "w");

	char line[MAX_LEN];

	fgets(line, MAX_LEN, myfile);

	// reading line by line of the file
	// this while loop logic deals with the second pass of thr program
	// which mainly deals with translating a and c commands.
	// for the a command section it sees if a a variable is new or
	// has already been assessed a value 
	int next_var = 16;
	while(!feof(myfile)){
		char cleanline[MAX_LEN];
		char translatedline[17];
		char clsub[MAX_LEN];
		removeSpaceComments(line, cleanline);
		// if statement logic for seeing which command the line is if its not empty
		if(cleanline[0]!='\0'){
			if(cleanline[0]=='@'){
				getsubstring(cleanline, clsub);
				char str[20];
//				puts(clsub);
				//puts("clsub");
				sprintf(str, "%d", clsub[0]);
				int val = atoi(str);
				if(!isdigit(val)){
					char num[MAX_LEN];
					sprintf(num, "%d", next_var);
					int index;
					index = containsKey(varvals, clsub);

					char * value;
					char lookupVal[MAX_LEN];
					if(index == -1){
						insertKey(varvals, clsub, num);
						constructacommand(num, translatedline);
						next_var++;
						fputs(translatedline, outputfile);
						fputs("\n", outputfile);
					}
					else{
						value = lookupKey(varvals, clsub);
						strcpy(lookupVal, value);
						//puts(lookupVal);
						constructacommand(lookupVal, translatedline);
						//puts(translatedline);
						fputs(translatedline, outputfile);
						fputs("\n", outputfile);
					}
					//insertKey(varvals, clsub, num);
					//next_var++;
					//char * value;
					//char lookupVal[MAX_LEN];
					//value = lookupIndex(varvals, clsub);
					//strcpy(lookedupVal, value);
				}
				else{
					constructacommand(clsub, translatedline);
					fputs(translatedline, outputfile);
					fputs("\n", outputfile);
				}
			}
			else if (cleanline[0] == '('){
				fgets(line, MAX_LEN, myfile);
				continue;
			}
			else{
				if(strcmp(cleanline, "SP")==0){
					puts(line);
				}
				//fputs(C_C, outputfile);
				translateparts(cleanline, translatedline);
				fputs(translatedline, outputfile);
				fputs("\n", outputfile);
			}
		}
		fgets(line, MAX_LEN, myfile);
	}
	freeMap(varvals);
	fclose(myfile);
	fclose(outputfile);
	return 0;
}

