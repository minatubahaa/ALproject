
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


INFORMATION user_input(int ID);

void search_task(TASK *head, char *Xword);




int already_exist(TASK *list , int ID);
void modify_task(TASK **list, int id_input );

// Helper function for printing a task


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

                
                break;
            case 4:

               
                break;
            case 5:
                
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




INFORMATION user_input(int ID) { //writed by bahaa

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




INFORMATION user_input(int ID) {

    // fonction writed by bahaa

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

void search_task(TASK *head, char *Xword) {        

    if (head == NULL) {
        printf("The task list is empty.\n");
        return;
    }
       // list tasck is not empty
    TASK *current = head;
    while (current != NULL) {
        if (strcmp(current->DATA.NAME, Xword) == 0) {
            printf("Task: %s exists with ID: %dPriority: %d\n", current->DATA.NAME, current->DATA.ID, current->DATA.PRIO); // search the tasck
            return;
        }
        current = current->NEXT; // travers the liste tasck
    }
    printf("Task not found.\n"); // display the tasck
}



int already_exist(TASK *list , int ID) {

    //function check if the task with given ID already exist
    while (list != NULL) {
        if (list->DATA.ID == ID) {
            return 1;
        }
        list = list->NEXT;
    }
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


    
    
