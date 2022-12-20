#include "sharedLib.h"
//Константы и структура для операций


int main() {

    //struct OperationStructure* ptr = allocateShm();
    sem_t* main_sem = sem_open(MAIN_SEMAPHOR, 0);
    sem_t* add_sem = sem_open(ADD_SEMAPHOR, 0);
    struct OperationStructure* ptr = allocateShm();
    printf("%s", "addition program init");
    while(1){
        sem_wait(add_sem);
        ptr->originalValue +=ptr->modificationValue;
        sem_post(main_sem);
    }


    // sem_t* main_sem;
    // 
	// printf("%s", "waiting for add_sem release");

    //     printf("%s", "addition process initialisation");
    // char* name = "lab1_shm\n\r";
    // struct OperationStructure* ptr = allocateShm();
    // sem_post(&main_sem); 
	// while(1) {
    //     sem_wait(&add_sem);
	// 	ptr->originalValue +=ptr->modificationValue;
    //     printf("%s", "releasing main_sem");
    //     sem_post(&main_sem); 
	// }
	return 0;
}