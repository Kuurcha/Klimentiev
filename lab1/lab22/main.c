//ADHL
// A - Независимые потоки
// D - Семафоры 
// H - Разделяемая память
// L - Квадратное уравнение

#include "sharedLib.h"

#include <pthread.h>
#include <stdbool.h>
//Константы и структура для операций и с общими библиотеками


sem_t *mult_sem;
sem_t *add_sem;
sem_t *main_sem;
sem_t *div_sem;
sem_t *sub_sem;
sem_t *sqrt_sem;

struct OperationStructure* ptr;
double a = 3;
double b = 6;
double c = 9;


void printValues(){
    printf("%.2f",  ptr->originalValue);
    printf("%s", "\n\r");
}
void lab_sub(double argument){
        printf("%s", "\n\r");
        printf("%s", "substracting: ");
        printf("%f", argument);
        printf("%s", "\n\r");
        ptr->modificationValue = argument;
        sem_post(sub_sem);
        sem_wait(main_sem);
        printf("%s", "Result: "); 
        printValues();
        printf("%s", "\n\r");
}
void lab_add(double argument){
        printf("%s", "\n\r");
        printf("%s", "addition: ");
        printf("%f", argument);
        printf("%s", "\n\r");
        ptr->modificationValue = argument;
        sem_post(add_sem);
        sem_wait(main_sem);
        printf("%s", "Result: "); 
        printValues();
        printf("%s", "\n\r");
}
void lab_mult(double argument){
        printf("%s", "\n\r");
        printf("%s", "multiplication: ");
        printf("%f", argument);
        printf("%s", "\n\r");
        ptr->modificationValue = argument;
        sem_post(mult_sem);
        sem_wait(main_sem);
        printf("%s", "Result: ");
        printValues();
        printf("%s", "\n\r");
}
void lab_div(double argument){
        printf("%s", "\n\r");
        printf("%s", "division: ");
        printf("%f", argument);
        ptr->modificationValue = argument;
        sem_post(div_sem);
        sem_wait(main_sem);
        printf("%s", "\n\r");
        printf("%s", "Result: ");
        printValues();
        printf("%s", "\n\r");
}
void lab_sqrt(){
        printf("%s", "\n\r");
        printf("%s", "sqaureRooting: ");
        printf("%s", "\n\r");
        sem_post(sqrt_sem);
        sem_wait(main_sem);
        printf("%s", "Result: "); 
        printValues();
        printf("%s", "\n\r");
}



int inputValues (double *a, double *b, double *c){
    printf("Input a: \n");
    scanf("%lf", a);
    printf("Input b: \n");
    scanf("%lf", b);
    printf("Input c: \n");
    scanf("%lf", c);

    printf(" Коеф1: %f", a);
    printf(" Коеф2: %f", b);
    printf(" Коеф3: %f", c);
}

sem_t* createSem(char* errorMessage, const char * semName, unsigned int initialValue){
    sem_t* temp = sem_open(semName, O_CREAT | O_EXCL, SEMAPHOR_PERMISSIONS, initialValue);
    if (temp == SEM_FAILED){
        perror(errorMessage);
        exit(1);
    }
    return temp;
}

double popValue(){
    double value = ptr->originalValue;
    ptr->originalValue = 0;
    ptr->modificationValue = 0;
    return value;
}
void delete_semaphores(){
    sem_unlink(MAIN_SEMAPHOR);
	sem_unlink(ADD_SEMAPHOR);
    sem_unlink(SUBSTRACTION_SEMAPHOR);
    sem_unlink(DIVISION_SEMAPHOR);
    sem_unlink(MULTIPLICATION_SEMAPHOR);
    sem_unlink(SQUAREROOT_SEMAPHOR);

}
void initSemaphors(){
    delete_semaphores();
    main_sem = createSem("main_sem sem_open error", MAIN_SEMAPHOR, INITIAL_VALUE);
    add_sem = createSem("add_sem sem_open error", ADD_SEMAPHOR, INITIAL_VALUE);
    sub_sem = createSem("sub_sem sem_open error", SUBSTRACTION_SEMAPHOR, INITIAL_VALUE);
    div_sem = createSem("div_sem sem_open error", DIVISION_SEMAPHOR, INITIAL_VALUE);
    mult_sem = createSem("mult_sem sem_open error", MULTIPLICATION_SEMAPHOR, INITIAL_VALUE);
    sqrt_sem = createSem("sqrt_sem sem_open error", SQUAREROOT_SEMAPHOR, INITIAL_VALUE);

	printf("семафоры инициализированы!\n");	

}


double Discriminant(){
    double d = 0;
    lab_add(1);
    lab_mult(b);
    lab_mult(b);
    double firstComponent = popValue();

    lab_add(4);
    lab_mult(a);
    lab_mult(c);

    double secondComponent = popValue();
    d = firstComponent - secondComponent;
    return d;
}

double calculateRoot(bool substract, double discrimenant){
    double x = 0;
    


    lab_add(discrimenant);
    lab_sqrt();
    
    double sqrtD = popValue();
    lab_sub(b);
    if (substract){
        lab_sub(sqrtD);  
    }
    else{
        
        lab_add(sqrtD);
    }

    double dividend = popValue();

    lab_add(a);
    lab_mult(2);
    double divisor = popValue();
    lab_add(dividend);
    lab_div(divisor);

    double result = popValue();
    return result;

}

void switchToOtherProgram(pid_t returnPid, char * path){
   
    printf("%s", "\n\r");
    if (returnPid == 0){
        printf("%s", "Process ");
        printf("%s", path);
        printf("%s", " Switched ");
        execv(path, (char *) NULL);
    }
    else if(returnPid < 0){
        printf("%s","Critical mistakes when creating PID");
    }
    else{
        printf("%s", "Main");
    }
    
    printf("%s", "\n\r");
}

pid_t forkDebug(char * path){
    printf("%s", "\n\r");
    int returnPid = fork();
    printf("%s", "Creating process: ");
    printf("%s", path);
    printf("%s", "\n\r");
    printf("%s", "Pid value:");
    printf("%f", returnPid);
    printf("%s", "\n\r");
    return returnPid;
}
int main() {
    pid_t p1 = -1, p2 = -1, p3 = -1, p4 = -1, p5 = -1;
    //x1 = -b +- sqrt(D)/2a
    //D = b^2 - 4ac
    
    inputValues(&a, &b, &c);
    ptr = allocateShm();    
    ptr->originalValue= 0;
    ptr->modificationValue = 0;
    initSemaphors();

    
    p1 = forkDebug(ADD_PROGRAM);
    switchToOtherProgram(p1, ADD_PROGRAM);
    sem_wait(main_sem);
    p2 = forkDebug(MULTIPLICATION_PROGRAM);
    switchToOtherProgram(p2, MULTIPLICATION_PROGRAM);
    sem_wait(main_sem);

    p3 = forkDebug(SUBSTRACTION_PROGRAM);
    switchToOtherProgram(p3, SUBSTRACTION_PROGRAM);
    sem_wait(main_sem);

    p4 = forkDebug(DIVISION_PROGRAM);
    switchToOtherProgram(p4, DIVISION_PROGRAM);
    sem_wait(main_sem);

    p5 = forkDebug(SQUAREROOT_PROGRAM);
    switchToOtherProgram(p5, SQUAREROOT_PROGRAM);
    sem_wait(main_sem);

    double discriminant = Discriminant();
    printf("%s", "Discremenant is: ");
    printf("%f", discriminant);
    printf("%s", "\n\r");
    if (discriminant < 0){
        printf("%s", "No solutions!");
    }
    else {
        double firstRoot = calculateRoot(true, discriminant);
        double secondRoot = calculateRoot(false, discriminant);
        if (discriminant == 0){
            printf("%s", "One solution: ");
            printf("%f", firstRoot < secondRoot? secondRoot: firstRoot);
        }
        else{
           printf("%s", "Two solutions: ");
           printf("%s", "\n\r");
           printf("%s", "x1: ");
           printf("%f", firstRoot);
           printf("%s", "\n\r");
           printf("%s", "x2: ");
           printf("%f", secondRoot);
        }
    }
   

    close(ptr);
    shm_unlink(SHM_NAME);
    kill(p1, SIGTERM);
    kill(p2, SIGTERM);
    kill(p3, SIGTERM);
    kill(p4, SIGTERM);
    kill(p5, SIGTERM);
    printf("%s", "\n\r");
    printf("%s", "main program ending");
    printf("%s", "\n\r");
    exit(0);
  
}