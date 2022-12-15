#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>			//независимые процесс
#include <semaphore.h>		//функции для семафоров

#define SEM_CALC "/semaphore_calc"
#define SEM_ADD "/semaphore_add"
sem_t *s_calc_data, *s_add;

#define ADD_PIPE "addfifo"		// FIFO file path



void add_process () {
	int add_file_descriptor = open(ADD_PIPE, O_RDONLY); 	// Open FIFO for Read only
	if(add_file_descriptor == -1) {
		perror("ERROR [SERVER] opening file on read");
   	  	exit(1);
	}
	sem_wait(s_add);
	double add1, add2;
	if(read(add_file_descriptor, &add1, sizeof(double)) == -1) {
		perror("ERROR [SERVER] reading 1st");
   	  	exit(1);
	}
	if (read(add_file_descriptor, &add2, sizeof(double)) == -1) {
		perror("ERROR [SERVER] reading 2nd");
   	  	exit(1);
	}
	close(add_file_descriptor);
	
	sem_post(s_calc_data);
	double res = add1+add2;
	add_file_descriptor = open(ADD_PIPE, O_WRONLY);
	if(add_file_descriptor == -1) {
		perror("ERROR [SERVER] opening file on write");
   	  	exit(1);
	}
	if(write(add_file_descriptor, &res, sizeof(double)) == -1) {
		perror("ERROR [SERVER] writing result");
   	  	exit(1);
	}
	close(add_file_descriptor);
}

int main() {
	s_calc_data = sem_open(SEM_CALC, O_RDWR);
	if (s_calc_data == SEM_FAILED) {
        perror("s_cald_data sem_open(3) error");
        exit(1);
    }
    s_add = sem_open(SEM_ADD, O_RDWR);
	if (s_calc_data == SEM_FAILED) {
        perror("s_add sem_open(3) error");
        exit(1);
    }
	
	
	while(1) {
		add_process();
	}
	return 0;
}

