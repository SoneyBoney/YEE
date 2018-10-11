#include "lib/countdown.h"

node *dictionary_head;


node *new_Node(void) {
	node *root = (node *) malloc(sizeof(node));
	if(root != NULL) {
		root -> is_Leaf = false;
		for(int i = 0; i < SIZE_ALPHA; i++)
			root -> children[i] = NULL;
	}
	return root;
}

void insert_Trie(node *root, char *string) {
	node *iterator = root;
	int length = strlen(string);
	int index;
	for(int i = 0; i < length; i++) {
		index = CHAR_TO_INDEX(string[i]);
		if(iterator -> children[index] == NULL) {
			iterator -> children[index] = new_Node();
		}
		iterator = iterator -> children[index];
	}
	iterator -> is_Leaf = true;
	return;
}

bool search_Trie(node *root, char *string) {
	node *iterator = root;
	int length = strlen(string);
	int index;
	for(int i = 0; i < length; i++) {
		index = CHAR_TO_INDEX(string[i]);
		if(iterator -> children[index] == NULL)
			return false;
		iterator = iterator -> children[index];
	}
	return ((iterator -> is_Leaf) && (iterator != NULL));
}

void string_toLower(char *string) {
	char temp;
	int length = strlen(string);
	for(int i = 0; i < length; i++) {
		temp = string[0];
		string[0] = (char) tolower(temp);
	}
	return;
}

bool check_valid_word(char *string) {
	char check;
	while(*string != '\0') {
		check = (int) CHAR_TO_INDEX(*string);
		if((check < 0 || check > 26) && (*string != '\n')) {
			return false;
		}
		string++;
	}
	return true;
}

void remove_newline(char *string) {
	while(*string != '\0') {
		if(*string == '\n')
			*string = '\0';
		string++;
	}
	return;
}

void load_dictionary(void) {
	char buffer[30];
	FILE *fp = fopen("dict.txt", "r");
	dictionary_head = new_Node();
	if(dictionary_head != NULL) {
		int i = 0;
		while(fgets(buffer, 30, fp) != NULL) {
			string_toLower(buffer);
			if(check_valid_word(buffer)) {
				remove_newline(buffer);
				insert_Trie(dictionary_head, buffer);
				i++;
			}
		}
	}
	else
		exit(1);
	return;
}

bool is_Word(char *string) {
	string_toLower(string);
	return search_Trie(dictionary_head, string);
}

/* Permutation/Combination functions*/

void swap(char *a, char *b) {
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void real_perm(char *A, int L, int R, char *answer) {
	int i;
	if(L == R) {
		if(is_Word(A))
			strcpy(answer, A);
		return;
	}
	else {
		for(i = L; i <= R; i++) {
			swap((A+L),(A+i));
			real_perm(A, L+1, R, answer);
			swap((A+L),(A+i));
		}
	}
}

void run_combo(char *A, int choose_num, char *answer) {
	int total_num = strlen(A);
	char *B = malloc(sizeof(char)*(choose_num + 1));
	combo(A, total_num, 0, B, choose_num, 0, answer);
}


void combo(char* A, int total_num, int iterator, char* B, int chosen_num, int chosen_index, char *answer) {
	if(chosen_index == chosen_num) {
		B[chosen_num + 1] = '\0';
		real_perm(B, 0, chosen_num - 1, answer);
		return;
	}
	if(iterator == total_num) {
		return;
	}
	B[chosen_index] = A[iterator];
	combo(A, total_num, iterator+1, B, chosen_num, chosen_index+1, answer);
	combo(A, total_num, iterator+1, B, chosen_num, chosen_index, answer);
}

char *longest_word(char *string) {
	int length = strlen(string);
	char *word = malloc(sizeof(char)*length);
	int j;
	word[0] = '\0';
	for(int i = length; i > 0; i--) {
		run_combo(string, i, word);
		if(word[0] != '\0')
			return word;
		word[0] = '\0';
	}
	return NULL;
}


int main(void) {
	char buffer[51];
	buffer[50] = '\0';
	char *answer;
	int choose_num;
	printf("Enter string please: ");
	scanf("%s", buffer);
	if(buffer[50] != '\0') {
		printf("please enter string shorter || equal to 50 characters\n");
		exit(1);
	}

	if(!check_valid_word(buffer)){
		printf("please only use characters\n");
		exit(1);
	}

	load_dictionary();
	answer = longest_word(buffer);
	if(answer == NULL)
		printf("no longest word RIP\n");
	printf("longest word is: %s\n", answer);
	return 1;

}