#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct TASK {
    char* word;
    int priority;
    struct TASK* next;
};
typedef struct TASK* ListTASK;
//search task provided by abderahman
bool Search_Task(char* word, int priority, ListTASK X1) {
    ListTASK Q = X1;
    while (Q != NULL) {
        if (strcmp(word, Q->word) == 0 && priority == Q->priority) {
            return true;
        }
        Q = Q->next;
    }
    return false;
}

void Display_task(ListTASK list) {
    ListTASK Q = list;
    while (Q != NULL) {
        printf("priority: %d_%s\n", Q->priority, Q->word);
        Q = Q->next;
    }
}

ListTASK delete(ListTASK list, char* word, int priority) {
    ListTASK p, q;
    p = list;
    q = NULL;

    // Special case: the first element is the one to delete
    if (strcmp(word, p->word) == 0 && priority == p->priority) {
        list = p->next;
        free(p);
        return list;
    }

    // Traverse the list to find the element to delete
    while (p != NULL && (strcmp(word, p->word) != 0 || priority != p->priority)) {
        q = p;
        p = p->next;
    }

    // If the element was found, remove it
    if (p != NULL) {
        q->next = p->next;
        free(p);
    }

    return list;
}

int main() {
    ListTASK personal = NULL; 
    ListTASK important = NULL; 
    ListTASK history = NULL;
    ListTASK temp;
    int option; 
    char word[150]; 
    int priority;
    char listname[11];

    printf("choose an option\n");
    printf("3- delete a Task   |   4- delete a List\n");
    scanf("%d", &option);

    if (option == 3) { // 3 is the delete option
        printf("Would you like to delete a:\n 1- urgent task |  2- personal task  |  3- checked task\n");
        scanf("%d", &option);

        switch (option) {
            case 1: 
                Display_task(important); 
                temp = important; 
                strcpy(listname, "important");
                break;
            case 2: 
                Display_task(personal); 
                temp = personal; 
                strcpy(listname, "personal");
                break;
            case 3: 
                Display_task(history);  
                temp = history;  
                strcpy(listname, "history");
                break;
            default: 
                printf("Error, choose 1, 2, or 3!\n");
                return 1;
        }

        printf("What task would you like to delete?\nEnter name: ");
        scanf(" %[^\n]", word);    
        printf("Enter priority: "); 
        scanf("%d", &priority);

        if (Search_Task(word, priority, temp)) {
            temp = delete(temp, word, priority); 
            printf("The task has been deleted successfully!\n");
            printf("The updated %s list:\n", listname);
            Display_task(temp);

            // Update the original list
            if (strcmp(listname, "important") == 0) {
                important = temp;
            } else if (strcmp(listname, "personal") == 0) {
                personal = temp;
            } else if (strcmp(listname, "history") == 0) {
                history = temp;
            }
        } else {
            printf("Error, this task doesn't exist!\n");
        }
    } else if (option == 4) { // Code block to delete a list
        printf("What list would you like to delete?\n1- Important Tasks List |  2- Personal Tasks List |  3- Checked Task List\n");
        scanf("%d", &option);

        switch (option) {
            case 1: 
                important = NULL; 
                printf("List has been deleted successfully!\n");
                break;
            case 2: 
                personal = NULL; 
                printf("List has been deleted successfully!\n");
                break;
            case 3: 
                history = NULL; 
                printf("List has been deleted successfully!\n");
                break;
            default: 
                printf("Error, please choose 1, 2, or 3.\n");
                break;
        }
    } else {
        printf("Error, please choose 3 or 4.\n");
    }

    return 0;
}
