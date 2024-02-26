// calculator.h

#ifndef CALCULATOR_H
#define CALCULATOR_H

// Declare result as an extern variable
extern long long int result;

// Function prototypes
int getMenuChoice();
long long int getOperand(int base);

void displayMenu();
void binaryPadding(char *binaryResult, int targetWidth);
void performBitwiseOperation(int choice, long long int operand1, long long int operand2, int base);
void convertAndDisplayResult(long long int result, int base);
void convertToBinary(long long int value, char *binaryResult);
void clearInputBuffer();
void stringToLower(char *str);
int mapChoiceToOperation(char *choiceStr);
int validateNumber(long long int number, int base);
int replayOperation();
int getNumberSystem();

#endif // CALCULATOR_H
