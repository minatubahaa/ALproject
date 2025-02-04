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

//provided by yasser
void printTask(INFORMATION task) {
    printf("%d\t%-30s\t%d\n", task.ID, task.NAME, task.PRIO);
}
//provided by yasser
int empty_task(TASK *head) {
    return head == NULL;
}
//provided by abdrahman
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
// provided by yasser
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

TASK** delete_list(TASK* HEAD){

    TASK* TEMP = NULL;
    while(HEAD != NULL){
        TEMP = HEAD;
        HEAD = HEAD->NEXT;
        free(TEMP);
    }

    return NULL;
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


int main(int argc, char const *argv[]) {
    int option;
    int choice;

    int id_input;

    TASK *URGENT = NULL, *NORMAL = NULL, *HISTORY = NULL;
    TASK **target_list = NULL;


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
                

}