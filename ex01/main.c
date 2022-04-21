#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BYTES 100

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Not enough arguments.");
		return (1);
	}
	int fd = open(argv[1], O_RDONLY); // 読み込み専用でファイルを開く
	if (fd == -1) // ファイルを開くのに失敗した場合
	{
		perror("open");
		exit(1);
	}

	char buffer[MAX_BYTES + 1]; // ファイル読み込み分を格納する静的な配列を用意する
	// ssize_t read(int fd, void *buf, size_t count);
	ssize_t bytes = read(fd, &buffer, MAX_BYTES);
	if (bytes == -1) // 読み込み失敗時
	{
		perror("read");
		exit(1);
	}
	buffer[bytes] = '\0'; // 終端文字列としてヌル文字を代入

	write(STDOUT_FILENO, buffer, bytes); // 「infile.txt」から読み取ったものを標準出力
	close(fd); // 開いたファイルを閉じる
	return (0);
}
