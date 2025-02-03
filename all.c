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

//You can use Ctrl + Left Click on the function name to navigate to its definition
// Function prototypes
int empty_task(TASK *head);
void displayTasks(TASK *head);
TASK* createNode(INFORMATION var);
INFORMATION user_input(int ID);
TASK* add_head(TASK *list, INFORMATION val);
void add_after(TASK* current, INFORMATION element);
TASK* add_task(TASK *task, INFORMATION input_task);
void search_task(TASK *head, char *Xword);
TASK* delete(TASK *head,int ID, INFORMATION* task_deleted);
void check_task(TASK **list, TASK **history , int ID);

TASK** delete_list(TASK* HEAD);

int already_exist(TASK *list , int ID);
void modify_task(TASK **list, int id_input);

// Helper function for printing a task
void printTask(INFORMATION task) {
    printf("%d\t%-30s\t%d\n", task.ID, task.NAME, task.PRIO);
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
    printf("_______________________________TO DO LIST MANAGER____________________________________________\n\n");

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

                printf("Searching in Urgent tasks...\n");
                search_task(URGENT, search_word);

                printf("Searching in Normal tasks...\n");
                search_task(NORMAL, search_word);

                break;
            }
            case 3:

                printf("History:\n");
                displayTasks(HISTORY);
                break;
            case 4:

                printf("Choose :\n1 - Delete Urgent\n2 - Delete Normal\n3 - Delete History \n");
                do {
                    scanf("%d", &choice);
                    if (choice != 1 && choice != 2 && choice != 3){
                        printf("Invalid input. Please enter 1 or 2 or 3.\n");
                    }
                } while (choice != 1 && choice != 2 && choice != 3);

                switch (choice) {
                    case 1:
                        target_list = &URGENT;
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

                printf("Do you want to :\n1 - Delete a Task\n2 - Delete all The Tasks\n");
                do {
                    scanf("%d", &choice);
                    if (choice != 1 && choice != 2){
                        printf("Invalid input. Please enter 1 or 2 or 3.\n");
                    }
                }while(choice != 1 && choice != 2);

                if(empty_task(*target_list)){
                    printf("The list is empty.\n");
                }else{

                    if (choice == 1){
                        displayTasks(*target_list);
                        printf("Enter the ID of the task to delete:\n");
                        scanf("%d",&id_input);

                        INFORMATION temp_task; // tamporary variable we don't need the task after delete
                        
                        if (already_exist(*target_list,id_input)) {
                            *target_list = delete(*target_list, id_input , &temp_task);
                            printf("Task deleted successfully.\n");
                        }else
                        {
                            printf("Task not found with that ID.\n");
                        }    
                    }else{
                        target_list = delete_list(*target_list);
                        printf("All tasks has been deleted from the list.\n");
                    }
                }
                break;
            case 5:
                printf("Urgent tasks:\n");
                displayTasks(URGENT);
                printf("Normal tasks:\n");
                displayTasks(NORMAL);
                break;
            case 6:

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
                if (empty_task(*target_list)) {
                    printf("No tasks available to modify in this list.\n");
                }else
                {   
                    displayTasks(*target_list);
                    printf("Enter the ID of task to modify:\n");
                    int id_input; 
                    scanf("%d",&id_input);
                    modify_task(target_list, id_input);
                }
                break;  
            case 7:

                if(empty_task(NORMAL) && empty_task(URGENT)){
                    printf("The Task lists are empty there is nothing to check.\n");
                }else{
                    printf("Urgent Tasks:\n");
                    displayTasks(URGENT);
                    printf("Personnal Tasks:\n");
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
        printf("The task list is empty.\n");
        return;
    }

    printf("ID\tNAME\t\t\t\tPriority\n");
    printf("-------------------------------------------------\n");

    TASK *current = head;
    while (current != NULL) {
        printTask(current->DATA);
        current = current->NEXT;
    }
    printf("-------------------------------------------------\n");
}

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

TASK *add_head(TASK *list, INFORMATION element) {
    //add element at the head of the list
    TASK *new = createNode(element);
    new->NEXT = list;
    return new;
}

void add_after(TASK *current, INFORMATION element) {

    //add after given value
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
        // first element or there is no other task with haigher priority 
        task = add_head(task, input_task);
    } else {
        //add after 
        add_after(previous, input_task);
    }
    printf("TASK: %s with priority %d and ID: %d was added successfully!\n", input_task.NAME, input_task.PRIO , input_task.ID);
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
            printf("Task: %s exists with ID: %dPriority: %d\n", current->DATA.NAME, current->DATA.ID, current->DATA.PRIO);
            return;
        }
        current = current->NEXT;
    }
    printf("Task not found.\n");
}

TASK* delete(TASK *head , int ID , INFORMATION* task_deleted) {

    TASK *current = head;
    TASK *prev = NULL;

    while (current != NULL && current->DATA.ID != ID){
        prev = current;
        current = current->NEXT;
    }

    if(current == NULL)
    {
        return head;
    }
    
    if (prev == NULL) {
        head = head->NEXT;
    } else {
         
        prev->NEXT = current->NEXT;       
    }

    //save it in variable to add it to history
    strcpy(task_deleted->NAME , current->DATA.NAME);
    task_deleted->PRIO = current->DATA.PRIO;
    task_deleted->ID = ID;

    free(current);
}

int already_exist(TASK *list , int ID) {

    //function check if the task with given ID already exist
    while (list != NULL) {
        if (list->DATA.ID == ID) {
            return 1;
        }
        list = list->NEXT;
    }
    return 0;
}

void modify_task(TASK **list, int id_input ) {

    if (already_exist(*list, id_input)) {

        INFORMATION temp_task;
        *list = delete(*list, id_input , &temp_task);
        printf("Enter the new details for the task:\n");

        INFORMATION new_task = user_input(id_input);
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

        INFORMATION old_task;
        *list = delete(*list, ID , &old_task);
        *history = add_head(*history, old_task);
        printf("Task checked and moved to history successfully.\n");

    } else {
        printf("Task not found here.\n");
    }
}

TASK** delete_list(TASK* HEAD){

    TASK* TEMP = NULL;
    while(HEAD != NULL){
        TEMP = HEAD;
        HEAD = HEAD->NEXT;
        free(TEMP);
    }

    return NULL;
}
