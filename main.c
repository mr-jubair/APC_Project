/*
Name : N.S.Mahammed Jubair
Date : 26/06/2026

Project Description:

The Arbitrary Precision Calculator (APC) is a command-line application implemented in C to perform arithmetic operations on integers 
that are larger than the range supported by built-in data types. To overcome this limitation, every digit of a number is stored as a 
node in a Doubly Linked List (DLL), allowing calculations on numbers of virtually any size.

The application follows the same step-by-step arithmetic process used in manual calculations. By combining linked list operations with 
dynamic memory allocation, it performs accurate computations while efficiently handling large numbers and various input conditions.

The project includes the following functionalities:

1. Addition
   - Computes the sum of two large integers.
   - Works with both positive and negative values.
   - Properly manages carry generated during addition.

2. Subtraction
   - Calculates the difference between two operands of any length.
   - Produces the correct sign for the final answer.
   - Handles borrow operations during computation.

3. Multiplication
   - Implements multiplication using the traditional long multiplication
     technique.
   - Stores intermediate products in temporary linked lists.
   - Combines all partial products to obtain the final result.

4. Division
   - Calculates the quotient using the repeated subtraction approach.
   - Supports both positive and negative operands.
   - Detects division by zero and prevents invalid execution.

5. Input Validation
   - Verifies the correctness of command-line inputs.
   - Rejects invalid operands, unsupported characters and incorrect formats.
   - Ensures that only valid integer values are processed.

6. Linked List Management
   - Dynamically creates linked lists for operands and results.
   - Uses insertion and deletion operations for efficient memory handling.
   - Releases temporary memory after every calculation.

7. Result Presentation
   - Eliminates unnecessary leading zeros from the output.
   - Displays the appropriate sign based on the operation performed.
   - Prints the final answer in a clear and user-friendly format.

Overall, this project demonstrates the practical use of Doubly Linked Lists, dynamic memory management, modular programming, 
and arithmetic algorithms. It provides hands-on experience in solving real-world programming problems where standard data types 
are insufficient for handling very large integers.

***********************************************************************************************************************************************
*/

#include "apc.h"

int main(int argc, char *argv[])
{
    // Initialize operand and result lists
    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;
    node *headR = NULL, *tailR = NULL;

    // Validate command line arguments
    if (cla_validation(argc, argv) == FAILURE)
    {
        printf(BOLD RED"Invalid Arguments\n"RESET);
        return FAILURE;
    }

    // Store signs of both operands
    int sign1 = 0;
    int sign2 = 0;

    char *op1 = argv[1];
    char *op2 = argv[3];

    // Check sign of first operand
    if(op1[0] == '-')
    {
        sign1 = 1;
        op1++;
    }
    else if(op1[0] == '+')
    {
        op1++;
    }

    // Check sign of second operand
    if(op2[0] == '-')
    {
        sign2 = 1;
        op2++;
    }
    else if(op2[0] == '+')
    {
        op2++;
    }

    // Create linked lists for both operands
    create_list(op1, &head1, &tail1);
    create_list(op2, &head2, &tail2);

    // Remove leading zeros from operands
    remove_pre_zeros(&head1);
    remove_pre_zeros(&head2);

    char oper = argv[2][0];
    int sign = 0;

    // Perform operation based on the operator
    switch (oper)
    {
        case '+':
        {
            int ret;

            // Add two positive numbers
            if(sign1 == 0 && sign2 == 0)
            {
                addition(tail1, tail2, &headR, &tailR);
            }

            // Add two negative numbers
            else if(sign1 == 1 && sign2 == 1)
            {
                sign = 1;
                addition(tail1, tail2, &headR, &tailR);
            }

            // Add positive and negative numbers
            else if(sign1 == 0 && sign2 == 1)
            {
                // Compare operands before subtraction
                ret = compare_list(head1, head2);

                if(ret == OPERAND1 || ret == SAME)
                {
                    subtraction(head1, tail1, head2, tail2, &headR, &tailR);
                }
                else
                {
                    sign = 1;
                    subtraction(head2, tail2, head1, tail1, &headR, &tailR);
                }
            }

            // Add negative and positive numbers
            else
            {
                // Compare operands before subtraction
                ret = compare_list(head1, head2);

                if(ret == OPERAND1)
                {
                    sign = 1;
                    subtraction(head1, tail1, head2, tail2, &headR, &tailR);
                }
                else
                {
                    subtraction(head2, tail2, head1, tail1, &headR, &tailR);
                }
            }
            break;
        }

        case '-':
        {
            int ret;

            // Subtract two positive numbers
            if(sign1 == 0 && sign2 == 0)
            {
                ret = compare_list(head1, head2);

                if(ret == OPERAND1 || ret == SAME)
                {
                    subtraction(head1, tail1, head2, tail2, &headR, &tailR);
                }
                else
                {
                    sign = 1;
                    subtraction(head2, tail2, head1, tail1, &headR, &tailR);
                }
            }

            // Subtract positive number from negative number
            else if(sign1 == 1 && sign2 == 0)
            {
                sign = 1;
                addition(tail1, tail2, &headR, &tailR);
            }

            // Convert subtraction of negative number into addition
            else if(sign1 == 0 && sign2 == 1)
            {
                addition(tail1, tail2, &headR, &tailR);
            }

            // Handle subtraction of two negative numbers
            else
            {
                ret = compare_list(head1, head2);

                if(ret == OPERAND1)
                {
                    sign = 1;
                    subtraction(head1, tail1, head2, tail2, &headR, &tailR);
                }
                else if(ret == OPERAND2)
                {
                    subtraction(head2, tail2, head1, tail1, &headR, &tailR);
                }
                else
                {
                    // Result is zero when both operands are equal
                    insert_first(&headR, &tailR, 0);
                }
            }

            break;
        }

        case 'x':
        case 'X':
        case '*':
        {
            // Determine sign of multiplication result
            if(sign1 != sign2)
                sign = 1;
            else
                sign = 0;

            // Perform multiplication
            multiplication(tail1, tail2, &headR, &tailR);
            break;
        }

        case '/':
        {
            // Check for division by zero
            if(head2->data == 0 && head2->next == NULL)
            {
                printf(RED"Division by Zero is not Possible\n"RESET);
                return FAILURE;
            }

            // Determine sign of division result
            if(sign1 != sign2)
                sign = 1;
            else
                sign = 0;

            // Perform division
            division(head1, head2, &headR, &tailR);
            break;
        }

        default:
            // Handle invalid operators
            printf(RED"Invalid Operator\n"RESET);
            return FAILURE;
    }

    // Remove negative sign for zero result
    if(headR && headR->data == 0 && headR->next == NULL)
    {
        sign = 0;
    }

    // Display the final result
    printf("Result : ");
    printf(YELLOW);

    if(sign)
        printf("-");

    print_list(headR);
    printf(RESET"\n");

    return SUCCESS;
}