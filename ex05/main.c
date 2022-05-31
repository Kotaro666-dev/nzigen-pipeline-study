# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define PIPE_READ_FD 0
# define PIPE_WRITE_FD 1
# define MAX_BYTES 100

int main(void)
{
	int	pipe_fd[2];
	char buffer[MAX_BYTES + 1];
	ssize_t bytes;

	pipe(pipe_fd); // パイプラインを生成する
	write(pipe_fd[PIPE_WRITE_FD], "This is test message.", 21);
	// パイプライン書き込み口に出力する

	bytes = read(pipe_fd[PIPE_READ_FD], &buffer, MAX_BYTES);
	// パイプライン書き込み口から読み込む
	if (bytes == -1) // 読み込み失敗時
	{
		perror("read");
		exit(1);
	}
	buffer[bytes] = '\0';

	write(STDOUT_FILENO, buffer, bytes); // 読み込んだデータを標準出力する
	return (0);
}
