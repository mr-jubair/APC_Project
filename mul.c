#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *t1;

    // Point to the last digit of second operand
    node *t2 = tail2;

    // Store accumulated multiplication result
    node *headR1 = NULL;
    node *tailR1 = NULL;

    // Store intermediate multiplication result
    node *headR2 = NULL;
    node *tailR2 = NULL;

    int carry;
    int product;
    int digit;

    // Track the number of trailing zeros to append
    int count = 0;

    // Process each digit of the second operand
    while(t2)
    {
        carry = 0;

        // Start multiplication from the last digit of first operand
        t1 = tail1;

        // Multiply current digit with all digits of first operand
        while(t1)
        {
            product = (t1->data * t2->data) + carry;

            // Extract the result digit
            digit = product % 10;

            // Calculate carry for next multiplication
            carry = product / 10;

            // Store digit in intermediate result list
            insert_first(&headR2, &tailR2, digit);

            t1 = t1->prev;
        }

        // Insert remaining carry if present
        if(carry)
        {
            insert_first(&headR2, &tailR2, carry);
        }

        // Append zeros based on place value
        for(int i = 0; i < count; i++)
        {
            insert_last(&headR2, &tailR2, 0);
        }

        // Store first partial product directly
        if(headR1 == NULL)
        {
            headR1 = headR2;
            tailR1 = tailR2;
        }
        else
        {
            // Add current partial product to accumulated result
            addition(tailR1, tailR2, headR, tailR);

            // Free temporary result lists
            delete_list(&headR1, &tailR1);
            delete_list(&headR2, &tailR2);

            // Update accumulated result
            headR1 = *headR;
            tailR1 = *tailR;

            // Reset result pointers for next iteration
            *headR = NULL;
            *tailR = NULL;
        }

        // Reset intermediate result list
        headR2 = NULL;
        tailR2 = NULL;

        // Increase zero count for next partial product
        count++;

        // Move to previous digit of second operand
        t2 = t2->prev;
    }

    // Remove leading zeros from the final result
    remove_pre_zeros(&headR1);

    // Return final result to the caller
    *headR = headR1;
    *tailR = tailR1;
}