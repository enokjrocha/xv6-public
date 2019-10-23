
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define CICLE 1000000

int main(int argc, char *argv[]){
  int i, n;
  int n_process;
  int pid = 0;
  int retime = 0, rutime =  0, stime = 0;
  
  n = atoi(argv[1]);
  n_process = 3 * n;
  int c;
 
  for (i = 0; i < n_process; i++ ) {
    pid = fork();
    if (pid > 0){ 
      wait();
    }else{ 
      
      printf(1, "O processo %d foi criado\n",i);

      if (i % 3 == 2){ //TIPO IO-BOUND
        printf(0, "IO-Bound%d\n",pid);
        for (c = 0; c < 100; c++){
         sleep(1);
       }
      }

      if (i % 3 == 1){//TIPO S-BOUND
        printf(0, "S-Bound: %d\n",pid);
        for (c = 0; c < 100; c++){
           for (int j = 0; j < CICLE; j++){}
        yield();
      
        }
      }

      if (i % 3 == 0){//TIPO CPU-BOUND
      printf(0, "CPU-Bound: %d\n", pid);
    	 for (c = 0; c < 100; c++){
    	   for (int j = 0; j < CICLE; j++) {}
    	 }
    	}      
      break;
    }
  }
  
  wait2(&retime, &rutime, &stime);
  printf(0, "retime: %d, rutime: %d, stime: %d\n", (retime/n_process), (rutime/n_process), (stime/n_process));
  exit();
}