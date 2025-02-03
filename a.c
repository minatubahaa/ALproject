

// Define a task structure
typedef struct Task {
    char name[100];
    int priority; // 1 = High, 2 = Medium, 3 = Low
    struct Task *next;
} Task;

// Push a task to the history stack
void pushHistory(Task **history, char *name, int priority) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->next = *history;
    *history = newTask;
}


int main() {
    Task *urgentTasks = NULL;
    Task *normalTasks = NULL;
    Task *historyTasks = NULL; // Stack for checked tasks
    int choice;

    do {
        printf("\nMenu:\n1. Add a Task\n2. Delete a Task\n3. Search for a Task\n4. Check a Task\n5. Display Checked Tasks History\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);

   
         if (choice == 4) {
            char taskName[100];

            printf("Enter the name of the task to check: ");
            scanf("%s", taskName);

            Task *task = searchTask(urgentTasks, taskName);
            if (task != NULL) {
                pushHistory(&historyTasks, task->name, task->priority);
                deleteTask(&urgentTasks, task->name);
                printf("Task checked and moved to history!\n");
            } else {
                task = searchTask(normalTasks, taskName);
                if (task != NULL) {
                    pushHistory(&historyTasks, task->name, task->priority);
                    deleteTask(&normalTasks, task->name);
                    printf("Task checked and moved to history!\n");
                }
            }
        } else if (choice == 5) {
            printf("Checked Tasks History:\n");
            displayTasks(historyTasks);
        } else if (choice != 6) {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    printf("Exiting program.\n");
    return 0;
}
