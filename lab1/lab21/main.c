#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>


#define PORT 8080

pthread_mutex_t sum_mut,div_mut,sub_mut,pow_mut, mutex;
pthread_t server_thread, thread_sum, thread_div, thread_sub, thread_pow;

int flag=0;
int send_double(double num, int fd);

int receive_double(double *num, int fd);

void *sum_runnable() { 

    while(1) {  
        if(flag==0) {
            pthread_mutex_lock(&sum_mut);
            printf("\nsum_mutex lock\tthread %ld", pthread_self());
            struct sockaddr_in address;  
            int client_socket = socket(AF_INET, SOCK_STREAM, 0); 
            if (client_socket < 0) {
                perror("client_socket:socket");
                exit(1);
            }
            address.sin_family = AF_INET;
            address.sin_port = htons(PORT);
            address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
                
            if (connect(client_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
                perror("client_socket:connect");
                exit(2);
            }
           
	        printf("\nStart sum");
            double result = 0;
            double value;
            printf("\nsum[");
            for (int j = 0; j < 3; j++) {
                receive_double(&value, client_socket);
                printf("%.2f,", value);
                result += value;
            }
            printf("]\n");
            printf("Operation: sum[]=%.2f\tthread %ld\n", result, pthread_self());
            printf("End sum, send result\n");       
            
            send_double(result, client_socket); 
            flag=1;
            printf("\nsum_mutex unlock\tthread %ld", pthread_self());
            
            close(client_socket);

            pthread_mutex_unlock(&sum_mut);
        }
    }
    pthread_exit(NULL);
}

void *div_runnable() {

     while(1) {
        if(flag==1) {
            pthread_mutex_lock(&div_mut);
             printf("\ndiv_mutex lock\tthread %ld", pthread_self());  
            struct sockaddr_in address;
            address.sin_family = AF_INET;
            address.sin_port = htons(PORT);
            address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            
            int client_socket = socket(AF_INET, SOCK_STREAM, 0);
            if (client_socket < 0) {
                perror("client_socket:socket");
                exit(1);
            }
            if (connect(client_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
                perror("client_socket:connect");
                exit(2);
            }
        
	        printf("\nStart div");
            double value = 0;
            double divider = 0;
            receive_double(&value, client_socket);
            receive_double(&divider, client_socket);

            double result = value / divider;
            
            printf("\nOperation: %.2f/%.2f=%.2f\tthread %ld\n", value, divider, result, pthread_self());
            printf("End div, send result\n");
            
            
            send_double(result, client_socket);
            flag=2;
            printf("\ndiv_mutex unlock\tthread %ld", pthread_self());
             
            close(client_socket);

            pthread_mutex_unlock(&div_mut);
        }
    }   
    pthread_exit(NULL);
}

void *sub_runnable() { 

    while(1) {
        if(flag==2) {
            pthread_mutex_lock(&sub_mut);
            printf("\nsub_mutex lock\tthread %ld", pthread_self());
            struct sockaddr_in address;
            int connectId;
            int client_socket = socket(AF_INET, SOCK_STREAM, 0);
            if (client_socket < 0) {
                perror("client_socket:socket");
                exit(1);
            }
            address.sin_family = AF_INET;
            address.sin_port = htons(PORT);
            address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            
            connectId = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
            if (connectId < 0) {
                perror("client_socket:connect");
                exit(2);
            }
	    
	        printf("\nStart sub");
            double value = 0;
            double average = 0;
            receive_double(&value, client_socket);
            receive_double(&average, client_socket);

            double result = value - average;
            printf("\nOperation: %.2f-%.2f=%.2f\tthread %ld\n", value, average, result, pthread_self());
            printf("End sub, send result\n");
             
           
            send_double(result, client_socket);
            flag++;
            printf("\nsub_mutex unlock\tthread %ld", pthread_self());

            close(client_socket); 

            pthread_mutex_unlock(&sub_mut);   
        }
    } 
    pthread_exit(NULL);   
}

void *pow_runnable() 
{   

    while(1) { 
        if(flag==3) {
            pthread_mutex_lock(&pow_mut);
            printf("\npow_mutex lock\tthread %ld", pthread_self());
            struct sockaddr_in address;
            int connectId;

            int client_socket = socket(AF_INET, SOCK_STREAM, 0);
            if (client_socket < 0) {
                perror("client_socket:socket");
                exit(1);
            }

            address.sin_family = AF_INET;
            address.sin_port = htons(PORT);
            address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            
            connectId = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
            if (connectId < 0) {
                perror("client_socket:connect");
                exit(2);
            }
            
            printf("\nStart pow");
            double value;
            receive_double(&value, client_socket);
            double result = value * value;
            printf("\nOperation: %.2f^2=%.2f\tthread %ld\n", value, result, pthread_self());
            printf("End pow, send result\n");
           
            
            send_double(result, client_socket);
            flag=2;
            printf("\npow_mutex unlock\tthread %ld", pthread_self());
            pthread_mutex_unlock(&pow_mut);
            close(client_socket);
        }  
    }   
    pthread_exit(NULL);  
}

int main(int argc, char *argv[]) {
    printf("Enter three numbers\n");
    double a, b, c;
    double arr[3];
    
    pthread_mutex_init(&sum_mut, NULL);
    pthread_mutex_init(&div_mut, NULL);
    pthread_mutex_init(&sub_mut, NULL);
    pthread_mutex_init(&pow_mut, NULL);
    
    printf("1st number: ");
    scanf("%lf", &a);
    printf("2nd number: ");
    scanf("%lf", &b);
    printf("3rd number: ");
    scanf("%lf", &c);
    arr[0]=a;
    arr[1]=b;
    arr[2]=c;
    
    double sum = 0;
    double average = 0;
    double *results_buffer = malloc(sizeof(double) * 3);
    double result;
     
    int server_socket;
    struct sockaddr_in address;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("server_socket:socket");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("server_socket:bind");
        exit(2);
    }
    
    listen(server_socket, 10);
    printf("\nClient started\t\tthread %ld\n", pthread_self());

    pthread_mutex_lock(&sum_mut);
    pthread_mutex_lock(&div_mut);
    pthread_mutex_lock(&sub_mut);
    pthread_mutex_lock(&pow_mut);

    pthread_create(&thread_sum, NULL, sum_runnable, NULL);
    pthread_create(&thread_div, NULL, div_runnable, NULL);
    pthread_create(&thread_sub, NULL, sub_runnable, NULL);
    pthread_create(&thread_pow, NULL, pow_runnable, NULL);

    pthread_mutex_unlock(&sum_mut);
    printf("\nsum_mutex unlock\tthread %ld", pthread_self());
    
    int connectId = accept(server_socket, (struct sockaddr *) NULL, NULL);
    if (connectId < 0) {
        perror("accept");
        exit(3);
    }
    for (int i = 0; i < 3; i++) {
        send_double(arr[i], connectId);
    }


    receive_double(&sum, connectId);
    printf("\nSum: received: %.2f\tthread %ld\n", sum, pthread_self());
    
    pthread_mutex_lock(&sum_mut);
    printf("\nsum_mutex lock\tthread %ld", pthread_self());
    close(connectId);
    
    pthread_mutex_unlock(&div_mut);
    printf("\ndiv_mutex unlock\tthread %ld", pthread_self());

    connectId = accept(server_socket, (struct sockaddr *) NULL, NULL);
    if (connectId < 0) {
        perror("accept");
        exit(3);
    }
    send_double(sum, connectId);
    send_double(3, connectId);

    receive_double(&average, connectId);

    printf("\nDiv: received: %.2f\tthread %ld\n", average, pthread_self());
    
    pthread_mutex_lock(&div_mut);
    printf("\ndiv_mutex lock\tthread %ld", pthread_self());
    close(connectId);
     
    for (int i = 0; i < 3; i ++) {   
        pthread_mutex_unlock(&sub_mut);
        printf("\nsub_mutex unlock\tthread %ld", pthread_self());

        connectId = accept(server_socket, (struct sockaddr *) NULL, NULL);
        if (connectId < 0) {
            perror("accept");
            exit(3);
        }
        send_double(arr[i], connectId);
        send_double(average, connectId);

        receive_double(&results_buffer[i], connectId);
        printf("\nSub: received: %.2f\tthread %ld\n", results_buffer[i], pthread_self());
        
    
        flag=3;
        pthread_mutex_lock(&sub_mut);
        printf("\nsub_mutex lock\tthread %ld", pthread_self());
        close(connectId);
        
        pthread_mutex_unlock(&pow_mut);
        printf("\npow_mutex unlock\tthread %ld", pthread_self());

        connectId = accept(server_socket, (struct sockaddr *) NULL, NULL);
        if (connectId < 0) {
            perror("accept");
            exit(3);
        }
        send_double(results_buffer[i], connectId);

        receive_double(&results_buffer[i], connectId);

        printf("\nPow: received: %.2f\tthread %ld\n", results_buffer[i], pthread_self());
        
        if(i==2) {
           flag=0;
        }
        else{flag=2;}
        
        pthread_mutex_lock(&pow_mut);
        printf("\npow_mutex lock\tthread %ld", pthread_self());
        close(connectId);
        
    }
    pthread_mutex_unlock(&sum_mut);
    if (connectId < 0) {
        perror("accept");
        exit(3);
    }
    for (int i = 0; i < 3; i++) {
        send_double(results_buffer[i], connectId);
    }

    
    connectId = accept(server_socket, (struct sockaddr *) NULL, NULL);

    receive_double(&sum, connectId);
    printf("\nSum: received: %.2f\tthread %ld\n", sum, pthread_self());
    pthread_mutex_lock(&sum_mut);
    close(connectId);
    

    if (connectId < 0) {
        perror("accept");
        exit(3);
    }
    send_double(sum, connectId);
    send_double(2, connectId);

    pthread_mutex_unlock(&div_mut);
    connectId = accept(server_socket, (struct sockaddr *) NULL, NULL);

    receive_double(&result, connectId);
    printf("\nDiv: received: %.2f\tthread %ld\n", result, pthread_self());
    pthread_mutex_lock(&div_mut);
    flag=-1;
    close(connectId);
    
    printf("\n-----\nResult: %.2f\tthread %ld\n", result, pthread_self());
    
    close(server_socket);

    pthread_mutex_destroy(&sum_mut); 
    pthread_mutex_destroy(&div_mut);  
    pthread_mutex_destroy(&sub_mut);  
    pthread_mutex_destroy(&pow_mut);   
    return 0;
}

int send_double(double num, int fd) {
    char *data = (char *) &num;
    long left = sizeof(num);
    long rc;
    do {
        rc = send(fd, data, left, 0);
        if (rc < 0) {
            if (errno != EINTR) {
                return -1;
            }
        } else {
            data += rc;
            left -= rc;
        }
    } while (left > 0);
    return 0;
}

int receive_double(double *num, int fd) {
    double ret;
    char *data = (char *) &ret;
    long left = sizeof(ret);
    long rc;
    do {
        rc = recv(fd, data, left, 0);
        if (rc <= 0) {
            if (errno != EINTR) {
                return -1;
            }
        } else {
            data += rc;
            left -= rc;
        }
    } while (left > 0);
    *num = ret;
    return 0;
}

