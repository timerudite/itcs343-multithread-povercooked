#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>

int orderSpaceCount = 5;
int cookSpaceCount = 0;

// Declare global variable, flags, arrays
#define SIZE 5
#define PMAX 10

int  quitFlag = 0;

char orderArray[SIZE][30];
int pairArray[SIZE];

sem_t cookSpace;
sem_t orderSpace;
pthread_mutex_t mutex;

void fillOrder(char *orderName); 
const char* getOrder(int index);
int pairing(int threadId);
void unPairing(int pairIndex);

void cooking(const char* orderName, int tid) {
 
  
  if (strcmp(orderName, "TonkotsuRamen") == 0) {
    int amount = 3;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "ButterChicken") == 0) {
    int amount = 10;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "BeefBurger") == 0) {
    int amount = 2;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "Padthai") == 0) {
    int amount = 1;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "Pancake") == 0) {
    int amount = 3;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "EggBenedict") == 0) {
    int amount = 2;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "FriedRice") == 0) {
    int amount = 3;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "PorkChop") == 0) {
    int amount = 4;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "Pho") == 0) {
    int amount = 1;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else if (strcmp(orderName, "FishAndShip") == 0) {
    int amount = 2;
    printf("Thread %d is cooking %s for %d second\n", tid, orderName, amount);
    sleep(amount);
  } else {
    printf("Error for sure ==== Thread %d is cooking %s\n", tid, orderName);
    sleep(2);
  }
}

void *playerThread(void *id){
  int tid = (intptr_t) id;
  printf("Thread %d  ready to work\n", tid);
  while (1) {
    sem_wait(&cookSpace);

    if(quitFlag == 1) {
      printf("______Thread %d is quiting\n", tid);
      sem_post(&cookSpace);
      return NULL;
    }

    pthread_mutex_lock(&mutex);
    int pairNumber = pairing(tid);
    // printf("Process %d got pairNUmber: %d\n", tid, pairNumber);
    pthread_mutex_unlock(&mutex);
    
    const char* orderName = getOrder(pairNumber);

    if(strcmp(orderName, "quit") == 0) {
      printf("______Thread %d was told to quit\n", tid);
      unPairing(pairNumber);
      quitFlag = 1;
      sem_post(&cookSpace);
      return NULL;
    }
    printf("Thread %d process %s\n", tid, orderName);

    cooking(orderName, tid);


    // printf("Process %d is processing %s\n", tid, orderName);
    unPairing(pairNumber);
    printf("Thread %d finishes %s\n", tid, orderName);
    sem_post(&orderSpace);
    
  }
  return NULL;
}

void fillOrder(char *orderName) {
  int index;
  int i;
  for(i=0; i<SIZE; i++) {
    if (pairArray[i] == -1) {
      index = i;
      strcpy(orderArray[index], orderName);
      // printf("receive order to be filled: %s\n", orderArray[index]);
      break;
    }
  }
}
 
const char* getOrder(int index) {
  return orderArray[index];
}

int pairing(int threadId) {
  int i;
  // int pairNumber = 0;
  for(i=0; i<SIZE; i++) {
    if(pairArray[i] == -1) {
      pairArray[i] = threadId;
      return i;
    }
  }
  printf("Error for sure\nprobably cannot find element with -1");
  exit(1);
  return 0;
}

void unPairing(int pairIndex) {
  pairArray[pairIndex] = -1;
}

int main() {
  printf("Start program...\n");

  // initialize the pair array for every element to be -1
  int i;
  for(i=0; i<SIZE; i++) {
    pairArray[i] = -1;
  }

  // initialize semaphore, 
  // cookSpace for limiting thread to access order array, starting at 0
  // orderSpace for limiting main() to access order array, starting at 5
  sem_init(&orderSpace, 0, 5);
  sem_init(&cookSpace, 0, 0);
  pthread_mutex_init(&mutex, NULL);

  // initialize player threads
  pthread_t player[PMAX];
  for(i=0; i<PMAX; i++) {
    pthread_create(&player[i], NULL, playerThread, (void *) (intptr_t) i);
  }

  
  // // Input order from file 1
  // char *line;
  // ssize_t lineSize;
  // size_t len = 0;
  // FILE *fptr;
  // // Error handlinig when pointer returns NULL.
  // if((fptr = fopen("orders.txt", "r")) == NULL) {
  //   printf("Error! unable to open file");
  //   exit(1);
  // }
  // fptr = fopen("orders.txt", "r");
  // if(fptr == NULL) {
  //   printf("Error! Unable to open file");
  //   exit(1);
  // }

  // // read line by line from the file
  // while((lineSize = getline(&line, &len, fptr)) != -1) {
  //   // printf("Retrieved line of length %zu:\n", lineSize);
  //   // printf("%s", line);
  //   printf("Producer: Waiting to add order\n");
  //   sem_wait(&orderSpace);
    
  //   printf("Producer: OrderSpace Decrease || Adding order\n");
  //   fillOrder(line);
  //   printf("Producer: CookSpace will Increase || Add %s\n", line);
  //   sem_post(&cookSpace);

  // }
  // // end input 1

  // Input order from file 2
  char line[20];
  int len = 20;
  FILE *fptr;
  // Error handling when pointer returns NULL.
  fptr = fopen("orders.txt", "r");
  if(fptr == NULL) {
    printf("Error! Unable to open file");
    exit(1);
  }
  // read line by line from the file
  while(fgets(line, len, fptr) != NULL) {
    line[strlen(line)-1] = '\0';
    // printf("%s\n", line);
    printf("Producer: Waiting to add order\n");
    
    sem_wait(&orderSpace);
    printf("Producer: OrderSpace Decrease || Adding order\n");
    fillOrder(line);
    printf("Producer: CookSpace will Increase || Add %s\n", line);
    sem_post(&cookSpace);
  }
  fclose(fptr);
  
  // end input 2

  // wait for all thread to finish
  for(i=0; i<PMAX; i++) {
    pthread_join(player[i], NULL);
  }
  pthread_mutex_destroy(&mutex);

  printf("Finish program\n");
  return 0;


}
