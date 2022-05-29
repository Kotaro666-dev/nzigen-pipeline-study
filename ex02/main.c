#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>

#define MAX_BYTES 100 // 最大読み込みバイト数の定義

int	main(void)
{
	ssize_t	bytes; // 読み込み成功した分のバイト数を格納する変数
	char	buffer[MAX_BYTES + 1]; // 読み込んだデータを格納する静的配列

	while (1) // 無限ループ
	{
		bytes = read(STDIN_FILENO, &buffer, MAX_BYTES); // ① 標準入力からデータを読み取り、バッファに格納する。
		if (bytes == -1) // 読み込み失敗時の対応
		{
			write(STDERR_FILENO, "Error\n", 6); // ② エラーメッセージとともに標準エラー出力する
			exit(1);
		}
		buffer[bytes] = '\0'; // 終端文字列としてヌル文字を代入する
		write(STDOUT_FILENO, buffer, bytes); // ③ バッファに格納されたデータを標準出力する
		bzero(buffer, bytes); // バッファの中を初期化する
	}
	return (0);
}
