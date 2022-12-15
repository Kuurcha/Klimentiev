//ADHL
// A - Независимые потоки
// D - Семафоры 
// H - Разделяемая память
// L - Квадратное уравнение
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <sys/types.h>

// Семафоры
#include <sys/sem.h>
#include <sys/ipc.h>

//Разедялемая память
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#include <pthread.h>
#include <semaphore.h>

#define SHMSIZE 128
#define READWRITE_PERMISSION 0666

sem_t mult_sem, div_sem, add_sem, sub_sem, sqrt_sem;
sem_t sync_mult_sem, sync_div_sem, sync_add_sem, sync_sub_sem, sync_sqrt_sem;
pthread_t mult_thread, div_thread, add_thread, sub_thread, sqrt_thread;

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

void checkForError(int errorVariable, char* errorMessage){
        if (errorVariable == -1){
        perror(errorMessage);
        exit(1);
    }
}

void initSemaphors(){
    sem_init(&mult_sem,0,0);
	sem_init(&div_sem,0,0);
	sem_init(&add_sem,0,0);
	sem_init(&sub_sem,0,0);
	sem_init(&sqrt_sem,0,0);
	sem_init(&sync_mult_sem,0,0);
	sem_init(&sync_div_sem,0,0);
	sem_init(&sync_add_sem,0,0);
    sem_init(&sync_sub_sem, 0, 0);
    sem_init(&sync_sqrt_sem, 0, 0);
}

void initThreads(){
    // pthread_create(&disp_sum_thread, NULL, &disp_sum,NULL);
	// pthread_create(&disp_mult_thread, NULL, &disp_mult,NULL);
	// pthread_create(&disp_diff_thread, NULL,&disp_diff,NULL);
	// pthread_create(&disp_div_thread, NULL,&disp_div,NULL);
}

int main() {

    double a = 3;
    double b = 6;
    double c = 9;

    //initSemaphors();
    // inputValues(&a, &b, &c);

    char* name = "lab1_shm\n\r";
    int shmDesc = shm_open(name, O_RDWR | O_CREAT,  READWRITE_PERMISSION);
    checkForError(shmDesc, "Shared memory open error");

    int truncateReturnCode = ftruncate(shmDesc, SHMSIZE);
    checkForError(truncateReturnCode, "Setting Shared Memory Size error");
    
    void* ptr = mmap(NULL, SHMSIZE, PROT_WRITE, MAP_SHARED, shmDesc, 0);
    checkForError(ptr, "Mapping memory error");
    
    sprintf(ptr, "%s", name);
    

    char* test = &ptr;

    printf("%s", &ptr);
    
    char* name1 = "lab2_shm\n\r";
    
    sprintf(ptr, "%s", name1);

    char* test1 = &ptr;

    printf("%s", test1);


    close(ptr);
    shm_unlink(name);
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



    



}