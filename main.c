#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Array{

    int size;
    char* string;

};

typedef struct Array string;

#define CHOICE 67
#define MUTATE 15
#define COPIES 60

int generateRandom(int n);
int identifyFitness(const char *a, const char *b);
void mutateSentence(const char *a, char *b, string* sourceString);

int main()
{
    string* targetString = malloc(sizeof(string));
    targetString->size = 60;
    targetString->string = malloc(30* sizeof(char ));
    targetString->string = "Today weather is amazing...";

    string* sourceString = malloc(sizeof(string));
    sourceString->size = 30;
    sourceString->string = "ABCDEFGHIJKLMNOPQRSTUVWXYZqwertyuıopğüasdfghjklşizxcvbnmöç., ";

    int i, best_i, unfit, best = 0, iters = 0;
    char specimen[COPIES][60];

    /* init rand string */
    for (i = 0; targetString->string[i]; i++)
        specimen[0][i] = sourceString->string[generateRandom(CHOICE)];
    specimen[0][i] = 0;

    do {
        for (i = 1; i < COPIES; i++)
            mutateSentence(specimen[0], specimen[i], sourceString);

        /* find best fitting string */
        for (best_i = i = 0; i < COPIES; i++) {
            unfit = identifyFitness(targetString->string, specimen[i]);
            if(unfit < best || !i) {
                best = unfit;
                best_i = i;
            }
        }

        if (best_i) strcpy(specimen[0], specimen[best_i]);
        printf("Generation %d, score %d: %s\n", iters++, best, specimen[0]);
    } while (best);

    return 0;
}

/* returns random integer from 0 to n - 1 */
int generateRandom(int n)
{
    int r, rand_max = RAND_MAX - (RAND_MAX % n);
    while((r = rand()) >= rand_max);
    return r / (rand_max / n);
}

/* number of different chars between a and b */
int identifyFitness(const char *a, const char *b)
{
    int sum = 0;
    for (int i = 0; a[i]; i++)
        sum += (a[i] != b[i]);
    return sum;
}

/* Each char of b has 1/MUTATE chance of differing from a */
void mutateSentence(const char *a, char *b, string* sourceString)
{
    int i;
    for (i = 0; a[i]; i++)
        b[i] = generateRandom(MUTATE) ? a[i] : sourceString->string[generateRandom(CHOICE)];

    b[i] = '\0';
}




