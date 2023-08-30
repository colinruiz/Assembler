// atranslate.c
// This code translates the a commands

// Author: Colin Ruiz and Zach Kratz
// Partnering method: Worked on methods together

// Date 2/27/2023
// Version 2.0

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


// this function takes in two arrays and modifies the string array to only contain the stuff after the first value in the array
// puts it into subsring @16 --> 16
void getsubstring(char string[], char substring[]){

	int subindex = 0;
	// copy string over to get the length
	int index = 0;

	while(string[index] !='\0') {
		if(index != 0){
			substring[subindex] = string[index];
			subindex++;
		}
		index++;
	}
	substring[subindex] = '\0';

	//puts(substring);

}

// takes in two arrays and modifies the string array to a 15 bit binary representation of the value inside it
// stores that into the binary array
void decimaltobinary(char string[], char binary[]){
	int val = atoi(string);

	int index = 14;
	while (val > 0 && index >=0){
		binary[index--] = (val %2) +'0';
		val /=2;
	}
	// replaces the rest of the values with 0
	while (index>=0){
		binary[index--] = '0';
	}

}

// constructs the a command by taking in a string and parsing it through to give back a 16 bit binary representation of it
// stores it into the finalbinary array
void constructacommand(char string[], char finalbinary[]){
	//char substring[100];
	char binary[16] = {0};
//	getsubstring(string, substring);
	decimaltobinary(string, binary);
	//char finalbinary[17];
	finalbinary[0] = '0';
	int index =1;
	int binaryindex = 0;
	while (binary[binaryindex] != '\0'){
		finalbinary[index] = binary[binaryindex];
		index++;
		binaryindex++;
	}
	finalbinary[index] = '\0';
	//puts(finalbinary);
}

//int main(){
//	char string[100] = "@24576";
//	char finalbinary[17];
//	constructacommand(string, finalbinary);
//	puts(finalbinary);
//	return 0;
//}
