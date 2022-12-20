//ADHL
// A - Независимые потоки
// D - Семафоры 
// H - Разделяемая память
// L - Квадратное уравнение

#include "sharedLib.h"

#include <pthread.h>
//Константы и структура для операций и с общими библиотеками


sem_t *mult_sem;
sem_t *add_sem;
sem_t *main_sem;
sem_t *div_sem;
sem_t *sub_sem;
sem_t *sqrt_sem;
pthread_t mult_thread, div_thread, add_thread, sub_thread, sqrt_thread;
double a = 3;
double b = 6;
double c = 9;


void* lab_sub(struct OperationStructure** ptr){
    while (1){
        sem_wait(&sub_sem);
        (*ptr)->originalValue -=(*ptr)->modificationValue;
        sem_post(&main_sem);
    }
}

void* lab_mult(struct OperationStructure** ptr){
    while (1){
        sem_wait(&mult_sem);
        (*ptr)->originalValue *=(*ptr)->modificationValue;
        sem_post(&main_sem);
    }
}

void* lab_div(struct OperationStructure** ptr){
    while (1){
        sem_wait(&div_sem);
        (*ptr)->originalValue /=(*ptr)->modificationValue;
        sem_post(&main_sem);
    }
}

void* lab_sqrt(struct OperationStructure** ptr){
    while (1){
        sem_wait(&sqrt_sem);
        (*ptr)->originalValue /=(*ptr)->modificationValue;
        sem_post(&main_sem);
    }
}

int inputValues (double *a, double *b, double *c){
    printf("Input a: \n");
    scanf("%lf", a);
    printf("Input b: \n");
    scanf("%lf", b);
    printf("Input c: \n");

    printf(" Коеф1: %f", a);
    printf(" Коеф2: %f", b);
    printf(" Коеф3: %f", c);
}

void createSem(sem_t* sem, char* errorMessage, const char * semName, unsigned int initialValue){
    sem = sem_open(semName, O_CREAT | O_EXCL, SEMAPHOR_PERMISSIONS, initialValue);
    if (sem == SEM_FAILED){
        perror(errorMessage);
        exit(1);
    }
}


void delete_semaphores(){
    sem_close(main_sem);
    sem_close(add_sem);
    sem_unlink(MAIN_SEMAPHOR);
    sem_unlink(ADD_SEMAPHOR);

}
void initSemaphors(){
    sem_close(main_sem);
    sem_close(add_sem);
    sem_unlink(MAIN_SEMAPHOR);
    sem_unlink(ADD_SEMAPHOR);
    // createSem(main_sem, "Error while creating main sem", MAIN_SEMAPHOR, 0);
    // createSem(add_sem, "Error while creating add sem", ADD_SEMAPHOR, 1);

}


int main() {
    pid_t p1, p2, p3, p4, p5;

    struct OperationStructure* ptr;



//    initThreads(ptrToPtr);
    // inputValues(&a, &b, &c);

    ptr = allocateShm();
    
    ptr->originalValue= 0;
    ptr->modificationValue= 5;
    printf("%.2f %.2f",  ptr->originalValue, ptr->modificationValue);
    printf("%s", "\n\r");
    
    initSemaphors();


    main_sem = sem_open(MAIN_SEMAPHOR, O_RDWR |O_CREAT | O_EXCL, SEMAPHOR_PERMISSIONS, 1);
    if (main_sem == SEM_FAILED){
        perror( "Error while creating main sem");
        exit(1);
    }

    add_sem = sem_open(ADD_SEMAPHOR, O_RDWR | O_CREAT | O_EXCL, SEMAPHOR_PERMISSIONS, 0);
    if (add_sem == ADD_SEMAPHOR){
        perror( "Error while creating add sem");
        exit(1);
    }
    // p1 = fork();
    // if (p1 == 0){
    //     execl(ADD_PROGRAM, ADD_PROGRAM, (char *) NULL);
    // }

    printf("%f", p1);
    printf("%s", "\n\r");
    printf("%s", "posting add_sem..");
     printf("%s", "\n\r");
    sem_post(&add_sem);
    printf("%s", "waiting for main_sem to release...");
    // sem_wait(&main_sem);
    // printf("%.2f %.2f",  ptr->originalValue, ptr->modificationValue);
    // printf("%s", "\n\r");
    // printf("%s", "\n\r");
    // printf("%.2f %.2f", (*ptrToPtr)->originalValue, (*ptrToPtr)->modificationValue);
    // (*ptrToPtr)->modificationValue = 10;
    // sem_post(&sub_sem);
    // sem_wait(&main_sem);
    // printf("%s", "\n\r");
    // printf("%.2f %.2f", (*ptrToPtr)->originalValue, (*ptrToPtr)->modificationValue);
    // printf("%s", "\n\r");

    // printf("%s", "\n\r");


    // sprintf(ptr,"%9.6f", os.modificationValdue);

    // printf("%s", "\n\r");
    // printf("%p\n", (void *) ptr);
    // printf("%f", ptr);
    // printf("%s", "\n\r");
    // ptr -= sizeof(os.modificationValue);
    // printf("%p\n", (void *) ptr);
    // printf("%s", test);
    
    // char* name1 = "lab2_shm\n\r";
    
    // sprintf(ptr, "%s", name1);

    // char* test1 = (char*)ptr;

    // printf("%s", test1);


    close(ptr);
    shm_unlink(SHM_NAME);
    kill(p1, SIGTERM);
    // int r, f, i;
    // char *m;
    // f = open("/dev/mem", O_RDONLY, 0);
    // m = (char *) mmap( 0, 0xFFFFF, PROT_READ, MAP_SHARED, f, 0);
    // for (i=0xFFFF5;i<0xFFFFD;i++) write(1, &m[i], 1);
    // munmap( m, 0xFFFFF);
    // close(f);

    
    //ключ для ядра объекта операционной системы
    // key_t kernelKey = ftok(".", 0);
    // if (kernelKey == -1){
    //     perror("Kernel allocation error");
    //     exit(1);
    // }

    // Создаем общую область памяти
    // int shmid = shmget(kernelKey, SHSIZE, READWRITE_PERMISSION | IPC_CREAT );
    // if (shmid == -1){
    //     perror("memory creation error");
    //     exit(1);
    // }
    // char *shmPointer;
    // shmPointer = shmat(shmid, NULL, 0);
    // memcpy(shmPointer, "Hello", 5);

    // printf("Child wrote: %s\n", shmPointer);

    //создаем набор семафора
    // int semId = semget(kernelKey, 1, READWRITE_PERMISSION | IPC_CREAT | IPC_EXCL);

    // if (semId != -1){
       
    //     exit(1);
    // }
    // else{
    //     perror("semget creation error");
    //     exit(1);
    // }



    


    printf("%s", "main program ending");
}