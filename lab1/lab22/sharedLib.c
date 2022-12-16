#include "sharedLib.h"
void checkForError(int errorVariable, char* errorMessage){
        if (errorVariable == -1){
        perror(errorMessage);
        exit(1);
    }
}

struct OperationStructure* allocateShm(){
    struct OperationStructure* ptr;
    int shmDesc = shm_open(SHM_NAME, O_RDWR | O_CREAT,  READWRITE_PERMISSION);
    checkForError(shmDesc, "Shared memory open error");

    int truncateReturnCode = ftruncate (shmDesc, sizeof(struct OperationStructure));
    checkForError(truncateReturnCode, "Setting Shared Memory Size error");
    
    ptr = (struct OperationStructure*) mmap(NULL, SHMSIZE, PROT_WRITE, MAP_SHARED, shmDesc, 0);
    checkForError(ptr, "Mapping memory error");
    return ptr;
}