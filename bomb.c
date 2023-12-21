/***************************************************************************
 * Dr. Evil's Insidious Bomb, Version 1.1
 * Copyright 2011, Dr. Evil Incorporated. All rights reserved.
 *
 * LICENSE:
 *
 * Dr. Evil Incorporated (the PERPETRATOR) hereby grants you (the
 * VICTIM) explicit permission to use this bomb (the BOMB).  This is a
 * time limited license, which expires on the death of the VICTIM.
 * The PERPETRATOR takes no responsibility for damage, frustration,
 * insanity, bug-eyes, carpal-tunnel syndrome, loss of sleep, or other
 * harm to the VICTIM.  Unless the PERPETRATOR wants to take credit,
 * that is.  The VICTIM may not distribute this bomb source code to
 * any enemies of the PERPETRATOR.  No VICTIM may debug,
 * reverse-engineer, run "strings" on, decompile, decrypt, or use any
 * other technique to gain knowledge of and defuse the BOMB.  BOMB
 * proof clothing may not be worn when handling this program.  The
 * PERPETRATOR will not apologize for the PERPETRATOR's poor sense of
 * humor.  This license is null and void where the BOMB is prohibited
 * by law.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct listNode {
    int val;
    int index;
    struct listNode *next;
};

void phase_1(char *input)
{
#if defined(PROBLEM)
    if (strings_not_equal(input, "I turned the moon into something I like to call a Death Star.") != 0)
	explode_bomb();
#elif defined(SOLUTION)
    printf("I turned the moon into something I like to call a Death Star.\n");
#else
    invalid_phase("1c");
#endif
}
/* 
 * phase2c.c - To defeat this stage the user must enter sequence of 
 * 6 numbers such that x[i] = x[i+3], not all zero.
 */
void phase_2(char *input)
{
#if defined(PROBLEM)
    int ii, sum = 0;
    int numbers[6];

    read_six_numbers(input, numbers);

    for (ii = 0; ii < 3; ii++) {
	if (numbers[ii] != numbers[ii+3])
	    explode_bomb();
	sum += numbers[ii];
    }

    if (sum == 0)
	explode_bomb();
#elif defined(SOLUTION)
    printf("1 2 3 1 2 3\n");
#else
    invalid_phase("2c");
#endif
}

/* 
 * phase3a.c - A long switch statement that the compiler should implement
 * with a jump table. The user has to enter both an index into the table 
 * and a value stored there.
 */
void phase_3(char *input)
{
#if defined(PROBLEM)
    int index, val, x = 0;
    int numScanned = 0;

    numScanned = sscanf(input, "%d %d", &index, &val);

    if (numScanned < 2)
	explode_bomb();

    switch(index) {
    case 0:
	x = 61;
	break;
    case 1:
	x = 439;
	break;
    case 2:
	x = 164;
	break;
    case 3:
	x = 443;
	break;
    case 4:
	x = 346;
	break;
    case 5:
	x = 639;
	break;
    case 6:
	x = 704;
	break;
    case 7:
	x = 153;
	break;
    default:
	explode_bomb();
    }

    if (x != val)
	explode_bomb();
#elif defined(SOLUTION)
    printf("5 639\n");
#else
    invalid_phase("3a");
#endif
}
/* 
 * phase4b.c - A recursive function to sort out. 
 * Computes powers of 7, must match the power of 7 randomly generated. 
 */
#if defined(PROBLEM)
int func4(int i) {
    if (i <= 0) {
	return 1;
    }
    return 7 * func4(i - 1);
}
#elif defined(SOLUTION)
/* given y = 7^x , return x */
int func4_inverse(int y) {
    switch (y) {
    case 49: return 2;
    case 343 : return 3; 
    case 2401: return 4;
    case 16807: return 5; 
    case 117649: return 6; 
    case 823543: return 7; 
    case 5764801: return 8; 
    default:
	fprintf(stderr, "ERROR: bad input in phase4b\n");
	exit(8);
    }
}
#endif

void phase_4(char *input) {
#if defined(PROBLEM)
    int result, val, numScanned = sscanf(input, "%d", &val);

    if((numScanned != 1) || (val < 1)) {
	explode_bomb();
    }

    result = func4(val);

    if(result != 117649) {
	explode_bomb();
    }
#elif defined(SOLUTION)
    printf("%d %s\n", func4_inverse(117649), SECRET_PHRASE);
#else
    invalid_phase("4b");
#endif
}
/* 
 * phase5c.c - This stage requires the user to enter 6 unique numbers that 
 * are used as offsets into the integer array.  The sum of the six numbers
 * indexed by the offsets must equal a particular sum.             
 */
void phase_5(char *input)
{
#if defined(PROBLEM)
    static int array[] = {
	2,
	10,
	6,
	1,
	12,
	16,
	9,
	3,
	4,
	7,
	14,
	5,
	11,
	8,
	15,
	13,
    };
    int i, sum;
    int length;

    length = string_length(input);
    if (length != 6)
      explode_bomb();

    sum = 0;
    for (i = 0; i < 6; i++)
      sum += array[ (input[i] & 0x0f) ];

    if (sum != 37)
      explode_bomb();
#elif defined(SOLUTION)
    printf("1<1000\n");
#else
    invalid_phase("5c");
#endif
}

/* 
 * phase6b.c - The user has to enter the node numbers (from 1 to 6) in 
 * the order that they will occur when the list is sorted.
 */

struct listNode node6 = {344, 6, NULL};
struct listNode node5 = {630, 5, &node6};
struct listNode node4 = {543, 4, &node5};
struct listNode node3 = {262, 3, &node4};
struct listNode node2 = {968, 2, &node3};
struct listNode node1 = {206, 1, &node2};

#if defined(SOLUTION)
/* Sort list */
listNode *fun6(listNode *start)
{
    listNode *head = start;
    listNode *p, *q, *r;

    head = start;
    p = start->next;
    head->next = NULL;

    while (p != NULL) {
	r = head;
	q = head;

	while ((r != NULL) && (r->value > p->value)) {
	    q = r;
	    r = r->next;
	}

	if (q != r)
	    q->next = p;
	else
	    head = p;

	q = p->next;
	p->next = r;

	p = q;
    }

    return head;
}
#endif

void phase_6(char *input)
{
#if defined(PROBLEM)
    listNode *start = &node1;
    listNode *p;
    int indices[6];
    listNode *pointers[6];
    int i, j;

    read_six_numbers(input, indices);

    /* Check the range of the indices and whether or not any repeat */
    for (i = 0; i < 6; i++) {
	if ((indices[i] < 1) || (indices[i] > 6))
	    explode_bomb();
	
	for (j = i + 1; j < 6; j++) {
	    if (indices[i] == indices[j])
		explode_bomb();
	}
    }

    /* Rearrange the list according to the user input */
    for (i = 0; i < 6; i++) {
	p = start;
	for (j = 1; j < indices[i]; j++)
	    p = p -> next;
	pointers[i] = p;
    }

    start = pointers[0];
    p = start;

    for (i = 1; i < 6; i++) {
	p->next = pointers[i];
	p = p->next;
    }
    p->next = NULL;

    /* Now see if the list is sorted */
    p = start;
    for (i = 0; i < 5; i++) {
	if (p->value < p->next->value)
	    explode_bomb();
	
	p = p->next;
    }
#elif defined(SOLUTION)
    listNode *start = &node1;
    listNode *p;

    /* sort */
    start = fun6(start);

    /* emit the node indices of the sorted list */
    p = start;
    while (p) {
	printf("%d ", p->index);
	p = p->next;
    }
    printf("\n");
#else
    invalid_phase("6b");
#endif
}



/* 
 * phase7.c - The infamous secret stage! 
 * The user has to find leaf value given path in a binary tree.
 */

typedef struct treeNodeStruct
{
    int value;
    struct treeNodeStruct *left, *right;
} treeNode;

/* balanced binary tree containing randomly chosen values */
treeNode n48 = {1001, NULL, NULL};
treeNode n46 = {47, NULL, NULL};
treeNode n43 = {20, NULL, NULL};
treeNode n42 = {7, NULL, NULL};
treeNode n44 = {35, NULL, NULL};
treeNode n47 = {99, NULL, NULL};
treeNode n41 = {1, NULL, NULL};
treeNode n45 = {40, NULL, NULL};
treeNode n34 = {107, &n47, &n48};
treeNode n31 = {6, &n41, &n42};
treeNode n33 = {45, &n45, &n46};
treeNode n32 = {22, &n43, &n44};
treeNode n22 = {50, &n33, &n34};
treeNode n21 = {8, &n31, &n32};
treeNode n1 = {36, &n21, &n22};

/* 
 * Searches for a node in a binary tree and returns path value.
 * 0 bit denotes left branch, 1 bit denotes right branch
 * Example: the path to leaf value "35" is left, then right,
 * then right, and thus the path value is 110(base 2) = 6.
 */

int fun7(treeNode* node, int val)
{
    if (node == NULL) 
	return -1;
  
    if (val < node->value) 
	return fun7(node->left, val) << 1;
    else if (val == node->value) 
	return 0;
    else 
	return (fun7(node->right, val) << 1) + 1;
}
     
void secret_phase()
{

#if defined(PROBLEM)
    char *input = read_line();
    int target = atoi(input);
    int path;

    /* Make sure target is in the right range */
    if ((target < 1) || (target > 1001))
	explode_bomb();

    /* Determine the path to the given target */
    path = fun7(&n1, target);

    /* Compare the retrieved path to a random path */
    if (path != 4)
	explode_bomb();
  
    printf("Wow! You've defused the secret stage!\n");

    phase_defused();
#elif defined(SOLUTION)
    int path = 4;
    treeNode *node = &n1;
    
    node = (path    & 0x1) ? node->right : node->left;
    node = (path>>1 & 0x1) ? node->right : node->left;
    node = (path>>2 & 0x1) ? node->right : node->left;
    printf("%d\n", node->value);
#else
    invalid_phase("7");
#endif
}

/* 
 * Note to self: Remember to erase this file so my victims will have no
 * idea what is going on, and so they will all blow up in a
 * spectaculary fiendish explosion. -- Dr. Evil 
 */

FILE *infile;

int main(int argc, char *argv[])
{
    char *input;

    /* Note to self: remember to port this bomb to Windows and put a 
     * fantastic GUI on it. */

    /* When run with no arguments, the bomb reads its input lines 
     * from standard input. */
    if (argc == 1) {  
	infile = stdin;
    } 

    /* When run with one argument <file>, the bomb reads from <file> 
     * until EOF, and then switches to standard input. Thus, as you 
     * defuse each phase, you can add its defusing string to <file> and
     * avoid having to retype it. */
    else if (argc == 2) {
	if (!(infile = fopen(argv[1], "r"))) {
	    printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
	    exit(8);
	}
    }

    /* You can't call the bomb with more than 1 command line argument. */
    else {
	printf("Usage: %s [<input_file>]\n", argv[0]);
	exit(8);
    }

    /* Do all sorts of secret stuff that makes the bomb harder to defuse. */
    initialize_bomb();

    printf("Welcome to my fiendish little bomb. You have 6 phases with\n");
    printf("which to blow yourself up. Have a nice day!\n");

    /* Hmm...  Six phases must be more secure than one phase! */
    input = read_line();             /* Get input                   */
    phase_1(input);                  /* Run the phase               */
    phase_defused();                 /* Drat!  They figured it out!
				      * Let me know how they did it. */
    printf("Phase 1 defused. How about the next one?\n");

    /* The second phase is harder.  No one will ever figure out
     * how to defuse this... */
    input = read_line();
    phase_2(input);
    phase_defused();
    printf("That's number 2.  Keep going!\n");

    /* I guess this is too easy so far.  Some more complex code will
     * confuse people. */
    input = read_line();
    phase_3(input);
    phase_defused();
    printf("Halfway there!\n");

    /* Oh yeah?  Well, how good is your math?  Try on this saucy problem! */
    input = read_line();
    phase_4(input);
    phase_defused();
    printf("So you got that one.  Try this one.\n");
    
    /* Round and 'round in memory we go, where we stop, the bomb blows! */
    input = read_line();
    phase_5(input);
    phase_defused();
    printf("Good work!  On to the next...\n");

    /* This phase will never be used, since no one will get past the
     * earlier ones.  But just in case, make this one extra hard. */
    input = read_line();
    phase_6(input);
    phase_defused();

    /* Wow, they got it!  But isn't something... missing?  Perhaps
     * something they overlooked?  Mua ha ha ha ha! */
    
    return 0;
}
