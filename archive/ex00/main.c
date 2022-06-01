#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

static int	my_strlen(char *str)
{
	int length = 0;

	if (str == NULL)
	{
		return (0);
	}
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

// argc = コマンドライン引数として渡された数。
// argv = {"実行ファイル", "入力したい文字列", "ファイル名"}
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Not enough arguments.");
		return (1);
	}
	// argv[2] = "ファイル名"
	// O_CREAT：該当ファイルがなければ 00700 権限でファイルを生成
	// O_WRONLY：書き込み専用でファイルを開く
	int fd = open(argv[2], O_CREAT | O_WRONLY, S_IRWXU);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	write(fd, argv[1], my_strlen(argv[1]));
	write(fd, "\n", 1);
	return (0);
}
