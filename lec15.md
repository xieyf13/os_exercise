# lec15 课堂作业报告

2013011356 董豪宇

2013011302 李奕昕

## EDF概述

EDF的思路非常简单, 即在可抢占的情况下总是执行离ddl最近的一个进程. 

## 实验思路

### 相关数据结构说明

```
typedef struct {
    int id;
    int relative_deadline;
    int execute_time;
    int elapse_time;
} struct_proc;
```

用于PCB的模拟, relative_deadline表示距离ddl的时间, id是该进程的进程号, execute_time是该进程结束还需要的执行时间, elapse_time则是进程用去的时间. 

```
struct_proc *current = NULL;
```

current指针, 指向当前的进程. 

```
struct_proc procs[MAXPROC];
```

处于简化的考虑, 这里的procs既是ucore中的调度队列, 同时也是PCB的组织队列. 

### 重要函数说明

```
void execute()
```

用于实际进程算法模拟. 

```
bool create_proc()
```

分配PCB, 并随机地生成该进程的相对ddl(即离真正ddl时间), 需要执行的时间, 并分配进程号. 

```
void schedule()
```

进行调度, 即current的选取, 如果没有可用的进程, 那么current置为NULL, 表示idle进程正在运行. 

### 大体思路

设置全局时间time_elapse, execute中每循环一次time_elapse加1, 并且current也执行一个单位的时间, 并作响应处理, 并在每个回合结束时以1/3的概率创建新的进程. 

## 运行结果