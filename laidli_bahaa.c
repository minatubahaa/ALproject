#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct INFORMATION {
    int ID;
    char NAME[100];
    int PRIO;
} INFORMATION;

typedef struct TASK {
    INFORMATION DATA;
    struct TASK *NEXT;
} TASK;

TASK* createNode(INFORMATION var) {

    TASK *NEW = (TASK *)malloc(sizeof(TASK));
    if (NEW == NULL) {
        printf("Memory allocation failed.\n");
        exit(1); // exit if the memory allocation failed
    } 
    //copying the info into the node
    strcpy(NEW->DATA.NAME , var.NAME);
    NEW->DATA.PRIO = var.PRIO;
    NEW->DATA.ID = var.ID;

    NEW->NEXT = NULL;
    return NEW;
}

TASK *add_head(TASK *list, INFORMATION element) {
    //add element at the head of the list
    TASK *new = createNode(element);
    new->NEXT = list;
    return new;
}
void add_after(TASK *current, INFORMATION element) {

    //add after given value 
    // when adding in the body of the list we don't need return type cuz we are not modifying the head of the list 
    TASK *NEW = createNode(element);
    NEW->NEXT = current->NEXT;
    current->NEXT = NEW;
}

TASK *add_task(TASK *task, INFORMATION input_task) {

    TASK *previous = NULL, *current = task;
    while (current != NULL && input_task.PRIO > current->DATA.PRIO) {
        previous = current;
        current = current->NEXT;
    }

    if (previous == NULL) {
        task = add_head(task, input_task);
    } else {
        add_after(previous, input_task);
    }
    printf("TASK: %s with priority %d and ID: %d was added successfully!\n", input_task.NAME, input_task.PRIO , input_task.ID);
    return task;
}

INFORMATION user_input(int ID) {

    INFORMATION input_task;
    do
    {
        printf("Enter the priority:\n1 for High\n2 for Medium\n3 for Low\n");
        scanf("%d", &input_task.PRIO);

    } while(input_task.PRIO != 1 && input_task.PRIO != 2 && input_task.PRIO!= 3);
    
    printf("Enter the task NAME:\n");
    scanf(" %[^\n]", input_task.NAME);
    input_task.ID = ID;

    return input_task;
}

int main(int argc, char const *argv[]) {
    int option;
    int choice;

    int id_input;

    TASK *URGENT = NULL, *NORMAL = NULL, *HISTORY = NULL;
    TASK **target_list = NULL;

    time_t current_time;
    struct tm *time_info;

    // Get the current time
    time(&current_time);

    // Convert the current time to a tm struct
    time_info = localtime(&current_time);
    
    char user_name[20]; 
    printf("Hello user pls enter your name:\n");
    scanf(" %[^\n]" , user_name); // getting the username

    int ID = 1;
    INFORMATION input_task;
    printf("_______________________________TO DO LIST MANAGER___________________________________________\n\n");

    // Print the current date and time in a readable format
    printf("Hi %s!, it's: %s", user_name, asctime(time_info));

    while (1) { // infinite loop
        printf("--------------------------------------------------------------------------------------------\n");
        printf("1 - Add a task\n2 - Search\n3 - View history\n4 - Delete a task\n5 - Display tasks\n6 - Modify a task \n7 - Check a task\n8- Exit\n");
        printf("--------------------------------------------------------------------------------------------\n");
        printf("Choose an operation: ");
        scanf("%d" ,&option);
        
        switch (option) {
            case 1: {
                while (1) { // infinit loop
                    printf("Is it Urgent or Normal? \nprint 1 for Urgent or 2 for Normal:\n");
                    do {
                        scanf("%d", &choice);
                        if (choice != 1 && choice != 2) {
                            printf("Invalid input. Please enter 1 or 2.\n");
                        }
                    } while (choice != 1 && choice != 2);
                    
                    input_task = user_input(ID++);
                    if (choice == 1) {
                        URGENT = add_task(URGENT, input_task);
                    } else {
                        NORMAL = add_task(NORMAL, input_task);
                    }

                    printf("Do you want to add another task? \nPrint 0 to exit / Any other number to continue:\n");
                    scanf("%d", &choice);
                    if (choice == 0) break;
                }
                break;
            }
            case 2: 
            case 3:
            case 4:
            case 5:
            case 6:  
            case 7:
            case 8:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                continue;
        }
    }
}