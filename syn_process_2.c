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

int semid_ab;  // o semid_ab xrisimopoieitai gia na dilonei ektyposi tou ab me afxisi tou kai anamoni na ginei me meiosi tou 
int semid_cd;  // omoios o semid_cd xrisimiopoitai gia tin ektyposi tou cd

 semid_ab = semget(IPC_PRIVATE, 1, 0600);   
 semctl(semid, 0, SETVAL, 0);	

 semid_cd = semget(IPC_PRIVATE, 1, 0600);   
 semctl(semid, 0, SETVAL, 0);	


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
       display("ab");
	OP.sem_op = 1;
       semop(semid, &OP, 1);

	OP.sem_op = 1; // edw dilonetai oti egine ektyposi ab
       semop(semid_ab, &OP, 1);

	OP.sem_op = -1; // edw perimenei ektyposi cd
       semop(semid_cd, &OP, 1);
      }
    wait(NULL);
  }
  else
  {




 for (i=0;i<10;i++) {

OP.sem_op = -1; // edw perimenei ektyposi ab
       semop(semid_ab, &OP, 1);
	// prin kai meta ginetai xrisi tou semaphore kathorizontas tin praxi pou tha ginei
/// diladi miosi arxika tou semaphore kai meta afxisi
   OP.sem_op = -1; 
    semop(semid, &OP, 1);
    display("cd\n");
     OP.sem_op = 1;
       semop(semid, &OP, 1);


	OP.sem_op = 1; // edw dilonetai oti egine ektyposi cd
       semop(semid_cd, &OP, 1);

 }

  }

// kai diagrafi twn semaphorwn
      semctl(semid, 0, IPC_RMID);

semctl(semid_ab, 0, IPC_RMID);
semctl(semid_cd, 0, IPC_RMID);


   return 0;
}
