#include "apc.h"

void subtraction(node *head1, node *tail1, node *head2, node *tail2, node **headR, node **tailR)
{
    // Store borrow generated during subtraction
    int borrow = 0;

    int diff;

    // Traverse both operands from least significant digit
    while (tail1 || tail2)
    {
        int d1 = 0;
        int d2 = 0;

        // Get current digit from first operand
        if (tail1)
            d1 = tail1->data;

        // Get current digit from second operand
        if (tail2)
            d2 = tail2->data;

        // Subtract digits along with borrow
        diff = d1 - d2 - borrow;

        // Handle borrow when result becomes negative
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        // Insert the result digit at the beginning
        insert_first(headR, tailR, diff);

        // Move to previous digit of first operand
        if (tail1)
            tail1 = tail1->prev;

        // Move to previous digit of second operand
        if (tail2)
            tail2 = tail2->prev;
    }

    // Remove leading zeros from the result
    remove_pre_zeros(headR);
}