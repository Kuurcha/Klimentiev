#include "sharedLib.h"
#include <math.h>
//Константы и структура для операций
int main() {
    sem_t* main_sem = sem_open(MAIN_SEMAPHOR, 0);
    sem_t* sqrt_sem = sem_open(SQUAREROOT_SEMAPHOR, 0);
    struct OperationStructure* ptr = allocateShm();
    sem_post(main_sem);
    while(1){
        sem_wait(sqrt_sem);
        ptr->modificationValue = 0;
        ptr->originalValue = sqrt(ptr->originalValue);
        sem_post(main_sem);
    }
	return 0;
}