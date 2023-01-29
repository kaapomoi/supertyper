# supertyper
A tool for typing practice.

## Installation

### Dependencies

CMake
[CMake Home Page](https://cmake.org/)

NCurses
[ncurses 6.4 direct download](https://invisible-island.net/archives/ncurses/ncurses-6.4.tar.gz)

NCurses installation steps, from [Tmux GitHub Wiki](https://github.com/tmux/tmux/wiki/Installing):

```bash
tar -zxf ncurses-*.tar.gz
cd ncurses-*/
./configure --prefix=$HOME/local --with-shared --with-termlib --enable-pc-files --with-pkg-config-libdir=$HOME/local/lib/pkgconfig
make && make install
```

## Building and running

```bash
source ./build.sh; build; run;
```

Exit the application with ESCAPE.

## Modify the word list

You can modify the word list by changing the contents of `words.txt` in the project root.

