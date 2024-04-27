#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define SIZE 20


typedef struct List {
    char surname[SIZE];
    char name[SIZE];
    char lastname[SIZE];
    struct List* next;
} List;

void GetStr(List* man, char* surname, char* name, char* father) {
    strcpy(man->surname, surname);
    strcpy(man->name, name);
    strcpy(man->lastname, father);
}

List* ToList(char* tmp) {
    List* result;
    int i = 0, j = 0, k = 0;
    char surname[SIZE], name[SIZE], lastname[SIZE];
    char q;
    while ((q = tmp[i]) != ' ') {
        surname[i] = q;
        i++;
    }
    surname[i] = '\0';
    i++;
    while ((q = tmp[i]) != ' ') {
        name[k] = q;
        i++;
        k++;
    }
    name[k] = '\0';
    i++;
    while ((q = tmp[i]) != '\0') {
        lastname[j] = q;
        i++;
        j++;
    }
    if (lastname[j - 1] == '\n' && j > 0) {
        lastname[j - 1] = '\0';
    }
    else {
        lastname[j] = '\0';
    }
    result = (List*)malloc(sizeof(List));
    if (result == NULL) {
        printf("not enough memory");
        return NULL;
    }
    GetStr(result, surname, name, lastname);
    return result;
}

void PrintList(List** top) {
    List* tmp = *top;
    while (tmp != NULL) {
        printf("%s %s %s\n", tmp->surname, tmp->name, tmp->lastname);
        tmp = tmp->next;
    }
}

int  Compare(List* man, List* input) {
    int length;
    if (input->surname != "") {
        length = strlen(input->surname);
        for (int i = 0; i < length; i++) {
            if (man->surname[i] != input->surname[i]) {
                //printf("not smth same");
                return 0;
            }
        }
    }
    if (input->name != "") {
        length = strlen(input->name); 
        for (int i = 0; i < length; i++) {
            if (man->name[i] != input->name[i]) {
                //printf("not smth same");
                return 0;
            }
        }
    }
    if (input->lastname != "") {
        length = strlen(input->lastname); 
        for (int i = 0; i < length; i++) {
            if (man->lastname[i] != input->lastname[i]) {
                //printf("not smth same");
                return 0;
            }
        }
    }
    return 1;
}

int PrintRequest(List** top, List* input) {
    int count = 0;
    List* tmp = (*top);

    while (tmp != NULL) {
        if (Compare(tmp, input) == 1) {
            printf("%s %s %s\n", tmp->surname, tmp->name, tmp->lastname);
            count++;
        }
        tmp = tmp->next; 
    }
    return count; //количество совпадений
}

int AddToList(List** top, List* man) {
    List* tmp = (*top);
    List* prev = NULL;

    if (*top == NULL) {
        man->next = *top;
        *top = man;
       // printf("that's all right");
        return 1;
    }

    while (tmp != NULL) {
        int SurnameFlag = strcmp(man->surname, tmp->surname);
        int NameFlag = strcmp(man->name, tmp->name);
        int FatherFlag = strcmp(man->lastname, tmp->lastname);

        if (SurnameFlag < 0) {
            if (prev == NULL) {
                man->next = (*top);
                (*top) = man;
                //printf("that's all right");
                return 1;
            }
            prev->next = man;
            man->next = tmp;
           // printf("that's all right");
            return 1;
        }

        else if (SurnameFlag == 0 && NameFlag < 0) {
            if (prev == NULL) {
                man->next = (*top);
                (*top) = man;
               // printf("that's all right");
                return 1;
            }
            prev->next = man;
            man->next = tmp;
           // printf("that's all right");
            return 1;
        } 
        else if (SurnameFlag == 0 && NameFlag == 0 && FatherFlag < 0) {
            if (prev == NULL) {
                man->next = (*top);
                (*top) = man;
               // printf("that's all right");
                return 1;
            }
            prev->next = man;
            man->next = tmp;
            //printf("that's all right");
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = man;
    man->next = NULL;
}


void FreeList(List** top) {
    List* tmp = (*top);
    if (tmp == NULL)
        return;

    while (*top != NULL) {
        tmp = *top;
        *top = (*top)->next;
        free(tmp);
    }
    free(*top);
}

int main() {
    List* top = NULL;
    List* input = NULL;
    FILE* file;

    file = fopen("List.txt", "r"); 
    if (file == NULL) {
        printf("error opening file");
        exit(1);
    }

    List* man = NULL;
    char* buffer = (char*)calloc(3 * SIZE, sizeof(char));
    while (!feof(file)) {
        fgets(buffer, 3 * SIZE, file);
        man = ToList(buffer);
        AddToList(&top, man);
    }
    PrintList(&top);
    
    printf("<<surname>> <<name>> <<second name>> : ");
    fgets(buffer, 3 * SIZE, stdin);
    input = ToList(buffer);
    int count = PrintRequest(&top, input);
    if (count == 0) { 
        printf("no matches found in list");
    }

    free(input);
    free(buffer);
    FreeList(&top);

    fclose(file);
    return 0;
}