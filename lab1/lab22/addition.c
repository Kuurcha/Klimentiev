
// Семафоры
#include <sys/sem.h>
#include <sys/ipc.h>
void* lab_add(struct OperationStructure** ptr){
    while (1){
        sem_wait(&add_sem);
        (*ptr)->originalValue +=(*ptr)->modificationValue;
        sem_post(&main_sem);   
    }
}
main(){
    char* name = "lab1_shm\n\r";
    int shmDesc = shm_open(name, O_RDWR | O_CREAT,  READWRITE_PERMISSION);
}