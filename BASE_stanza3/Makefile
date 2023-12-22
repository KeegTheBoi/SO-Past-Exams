CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_THREAD_SAFE -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE 
LFLAGS=
MODULES_DIR=./modules
LIBRARIES=-lpthread
SHELL=/bin/bash

all: 	tre.exe

tre.exe: tre.o ${MODULES_DIR}/DBGpthread.o
	gcc ${LFLAGS} -o tre.exe tre.o DBGpthread.o ${LIBRARIES}

tre.o: tre.c ${MODULES_DIR}/DBGpthread.h ${MODULES_DIR}/printerror.h
	gcc ${CFLAGS} -c tre.c

${MODULES_DIR}/DBGpthread.o: ${MODULES_DIR}/DBGpthread.c ${MODULES_DIR}/printerror.h
	gcc ${CFLAGS} -c ${MODULES_DIR}/DBGpthread.c

.PHONY:	clean

clean:
	-rm -f tre.o DBGpthread.o tre.exe


