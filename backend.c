#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Event {
    int eventID;
    char eventName[50];
    char location[50];
    char date[15]; 
    int seats;
    struct Event *prev, *next;
} Event;

Event *head = NULL;



void clearBuffer() {
    while (getchar() != '\n');
}

int dateToInt(const char *date) {
    int d, m, y;
    sscanf(date, "%d-%d-%d", &d, &m, &y);
    return y * 10000 + m * 100 + d; // YYYYMMDD
}

Event* createEvent(int id, char name[], char loc[], char date[], int seats) {
    Event* newEvent = (Event*)malloc(sizeof(Event));
    if (!newEvent) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newEvent->eventID = id;
    strcpy(newEvent->eventName, name);
    strcpy(newEvent->location, loc);
    strcpy(newEvent->date, date);
    newEvent->seats = seats;
    newEvent->prev = newEvent->next = NULL;

    return newEvent;
}

void removeNode(Event *node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        head = node->next;

    if (node->next)
        node->next->prev = node->prev;

    node->prev = node->next = NULL;
}



void insertEvent() {
    int id, seats;
    char name[50], loc[50], date[15];

    printf("\nEnter Event ID: ");
    scanf("%d", &id);
    clearBuffer();

    printf("Enter Event Name: ");
    scanf(" %[^\n]", name);

    printf("Enter Location: ");
    scanf(" %[^\n]", loc);

    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", date);

    printf("Enter Seats: ");
    scanf("%d", &seats);

    Event *newEvent = createEvent(id, name, loc, date, seats);

    if (!head) {
        head = newEvent;
        return;
    }

    Event *temp = head, *prev = NULL;
    while (temp && dateToInt(temp->date) < dateToInt(date)) {
        prev = temp;
        temp = temp->next;
    }

    if (!prev) {
        newEvent->next = head;
        head->prev = newEvent;
        head = newEvent;
    } else {
        newEvent->next = temp;
        newEvent->prev = prev;
        prev->next = newEvent;
        if (temp)
            temp->prev = newEvent;
    }
}

void deleteEvent() {
    int id;
    printf("\nEnter Event ID to delete: ");
    scanf("%d", &id);

    Event *temp = head;
    while (temp && temp->eventID != id)
        temp = temp->next;

    if (!temp) {
        printf("Event not found!\n");
        return;
    }

    removeNode(temp);
    free(temp);
    printf("Event deleted successfully.\n");
}

void modifyEvent() {
    int id;
    printf("\nEnter Event ID to modify: ");
    scanf("%d", &id);
    clearBuffer();

    Event *temp = head;
    while (temp && temp->eventID != id)
        temp = temp->next;

    if (!temp) {
        printf("Event not found!\n");
        return;
    }

    printf("Modify Name: ");
    scanf(" %[^\n]", temp->eventName);

    printf("Modify Location: ");
    scanf(" %[^\n]", temp->location);

    printf("Modify Date (DD-MM-YYYY): ");
    scanf("%s", temp->date);

    printf("Modify Seats: ");
    scanf("%d", &temp->seats);

    removeNode(temp);

    Event *cur = head, *prev = NULL;
    while (cur && dateToInt(cur->date) < dateToInt(temp->date)) {
        prev = cur;
        cur = cur->next;
    }

    if (!prev) {
        temp->next = head;
        if (head) head->prev = temp;
        head = temp;
    } else {
        temp->next = cur;
        temp->prev = prev;
        prev->next = temp;
        if (cur) cur->prev = temp;
    }

    printf("Event modified successfully.\n");
}

void searchEvent() {
    int id;
    printf("\nEnter Event ID to search: ");
    scanf("%d", &id);

    Event *temp = head;
    while (temp && temp->eventID != id)
        temp = temp->next;

    if (!temp) {
        printf("Event not found!\n");
        return;
    }

    printf("\n--- Event Found ---\n");
    printf("ID: %d\nName: %s\nLocation: %s\nDate: %s\nSeats: %d\n",
           temp->eventID, temp->eventName, temp->location,
           temp->date, temp->seats);
}

void displayForward() {
    if (!head) {
        printf("\nNo events available!\n");
        return;
    }

    Event *temp = head;
    printf("\n--- Events (Chronological Order) ---\n");
    while (temp) {
        printf("ID: %d | %s | %s | %s | Seats: %d\n",
               temp->eventID, temp->eventName,
               temp->location, temp->date, temp->seats);
        temp = temp->next;
    }
}

void displayReverse() {
    if (!head) {
        printf("\nNo events available!\n");
        return;
    }

    Event *temp = head;
    while (temp->next)
        temp = temp->next;

    printf("\n--- Events (Reverse Order) ---\n");
    while (temp) {
        printf("ID: %d | %s | %s | %s | Seats: %d\n",
               temp->eventID, temp->eventName,
               temp->location, temp->date, temp->seats);
        temp = temp->prev;
    }
}



int main() {
    int choice;

    while (1) {
        printf("\n\n===== Event Scheduling System =====\n");
        printf("1. Insert Event\n");
        printf("2. Delete Event\n");
        printf("3. Modify Event\n");
        printf("4. Search Event\n");
        printf("5. Display (Chronological)\n");
        printf("6. Display (Reverse)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: insertEvent(); break;
            case 2: deleteEvent(); break;
            case 3: modifyEvent(); break;
            case 4: searchEvent(); break;
            case 5: displayForward(); break;
            case 6: displayReverse(); break;
            case 7: exit(0);
            default: printf("Invalid option!\n");
        }
    }
}
