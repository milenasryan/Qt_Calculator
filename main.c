#include "calculator.h"
#include <stdio.h>

int main() {
    int inputBase, outputBase;

    printf("Bitwise Calculator\n");

    // Get input number system
    inputBase = getNumberSystem();

    // Get output number system
    outputBase = getNumberSystem();

    while (1) {
        // Display menu and get operation choice
        int choice = getMenuChoice();

        if (choice == 7) {
            printf("Program terminated\n");
            break;
        }

        // Get operands and perform the operation
        long long int operand1, operand2;
        operand1 = getOperand(inputBase);
        operand2 = getOperand(inputBase);

        // Perform the chosen bitwise operation
        performBitwiseOperation(choice, operand1, operand2, inputBase);

        // Convert and display the result in the output number system
        convertAndDisplayResult(result, outputBase);

        // Check if the operation is "Replay"
        if (choice == 7) {
            continue; // Continue to the next iteration without prompting for a new operation
        }
    }

    return 0;
}
