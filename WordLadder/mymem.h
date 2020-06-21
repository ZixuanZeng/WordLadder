/*mymem.h*/

//
// wrapper funtions for malloc and free
//
// Zixuan Zeng
// Visual Studio 2015 on Windows
// U. of Illinois, Chicago
// CS251, Fall 2016
// HW #14
//

void *mymalloc(unsigned int size);
void  myfree(void *ptr);
void  mymem_stats();
