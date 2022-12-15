#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>			//sqrt()

#include <unistd.h>			//независимые процесс
#include <semaphore.h>		//функции для семафоров

#define SEM_CALC "/semaphore_calc"
#define SEM_SQRT "/semaphore_sqrt"

sem_t *s_calc_data, *s_sqrt;

#define SQRT_PIPE "sqrtfifo"	// FIFO file path

void sqrt_process() {
	int sqrt_file_descriptor = open(SQRT_PIPE, O_RDONLY); 	// Open FIFO for Read only
	if(sqrt_file_descriptor == -1) {
		perror("ERROR opening file on read");
   	  	exit(1);
	}
	sem_wait(s_sqrt);
	double value;
	if(read(sqrt_file_descriptor, &value, sizeof(double)) == -1) {
		perror("ERROR reading");
   	  	exit(1);
	}
	close(sqrt_file_descriptor);
	
	sem_post(s_calc_data);
	double res = sqrt(value);
	sqrt_file_descriptor = open(SQRT_PIPE, O_WRONLY);
	if(sqrt_file_descriptor  == -1) {
		perror("ERROR opening file on write");
   	  	exit(1);
	}
	if(write(sqrt_file_descriptor, &res, sizeof(double)) == -1) {
		perror("ERROR writing result");
   	  	exit(1);
	}
	close(sqrt_file_descriptor);
}

int main() {
	s_calc_data = sem_open(SEM_CALC, O_RDWR);
	if (s_calc_data == SEM_FAILED) {
        perror("s_cald_data sem_open(3) error");
        exit(1);
    }
    s_sqrt = sem_open(SEM_SQRT, O_RDWR);
	if (s_calc_data == SEM_FAILED) {
        perror("s_sqrt sem_open(3) error");
        exit(1);
    }
	
	
	while(1) {
		sqrt_process();
	}
	return 0;
}