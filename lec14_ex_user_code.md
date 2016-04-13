```
#include <stdio.h>
#include <ulib.h>

int
main(void) {
    cprintf("in user_process -- start execute\n");
    int pid = fork();
    if (pid == 0) {
        cprintf("in user_child_process -- start execute\n");
        int run_turns = 200000;
        while (run_turns --) {
            if (run_turns % 100000 == 0) {
                cprintf("in user_child_process -- now is %d\nI'll drop the control\n", run_turns / 100000);
                yield();
            }
        }
        cprintf("in user_child_process -- I will exit with number %x\n", 0x12345678);
        exit(0x12345678);
    } else {
        cprintf("in user_process -- child pid is %d\n", pid);
        cprintf("in user_process -- I will wait my child\n");
        int exit_code;
        waitpid(pid, &exit_code);
        cprintf("in user_process -- I catch my child with exit number %x\n", exit_code);
        cprintf("in user_process -- I will return\n");
        return 0;
    }
}
```