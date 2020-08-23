#define type int
#include "list.h"
#include <time.h>
void print(int_const_reference data)
{
	printf("i = %d\n", *data);
}
static bool comp(int_const_reference data1, int_const_reference data2)
{
	return *data1 <= *data2 ? true : false;
}
int main()
{
	int temp = 0;
	int_list* list = int_ListConstructor("d");
	for (int i = 10000000; i != 0;  --i)
	{
		temp = i;
		list->push_back(&temp);
	}
	printf("插入完\n");
	clock_t start, finish;
   	double Total_time;
	start = clock();
	list->sort(comp);
	finish = clock();
	Total_time = (double)(finish-start) / CLOCKS_PER_SEC; 
    printf( "%f seconds\n", Total_time); 
	printf("size=%u\n", list->size());
	printf("%d\n", *list->front());
	return 0;
}


