#include <stdio.h>
#include <string.h>
//процессы
#include <stdlib.h>
#include <unistd.h>
//очереди сообщений
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//семафоры
#include <sys/sem.h>
#include <stdio.h>

//Процесс для умножения
#define TYPE 12345
#define RED          "\033[0;32;31m"
#define GREEN        "\033[0;32;32m"
#define BLUE         "\033[0;32;34m"
#define NONE         "\033[m"
#define YELLOW       "\033[1;33m"

struct msgbuf { long type; double msg[3]; };

int main() {

    fprintf(stdout,GREEN "\nMinus:" NONE " Start minus proc"); fflush(stdout);

    while(1){

        //создание семафора
        struct sembuf b1;
        key_t k1;
        int s1;
        k1 = ftok(".", 2); // ключ для ядра
        s1 = semget(k1, 1, 0644 | IPC_EXCL); // создание массива семафоров

        b1.sem_num = 0; // номер семафора
        b1.sem_op = -2; // код операции -n пока значение семафора S < n, процесс блокируется. Далее S = S - n;
        b1.sem_flg = 0;


        //ожидание установления семафора - сигнал о том что есть данные
        fprintf(stdout, GREEN"\nMinus:" NONE " Waiting data..."); fflush(stdout);
        if (semop(s1, &b1, 1)<0){
            printf("Plus Can\'t wait for condition\n");
            exit(-1);
        } // блокируем текущий процесс пока семафор не станет равным 2
        fprintf(stdout, GREEN"\nMinus:" NONE " Start calc"); fflush(stdout);


        //чтение данных из очереди сообщений
        double t, q, n;
        struct msgbuf buf;
        struct msqid_ds d;
        t = ftok(".",0x12);

        q = msgget( t, 0666 );
        n = msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
                    TYPE, MSG_NOERROR | IPC_NOWAIT );

        double coef1 = buf.msg[0]; // переменная 1
        double coef2 = buf.msg[1]; // переменная 2
        double result = coef1-coef2;

        fprintf(stdout,GREEN "\nMinus:" NONE " Коеф1: %f", coef1); fflush(stdout);
        fprintf(stdout,GREEN "\nMinus:" NONE " Коеф2: %f", coef2); fflush(stdout);


        //отправка сообщения с результатом умножения
        struct msgbuf buf2;
        int k2 = ftok(".",0x12);
        q = msgget( k2, 0666 | IPC_CREAT );
        buf2.type = TYPE;
        buf2.msg[0] = result;
        msgsnd( q, &buf2, sizeof(struct msgbuf)-sizeof(long), 0);


        // устанавливает семафор равным 3 - команда для main что данные отправлены и он может с ними работать
        int u = 3;
        if (semctl(s1, 0, SETVAL, u )){
            printf(GREEN "Minus: " NONE " Can\'t set val\n");
            exit(-1);
        }

        fprintf(stdout, GREEN "\nMinus:" NONE " Finish calc"); fflush(stdout);

    }

    return 0;

}
