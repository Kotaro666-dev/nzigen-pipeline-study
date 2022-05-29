#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	pid_t	pid;
	int		status;

	printf("1. Execute fork.\n");
	pid = fork();
	if (pid == -1)
	{
		write(STDERR_FILENO, "Error\n", 6);
		exit(1);
	}
	else if (pid == 0) // 子プロセスの処理
	{
		printf("2. Executing child process....\n");
		sleep(2);
		printf("3. Finishing child process!\n");
		exit(0); // 子プロセスを終了し、親にSIGCHILDが送信される
	}
	else // 親プロセスの処理
	{
		wait(&status); // 子プロセスが終了するまで呼び出し側をプロックする
		printf("4. Executing parent process....\n");
	}
	printf("5. Finishing program.\n");
	return (0);
}
