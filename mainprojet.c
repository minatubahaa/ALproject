#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct informations {
    int ID;
    char NAME[100];
    int PRIO;
} informations;

typedef struct TASK {
    informations DATA;
    struct TASK *next;
} TASK;

// Function prototypes
int empty_task(TASK *head);
void displayTasks(TASK *head);
TASK *createNode(TASK val);
TASK user_input(int ID);
TASK *Add_Head(TASK *list, TASK val);
void addAfter(TASK *current, TASK element);
TASK *add_task(TASK *task, TASK input_task);
void search_task(TASK *head, char *Xword);
TASK *delete (TASK *head,int ID, TASK* task_deleted);
void check_task(TASK **list, TASK **history , int ID);

int already_exist(TASK *list , int ID);
void modify_task(TASK **list, TASK **history);
void delet_liste(TASK**HEAD);

// Helper function for printing a task
void printTask(TASK *task) {
    printf("%d\t%-30s\t%d\n", task->DATA.ID, task->DATA.NAME, task->DATA.PRIO);
}

int main(int argc, char const *argv[]) {
    int option;
    int choice;
    char temp;

    int id_input;

    TASK *URGENT = NULL, *NORMAL = NULL, *HISTORY = NULL;
    int ID = 1;
    TASK input_task;
    printf("_______________________________TO DO LIST MANAGER_________________________________________\n");

    while (1) { //boucle infinit
        printf("-----------------------------------------------------------------------------------\n");
        printf("1 - Add a task\n2 - Search\n3 - View history\n4 - Delete a task\n5 - Display tasks\n6 - Modify a task \n7 - Check a task\n8- Exit\n");
        printf("Choose an operation: ");

        if(scanf("%d%c" ,&option, &temp) != 2 || temp != '\n'){
            printf("Invalid input pls Re-launch the program.\n");
            break;
        }

        printf("-----------------------------------------------------------------------------------\n");

        switch (option) {
            case 1: {
                while (1) {
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
            case 2: {
                char search_word[50];
                printf("Enter the task to search:\n");
                scanf(" %[^\n]", search_word);
                printf("Searching in Normal tasks...\n");
                search_task(NORMAL, search_word);
                printf("Searching in Urgent tasks...\n");
                search_task(URGENT, search_word);
                break;
            }
            case 3:
                printf("History:\n");
                displayTasks(HISTORY);
                break;
            case 4:
                printf("Choose :\n1 - Delete a task\n2 - Delete a list\n");
                do {
                    scanf("%d", &choice);
                    if (choice != 1 && choice != 2) {
                        printf("Invalid input. Please enter 1 or 2.\n");
                    }
                } while (choice != 1 && choice != 2);
                if (choice == 1) {
                    printf("Would you like to delete:\n1 - Urgent task\n2 - Normal task\n3 - Task from history\n");
                    scanf("%d", &choice);
                    TASK **target_list = NULL;
                    switch (choice) {
                        case 1:
                            target_list=&URGENT;
                            break;
                        case 2:
                            target_list = &NORMAL;
                            break;
                        case 3:
                            target_list = &HISTORY;
                            break;
                        default:
                            printf("Invalid choice.\n");
                            break;
                    }
                    if(empty_task(*target_list)){
                        printf("The list is empty.\n");
                    }else{
                        displayTasks(*target_list);
                        printf("Enter the ID of the task to delete:\n");
                        scanf("%d",&id_input);
                
                        TASK temp_task;
                        if (already_exist(*target_list,id_input)) {
                            *target_list = delete(*target_list, id_input , &temp_task);
                            printf("Task deleted successfully.\n");
                        }else
                        {
                            printf("Task not found with that ID.\n");
                        }    
                    }
                }
                else if(choice==2) {
                    printf("Which list would you like to delete?\n1 - Urgent\n2 - Normal\n3 - History\n");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1:
                            delet_liste(&URGENT);
                            break;
                        case 2:
                            delet_liste(&NORMAL);
                            break;
                        case 3:
                            delet_liste(&HISTORY);
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                    printf("List deleted successfully.\n");
                } else {
                    printf("Invalid option.\n");
                }
                break;
            case 5:
                printf("Urgent tasks:\n");
                displayTasks(URGENT);
                printf("Normal tasks:\n");
                displayTasks(NORMAL);
                break;
            case 6:
                TASK **target_list = NULL;
                printf("Choose a task to edit from:\n");
                do 
                {   
                    printf("1 - Urgent\n2 - normal\n");
                    scanf("%d", &choice);
                    if (choice != 1 && choice != 2) {
                        printf("Invalid input. Please enter 1 or 2.\n");
                    }
                } while (choice != 1 && choice != 2);
                if(choice == 1)
                    target_list = &URGENT;
                else{
                    target_list = &NORMAL;
                }
                modify_task(target_list, &HISTORY);
                break;  
            case 7:
                if(empty_task(NORMAL) && empty_task(URGENT)){
                    printf("The Task lists are empty there is nothing to check.\n");
                }else{
                    printf("Task Urgent:\n");
                    displayTasks(URGENT);
                    printf("Task personnal:\n");
                    displayTasks(NORMAL);
                    printf("Enter the ID of task to check:\n");
                    scanf("%d",&id_input);
                    printf("Verifying in Urgent task..\n");
                    check_task(&URGENT, &HISTORY , id_input);
                    printf("Verifying in personnal task..\n");
                    check_task(&NORMAL, &HISTORY , id_input);
                }
                break;
            case 8:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                continue;
        }
    }   
}
void displayTasks(TASK *head) {
    if (empty_task(head)) {
        printf("\tThe task list is empty.\n");
        return;
    }

    printf("ID\tNAME\t\t\t\tPriority\n");
    printf("-------------------------------------------------\n");

    TASK *current = head;
    while (current != NULL) {
        printTask(current);
        current = current->next;
    }
    printf("-------------------------------------------------\n");
}

TASK *createNode(TASK val) {
    TASK *new = (TASK *)malloc(sizeof(TASK));
    if (new == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    new->DATA = val.DATA;
    new->next = NULL;
    return new;
}

TASK user_input(int ID) {
    TASK input_task;

    do
    {
        printf("Enter the priority:\n1 for High\n2 for Medium\n3 for Low\n");
        scanf("%d", &input_task.DATA.PRIO);
    } while(input_task.DATA.PRIO != 1 && input_task.DATA.PRIO != 2 && input_task.DATA.PRIO!= 3);
    
    printf("Enter the task NAME:\n");
    scanf(" %[^\n]", input_task.DATA.NAME);
    input_task.DATA.ID = ID;
    return input_task;
}

TASK *Add_Head(TASK *list, TASK element) {
    TASK *new = createNode(element);
    new->next = list;
    return new;
}

void addAfter(TASK *current, TASK element) {
    TASK *new = createNode(element);
    new->next = current->next;
    current->next = new;
}

TASK *add_task(TASK *task, TASK input_task) {

    TASK *previous = NULL, *current = task;
    while (current != NULL && input_task.DATA.PRIO > current->DATA.PRIO) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        task = Add_Head(task, input_task);
    } else {
        addAfter(previous, input_task);
    }
    printf("TASK: %s with priority %d and ID: %d was added successfully!\n", input_task.DATA.NAME, input_task.DATA.PRIO , input_task.DATA.ID);
    return task;
}

int empty_task(TASK *head) {
    return head == NULL;
}

void search_task(TASK *head, char *Xword) {

    if (head == NULL) {
        printf("The task list is empty.\n");
        return;
    }

    TASK *current = head;
    while (current != NULL) {
        if (strcmp(current->DATA.NAME, Xword) == 0) {
            printf("Task: %s exists with ID: %d\tPriority: %d\n", current->DATA.NAME, current->DATA.ID, current->DATA.PRIO);
            return;
        }
        current = current->next;
    }
    printf("Task not found.\n");
}

TASK *delete(TASK *head , int ID , TASK* task_deleted) {
    TASK *current = head;
    TASK *prev = NULL;

    while (current != NULL && current->DATA.ID != ID) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    //we need it to add it to history
    strcpy(task_deleted->DATA.NAME , current->DATA.NAME);
    task_deleted->DATA.PRIO = current->DATA.PRIO;
    task_deleted->DATA.ID = ID;

    free(current);

    return head;
}

int already_exist(TASK *list , int ID) {
    while (list != NULL) {
        if (list->DATA.ID == ID) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

void modify_task(TASK **list, TASK **history) {

    if (empty_task(*list)) {
        printf("No tasks available to modify in this list.\n");
        return;
    }
    displayTasks(*list);
    printf("Enter the ID of task to modify:\n");
    int id_input; 
    scanf("%d",&id_input);

    if (already_exist(*list, id_input)) {
        TASK temp_task;
        *list = delete(*list, id_input , &temp_task);
        printf("Enter the new details for the task:\n");

        TASK new_task = user_input(id_input);
        *list = add_task(*list, new_task);
        printf("Task modified successfully.\n");
    } else {
        printf("Task not found.\n");
    }
}
void check_task(TASK **list, TASK **history , int ID) {

    if (empty_task(*list)) {
        printf("No tasks available to check in this list.\n");
        return;
    }

    if(already_exist(*list, ID)) {

        TASK old_task;
        *list = delete(*list, ID , &old_task);
        *history = Add_Head(*history, old_task);
        printf("Task checked and moved to history successfully.\n");
    } else {
        printf("Task not found here.\n");
    }
}


void delet_liste(TASK**HEAD){
    TASK*current;
    if(*HEAD==NULL){
        printf("this liste is empty");
        return;
    }
    else{
        current=*HEAD;
        while(current!=NULL){
            *HEAD=(*HEAD)->next;
            free(current);
            current=*HEAD;

        }
    }
}