
#ifndef SHAREDLIB_H
#define SHAREDLIB_H

#define SHMSIZE 128
#define READWRITE_PERMISSION 0666
#define SEMAPHOR_PERMISSIONS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define INITIAL_VALUE 0

#define ADD_PROGRAM "./addition"
#define DIVISION_PROGRAM "./division"
#define MULTIPLICATION_PROGRAM "./multiplication"
#define SQAREROOT_PROGRAM "./squareRoot"
#define SUBSTRACTION_PROGRAM "./substraction"
#define MAIN_PROGRAM "./main"


#define MAIN_SEMAPHOR "/mainsem"
#define ADD_SEMAPHOR "/additionsem"
#define DIVISION_SEMAPHOR "/divisionsem"
#define MULTIPLICATION_SEMAPHOR "/multiplicationsem"
#define SUBSTRACTION_SEMAPHOR "/substractionsem"
#define SQUAREROOT_SEMAPHOR "/squareRootsem"

#define SYNC_MAIN_SEMAPHOR "/mainsemSYNC_"
#define SYNC_ADD_SEMAPHOR "/additionsemSYNC_"
#define SYNC_DIVISION_SEMAPHOR "/divisionsemSYNC_"
#define SYNC_MULTIPLICATION_SEMAPHOR "/multiplicationsemSYNC_"
#define SYNC_SUBSTRACTION_SEMAPHOR "/substractionsemSYNC_"
#define SYNC_SQUAREROOT_SEMAPHOR "/squareRootsemSYNC_"

#define SHM_NAME "lab1_shm"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
//Разедялемая память
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
// Семафоры
#include <sys/sem.h>
#include <sys/ipc.h>
#include <signal.h>
#include <semaphore.h>

struct OperationStructure{
    float originalValue;
    float modificationValue;
};

struct OperationStructure* allocateShm();

void checkForError(int errorVariable, char* errorMessage);

#endif