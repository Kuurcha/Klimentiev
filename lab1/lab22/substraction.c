#include "sharedLib.h"
//Константы и структура для операций
int main() {
    sem_t* main_sem = sem_open(MAIN_SEMAPHOR, 0);
    sem_t* sub_sem = sem_open(SUBSTRACTION_SEMAPHOR, 0);
    struct OperationStructure* ptr = allocateShm();
    sem_post(main_sem);
    while(1){
        sem_wait(sub_sem);
        ptr->originalValue -= ptr->modificationValue;
        sem_post(main_sem);
    }
	return 0;
}