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
        
          
            case 3:

                printf("History:\n");
                displayTasks(HISTORY);
                break;
              
            case 5:
                printf("Urgent tasks:\n");
                displayTasks(URGENT);
                printf("Normal tasks:\n");
                displayTasks(NORMAL);
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




int empty_task(TASK *head) {
    return head == NULL;
}


void printTask(INFORMATION task) {
    printf("%d\t%-30s\t%d\n", task.ID, task.NAME, task.PRIO);
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


