// assembler.c
// This code translates c commands

// Author: Colin Ruiz and Zach Kratz
// Partnering method: Worked on methods together

// Date 3/1/2023
// Version 2.0

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "map.h"


map compmap;
map destmap;
map jumpmap;

// this function makes the compmap
void makecompmap(){
	compmap = createMap(28);

	insertKey(compmap, "0", "0101010");
	insertKey(compmap, "1", "0111111");
	insertKey(compmap, "-1", "0111010");
	insertKey(compmap, "D", "0001100");
	insertKey(compmap, "A", "0110000");
	insertKey(compmap, "!D", "0001101");
	insertKey(compmap, "!A", "0110001");
	insertKey(compmap, "-D", "0001101");
	insertKey(compmap, "-A", "0110011");
	insertKey(compmap, "D+1", "0011111");
	insertKey(compmap, "A+1", "0110111");
	insertKey(compmap, "D-1", "0001110");
	insertKey(compmap, "A-1", "0110010");
	insertKey(compmap, "D+A", "0000010");
	insertKey(compmap, "D-A", "0010011");
	insertKey(compmap, "A-D", "0000111");
	insertKey(compmap, "D|A", "0010101");
	insertKey(compmap, "M", "1110000");
	insertKey(compmap, "!M", "1110001");
	insertKey(compmap, "-M", "11110011");
	insertKey(compmap, "M+1", "1110111");
	insertKey(compmap, "M-1", "1110010");
	insertKey(compmap, "D+M", "1000010");
	insertKey(compmap, "D-M", "1010011");
	insertKey(compmap, "M-D", "1000111");
	insertKey(compmap, "D&M", "1000000");
	insertKey(compmap, "D|M", "1010101");
}

// this function makes the destmap
void makedestmap(){
	destmap = createMap(8);
    	insertKey(destmap, "\0", "000");
    	insertKey(destmap, "M", "001");
    	insertKey(destmap, "D", "010");
    	insertKey(destmap, "MD", "011");
    	insertKey(destmap, "A", "100");
    	insertKey(destmap, "AM", "101");
    	insertKey(destmap, "AD", "110");
    	insertKey(destmap, "AMD", "111");
}

// this function makes the jump map
void makejumpmap(){
	jumpmap = createMap(8);
	insertKey(jumpmap, "\0", "000");
    	insertKey(jumpmap, "JGT", "001");
    	insertKey(jumpmap, "JEQ", "010");
    	insertKey(jumpmap, "JGE", "011");
    	insertKey(jumpmap, "JLT", "100");
    	insertKey(jumpmap, "JNE", "101");
    	insertKey(jumpmap, "JLE", "110");
    	insertKey(jumpmap, "JMP", "111");
}

// this function takes a string and takes out the part that should be the comp part
void compsubstring(char string[], char substring[]){
	//int subindex = 0;

	//int index =0;

	const char eq = '=';
	char *comp = strchr(string, eq);

	const char semicol = ';';
	char *semicomp = strchr(string, semicol);
	if (comp != NULL && semicomp == NULL) {

		strcpy(substring, comp+1); // output: comp: value
	}
	else if(comp != NULL && semicomp != NULL){
		int index = (int)(comp - string +1);
		int subindex = 0;
		while(string[index] !=';'){
			substring[subindex] = string[index];
			subindex++;
			index++;
		}
			substring[subindex] = '\0';
	}
	else if(comp == NULL){
		int index =0;
		int subindex = 0;
		while(string[index] != ';'){
			substring[subindex] = string[index];
			subindex++;
			index++;
		}
		substring[subindex] = '\0';
	}
// failed code
// substring might have a bunch of '\0'
	//else{
	//	int index = 0;
	//	int subindex = 0;
	//	while(string[index] !='\0'){
	//		if(string[index] ==';'){
	//			subindex++;
	//			index++;
	//			break;
	//		}
	//		substring[subindex] = string[index];
	//		subindex++;
	//		index++;

	//	}
	//	substring[subindex] = '\0';
	//}

}

// this function takes a string and modifies it so it only contains the dest part and puts that part into the substring
void destsubstring(char string[], char substring[]){

	const char eq = '=';
	char *comp = strchr(string, eq);

	if(comp == NULL){
		substring[0] = '\0';
	}
	else{
		int index = 0;
		int subindex = 0;

		while(string[index] != '='){
			substring[subindex] = string[index];
			index++;
			subindex++;
		}
		substring[subindex] = '\0';
	}
}

// this function takes a string and modifies it so it only contains the jump part and puts that part into the substring
void jumpsubstring(char string[], char substring[]){
	const char semicol = ';';
	const char *comp = strchr(string, semicol);

	if(comp != NULL){
		strcpy(substring, comp + 1);
	}
	else{
		substring[0] = '\0';
	}
}

// this function takes in two arrays and based on the jumpsub array gets the corresponding value for that in the jump map
// and stores that into jumpval
void lookupjumpKeys(char jumpsub[],  char jumpval[]){
	makejumpmap();
	char * lookedupVal = lookupKey(jumpmap, jumpsub);
//	printf("Looked up value: %s\n", lookedupVal);

	strcpy(jumpval, lookedupVal);

	//strcpy(jumpval, lookedupVal);
	freeMap(jumpmap);
}

// this function takes in two arrays and based on the compsub array gets the corresponding value for that in the comp map
// and stores that into compval
void lookupcompKeys(char compsub[], char compval[]){
	makecompmap();
	char * lookedupVal = lookupKey(compmap, compsub);
	strcpy(compval, lookedupVal);
	freeMap(compmap);
}

// this function takes in two arrays and based on the destsub array gets the corresponding value for that in the dest map
// and stores that into destval
void lookupdestKeys(char destsub[], char destval[]){
	makedestmap();
	char * lookedupVal = lookupKey(destmap, destsub);
	strcpy(destval, lookedupVal);
	freeMap(destmap);
}

// this function takes in two arrays and based on the input array translates it into the binary represenation and stores that into
// the output array
void translateparts(char input[], char output[]){
	//char string[10] = "D=M";
	char jumpsub[10];
	char destsub[10];
	char compsub[10];

	destsubstring(input, destsub);
	jumpsubstring(input, jumpsub);
	compsubstring(input, compsub);
//	puts(jumpsub);
	char jumpval[5];
	char compval[8];
	char destval[5];
	lookupjumpKeys(jumpsub, jumpval);
	lookupcompKeys(compsub, compval);
	lookupdestKeys(destsub, destval);
	//printf("Expecting 000: %s\n", jumpval);
	//printf("Expecting 1110000: %s\n", compval);
	//printf("Expecting 010: %s\n", destval);
	char start[] = "111";
	strcpy(output, start);
	strcat(output, compval);
	strcat(output, destval);
	strcat(output, jumpval);
	//printf("Expecting 1111110000010000: %s\n", output);
}
// testing code
//int main(){
//	makejumpmap();
//	char output[17];
//	char input[10] = "D=M";
//	translateparts(input, output);
//	freeMap(jumpmap);
//	return 0;
//}

