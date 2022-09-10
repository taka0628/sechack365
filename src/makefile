SHELL := /bin/bash

CXX := g++
TARGET := fileEncSysCmd.out
SRC := $(shell find . -name "*.cpp" -type f)

OBJS := ${SRC:%.cpp=%.o}

LDFLAGS	:= -lssl \
	-ldl \
	-pthread \
	-Wl,-rpath=./ -lcrypto

CFLAGS := -Wall\
	-std=c++11

${TARGET}: ${OBJS}
	${CXX} -o $@ $^ ${LDFLAGS}

%.o: %.cpp
	${CXX} -c $^ ${CFLAGS}

test:
	echo ${SRC}
	echo ${OBJS}