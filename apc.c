#include "apc.h"
#include<ctype.h>

int cla_validation(int argc, char *argv[])
{
    // Validate the number of command line arguments
    if(argc != 4)
        return FAILURE;

    // Ensure the operator contains only one character
    if(strlen(argv[2]) != 1)
        return FAILURE;

    char op = argv[2][0];

    // Check whether the operator is supported
    if(op != '+' && op != '-' && op != 'x' && op != 'X' && op != '/')
    {
        return FAILURE;
    }

    // Validate the first operand
    if(validate_operand(argv[1]) == FAILURE)
        return FAILURE;

    // Validate the second operand
    if(validate_operand(argv[3]) == FAILURE)
        return FAILURE;

    return SUCCESS;
}

int validate_operand(char *str)
{
    int i = 0;

    // Reject empty operands
    if(str[0] == '\0')
        return FAILURE;

    // Handle optional sign at the beginning
    if(str[0] == '-' || str[0] == '+')
    {
        // Reject sign without digits
        if(str[1] == '\0')
            return FAILURE;

        // Reject multiple consecutive signs
        if(str[1] == '-' || str[1] == '+')
            return FAILURE;

        i = 1;
    }

    // Verify that all remaining characters are digits
    for(; str[i]; i++)
    {
        if(!isdigit(str[i]))
            return FAILURE;
    }

    return SUCCESS;
}

int insert_first(node **head, node **tail, int data)
{
    // Allocate memory for a new node
    node *new = malloc(sizeof(node));

    // Return failure if memory allocation fails
    if (new == NULL)
        return FAILURE;

    // Initialize the new node
    new->data = data;
    new->prev = NULL;
    new->next = *head;

    // Update previous link of existing head node
    if (*head)
        (*head)->prev = new;
    else
        *tail = new;

    // Make the new node as head
    *head = new;

    return SUCCESS;
}

int insert_last(node **head, node **tail, int data)
{
    // Allocate memory for a new node
    node *new = malloc(sizeof(node));

    // Return failure if memory allocation fails
    if (new == NULL)
        return FAILURE;

    // Initialize the new node
    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    // Link the new node at the end of the list
    if (*tail)
        (*tail)->next = new;
    else
        *head = new;

    // Update the tail pointer
    *tail = new;

    return SUCCESS;
}

void create_list(char *str, node **head, node **tail)
{
    // Convert each digit character into a list node
    while (*str)
    {
        insert_last(head, tail, *str - '0');
        str++;
    }
}

void print_list(node *head)
{
    // Display all digits present in the list
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
}

int delete_list(node **head, node **tail)
{
    node *temp;

    // Free all nodes in the list
    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    // Reset the tail pointer
    *tail = NULL;

    return SUCCESS;
}

int list_len(node *head)
{
    int count = 0;

    // Count the number of nodes in the list
    while (head)
    {
        count++;
        head = head->next;
    }

    return count;
}

void remove_pre_zeros(node **head)
{
    node *temp;

    // Remove leading zeros from the result list
    while (*head && (*head)->data == 0 && (*head)->next)
    {
        temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

int compare_list(node *head1, node *head2)
{
    // Find the lengths of both operands
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    // Compare operand lengths first
    if (len1 > len2)
    {
        return OPERAND1;
    }
    else if (len1 < len2)
    {
        return OPERAND2;
    }

    // Compare digits one by one when lengths are equal
    while (head1 && head2)
    {
        if (head1->data > head2->data)
        {
            return OPERAND1;
        }
        else if (head1->data < head2->data)
        {
            return OPERAND2;
        }

        head1 = head1->next;
        head2 = head2->next;
    }

    // Both operands are equal
    return SAME;
}