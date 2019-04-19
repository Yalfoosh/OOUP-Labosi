#include <stdio.h>
#include <string.h>

const void* mymax(const void *array, size_t array_len, size_t member_size, int (*cmp)(const void *, const void *))
{
    void* current_element = (void*)array;
    void* max = current_element;

    for(int i = 0; i < array_len; ++i, current_element += member_size)
        if(cmp(current_element, max)) max = current_element;

    return max;
}

int gt_int(const void* a, const void* b) { return *((int*)a) > *((int*)b); }
int gt_char(const void* a, const void* b) { return *((char*)a) > *((char*)b); }
int gt_str(const void* a, const void* b) { return strcmp(*((char**)a), *((char**)b)) > 0; }

int main()
{
    int arr_int[] = {1, 3, 5, 7, 4, 6, 9, 2, 0};
    char arr_char[] = "Suncana strana ulice";
    const char* arr_str[] = {"Gle", "malu", "vocku", "poslije", "kise", "Puna", "je", "kapi", "pa", "ih", "njise"};

    char ints[] = "{1, 3, 5, 7, 4, 6, 9, 2, 0}";
    char chars[] = "Suncana strana ulice";
    char strs[] = "{Gle, malu, vocku, poslije, kise, Puna, je, kapi, pa, ih, njise}";

    printf("Max od %s je %d.\n",
           ints,
           *((int*)mymax(arr_int, sizeof(arr_int) / sizeof(*arr_int), sizeof(*arr_int), &gt_int)));

    printf("Max od \"%s\" je %c.\n",
           chars,
           *((char*)mymax(arr_char, sizeof(arr_char) / sizeof(*arr_char), sizeof(*arr_char), &gt_char)));

    printf("Max od %s je \"%s\".\n",
           strs,
           *((char**)mymax(arr_str, sizeof(arr_str) / sizeof(*arr_str), sizeof(*arr_str), &gt_str)));
}