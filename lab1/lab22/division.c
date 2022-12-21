#include "sharedLib.h"
//Константы и структура для операций
int main() {
    sem_t* main_sem = sem_open(MAIN_SEMAPHOR, 0);
    sem_t* div_sem = sem_open(DIVISION_SEMAPHOR, 0);
    struct OperationStructure* ptr = allocateShm();
    sem_post(main_sem);
    while(1){
        sem_wait(div_sem);
        ptr->originalValue = ptr->originalValue/ptr->modificationValue;
        sem_post(main_sem);
    }
	return 0;
}