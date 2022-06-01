#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define FILE_NAME "infile.txt"

int	main(void)
{
	int	fd;

	fd = open(FILE_NAME, O_RDONLY); // 読み込み専用でファイルを開く
	if (fd == -1) // ファイルを開くのに失敗した場合
	{
		perror("open");
		exit(1);
	}
	printf("File Descriptor = %d\n", fd);
	return (0);
}
