
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


#define MAIN_SEMAPHOR "/main_sem"
#define ADD_SEMAPHOR "/addition_sem"
#define DIVISION_SEMAPHOR "/division_sem"
#define MULTIPLICATION_SEMAPHOR "/multiplication_sem"
#define SUBSTRACTION_SEMAPHOR "/substraction_sem"
#define SQUAREROOT_SEMAPHOR "/squareRoot_sem"

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