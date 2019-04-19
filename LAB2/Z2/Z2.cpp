#include <cstdio>
#include <cstring>
#include <iostream>

template <typename Iterator, typename Predicate>
Iterator mymax(Iterator current, Iterator last, Predicate predicate)
{
	Iterator max;

	for(max = current; current != last; ++current)
	    if(predicate(current, max)) max = current;

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

    std::cout << "Max od " << ints
              << " je " << *mymax(arr_int, arr_int + (sizeof(arr_int) / sizeof(*arr_int)), gt_int)
              << "." << std::endl;

    std::cout << "Max od \"" << chars
              << "\" je " << *mymax(arr_char, arr_char + (sizeof(arr_char) / sizeof(*arr_char)), gt_char)
              << "." << std::endl;

    std::cout << "Max od " << strs
              << " je \"" << *mymax(arr_str, arr_str + (sizeof(arr_str) / sizeof(*arr_str)), gt_str)
              << "\"." << std::endl;
}
