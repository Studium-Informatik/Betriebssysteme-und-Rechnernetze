typedef struct dl_proc_node {
    int pid;
    int ppid;
    struct dl_proc_node* prev;
    struct dl_proc_node* next;
} dl_proc_node;


typedef struct dl_proc_list {
    dl_proc_node* head;
} dl_proc_list;


dl_proc_list* dl_proc_list_create(void);

int dl_proc_list_insert(dl_proc_list *list, int pid);

int dl_proc_list_get(dl_proc_list *list, int position, int* pid, int* ppid);

int dl_proc_list_remove(dl_proc_list *list, int pid);

void dl_proc_list_free(dl_proc_list *list);
