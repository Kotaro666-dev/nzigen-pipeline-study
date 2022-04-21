# 概要

以下のコマンドを再現する。
処理：output.txtに「Hello World」を書き込む。

```
$ echo "Hello World" > output.txt
```

## 実行

```
$ make
$ ./ex00 "Hello World" output.txt
```

## 実装手順

1. output.txt ファイルを書き込み専用で開き、そのファイルディスクリプタを取得する
2. 取得したファイルディスクリプタにwriteシステムコールで文字列を書き込む
