/*
Вариант 20 ADIM:
	A = Process
	D = Semathores
	I = Pipe FIFO
	M = sqrt(a^2 + b^2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>			//независимые процесс
#include <semaphore.h>		//функции для семафоров

#include <signal.h>			//чтобы убить дочерние процессы (т.к. они в бесконечных циклах)

#define SEM_CALC "/semaphore_calc"
#define SEM_ADD "/semaphore_add"
#define SEM_POW2 "/semaphore_pow2"
#define SEM_SQRT "/semaphore_sqrt"
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define INITIAL_VALUE 0
sem_t *s_calc_data, *s_add, *s_pow2, *s_sqrt;

#define ADD_PROGRAM "./add-ser"
#define POW2_PROGRAM "./pow2-ser"
#define SQRT_PROGRAM "./sqrt-ser"

#define ADD_PIPE "addfifo"		// FIFO file path
#define POW2_PIPE "pow2fifo"	// FIFO file path
#define SQRT_PIPE "sqrtfifo"	// FIFO file path

double add(double value1, double value2) {
	printf("+\n");
	int add_file_descriptor = open(ADD_PIPE, O_WRONLY);	// Write the value on FIFO and close it
	if(add_file_descriptor == -1) {
		perror("ERROR [CLIENT] opening file on write");
   	  	exit(1);
	}
	//printf("Client opened writing\n");
	if( write(add_file_descriptor, &value1, sizeof(double)) == -1)	//отправить value1 
	{
		perror("ERROR [CLIENT] writing 1st");
   	  	exit(1);
	}
	if(write(add_file_descriptor, &value2, sizeof(double)) == -1)	//отправить value2
	{
		perror("ERROR [CLIENT] writing 2nd");
   	  	exit(1);
	}
	sem_post(s_add);
	close(add_file_descriptor);
	//printf("[CLIENT] closed writing\n");
	sem_wait(s_calc_data);
	double res;
	add_file_descriptor = open(ADD_PIPE, O_RDONLY); // Open FIFO for Read only
	if(add_file_descriptor == -1) {
		perror("ERROR [CLIENT] opening file on read");
   	  	exit(1);
	}
	//printf("[CLIENT] opened reading\n");
	if(read(add_file_descriptor, &res, sizeof(double)) == -1) {
		perror("ERROR [CLIENT] reading file");
   	  	exit(1);
	}
	printf("add server reply: %lf\n", res);
	close(add_file_descriptor);
	return res;
}
double pow2(double value)  {
	printf("^2\n");
	int pow2_file_descriptor = open(POW2_PIPE, O_WRONLY);
	if(pow2_file_descriptor == -1) {
		perror("ERROR opening file on write");
   	  	exit(1);
	}
	if(write(pow2_file_descriptor, &value, sizeof(double)) == -1) {
		perror("ERROR writing");
   	  	exit(1);
	}
	sem_post(s_pow2);
	close(pow2_file_descriptor);
	sem_wait(s_calc_data);
	double res;
	pow2_file_descriptor = open(POW2_PIPE, O_RDONLY); // Open FIFO for Read only
	if(pow2_file_descriptor == -1) {
		perror("ERROR opening file on read");
   	  	exit(1);
	}
	if(read(pow2_file_descriptor, &res, sizeof(double)) == -1) {
		perror("ERROR reading file");
   	  	exit(1);
	}
	printf("pow2 server reply: %lf\n", res);
	close(pow2_file_descriptor);
	return res;
}

double square_root(double value)  {
	printf("K\n");
	int sqrt_file_descriptor = open(SQRT_PIPE, O_WRONLY);
	if(sqrt_file_descriptor == -1) {
		perror("ERROR opening file on write");
   	  	exit(1);
	}
	if(write(sqrt_file_descriptor, &value, sizeof(double)) == -1) {
		perror("ERROR writing");
   	  	exit(1);
	}
	sem_post(s_sqrt);
	close(sqrt_file_descriptor);
	sem_wait(s_calc_data);
	double res;
	sqrt_file_descriptor = open(SQRT_PIPE, O_RDONLY); // Open FIFO for Read only
	if(sqrt_file_descriptor == -1) {
		perror("ERROR opening file on read");
   	  	exit(1);
	}
	if(read(sqrt_file_descriptor, &res, sizeof(double)) == -1) {
		perror("ERROR reading file");
   	  	exit(1);
	}
	printf("sqrt server reply: %lf\n", res);
	close(sqrt_file_descriptor);
	return res;
}


double hypotenuse(double a, double b) {
	double result = pow2(a);	//a^2
	double temp = pow2(b);			//b^2
	result = add(result, temp);	//a^2 + b^2
	result = square_root(result);		//sqrt(a^2 + b^2)
	return result;
}

void init_semaphores() {
	//инициализация семафоров
	sem_unlink(SEM_CALC);
	sem_unlink(SEM_ADD);
	sem_unlink(SEM_POW2);
	sem_unlink(SEM_SQRT);
	s_calc_data = sem_open(SEM_CALC, O_CREAT | O_EXCL, SEM_PERMS, INITIAL_VALUE);
	if (s_calc_data == SEM_FAILED) {
        perror("s_cald_data sem_open(3) error");
        exit(1);
    }
    s_add = sem_open(SEM_ADD, O_CREAT | O_EXCL, SEM_PERMS, INITIAL_VALUE);
	if (s_add == SEM_FAILED) {
        perror("s_add sem_open(3) error");
        exit(1);
    }
	s_pow2 = sem_open(SEM_POW2, O_CREAT | O_EXCL, SEM_PERMS, INITIAL_VALUE);
	if (s_pow2 == SEM_FAILED) {
        perror("s_pow2 sem_open(3) error");
        exit(1);
    }
	s_sqrt = sem_open(SEM_SQRT, O_CREAT | O_EXCL, SEM_PERMS, INITIAL_VALUE);
	if (s_sqrt == SEM_FAILED) {
        perror("s_sqrt sem_open(3) error");
        exit(1);
    }
	printf("семафоры инициализированы!\n");	
}

void delete_semaphores() {
	sem_unlink(SEM_CALC);
	sem_unlink(SEM_ADD);
	sem_unlink(SEM_POW2);
	sem_unlink(SEM_SQRT);
	printf("семафоры удалены!\n");
}

void init_fifos() {
	if( mkfifo(ADD_PIPE, 0777) == -1) {
		perror("Coudn't create add fifo file");
        exit(1);
	}
	if( mkfifo(POW2_PIPE, 0777) == -1) {
		perror("Coudn't create pow2 fifo file");
        exit(1);
	}
	if( mkfifo(SQRT_PIPE, 0777) == -1) {
		perror("Coudn't create sqrt fifo file");
        exit(1);
	}
	printf("Fifo created\n");
}

void delete_fifos() {
	unlink(ADD_PIPE);
	unlink(POW2_PIPE);
	unlink(SQRT_PIPE);
	printf("файлы fifo удалены!\n");
}

pid_t p1, p2, p3;
int main(void) {

	init_semaphores();
	init_fifos();
    
	p1 = fork();
    if (p1) {
		
		p2 = fork();
		if(p2) {
			
			p3 = fork();
			if(p3) {
				
				//основной процесс
				printf("Введите два катета гипотенузы:\n");
				printf("1-ый катет = ");
				double a, b;
				scanf("%lf", &a);
				printf("2-ой катет = ");
				scanf("%lf", &b);
				double res = hypotenuse(a, b);
				printf("Result = %lf\n", res);
			}
			else {
				execl(SQRT_PROGRAM, SQRT_PROGRAM, NULL);
			}
		}
		else {
			execl(ADD_PROGRAM, ADD_PROGRAM, NULL);
		}
	}
	else {
		execl(POW2_PROGRAM, POW2_PROGRAM, NULL);
		
	}
	
	delete_semaphores();
	delete_fifos();
	//закрываем детей
	kill(p1, SIGTERM);
	kill(p2, SIGTERM);
	kill(p3, SIGTERM);

	return 0;
}
