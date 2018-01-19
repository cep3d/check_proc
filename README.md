# Xcode - using curl and mariadb

## Curl
Other Linker Flags：-lcurl

## MariaDB
Other Linker Flags: -lm -lz -lmysqlclient

## Search Paths
Header Search Paths:

/usr/local/include/mariadb

Library Search Paths:

/usr/local/lib/mariadb

/usr/local/lib


1. Install MariaDB
```
$ brew install mariadb
```

2. Install CMAKE
(cmakeがインストールされていない場合。)
```
$ brew install cmake
```

Download MariaDB Connector/C Driver

https://downloads.mariadb.org/connector-c/

3. Configure MariaDB Driver
```
$ cmake mariadb-connector-c-3.0.3-src/ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local
```

(ダウンロードディレクトリと同じディレクトリでコンパイルしないこと)

```
$ cmake —build . —config RelWithDebInfo

$ make
$ make install
```

## ライブラリ読み込みエラー
** dyld: Library not loaded: libmysqlclient.18.dylib

シンボリックリンクを作成する。

```
$ sudo ln -s /usr/local/mysql/lib/libmysqlclient.18.dylib /usr/local/lib/libmysqlclient.18.dylib
```

https://stackoverflow.com/questions/10557507/rails-mysql-on-osx-library-not-loaded-libmysqlclient-18-dylib

https://qiita.com/puzzel/items/8768324d6c60417f4d6c
