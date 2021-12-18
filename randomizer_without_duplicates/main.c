#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int* arr;
    int len;
    int last;
} Randomizer;

Randomizer randomizer_new(int* arr, int len)
{
    Randomizer rd;
    rd.arr = arr;
    rd.len = len;
    return rd;
}

int get_next_random(Randomizer* rd)
{
#define next rd->arr[rand() % rd->len]
    int x = next;
    while (rd->last == x)
        x = next;
    rd->last = x;
    return x;
#undef next
}

int main()
{
    srand(time(NULL));

    const int loclen = 8;
    int* arr = malloc(sizeof(int) * loclen);
    for (int i = 0; i < loclen; i++)
        arr[i] = i + 1;

    Randomizer rd = randomizer_new(arr, loclen);

    for (int i = 0; i < 1000; i++)
        printf("%d ", get_next_random(&rd));
}
