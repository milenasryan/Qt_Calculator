// calculator.c

#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define result here
long long int result;
int shiftAmount;
char binaryResult[64];

void displayMenu() {
    printf("\nBitwise Calculator\n");
    printf("Enter number system for Input (2 for binary, 10 for decimal, 16 for hexadecimal): ");
}

void binaryPadding(char *binaryResult, int targetWidth) {
    int resultWidth = strlen(binaryResult);

    if (resultWidth < targetWidth) {
        memmove(binaryResult + targetWidth - resultWidth, binaryResult, resultWidth + 1);
        memset(binaryResult, '0', targetWidth - resultWidth);
    }
}

void performBitwiseOperation(int choice, long long int operand1, long long int operand2, int base) {
    switch (choice) {
        case 1:
            result = operand1 & operand2;
            break;
        case 2:
            result = operand1 | operand2;
            break;
        case 3:
            result = operand1 ^ operand2;
            break;
        case 4:
            result = ~(operand1 | operand2);
            break;
        case 5:
            printf("Enter shift amount: ");
            scanf("%d", &shiftAmount);
            result = operand1 << shiftAmount;
            break;
        case 6:
            printf("Enter shift amount: ");
            scanf("%d", &shiftAmount);
            result = operand1 >> shiftAmount;
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }
}

void convertAndDisplayResult(long long int result, int base) {
    switch (base) {
        case 2:
            printf("Result in binary: ");
            convertToBinary(result, binaryResult);
            binaryPadding(binaryResult, 32); // Assuming a 32-bit result
            printf("%s\n", binaryResult);
            break;
        case 10:
            printf("Result in decimal: %lld\n", result);
            break;
        case 16:
            printf("Result in hexadecimal: 0x%llx\n", result);
            break;
        default:
            printf("Invalid base.\n");
    }
}

void convertToBinary(long long int value, char *binaryResult) {
    int index = 0;
    while (value > 0 || index == 0) {
        binaryResult[index++] = (value % 2) + '0';
        value /= 2;
    }

    // Add padding with zeros
    while (index < 32) {
        binaryResult[index++] = '0';
    }

    binaryResult[index] = '\0';

    // Reverse the string
    int start = 0;
    int end = index - 1;
    while (start < end) {
        char temp = binaryResult[start];
        binaryResult[start] = binaryResult[end];
        binaryResult[end] = temp;
        start++;
        end--;
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard characters until newline or end of file
    }
    fflush(stdin); // Clear the input buffer
}


void stringToLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int mapChoiceToOperation(char *choiceStr) {
    stringToLower(choiceStr);

    if (strcmp(choiceStr, "and") == 0) {
        return 1;
    } else if (strcmp(choiceStr, "or") == 0) {
        return 2;
    } else if (strcmp(choiceStr, "xor") == 0) {
        return 3;
    } else if (strcmp(choiceStr, "nor") == 0) {
        return 4;
    } else if (strcmp(choiceStr, "left shift") == 0) {
        return 5;
    } else if (strcmp(choiceStr, "right shift") == 0) {
        return 6;
    } else if (strcmp(choiceStr, "replay") == 0) {
        return 7;
    } else if (strcmp(choiceStr, "exit") == 0) {
        return 8;
    } else {
        return 0; // Invalid choice
    }
}


int validateNumber(long long int number, int base) {
    if (base == 2) {
        while (number > 0) {
            int digit = number % 10;
            if (digit != 0 && digit != 1) {
                return 0; // Invalid binary digit
            }
            number /= 10;
        }
        return 1;
    } else if (base == 10) {
        // No specific validation for decimal
        return 1;
    } else if (base == 16) {
        while (number > 0) {
            int digit = number % 16;
            if (!((digit >= 0 && digit <= 9) || (digit >= 10 && digit <= 15))) {
                return 0; // Invalid hexadecimal digit
            }
            number /= 16;
        }
        return 1;
    } else {
        return 0; // Invalid base
    }
}

int replayOperation() {
    char replayChoice[10];
    printf("7. Replay\n");
    printf("8. Exit\n");
    printf("Choose an operation: ");
    scanf("%s", replayChoice);
    clearInputBuffer(); // Clear the input buffer

    int replay = mapChoiceToOperation(replayChoice);

    if (replay == 7) {
        return 1; // Replay
    } else if (replay == 8) {
        printf("Program terminated\n");
        exit(0); // Terminate the program
    } else {
        printf("Invalid choice.\n");
        return 0; // Continue with another operation
    }
}


int getNumberSystem() {
    int numberSystem;
    char input[20];
    
    printf("Enter number system for Input (2 for binary, 10 for decimal, 16 for hexadecimal): ");

    while (1) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove trailing newline character
            input[strcspn(input, "\n")] = '\0';

            if (sscanf(input, "%d", &numberSystem) == 1) {
                clearInputBuffer();  // Clear the input buffer to handle invalid input
                if (numberSystem == 2 || numberSystem == 10 || numberSystem == 16) {
                    return numberSystem;  // Valid input, return the number system
                } else {
                    printf("Invalid choice. Please try again: ");
                }
            } else {
                clearInputBuffer();  // Clear the input buffer in case of non-integer input
                printf("Invalid input. Please enter a valid number: ");
            }
        } else {
            printf("Error reading input. Please try again: ");
            clearInputBuffer();  // Clear the input buffer in case of an error
        }
    }
}

int getMenuChoice() {
    int choice;

    printf("Bitwise Calculator Menu:\n");
    printf("1. AND\n");
    printf("2. OR\n");
    printf("3. XOR\n");
    printf("4. NOR\n");
    printf("5. Left Shift\n");
    printf("6. Right Shift\n");
    printf("7. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer(); // Clear the input buffer

    return choice;
}

long long int getOperand(int base) {
    long long int operand;

    while (1) {
        printf("Enter operand: ");
        if (base == 2) {
            scanf("%lld", &operand);
            clearInputBuffer(); // Clear the input buffer
            if (validateNumber(operand, 2)) {
                return operand;
            } else {
                printf("Invalid binary number. Please try again.\n");
            }
        } else if (base == 10) {
            if (scanf("%lld", &operand) == 1) {
                clearInputBuffer(); // Clear the input buffer
                return operand;
            } else {
                clearInputBuffer(); // Clear the input buffer in case of non-integer input
                printf("Invalid input. Please enter a valid number.\n");
            }
        } else if (base == 16) {
            printf("0x");
            if (scanf("%llx", &operand) == 1) {
                clearInputBuffer(); // Clear the input buffer
                return operand;
            } else {
                clearInputBuffer(); // Clear the input buffer in case of invalid hexadecimal input
                printf("Invalid hexadecimal number. Please try again.\n");
            }
        } else {
            printf("Invalid base.\n");
            exit(1);
        }
    }
}
