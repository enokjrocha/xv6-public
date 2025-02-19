#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int sys_set_prio (void){
  int priority;

  if(argint(0, &priority) < 0){
    return -1; //error
  }else{
    return set_prio (priority);
  }
}


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_yield(void){
  yield();
  return 0;
}

int sys_wait2(void){
  int *retime, *rutime, *stime;
  
  if(argptr(0 , (char**)&retime ,sizeof(int)) < 0){
    return -1;
  }else if(argptr(1 , (char**)&rutime ,sizeof(int)) < 0){
    return -1;
  }else if(argptr(2 , (char**)&stime ,sizeof(int)) < 0){
    return -1;
  }else{
    return wait2(retime, rutime, stime);
  }
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
