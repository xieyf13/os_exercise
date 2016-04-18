#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "unistd.h"
#include "time.h"
#include "assert.h"

#define MAXPROC (8)
#define true (1)
#define false (0)

typedef int bool;

typedef struct {
    int id;
    int relative_deadline;
    int execute_time;
    int elapse_time;
} struct_proc;

struct_proc *current = NULL;
struct_proc procs[MAXPROC];

bool create_proc() {
    static int id = 0;
    if (id >= MAXPROC) {
        return false;
    }
    procs[id].id = id;
    procs[id].execute_time = rand() % 10 + 1;
    procs[id].relative_deadline = rand () % 30 + 1 + 10;
    procs[id].elapse_time = 0;
    printf("in create_proc id is %d exe is %d deadline is %d\n", procs[id].id, procs[id].execute_time, procs[id].relative_deadline);
    ++ id;
    return true;
}

void schedule() {
    int relative_deadline = 0x07FFFFFFF;
    int id = -1;
    int i;
    for (i = 0; i < MAXPROC; ++i) {
        if (procs[i].id >= 0 && procs[i].relative_deadline < relative_deadline) {
            relative_deadline = procs[i].relative_deadline;
            id = i;
        }
    }
    if (id == -1) {
        current = NULL;
        printf("no procs can be schedule, so current is idle\n");
    } else {
        printf("select proc %d\n", id);
        current = procs + id;
    }
    return;
}

void execute() {
    int time_elapse = 0;
    while (1) {
        time_elapse += 1;
        printf("now time: %d\n", time_elapse);
        if (current) {
            current->relative_deadline --;
            current->execute_time --;
            current->elapse_time ++;
            printf("proc: %d -- exe %d need %d relative_deadline %d\n", current->id, current->elapse_time, current->execute_time, current->relative_deadline);
            if (current->execute_time == 0) {
                printf("proc %d finish -- elapse_time is %d relative_deadline is %d\n", current->id, current->elapse_time, current->relative_deadline);
                current->id = -1;
                schedule();
                continue;
            }
            if (current->relative_deadline == 0) {
                printf("boom!!!!!!!!!!!! proc %d miss it deadline\n", current->id);
                break;
            }
        } else {
            printf("idle execute\n");
            schedule();
        }
        if (rand() % 3 == 0) {
            if (!create_proc()) {
                int i;
                bool found = false;
                for (i = 0; i < MAXPROC; ++i) {
                    if (procs[i].id != -1) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    printf("all proc has finished\n");
                    break;
                }
            }
        }
    }
}

void init() {
    int i;
    for (i = 0; i < MAXPROC; ++i) {
        procs[i].id = -1;
    }
    srand(time(0));
}

int main() {
    init();
    execute();
}
