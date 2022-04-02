#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <limits.h>
/*
2.	Написать программу, создающую два дочерних процесса с использованием двух вызовов fork(). 
Родительский и два дочерних процесса должны выводить на экран 
свой pid и pid родительского процесса и текущее время в формате: часы: минуты: секунды: миллисекунды. 
Используя вызов system (), выполнить команду ps -x в родительском процессе. 
Найти свои процессы в списке запущенных процессов. 
*/

int main(int argc, char *argv[])
{
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 != 0) { // not the child
        pid2 = fork();
    }
    if (pid1 > 0 && pid2 > 0) {
        system("ps -x");
    }

    // time
    struct timeval timeVal;
	gettimeofday( &timeVal, NULL );
	int msecs = timeVal.tv_usec / 1000;
	int secs  = timeVal.tv_sec % 60;
	int mins  = (timeVal.tv_sec / 60) % 60;
	int hrs   = (timeVal.tv_sec / 3600 + 3) % 24; // +3 is gmt

    printf("process PID: %6d\nparent PID: %6d\ntime: %02d:%02d:%02d:%03d\n\n", getpid(), getppid(),hrs, mins, secs, msecs);
    
    if (pid1 != 0 && pid2 != 0) {
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }
    return 0;
}



