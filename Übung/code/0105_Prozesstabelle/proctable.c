#include <stdio.h>
#include <stdlib.h>
#include "dl_proc_list.h"

int main(int argc, char *argv[]) {
    dl_proc_list *plist = dl_proc_list_create();
    if (!plist) {
        fprintf(stderr, "Fehler: Konnte Prozesstabelle nicht erstellen.\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        char *endptr;
        long val = strtol(argv[i], &endptr, 10);

        if (*endptr != '\0') {
            fprintf(stderr, "Warnung: Ungueltiges Argument \"%s\" ignoriert.\n", argv[i]);
            continue;
        }

        if (val == 0) {
            fprintf(stderr, "Warnung: PID = 0 wird ignoriert.\n");
            continue;
        }

        if (val > 0) {
            if (dl_proc_list_insert(plist, (int)val) < 0) {
                fprintf(stderr, "Fehler beim Einfuegen: PID %ld existiert bereits.\n", val);
            }
        } else {
            int pid_to_remove = (int)(-val);
            if (pid_to_remove == 1) {
                fprintf(stderr, "Fehler: Prozess mit ID = 1 kann nicht geloescht werden.\n");
            } else if (dl_proc_list_remove(plist, pid_to_remove) < 0) {
                fprintf(stderr, "Fehler beim Loeschen: Prozess mit ID = %d existiert nicht.\n", pid_to_remove);
            }
        }
    }

    int pos = 0, pid, ppid;
    while (dl_proc_list_get(plist, pos, &pid, &ppid) == 0) {
        printf("PID = %d, Parent PID = %d\n", pid, ppid);
        pos++;
    }

    dl_proc_list_free(plist);
    return EXIT_SUCCESS;
}
