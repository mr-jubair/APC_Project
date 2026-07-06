#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"

// Status codes 
#define SUCCESS		1
#define FAILURE		0

// Return values 
#define SAME		0
#define OPERAND1	1
#define OPERAND2	2

// Structure for storing each digit in a doubly linked list
typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} node;

// Perform addition of two large numbers
void addition(node *tail1, node *tail2, node **headR, node **tailR);

// Perform subtraction of two large numbers
void subtraction(node *head1, node *tail1, node *head2, node *tail2, node **headR, node **tailR);

// Perform multiplication of two large numbers
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);

// Perform division of two large numbers
void division(node *head1, node *head2, node **headR, node **tailR);

// Validate command line arguments
int cla_validation(int argc, char *argv[]);

// Validate the given operand string
int validate_operand(char *str);

// Create a linked list from the operand string
void create_list(char *opr, node **head, node **tail);

// Insert a digit at the beginning of the list
int insert_first(node **head, node **tail, int data);

// Insert a digit at the end of the list
int insert_last(node **head, node **tail, int data);

// Delete all nodes from the list
int delete_list(node **head, node **tail);

// Display the number stored in the list
void print_list(node *head);

// Compare two operand lists
int compare_list(node *head1, node *head2);

// Find the number of digits in the list
int list_len(node *head);

// Remove leading zeros from the list
void remove_pre_zeros(node **head);

#endif