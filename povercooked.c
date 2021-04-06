#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>

// Declare global variable, flags, arrays
#define SIZE 5
#define PMAX 10

int quitFlag = 0;

int use = 0;
int fill = 0;

char orderArray[SIZE][30];
// int pairArray[SIZE];

sem_t cookSpace;
sem_t orderSpace;
pthread_mutex_t mutex;

void fillOrder(char *orderName);
const char *getOrder();
// int pairing(int threadId);
// void unPairing(int pairIndex);

void timeCounter()
{
    printf("timeCounter starts \n");
    printf("Press enter to stop fun \n");
    while (1)
    {
        if (getchar())
            break;
    }
    printf("fun() ends \n");
}

void cooking(const char *orderName, int tid)
{
    if (strcmp(orderName, "TonkotsuRamen") == 0)
    {
        printf("Thread %d: start %s\n", tid, orderName);

        printf("cooking: %s : strlen = %zu <- input\ncooking: %s : strlen = %zu <- string\n", orderName, strlen(orderName), "TonkotsuRamen", strlen("TonkotsuRamen"));

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
    }
    else if (strcmp(orderName, "FriedRice") == 0)
    {
        printf("Thread %d: start %s\n", tid, orderName);

        char Ingre[3][10] = {"Rice", "Egg", "Onions"};
        char Met[3][10] = {"CookRiced", "Frie", "Frie"};
        int prep_0 = 5, prep_1 = 2, prep_2 = 3;
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
    }
    else if (strcmp(orderName, "FishAndChip") == 0)
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
    }
    else
    {
        printf("Error for sure ==== Thread %d is cooking %s\n", tid, orderName);
        sleep(2);
    }
}

float sumTime = 0;

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
            sem_post(&cookSpace);
            return NULL;
        }
        time_t startTime = time(NULL);
        fprintf(stdout, "Thread %d starts working at %ld\n", tid, startTime);
        pthread_mutex_lock(&mutex);
        const char *orderName = getOrder();
        pthread_mutex_unlock(&mutex);
        if (strcmp(orderName, "quit") == 0)
        {
            printf("______Thread %d was told to quit\n", tid);
            quitFlag = 1;
            sem_post(&cookSpace);
            return NULL;
        }
        printf("Thread %d recieves order: %s\n", tid, orderName);

        cooking(orderName, tid);

        // printf("Process %d is processing %s\n", tid, orderName);
        // unPairing(pairNumber);

        printf("\nThread %d finishes %s\n", tid, orderName);
        time_t endTime = time(NULL);
        fprintf(stdout, "Thread %d finishes working at %ld\n", tid, endTime);
        fprintf(stdout, "Thread %d use %ld second for cooking\n", tid, (endTime - startTime));
        float useTime = (float)(endTime - startTime);
        sumTime += useTime;
        sem_post(&orderSpace);
    }
    return NULL;
}

void fillOrder(char *orderName)
{
    strcpy(orderArray[fill], orderName);
    fill += 1;
    if (fill == SIZE)
    {
        fill = 0;
    }
}

const char *getOrder()
{
    const char *orderName = orderArray[use];
    use += 1;
    if (use == SIZE)
    {
        use = 0;
    }
    return orderName;
}

int main()
{
    printf("Start program...\n");

    // initialize semaphore, and mutex locj
    // cookSpace for limiting thread to access order array, starting at 0
    // orderSpace for limiting main() to access order array, starting at 5
    sem_init(&orderSpace, 0, 5);
    sem_init(&cookSpace, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // initialize player threads
    int i;
    pthread_t player[PMAX];

    for (i = 0; i < PMAX; i++)
    {
        pthread_create(&player[i], NULL, playerThread, (void *)(intptr_t)i);
    }

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

    float numOrder = 0;
    // read line by line from the file
    while (fgets(line, len, fptr) != NULL)
    {
        // get rid of trailing character at the end of line.
        line[strlen(line) - 1] = '\0';

        sem_wait(&orderSpace);
        // pthread_mutex_lock(&mutex);
        // printf("Producer: OrderSpace Decrease || Adding order\n");
        fillOrder(line);
        printf("Producer: CookSpace will Increase || Add %s\n", line);
        // pthread_mutex_unlock(&mutex);
        sem_post(&cookSpace);
        numOrder += 1.00;
    }
    fclose(fptr);
    // end input 2

    // wait for all thread to finish
    for (i = 0; i < PMAX; i++)
    {
        pthread_join(player[i], NULL);
    }

    //printf("Total time = %f seconds\n", totalTime);

    pthread_mutex_destroy(&mutex);

    printf("\n------------------------------------------");
    printf("\nA whole time that use for every order is %.2f second\n", sumTime);
    float turnAround = sumTime / (numOrder - 1);
    printf("Average turnaround time for each order is %.2f second\n", turnAround);

    printf("\nFinish program: Enjoy your meal !!\n");
    return 0;
}
