#include "apc.h"

void division(node *head1, node *head2, node **headR, node **tailR)
{
    // Find the tail of the first operand
    node *tail1 = head1;

    // Find the tail of the second operand
    node *tail2 = head2;

    while(tail1->next)
        tail1 = tail1->next;

    while(tail2->next)
        tail2 = tail2->next;

    // Store the quotient value
    int count = 0;

    // Repeatedly subtract divisor from dividend
    while(compare_list(head1, head2) != OPERAND2)
    {
        node *tempHead = NULL;
        node *tempTail = NULL;

        // Perform one subtraction step
        subtraction(head1, tail1, head2, tail2, &tempHead, &tempTail);

        // Free the previous dividend list
        delete_list(&head1, &tail1);

        // Update dividend with the subtraction result
        head1 = tempHead;
        tail1 = tempTail;

        // Increment the quotient count
        count++;
    }

    // Convert quotient into string format
    char quotient[50];

    sprintf(quotient, "%d", count);

    // Store the quotient in the result list
    create_list(quotient, headR, tailR);
}