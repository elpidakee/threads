#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display.h"
#include <sys/sem.h>



int main()
{
 		 
  int i;
struct sembuf OP={0,0,0};
 int semid;  


// orizetai enas semaphore pou tha prostatevei tis ektyposeis display
 semid = semget(IPC_PRIVATE, 1, 0600);   
 semctl(semid, 0, SETVAL, 1);	

  if (fork())
  {
     for (i=0;i<10;i++) {
	// prin kai meta ginetai xrisi tou semaphore kathorizontas tin praxi pou tha ginei
/// diladi miosi arxika tou semaphore kai meta afxisi
	OP.sem_op = -1; 
       semop(semid, &OP, 1);
       display("Hello world\n");
	OP.sem_op = 1;
       semop(semid, &OP, 1);
      }
    wait(NULL);
  }
  else
  {

	// prin kai meta ginetai xrisi tou semaphore kathorizontas tin praxi pou tha ginei
/// diladi miosi arxika tou semaphore kai meta afxisi
 for (i=0;i<10;i++) {
   OP.sem_op = -1; 
    semop(semid, &OP, 1);
    display("Kalimera kosme\n");
     OP.sem_op = 1;
       semop(semid, &OP, 1);
 }

  }

// kai diagrafi tou semaphore
      semctl(semid, 0, IPC_RMID);


   return 0;
}
