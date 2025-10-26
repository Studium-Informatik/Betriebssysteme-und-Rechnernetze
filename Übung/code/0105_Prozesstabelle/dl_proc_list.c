#include "dl_proc_list.h"
#include <stdlib.h>

// Creates a new process list with the initial process (PID = 1, PPID = 0)
dl_proc_list* dl_proc_list_create() {
    // Create list
    dl_proc_list *list;
    list = (dl_proc_list *) malloc(sizeof(dl_proc_list));

    if (!list) {
        return NULL;
    }
    
    // Create first process node
    dl_proc_node *first_node;
    first_node = (dl_proc_node *) malloc(sizeof(dl_proc_node));

    if (!first_node) {
        free(list);
        return NULL;
    }

    // Initialize first process node (PID = 1, PPID = 0)
    first_node->pid = 1;
    first_node->ppid = 0;

    first_node->prev = NULL;
    first_node->next = NULL;
    
    // Set head of list to first node
    list->head = first_node;

    return list;
}


// Inserts a new process with given PID into process list
// Returns 1 on success, -1 on memory allocation failure,
// -2 on invalid args, -3 if PID already exists
int dl_proc_list_insert(dl_proc_list *list, int pid){
    // Invalid list
    if (!list) {
        return -2;
    }

    // Invalid PID
    if (pid <= 1) {
        return -2;
    }

    // Find position to insert new process node
    dl_proc_node *pre_new = list->head;

    while (pre_new->next && pre_new->next->pid < pid) {
        pre_new = pre_new->next;
    }

    // PID already exists
    if (pre_new->next && pre_new->next->pid == pid) {
        return -3;
    }

    // pre_new is either the end of the list or the last node with PID < new PID

    // Invalid position
    if (!pre_new) {
        return -3;
    }

    // Create new process node
    dl_proc_node *new_node = (dl_proc_node *) malloc(sizeof(dl_proc_node));
    if (!new_node) {
        return -1;
    }

    new_node->pid = pid;
    new_node->ppid = pre_new->pid;
    new_node->prev = pre_new;
    new_node->next = pre_new->next;

    if (pre_new->next) {
        pre_new->next->prev = new_node;
    }
    pre_new->next = new_node;

    return 0;
}

int dl_proc_list_get(dl_proc_list *list, int position, int* pid, int* ppid){
    // Invalid list
    if (!list) {
        return -1;
    }

    dl_proc_node *current = list->head;
    int index = 0;

    while (current && index < position) {
        current = current->next;
        index++;
    }

    // Position out of bounds
    if (!current) {
        return -2;
    }

    *pid = current->pid;
    *ppid = current->ppid;

    return 0;
}

int dl_proc_list_remove(dl_proc_list *list, int pid){
    // Invalid list
    if (!list) {
        return -2;
    }

    // Invalid PID, cannot remove PID 1
    if (pid <= 1) {
        return -2;
    }

    dl_proc_node *current = list->head;

    while (current && current->pid != pid) {
        current = current->next;
    }

    // PID not found
    if (!current) {
        return -3;
    }

    // Remove the node from the list
    if (current->prev) {
        current->prev->next = current->next;
    } else {
        // Removing head node
        list->head = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    }

    free(current);
    return 0;
}

void dl_proc_list_free(dl_proc_list *list){
    if (!list) {
        return;
    }

    dl_proc_node *current = list->head;
    dl_proc_node *next_node;

    while (current) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    free(list);
}
