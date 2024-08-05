/****************************************************************
**	Dining - Solution for the "Dining Philosopher Problem"
**
**	Harel Wallach 31966708
**	Daniel Kletter 37267630
**	
**	Discription:
**	The initialization code is from: http://rosettacode.org/wiki/Dining_philosophers.
**	We used the code for generating the threads, the philosopher data and 
**	main function control flow.
**	We replaced the locking mechanism with Double mutex.
**	The algorithm uses mutex array represanting each fork, and
**	another global mutex to synchronize the "picking up" procedure. 
**	This means that when a thread wants to pick up forks it needs to lock 
**	all other threads. This way picking up two fork becomes an atomic operation.
**	
**	If this solution is right, we should get world wide recognition.
**	
*********************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 8 
#define TOTALRUN 20
 
typedef struct philData {
    pthread_mutex_t *fork_lft, *fork_rgt, *pickup;
    int name;
    pthread_t thread;
    int   fairness;
} Philosopher;

int running;

int pickupforks( Philosopher *phil) {
	int stat;
	if ( !(stat = pthread_mutex_trylock(phil->pickup))) {			//try locking everyone
		if (!(stat = pthread_mutex_lock(phil->fork_lft))){		//lock left
			if(!(stat = pthread_mutex_lock(phil->fork_rgt))){	//lock right
				pthread_mutex_unlock(phil->pickup);				//release everyone
				return 1;
			}
		}
	}
	pthread_mutex_unlock(phil->pickup);
	return 0;	
}

void releaseforks( Philosopher *phil) {
	pthread_mutex_unlock( phil->fork_lft);
    pthread_mutex_unlock( phil->fork_rgt);
}
 
void *PhilFunction(void *p) {
    Philosopher *phil = (Philosopher*)p;
 
    while (running) {
        printf("Philosopher %d is sleeping and thinking\n", phil->name);
		sleep(1);
        printf("Philosopher %d wants to eat\n", phil->name);
        while(!pickupforks(phil)){
		
		printf("Philosopher %d failed to pickup\n", phil->name);
		sleep(1);
		}
		printf("%d is eating\n", phil->name);
		sleep(1);
		phil->fairness++;	//eating counter
		releaseforks(phil);	
    }
    return NULL;
}
 
int main()
{
    pthread_mutex_t forks[N];
    pthread_mutex_t pickup;
    Philosopher philosophers[N];
    Philosopher *phil;
    int i;
    int failed;
 
    /*	initialize "forks"	*/
	for (i=0;i<N; i++) {
        failed = pthread_mutex_init(&forks[i], NULL);
        if (failed) {
            printf("Failed to initialize fork mutexes.");
            exit(1);
        }
    }
	
	/*	initialize global pickup mutex */
	failed = pthread_mutex_init(&pickup, NULL);
	if (failed) {
		printf("Failed to initialize pickup mutex.");
		exit(1);
	}
	
	/*	initalize philosopher threads*/
	running = 1;
    for (i=0;i<N; i++) {
        phil = &philosophers[i];
        phil->name = i;
		phil->fairness = 0;
        phil->fork_lft = &forks[i];
        phil->fork_rgt = &forks[(i+1)%N];
        phil->pickup = &pickup;
        pthread_create( &phil->thread, NULL, PhilFunction, phil);
    }
 
    sleep(TOTALRUN);	//let them dance
    running = 0;
    printf("cleanup time\n");
    printf("fairness check:\n");
	
    for(i=0; i<N; i++) {
        phil = &philosophers[i];
		printf("Philosopher %d ate %d times!\n", phil->name, phil->fairness);
        if ( pthread_cancel( phil->thread) ) {
            printf("error canceling thread for %d\n", phil->name);
            exit(1);
        }
    }
    return 0;
}