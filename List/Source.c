#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>


typedef struct {
	int ConnectedTop;
	struct top* next;
} top;

typedef struct {
	int name;
	struct top* p;
	struct TopList* next;
} TopList;

TopList* first = NULL;
TopList* CurrentTop = NULL;

void PrintList() {
	TopList* current = first;
	top* counter = NULL;
	while (current != NULL) {
		counter = current->p;
		printf("%i: ", current->name);
		while (counter != NULL) {
			printf("%i ", counter->ConnectedTop);
			counter = counter->next;
		}
		printf("\n");
		current = current->next;
	}
}

void AddTop(int k) {
	TopList* NewTopList = (TopList*)malloc(sizeof(TopList));
	NewTopList->name = k;
	NewTopList->p = NULL;
	NewTopList->next = NULL;
	if (first == NULL) {
		first = NewTopList;
		CurrentTop = first;
	}
	else {
		TopList* current = first;
		TopList* previous = NULL;

		while (current != NULL) {
			previous = current;
			current = current->next;
		}
		previous->next = NewTopList;
		CurrentTop = previous->next;
	}
}

void add(int param) {
	top* new_top = (top*)malloc(sizeof(top));
	new_top->ConnectedTop = param;
	new_top->next = NULL;
	if (CurrentTop->p == NULL) {
		CurrentTop->p = new_top;
	}
	else {
		top* current = CurrentTop->p;
		top* previous = NULL;
		while (current != NULL) {
			previous = current;
			current = current->next;
		}
		previous->next = new_top;
	}
}

void open(char* filename) {
	int k = 1, j = 1;
	char sym;

	FILE* file;
	file = fopen(filename, "r+");
	if (file == NULL) {
		printf("Error");
		exit(0);
	}

	sym = fgetc(file);
	while (sym != EOF) {
		AddTop(k);
		while (sym != '\n' && sym != EOF) {
			if (sym == '1') {
				add(j);
			}
			j += 1;
			sym = fgetc(file);
		}
		j = 1;
		k += 1;
		sym = fgetc(file);
	}
	fclose(file);
}

void FreeMemory() {
	TopList* current = first, * previous;
	top* curr = NULL, * prev = NULL;

	while (current != NULL) {
		previous = current;
		curr = current->p;
		while (curr != NULL) {
			prev = curr;
			curr = curr->next;
			free(prev);
		}
		current = current->next;
		free(previous);
	}
	free(current);
}

int main() {
	open("Test.txt");
	PrintList();
	FreeMemory();

	return 0;
}