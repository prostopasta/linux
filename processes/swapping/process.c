#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>
#include <sys/fcntl.h>
#include "limits.h"
#include "string.h"

#define MALLOCATE_SIZE UINT_MAX

/* родительский процесс начнёт выполняться с функции main() */
int main() {
    pid_t parent_pid = getpid();
    printf("PID родительского процесса: %d\n", parent_pid);

    /* создаём новый процесс */
    pid_t child_pid = fork();

    if (child_pid == 0) {
        /* дочернему процессу вернулся 0 */
        printf("Приветики от дочернего процесса!\n");

        /* запустим в дочернем процессе программу ls */
        char* args[] = { "/bin/ls", "-1", NULL};
        printf("ls выведет список файлов в текущей директории:\n");
        execve("/bin/ls", args, NULL);
    } else {
        /* а родителю вернулся PID потомка */
        printf("Приветики от родительского процесса!\n");
        printf("PID дочернего процесса: %d\n", child_pid);
        printf("Подождём, что он нам ответит\n");

        /* родитель может узнать, всё ли у него хорошо */
        int status;
        waitpid(child_pid, &status, 0);
        printf("Всё ли у него хорошо? Код возврата: %d (хорошо, если 0)\n", status);

        /* выделим немного памяти в куче (heap) */
        void *p = malloc(MALLOCATE_SIZE);

        /* если памяти не хватает, то указатель будет нулевым */
        if (p == NULL) {
            printf("ERROR: Не удалось выделить память\n");
            exit(2);
        }
        memset(p, 1, MALLOCATE_SIZE);

        int fd = open("/tmp/process.txt", O_CREAT | O_RDONLY);

        sleep(60);
        /* и не забудем освободить, чтобы память не утекала */
        free(p);
        close(fd);
    }

    return 0;
}