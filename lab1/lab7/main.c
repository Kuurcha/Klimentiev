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

//Вариант 7 - ADKL - Процессы семафоры очереди сообщений квадратное уравнение

#define TYPE 12345
#define RED          "\033[0;32;31m"
#define GREEN        "\033[0;32;32m"
#define YELLOW         "\033[0;32;34m"
#define NONE         "\033[m"

struct msgbuf { long type; double msg[3]; };


int main() {

    double coefA = 3;
    double coefB = -14;
    double coefC = -5;

    printf("Введите коэффициенты a, b, c: \n");
    scanf("%lf %lf %lf", &coefA, &coefB, &coefC);

    printf(RED "\nMain:" NONE " Коеф1: %f", coefA);
    printf(RED "\nMain:" NONE " Коеф2: %f", coefB);
    printf(RED "\nMain:" NONE " Коеф3: %f", coefC);

    //создание семафора
    int s;
    struct sembuf b;
    int u;
    key_t k;
    pthread_t t;
    k = ftok(".", 0); // ключ для ядра
    s = semget(k, 1, 0644 | IPC_CREAT | IPC_EXCL); //создает массив семафоров
    u = 1;
    semctl(s, 0, SETVAL, u);

    //создание процесса
    int pid = fork();
    if (pid == 0){
        char programPath[30] = "./";
        strcat(programPath, "multi");
        execl(programPath, programPath, (char *) NULL);
    }


    /*------------------------------------------------------------------------------------------------AC-------------------------------------------------------------------------------------*/
    //отправка сообщения
    struct msgbuf buf;
    int q;
    int k2 = ftok(".",0x12);
    q = msgget( k2, 0666 | IPC_CREAT );
    buf.type = TYPE;
    buf.msg[0] = coefA;
    buf.msg[1] = coefC;
    msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);

    // запуск семафора для потока умножения установка значения 2
    fprintf(stdout, RED "\nMain:" NONE " Run Multi..."); fflush(stdout);
    int s1;
    key_t k1;
    k1 = ftok(".", 0);
    s1 = semget(k1, 1, 0644);
    u = 2;
    if (semctl(s1, 0, SETVAL, u )){
        printf(RED "Main:" NONE " Can\'t set val\n");
        exit(-1);
    }


    // ожидание главным потоком завершения расчета потоком multi, сигнал - установка семафора = 3 в конце итерации цикла
    struct sembuf b1;
    b1.sem_num = 0; // номер семафора
    b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
    b1.sem_flg = 0;

    if (semop(s1, &b1, 1) < 0){
        printf(RED "Main:" NONE " Can\'t wait for condition\n");
        exit(-1);
    }


    //чтение результата умножения AC
    int k3 = ftok(".",0x12);
    q = msgget( k3, 0666 | IPC_CREAT );
    msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
                TYPE, MSG_NOERROR | IPC_NOWAIT );
    double multiResult = buf.msg[0];

    fprintf(stdout,RED "\nMulti:" NONE " Получен результат АС: %f", multiResult); fflush(stdout);
    k1 = ftok(".", 0);


    /*------------------------------------------------------------------------------------------------4AC-------------------------------------------------------------------------------------*/
    //отправка сообщения
    q = msgget( k2, 0666 | IPC_CREAT );
    buf.type = TYPE;
    buf.msg[0] = multiResult;
    buf.msg[1] = 4;
    msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);

    // запуск семафора для потока умножения установка значения 2
    fprintf(stdout, RED "\nMain:" NONE " Run Multi..."); fflush(stdout);
    k1 = ftok(".", 0);
    s1 = semget(k1, 1, 0644);
    u = 2;
    if (semctl(s1, 0, SETVAL, u )){
        printf(RED "Main:" NONE " Can\'t set val\n");
        exit(-1);
    }

    // ожидание главным потоком завершения расчета потоком multi, сигнал - установка семафора = 3 в конце итерации цикла
    b1.sem_num = 0; // номер семафора
    b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
    b1.sem_flg = 0;

    if (semop(s1, &b1, 1) < 0){
        printf(RED "Main:" NONE " Can\'t wait for condition\n");
        exit(-1);
    }

    //чтение результата умножения 4AC
    k3 = ftok(".",0x12);
    q = msgget( k3, 0666 | IPC_CREAT );
    msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
            TYPE, MSG_NOERROR | IPC_NOWAIT );
    double multiResult2 = buf.msg[0];

    fprintf(stdout,RED "\nMulti:" NONE " Получен результат 4AC: %f", multiResult2); fflush(stdout);


    /*------------------------------------------------------------------------------------------------B^2-------------------------------------------------------------------------------------*/
    //отправка сообщения
    q = msgget( k2, 0666 | IPC_CREAT );
    buf.type = TYPE;
    buf.msg[0] = coefB;
    buf.msg[1] = coefB;
    msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);

    // запуск семафора для потока умножения установка значения 2
    fprintf(stdout, RED "\nMain:" NONE " Run Multi..."); fflush(stdout);
    k1 = ftok(".", 0);
    s1 = semget(k1, 1, 0644);
    u = 2;
    if (semctl(s1, 0, SETVAL, u )){
        printf(RED "Main:" NONE " Can\'t set val\n");
        exit(-1);
    }

    // ожидание главным потоком завершения расчета потоком multi, сигнал - установка семафора = 3 в конце итерации цикла
    b1.sem_num = 0; // номер семафора
    b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
    b1.sem_flg = 0;

    if (semop(s1, &b1, 1) < 0){
        printf(RED "Main:" NONE " Can\'t wait for condition\n");
        exit(-1);
    }

    //чтение результата умножения BB
    k3 = ftok(".",0x12);
    q = msgget( k3, 0666 | IPC_CREAT );
    msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
            TYPE, MSG_NOERROR | IPC_NOWAIT );
    double multiResult3 = buf.msg[0];

    fprintf(stdout,RED "\nMain:" NONE " Получен результат B^2: %f", multiResult3); fflush(stdout);
    msgctl( q, IPC_RMID, NULL);

/*------------------------------------------------------------------------------------------------B^2-4AC-------------------------------------------------------------------------------------*/
    //создание семафора
    int sp;
    struct sembuf bp;
    int up;
    key_t kp;
    pthread_t tp;
    kp = ftok(".", 2); // ключ для ядра
    sp = semget(kp, 1, 0644 | IPC_CREAT | IPC_EXCL); //создает массив семафоров
    up = 1;
    semctl(sp, 0, SETVAL, up);

    //создание процесса минус
    int pidp = fork();
    if (pidp == 0){
        char programPath[30] = "./";
        strcat(programPath, "minus");
        execl(programPath, programPath, (char *) NULL);
    }

    //отправка сообщения
    q = msgget( k2, 0666 | IPC_CREAT );
    buf.type = TYPE;
    buf.msg[0] = multiResult3;
    buf.msg[1] = multiResult2;
    msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);

    // запуск семафора для потока минус установка значения 2
    fprintf(stdout, RED "\nMain:" NONE " Run Minus..."); fflush(stdout);
    kp = ftok(".", 2);
    sp = semget(kp, 1, 0644);
    u = 2;
    if (semctl(sp, 0, SETVAL, u )){
        printf(RED "Main:" NONE " Can\'t set val\n");
        exit(-1);
    }

    // ожидание главным потоком завершения расчета потоком minus, сигнал - установка семафора = 3 в конце итерации цикла
    b1.sem_num = 0; // номер семафора
    b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
    b1.sem_flg = 0;

    if (semop(sp, &b1, 1) < 0){
        printf(RED "Main:" NONE " Can\'t wait for condition\n");
        exit(-1);
    }

    //чтение результата умножения B2 -4AC
    kp = ftok(".",0x12);
    q = msgget( kp, 0666 | IPC_CREAT );
    msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
            TYPE, MSG_NOERROR | IPC_NOWAIT );

    double discriminant = buf.msg[0];
    /*msgctl( q, IPC_RMID, NULL);*/
    fprintf(stdout,RED "\nMain:" NONE " Получен результат B^2-4AC: %f", discriminant); fflush(stdout);
    fprintf(stdout,RED "\nMain:" NONE "ДИСКРИМИНАНТ ПОСЧИТАН: %f", discriminant); fflush(stdout);


    if (discriminant<0){
        fprintf(stdout, RED "\nMain:" NONE "Нет корней"); fflush(stdout);
    }
    else{



        /*------------------------------------------------------------------------------------------------SQRT D-------------------------------------------------------------------------------------*/
        //создание семафора
        int sq;
        struct sembuf bq;
        int uq;
        key_t kq;
        pthread_t tq;
        kq = ftok(".", 3); // ключ для ядра
        sq = semget(kq, 1, 0644 | IPC_CREAT | IPC_EXCL); //создает массив семафоров
        uq = 1;
        semctl(sq, 0, SETVAL, uq);

        //создание процесса корень
        int pidq = fork();
        if (pidq == 0){
            char programPath[30] = "./";
            strcat(programPath, "sqrt");
            execl(programPath, programPath, (char *) NULL);
        }

        //отправка сообщения
        q = msgget( k2, 0666 | IPC_CREAT );
        buf.type = TYPE;
        buf.msg[0] = discriminant;
        msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);


        // запуск семафора для потока корень установка значения 2
        fprintf(stdout, RED "\nMain:" NONE " Run SQRT..."); fflush(stdout);
        kq = ftok(".", 3);
        sq = semget(kq, 1, 0644);
        u = 2;
        if (semctl(sq, 0, SETVAL, u )){
            printf(RED "Main:" NONE " Can\'t set val\n");
            exit(-1);
        }

        // ожидание главным потоком завершения расчета потоком sqrt, сигнал - установка семафора = 3 в конце итерации цикла
        b1.sem_num = 0; // номер семафора
        b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
        b1.sem_flg = 0;

        if (semop(sq, &b1, 1) < 0){
            printf(RED "Main:" NONE " Can\'t wait for condition\n");
            exit(-1);
        }

        //чтение результата вычисления корня
        kq = ftok(".",0x12);
        q = msgget( kq, 0666 | IPC_CREAT );
        msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
                TYPE, MSG_NOERROR | IPC_NOWAIT );

        double sqrt_discriminant = buf.msg[0];
        /*msgctl( q, IPC_RMID, NULL);*/
        fprintf(stdout,RED "\nMain:" NONE " Получен результат sqrt D: %f", sqrt_discriminant); fflush(stdout);

        /*------------------------------------------------------------------------------------------------2A-------------------------------------------------------------------------------------*/
        //отправка сообщения
        q = msgget( k2, 0666 | IPC_CREAT );
        buf.type = TYPE;
        buf.msg[0] = coefA;
        buf.msg[1] = 2;
        msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);

        // запуск семафора для потока умножения установка значения 2
        fprintf(stdout, RED "\nMain:" NONE " Run Multi..."); fflush(stdout);
        k1 = ftok(".", 0);
        s1 = semget(k1, 1, 0644);
        u = 2;
        if (semctl(s1, 0, SETVAL, u )){
            printf(RED "Main:" NONE " Can\'t set val\n");
            exit(-1);
        }

        // ожидание главным потоком завершения расчета потоком multi, сигнал - установка семафора = 3 в конце итерации цикла
        b1.sem_num = 0; // номер семафора
        b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
        b1.sem_flg = 0;

        if (semop(s1, &b1, 1) < 0){
            printf(RED "Main:" NONE " Can\'t wait for condition\n");
            exit(-1);
        }

        //чтение результата умножения 2A
        k3 = ftok(".",0x12);
        q = msgget( k3, 0666 | IPC_CREAT );
        msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
                TYPE, MSG_NOERROR | IPC_NOWAIT );
        double result2A = buf.msg[0];

        fprintf(stdout,RED "\nMain:" NONE " Получен результат 2A: %f", result2A); fflush(stdout);
        msgctl( q, IPC_RMID, NULL);


        /*-------------------------------------------------------------------------------------------------B+SQRTD-------------------------------------------------------------------------------------*/
        //создание семафора
        int spl;
        struct sembuf bpl;
        int upl;
        key_t kpl;
        pthread_t tpl;
        kpl = ftok(".", 1); // ключ для ядра
        spl = semget(kpl, 1, 0644 | IPC_CREAT | IPC_EXCL); //создает массив семафоров
        upl = 1;
        semctl(spl, 0, SETVAL, upl);

        //создание процесса плюс
        int pidpl = fork();
        if (pidpl == 0){
            char programPath[30] = "./";
            strcat(programPath, "plus");
            execl(programPath, programPath, (char *) NULL);
        }

        //отправка сообщения
        q = msgget( k2, 0666 | IPC_CREAT );
        buf.type = TYPE;
        buf.msg[0] = -coefB;
        buf.msg[1] = sqrt_discriminant;
        msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);


        // запуск семафора для потока корень установка значения 2
        fprintf(stdout, RED "\nMain:" NONE " Run Plus..."); fflush(stdout);
        kpl = ftok(".", 1);
        spl = semget(kpl, 1, 0644);
        u = 2;
        if (semctl(spl, 0, SETVAL, u )){
            printf(RED "Main:" NONE " Can\'t set val\n");
            exit(-1);
        }

        // ожидание главным потоком завершения расчета потоком plus, сигнал - установка семафора = 3 в конце итерации цикла
        b1.sem_num = 0; // номер семафора
        b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
        b1.sem_flg = 0;

        if (semop(spl, &b1, 1) < 0){
            printf(RED "Main:" NONE " Can\'t wait for condition\n");
            exit(-1);
        }

        //чтение результата вычисления сложения
        kpl = ftok(".",0x12);
        q = msgget( kq, 0666 | IPC_CREAT );
        msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
                TYPE, MSG_NOERROR | IPC_NOWAIT );

        double minusB_plus_sqrt_D = buf.msg[0];
        /*msgctl( q, IPC_RMID, NULL);*/
        fprintf(stdout,RED "\nMain:" NONE " Получен результат -B+SQRT D: %f", minusB_plus_sqrt_D); fflush(stdout);

        /*-------------------------------------------------------------------------------------------------B-SQRTD-------------------------------------------------------------------------------------*/
        //отправка сообщения
        q = msgget( k2, 0666 | IPC_CREAT );
        buf.type = TYPE;
        buf.msg[0] = -coefB;
        buf.msg[1] = sqrt_discriminant;
        msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);

        // запуск семафора для потока минус установка значения 2
        fprintf(stdout, RED "\nMain:" NONE " Run Minus..."); fflush(stdout);
        kp = ftok(".", 2);
        sp = semget(kp, 1, 0644);
        u = 2;
        if (semctl(sp, 0, SETVAL, u )){
            printf(RED "Main:" NONE " Can\'t set val\n");
            exit(-1);
        }

        // ожидание главным потоком завершения расчета потоком minus, сигнал - установка семафора = 3 в конце итерации цикла
        b1.sem_num = 0; // номер семафора
        b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
        b1.sem_flg = 0;

        if (semop(sp, &b1, 1) < 0){
            printf(RED "Main:" NONE " Can\'t wait for condition\n");
            exit(-1);
        }

        //чтение результата умножения -B-SQRT D
        kp = ftok(".",0x12);
        q = msgget( kp, 0666 | IPC_CREAT );
        msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
                TYPE, MSG_NOERROR | IPC_NOWAIT );

        double minusB_minus_sqrt_D = buf.msg[0];
        fprintf(stdout,RED "\nMain:" NONE " Получен результат -B-SQRT D: %f", minusB_minus_sqrt_D); fflush(stdout);


        /*-------------------------------------------------------------------------------------------------B+SQRTD / 2A-------------------------------------------------------------------------------------*/
        //создание семафора
        int sd;
        struct sembuf bd;
        int ud;
        key_t kd;
        pthread_t td;
        kd = ftok(".", 4); // ключ для ядра
        sd = semget(kd, 1, 0644 | IPC_CREAT | IPC_EXCL); //создает массив семафоров
        ud = 1;
        semctl(sd, 0, SETVAL, ud);

        //создание процесса div
        int pidd = fork();
        if (pidd == 0){
            char programPath[30] = "./";
            strcat(programPath, "div");
            execl(programPath, programPath, (char *) NULL);
        }

        //отправка сообщения
        q = msgget( k2, 0666 | IPC_CREAT );
        buf.type = TYPE;
        buf.msg[0] = minusB_plus_sqrt_D;
        buf.msg[1] = result2A;
        msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);


        // запуск семафора для потока div установка значения 2
        fprintf(stdout, RED "\nMain:" NONE " Run Div..."); fflush(stdout);
        kd = ftok(".", 4);
        sd = semget(kd, 1, 0644);
        u = 2;
        if (semctl(sd, 0, SETVAL, u )){
            printf(RED "Main:" NONE " Can\'t set val\n");
            exit(-1);
        }

        // ожидание главным потоком завершения расчета потоком деления, сигнал - установка семафора = 3 в конце итерации цикла
        b1.sem_num = 0; // номер семафора
        b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
        b1.sem_flg = 0;

        if (semop(sd, &b1, 1) < 0){
            printf(RED "Main:" NONE " Can\'t wait for condition\n");
            exit(-1);
        }

        //чтение результата вычисления
        kd = ftok(".",0x12);
        q = msgget( kq, 0666 | IPC_CREAT );
        msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
                TYPE, MSG_NOERROR | IPC_NOWAIT );

        double minusB_plus_sqrt_D_div_2a = buf.msg[0];
        /*msgctl( q, IPC_RMID, NULL);*/
        fprintf(stdout,RED "\nMain:" NONE " Получен результат -B+SQRT D / 2A: %f", minusB_plus_sqrt_D_div_2a); fflush(stdout);

        /*-------------------------------------------------------------------------------------------------B-SQRTD / 2A-------------------------------------------------------------------------------------*/
        //отправка сообщения
        q = msgget( k2, 0666 | IPC_CREAT );
        buf.type = TYPE;
        buf.msg[0] = minusB_minus_sqrt_D;
        buf.msg[1] = result2A;
        msgsnd( q, &buf, sizeof(struct msgbuf)-sizeof(long), 0);


        // запуск семафора для потока div установка значения 2
        fprintf(stdout, RED "\nMain:" NONE " Run Div..."); fflush(stdout);
        kd = ftok(".", 4);
        sd = semget(kd, 1, 0644);
        u = 2;
        if (semctl(sd, 0, SETVAL, u )){
            printf(RED "Main:" NONE " Can\'t set val\n");
            exit(-1);
        }

        // ожидание главным потоком завершения расчета потоком деления, сигнал - установка семафора = 3 в конце итерации цикла
        b1.sem_num = 0; // номер семафора
        b1.sem_op = -3; // код операции -3 ожидание семара со значением >=3
        b1.sem_flg = 0;

        if (semop(sd, &b1, 1) < 0){
            printf(RED "Main:" NONE " Can\'t wait for condition\n");
            exit(-1);
        }

        //чтение результата вычисления деления
        kd = ftok(".",0x12);
        q = msgget( kq, 0666 | IPC_CREAT );
        msgrcv( q, &buf, sizeof(struct msgbuf)-sizeof(long),
                TYPE, MSG_NOERROR | IPC_NOWAIT );

        double minusB_minus_sqrt_D_div_2a = buf.msg[0];
        /*msgctl( q, IPC_RMID, NULL);*/
        fprintf(stdout,RED "\nMain:" NONE " Получен результат -B-SQRT D / 2A: %f", minusB_minus_sqrt_D_div_2a); fflush(stdout);

        if(discriminant!=0){
            fprintf(stdout,RED "\nMain:" NONE " X1= %f", minusB_minus_sqrt_D_div_2a); fflush(stdout);
            fprintf(stdout,RED "\nMain:" NONE " X2= %f", minusB_plus_sqrt_D_div_2a); fflush(stdout);
        }
        else{
            fprintf(stdout,RED "\nMain:" NONE " X= %f", minusB_minus_sqrt_D_div_2a); fflush(stdout);
        }
    }

    sleep(1);

}
