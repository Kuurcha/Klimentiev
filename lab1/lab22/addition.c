#include "sharedLib.h"
//Константы и структура для операций
int main() {
    sem_t* main_sem = sem_open(MAIN_SEMAPHOR, 0);
    sem_t* add_sem = sem_open(ADD_SEMAPHOR, 0);
    sem_t*  sync_add_sem = sem_open(SYNC_ADD_SEMAPHOR, 0);
    struct OperationStructure* ptr = allocateShm();
    printf("%s", "addition program init");
    sem_post(main_sem);
    while(1){
        sem_wait(add_sem);
        ptr->originalValue +=ptr->modificationValue;
        sem_post(main_sem);
    }
	return 0;
}