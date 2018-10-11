#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define SIZE_ALPHA (26)
#define CHAR_TO_INDEX(c) ((int) c - (int) 'a')

typedef struct Trie {
	struct Trie *children[SIZE_ALPHA];
	bool is_Leaf;
} node;

node *new_Node(void);
void insert_Trie(node *root, char *string);
bool search_Trie(node *root, char *string);
void string_toLower(char *string);
bool check_valid_word(char *string);
void remove_newline(char *string);
void load_dictionary(void);
bool is_Word(char *string);
void swap(char *a, char *b);
void real_perm(char *A, int L, int R, char *answer);
void run_combo(char *A, int choose_num, char *answer);
void combo(char* A, int total_num, int iterator, char* B, int chosen_num, int chosen_index, char *answer);
char *longest_word(char *string);
