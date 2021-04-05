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

int quitFlag = 0;

char orderArray[SIZE][30];
int pairArray[SIZE];

sem_t cookSpace;
sem_t orderSpace;
pthread_mutex_t mutex;

void fillOrder(char *orderName);
const char *getOrder(int index);
int pairing(int threadId);
void unPairing(int pairIndex);

// Use for Turnaround Time
float amount_0 = 0, amount_1 = 0, amount_2 = 0, amount_3 = 0, amount_4 = 0, amount_5 = 0, amount_6 = 0, amount_7 = 0, amount_8 = 0, amount_9 = 0;

void cooking(const char *orderName, int tid)
{
  if (strcmp(orderName, "TonkotsuRamen") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[3][10] = {"Noodle", "Broth", "Chashu"};
    char Met[3][10] = {"Boil", "Boil", "Grill"};
    int prep_0 = 5, prep_1 = 9, prep_2 = 4;
    int cook_0 = 2, cook_1 = 3, cook_2 = 6;

    printf("Ingredients of %s: \n- %s\n- %s\n- %s", orderName, Ingre[0], Ingre[1], Ingre[2]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: %s is preparing for %d second\n", tid, Ingre[2], prep_2);
    sleep(prep_2);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[2], Met[2], cook_2);
    sleep(cook_2);

    amount_0 = (prep_0 + cook_0) + (prep_1 + cook_1) + (prep_2 + cook_2);
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_0, orderName);
  }
  else if (strcmp(orderName, "ButterChicken") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[3][10] = {"Nann", "Curry", "Chicken"};
    char Met[3][10] = {"Grill", "Boil", "Grill"};
    int prep_0 = 7, prep_1 = 9, prep_2 = 3;
    int cook_0 = 6, cook_1 = 8, cook_2 = 5;

    printf("Ingredients of %s: \n- %s\n- %s\n- %s", orderName, Ingre[0], Ingre[1], Ingre[2]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: %s is preparing for %d second\n", tid, Ingre[2], prep_2);
    sleep(prep_2);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[2], Met[2], cook_2);
    sleep(cook_2);

    amount_1 = (prep_0 + cook_0) + (prep_1 + cook_1) + (prep_2 + cook_2);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_1, orderName);
  }
  else if (strcmp(orderName, "BeefBurger") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[3][10] = {"Buns", "Veggies", "Beef"};
    char Met[3][10] = {"Toast", "", "Grill"};
    int prep_0 = 2, prep_1 = 2, prep_2 = 3;
    int cook_0 = 3, cook_1 = 0, cook_2 = 4;

    printf("Ingredients of %s: \n- %s\n- %s\n- %s", orderName, Ingre[0], Ingre[1], Ingre[2]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: %s is preparing for %d second\n", tid, Ingre[2], prep_2);
    sleep(prep_2);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[2], Met[2], cook_2);
    sleep(cook_2);

    amount_2 = (prep_0 + cook_0) + (prep_1 + cook_1) + (prep_2 + cook_2);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_2, orderName);
  }
  else if (strcmp(orderName, "Padthai") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[3][10] = {"Noodle", "Sauce", "Shrimp"};
    char Met[3][10] = {"Boil", "Boil", "Frie"};
    int prep_0 = 3, prep_1 = 5, prep_2 = 4;
    int cook_0 = 2, cook_1 = 3, cook_2 = 3;

    printf("Ingredients of %s: \n- %s\n- %s\n- %s", orderName, Ingre[0], Ingre[1], Ingre[2]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: %s is preparing for %d second\n", tid, Ingre[2], prep_2);
    sleep(prep_2);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[2], Met[2], cook_2);
    sleep(cook_2);

    amount_3 = (prep_0 + cook_0) + (prep_1 + cook_1) + (prep_2 + cook_2);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_3, orderName);
  }
  else if (strcmp(orderName, "Pancake") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[2][10] = {"PancakeMix", "Honey"};
    char Met[2][10] = {"Frie", ""};
    int prep_0 = 2, prep_1 = 3;
    int cook_0 = 4, cook_1 = 0;

    printf("Ingredients of %s: \n- %s\n- %s", orderName, Ingre[0], Ingre[1]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    amount_4 = (prep_0 + cook_0) + (prep_1 + cook_1);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_4, orderName);
  }
  else if (strcmp(orderName, "EggBenedict") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[2][10] = {"Egg", "Salt"};
    char Met[2][10] = {"Boil", ""};
    int prep_0 = 2, prep_1 = 1;
    int cook_0 = 6, cook_1 = 0;

    printf("Ingredients of %s: \n- %s\n- %s", orderName, Ingre[0], Ingre[1]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    amount_5 = (prep_0 + cook_0) + (prep_1 + cook_1);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_5, orderName);
  }
  else if (strcmp(orderName, "FriedRice") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[3][10] = {"Rice", "Egg", "Onions"};
    char Met[3][10] = {"CookRiced", "Frie", "Frie"};
    int prep_0 = 5, prep_1 = 2, prep_2 = 1;
    int cook_0 = 9, cook_1 = 6, cook_2 = 3;

    printf("Ingredients of %s: \n- %s\n- %s\n- %s", orderName, Ingre[0], Ingre[1], Ingre[2]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: %s is preparing for %d second\n", tid, Ingre[2], prep_2);
    sleep(prep_2);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[2], Met[2], cook_2);
    sleep(cook_2);

    amount_6 = (prep_0 + cook_0) + (prep_1 + cook_1) + (prep_2 + cook_2);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_6, orderName);
  }
  else if (strcmp(orderName, "PorkChop") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[3][10] = {"Pork", "Sauce", "Potato"};
    char Met[3][10] = {"Grill", "Boil", "Boil"};
    int prep_0 = 5, prep_1 = 5, prep_2 = 4;
    int cook_0 = 6, cook_1 = 2, cook_2 = 3;

    printf("Ingredients of %s: \n- %s\n- %s\n- %s", orderName, Ingre[0], Ingre[1], Ingre[2]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: %s is preparing for %d second\n", tid, Ingre[2], prep_2);
    sleep(prep_2);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[2], Met[2], cook_2);
    sleep(cook_2);

    amount_7 = (prep_0 + cook_0) + (prep_1 + cook_1) + (prep_2 + cook_2);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_7, orderName);
  }
  else if (strcmp(orderName, "Pho") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[3][10] = {"Noodle", "Sausage", "Veggies"};
    char Met[3][10] = {"Boil", "Boil", "Boil"};
    int prep_0 = 5, prep_1 = 3, prep_2 = 3;
    int cook_0 = 3, cook_1 = 6, cook_2 = 3;

    printf("Ingredients of %s: \n- %s\n- %s\n- %s", orderName, Ingre[0], Ingre[1], Ingre[2]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: %s is preparing for %d second\n", tid, Ingre[2], prep_2);
    sleep(prep_2);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[2], Met[2], cook_2);
    sleep(cook_2);

    amount_8 = (prep_0 + cook_0) + (prep_1 + cook_1) + (prep_2 + cook_2);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_8, orderName);
  }
  else if (strcmp(orderName, "FishAndShip") == 0)
  {
    printf("Thread %d: start %s\n", tid, orderName);

    char Ingre[2][10] = {"Fish", "Potato"};
    char Met[2][10] = {"Frie", "Frie"};
    int prep_0 = 8, prep_1 = 3;
    int cook_0 = 6, cook_1 = 6;

    printf("Ingredients of %s: \n- %s\n- %s\n", orderName, Ingre[0], Ingre[1]);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[0], prep_0);
    sleep(prep_0);

    printf("\nThread %d: %s is preparing for %d second", tid, Ingre[1], prep_1);
    sleep(prep_1);

    printf("\nThread %d: finishes ingredients preparation for %s", tid, orderName);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[0], Met[0], cook_0);
    sleep(cook_0);

    printf("\nThread %d: %s is %s for %d second", tid, Ingre[1], Met[1], cook_1);
    sleep(cook_1);

    amount_9 = (prep_0 + cook_0) + (prep_1 + cook_1);
    //printf("\n------------------------------------------");
    printf("\nThread %d uses %.2f second to serve %s\n", tid, amount_9, orderName);
  }
  else
  {
    printf("Error for sure ==== Thread %d is cooking %s\n", tid, orderName);
    sleep(2);
  }
}

void *playerThread(void *id)
{
  int tid = (intptr_t)id;
  printf("Thread %d  ready to work\n", tid);
  while (1)
  {
    sem_wait(&cookSpace);

    if (quitFlag == 1)
    {
      printf("______Thread %d is quiting\n", tid);
      //printf("\n------------------------------------------\n");
      sem_post(&cookSpace);
      return NULL;
    }

    pthread_mutex_lock(&mutex);
    int pairNumber = pairing(tid);
    // printf("Process %d got pairNUmber: %d\n", tid, pairNumber);
    pthread_mutex_unlock(&mutex);

    const char *orderName = getOrder(pairNumber);

    if (strcmp(orderName, "quit") == 0)
    {
      printf("______Thread %d was told to quit\n", tid);
      unPairing(pairNumber);
      quitFlag = 1;
      sem_post(&cookSpace);
      return NULL;
    }
    printf("Thread %d recieves order: %s\n", tid, orderName);

    cooking(orderName, tid);

    // printf("Process %d is processing %s\n", tid, orderName);
    unPairing(pairNumber);
    printf("\nThread %d finishes %s\n", tid, orderName);
    sem_post(&orderSpace);
  }
  return NULL;
}

void fillOrder(char *orderName)
{
  int index;
  int i;
  for (i = 0; i < SIZE; i++)
  {
    if (pairArray[i] == -1)
    {
      index = i;
      strcpy(orderArray[index], orderName);
      // printf("receive order to be filled: %s\n", orderArray[index]);
      break;
    }
  }
}

const char *getOrder(int index)
{
  return orderArray[index];
}

int pairing(int threadId)
{
  int i;
  // int pairNumber = 0;
  for (i = 0; i < SIZE; i++)
  {
    if (pairArray[i] == -1)
    {
      pairArray[i] = threadId;
      return i;
    }
  }
  printf("Error for sure\nprobably cannot find element with -1");
  exit(1);
  return 0;
}

void unPairing(int pairIndex)
{
  pairArray[pairIndex] = -1;
}

int main()
{
  printf("Start program...\n");

  // initialize the pair array for every element to be -1
  int i;
  for (i = 0; i < SIZE; i++)
  {
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
  for (i = 0; i < PMAX; i++)
  {
    pthread_create(&player[i], NULL, playerThread, (void *)(intptr_t)i);
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
  if (fptr == NULL)
  {
    printf("Error! Unable to open file");
    exit(1);
  }
  // read line by line from the file
  while (fgets(line, len, fptr) != NULL)
  {
    line[strlen(line) - 1] = '\0';
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
  for (i = 0; i < PMAX; i++)
  {
    pthread_join(player[i], NULL);
  }
  pthread_mutex_destroy(&mutex);

  float TT = (amount_0 + amount_1 + amount_2 + amount_3 + amount_4 + amount_5 + amount_6 + amount_7 + amount_8 + amount_9);
  float avgTT = TT / 10;

  printf("\n------------------------------------------");
  printf("\nA whole time that use for every order is %.2f second\n", TT);
  printf("Average turnaround time for each order is %.2f second\n", avgTT);

  printf("\nFinish program: Enjoy your meal !!\n");
  return 0;
}
