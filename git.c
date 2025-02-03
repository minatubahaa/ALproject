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


void modifieTasck(int IDX,TASK*head) { // old version

    TASK*current=head;
    int conf;
    struct TASK x;
    int inpute;
    char xs[100];


    while(current!=NULL && current->DATA.ID != IDX){
        current=current->NEXT;
    }
    if (current==NULL){
        printf("this task dosent existe");
        return;
    }
    printf("do you want modifie discription (1-yes|Any number-no): ");
    scanf("%d",&conf);

    if(conf==1){
        printf("entre your modification: ");
        scanf(" %[^\n]",current->DATA.NAME);
        
         printf("the modification sucsseded\n");
    }
         
    printf("do you want modifie priority (1-yes|Any number-no): ");
    scanf("%d",&conf);

    if(conf==1){

        printf("entre your modification: ");
        scanf("%d",&current->DATA.NAME);
        printf("the modification sucsseded\n");

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


    
    