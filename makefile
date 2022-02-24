all: main

main: main.o operacoes_problema.o
    gcc main.c operacoes_problema.c