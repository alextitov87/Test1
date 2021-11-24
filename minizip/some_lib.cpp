#include <cstdlib>
int *mz_zip_reader_create1(void **handle) {
	int k=100;
	int * i=static_cast<int*>(malloc(4)) ;
	*i=100;
    return i;
}
