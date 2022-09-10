SHELL := /bin/bash

CXX := g++
TARGET := fileEncSysCmd.out
SRC := $(shell find . -name "*.cpp" -type f)

OBJDIR := objects
OBJS := ${SRC:%.cpp=${OBJDIR}/%.o}

LDFLAGS	:= -lssl \
	-ldl \
	-pthread \
	-Wl,-rpath=./ -lcrypto

CFLAGS := -Wall\
	-std=c++11

${TARGET}: ${OBJS}
	${CXX} -o $@ $^ ${LDFLAGS}

${OBJDIR}/%.o: %.cpp
	mkdir -p ${OBJDIR}
	cd ${OBJDIR} && \
	${CXX} -c ../$^ ${CFLAGS}

clean:
	rm ${OBJDIR}/*.o
	rm ${TARGET}

test:
	echo ${SRC}
	echo ${OBJS}