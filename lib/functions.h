#pragma once
#ifndef HEADER_H
#define HEADER_H

//number input function
int getNum(void);
//filling an integer array with random numbers
void randomIntArrayFill(int* array, int size);
//filling an integer array with numbers from the keyboard
void fillIntArray(int* array, int size);
//filling in a string array from the keyboard
void fillStringArray(char** array, int size);
//output of a string array to the console
void printStringArray(char** array, int size);
//output an integer array to the console
void printIntArray(int* array, int size);

#endif