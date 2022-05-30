# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define PIPE_READ_FD 0
# define PIPE_WRITE_FD 1

static void	execute_child_command()
{
	char *argv[2];

	argv[0] = "/bin/cat";
	argv[1] = NULL;

	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
}

static void	start_child_process(int *pipe_fd)
{
	int		file_fd;

	close(pipe_fd[PIPE_READ_FD]);
	file_fd = open("access.log", O_RDONLY);
	if (file_fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (dup2(file_fd, STDIN_FILENO) == -1)
	{
		close(file_fd);
		perror("dup2");
		exit(1);
	}
	close(file_fd);
	if (dup2(pipe_fd[PIPE_WRITE_FD], STDOUT_FILENO) == -1)
	{
		close(pipe_fd[PIPE_WRITE_FD]);
		perror("dup2");
		exit(1);
	}
	close(pipe_fd[PIPE_WRITE_FD]);
	execute_child_command();
	exit(0);
}

static void	execute_parent_command()
{
	char *argv[3];

	argv[0] = "/usr/bin/grep";
	argv[1] = "POST";
	argv[2] = NULL;

	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
}

static void	start_parent_process(int *pipe_fd)
{
	close(pipe_fd[PIPE_WRITE_FD]);
	if (dup2(pipe_fd[PIPE_READ_FD], STDIN_FILENO) == -1)
	{
		close(pipe_fd[PIPE_READ_FD]);
		perror("dup2");
		exit(1);
	}
	close(pipe_fd[PIPE_READ_FD]);
	execute_parent_command();
}

int	main(void)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1) // エラー対応
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0) // 子プロセス
	{
		start_child_process(pipe_fd);
	}
	else // 親プロセス
	{
		wait(&status); // 子プロセスを待つ
		start_parent_process(pipe_fd);
	}
	return (0);
}
