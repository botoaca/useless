#include <stdlib.h>
#include <string.h>
int* bubble_sort(int* arr, int len)
{
    int* ret_arr = malloc(sizeof(int) * len);
    memcpy(ret_arr, arr, sizeof(int) * len);
    int i, j;
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < len - i - 1; j++)
        {
            if (ret_arr[j] > ret_arr[j + 1])
            {
                int tmp = ret_arr[j];
                ret_arr[j] = ret_arr[j + 1];
                ret_arr[j + 1] = tmp;
            }
        }
    }
    return ret_arr;
}