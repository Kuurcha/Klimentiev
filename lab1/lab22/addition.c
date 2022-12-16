
// Семафоры
#include <sys/sem.h>
#include <sys/ipc.h>


//Константы и структура для операций
#include <sharedLib.h>
void* lab_add(struct OperationStructure** ptr){
    while (1){
        sem_wait(&add_sem);
        (*ptr)->originalValue +=(*ptr)->modificationValue;
 
    }
}
sem_t* main_sem;
sem_t* add_sem;
int main() {
    char* name = "lab1_shm\n\r";
    int shmDesc = shm_open(name, O_RDWR | O_CREAT,  READWRITE_PERMISSION);
    
    main_sem = createSem(main_sem, "Error while creating main sem", MAIN_SEMAPHOR);
    add_sem = createSem(add_sem, "Error while creating main sem", ADD_SEMAPHOR);
	
	
	while(1) {
		add_process();
	}
	return 0;
}