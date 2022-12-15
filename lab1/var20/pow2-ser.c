#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>			//независимые процесс
#include <semaphore.h>		//функции для семафоров

#define SEM_CALC "/semaphore_calc"
#define SEM_POW2 "/semaphore_pow2"
sem_t *s_calc_data, *s_pow2;

#define POW2_PIPE "pow2fifo"	// FIFO file path


void pow2_process() {
	int pow2_file_descriptor = open(POW2_PIPE, O_RDONLY); 	// Open FIFO for Read only
	if(pow2_file_descriptor == -1) {
		perror("ERROR opening file on read");
   	  	exit(1);
	}
	sem_wait(s_pow2);
	double value;
	if(read(pow2_file_descriptor, &value, sizeof(double)) == -1) {
		perror("ERROR reading");
   	  	exit(1);
	}
	close(pow2_file_descriptor);
	sem_post(s_calc_data);
	double res = value*value;
	pow2_file_descriptor = open(POW2_PIPE, O_WRONLY);
	if(pow2_file_descriptor  == -1) {
		perror("ERROR opening file on write");
   	  	exit(1);
	}
	if(write(pow2_file_descriptor, &res, sizeof(double)) == -1) {
		perror("ERROR writing result");
   	  	exit(1);
	}
	close(pow2_file_descriptor);
}

int main() {
	s_calc_data = sem_open(SEM_CALC, O_RDWR);
	if (s_calc_data == SEM_FAILED) {
        perror("s_cald_data sem_open(3) error");
        exit(1);
    }
    s_pow2 = sem_open(SEM_POW2, O_RDWR);
	if (s_calc_data == SEM_FAILED) {
        perror("s_pow2 sem_open(3) error");
        exit(1);
    }
	
	
	while(1) {
		pow2_process();
	}
	
	return 0;
}