#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "display.h"




int main()
{
 		 
  int i;

pthread_t mythread1, mythread2;
pthread_mutex_t mymutex;


pthread_mutex_init(&mymutex,NULL);
	

  void *myfunction1 (void *pid)
  { int i;
     for (i=0;i<10;i++) {
	// prin kai meta ginetai xrisi tis mutex gia na min epitrepsei taftoxroni xrisi tou display
	pthread_mutex_lock(&mymutex);
       display("Hello world\n");
	pthread_mutex_unlock(&mymutex);
      }
    wait(NULL);
  }

// arxi protou thread pou kanei dislpay to hello world
 pthread_create(&mythread1,NULL,&myfunction1,NULL);

 void *myfunction2 (void *pid)
  { int i;
 for (i=0;i<10;i++) {
// prin kai meta ginetai xrisi tis mutex gia na min epitrepsei taftoxroni xrisi tou display
   pthread_mutex_lock(&mymutex);
    display("Kalimera kosme\n");
    pthread_mutex_unlock(&mymutex);
 }

}

// arxi tou defterou thread pou kanei display to kalimera kosme
	pthread_create(&mythread2,NULL,&myfunction2,NULL);

// syntonismos twn threads 
pthread_join(mythread1,NULL);
pthread_join(mythread2,NULL);

// diagrafi apo tin mnimi tis mutex
pthread_mutex_destroy(&mymutex);


   return 0;
}
