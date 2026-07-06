#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int sum, digit;
    int carry = 0;   // Store carry generated during addition

    // Traverse both operands from least significant digit
    while (tail1 || tail2)
    {
        // Add digits from both operands along with carry
        if (tail1 && tail2)
            sum = tail1->data + tail2->data + carry;

        // Add remaining digit from first operand
        else if (tail1)
            sum = tail1->data + carry;

        // Add remaining digit from second operand
        else
            sum = tail2->data + carry;

        // Extract the current result digit
        digit = sum % 10;

        // Calculate carry for the next iteration
        carry = sum / 10;

        // Insert the result digit at the beginning of the list
        insert_first(headR, tailR, digit);

        // Move to the previous digit of first operand
        if (tail1)
            tail1 = tail1->prev;

        // Move to the previous digit of second operand
        if (tail2)
            tail2 = tail2->prev;
    }

    // Insert the final carry if present
    if (carry)
        insert_first(headR, tailR, carry);
}