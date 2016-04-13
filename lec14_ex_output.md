```
in cpu_idle -- before schedule pid is 0in schedule -- proc switch from proc 0 to proc 1
in proc_run -- change the current to pid 1
in proc_run -- set esp to 0xc03a8000 and set cr3 to 0x002c4000
in proc_run --  before switch pid is 1
in alloc_proc -- set the proc status with PROC_UNINIT
in do_fork -- setup_kstack, copy_mm, copy_thread, get_pid
in wakeup_proc -- set proc 2 status with PROC_RUNNABLE
in do_wait -- set the proc 1 status with PROC_SLEEPING
in schedule -- proc switch from proc 1 to proc 2
in proc_run -- change the current to pid 2
in proc_run -- set esp to 0xc03af000 and set cr3 to 0x002c4000
in proc_run --  before switch pid is 2
kernel_execve: pid = 2, name = "exit".
in do_execve -- set cr3 with 0x002c4000 and decrease current->mm ref
in do_execve -- call load_icode
in user_process -- start execute
in user fork -- I'll call the sys_fork
in user sys_fork -- I'll call syscall(SYS_fork)
in kern sys_fork -- stack is 0xafffff0c I'll call do_fork
in alloc_proc -- set the proc status with PROC_UNINIT
in do_fork -- setup_kstack, copy_mm, copy_thread, get_pid
in wakeup_proc -- set proc 3 status with PROC_RUNNABLE
in user_process -- child pid is 3
in user_process -- I will wait my child
in user waitpid -- I'll call the sys_wait
in user sys_wait -- I'll call user syscall(SYS_wait, pid, store)
in kern sys_wait -- pid is 3 I'll call do_fork
in do_wait -- set the proc 2 status with PROC_SLEEPING
in schedule -- proc switch from proc 2 to proc 3
in proc_run -- change the current to pid 3
in proc_run -- set esp to 0xc03c0000 and set cr3 to 0x003c0000
in proc_run --  before switch pid is 3
in user_child_process -- start execute
in user_child_process -- now is 1
I'll drop the control
in trap -- current->need_resched before schedule pid is 3
in schedule -- proc switch from proc 3 to proc 3
in trap -- current->need_resched after schedule pid is 3
in user_child_process -- now is 0
I'll drop the control
in trap -- current->need_resched before schedule pid is 3
in schedule -- proc switch from proc 3 to proc 3
in trap -- current->need_resched after schedule pid is 3
in user_child_process -- I will exit with number 12345678
in user exit -- I'll call the sys_exit
in user sys_exit -- I'll call syscall(SYS_exit, error_code)
in kern sys_exit -- I'll call do_exit
in do_exit -- this proc is not idleproc or initproc
in do_exit -- set cr3 at 0x002c4000 decrease the reference number of current->mm
in do_exit -- set the status with PROC_ZOMBIE
in wakeup_proc -- set proc 2 status with PROC_RUNNABLE
in do_exit -- before schedule
in schedule -- proc switch from proc 3 to proc 2
in proc_run -- change the current to pid 2
in proc_run -- set esp to 0xc03af000 and set cr3 to 0x003af000
in proc_run --  before switch pid is 2
in proc_run --  after switch pid is 2
in do_wait -- find a zombie child 3 release the PCB and release stack
in user_process -- I catch my child with exit number 12345678
in user_process -- I will return
in user exit -- I'll call the sys_exit
in user sys_exit -- I'll call syscall(SYS_exit, error_code)
in kern sys_exit -- I'll call do_exit
in do_exit -- this proc is not idleproc or initproc
in do_exit -- set cr3 at 0x002c4000 decrease the reference number of current->mm
in do_exit -- set the status with PROC_ZOMBIE
in wakeup_proc -- set proc 1 status with PROC_RUNNABLE
in do_exit -- before schedule
in schedule -- proc switch from proc 2 to proc 1
in proc_run -- change the current to pid 1
in proc_run -- set esp to 0xc03a8000 and set cr3 to 0x002c4000
in proc_run --  before switch pid is 1
in proc_run --  after switch pid is 1
in do_wait -- find a zombie child 2 release the PCB and release stack
in schedule -- proc switch from proc 1 to proc 1
all user-mode processes have quit.
init check memory pass.
in do_exit -- exit from initproc
kernel panic at kern/process/proc.c:463:
    initproc exit.
```