.PHONY : build

# コンテナ名
CONTAINER-NAME := test-container
DOCKER_HOME_DIR := /home/guest
# ビルドディレクトリ
BUILD_DIR := sechack365/test

# Docker exec用オプション
ARG :=

CXX := g++

SHELL := /bin/bash

TARGET	:= test.out

SRCDIR := ../src

SRCS	:= key_list_c.cpp\
	dynamic_mem_c.cpp\
	file_ptr_c.cpp\
	sha_c.cpp\
	file_enc.cpp\
	aes_c.cpp\
	key_gen_c.cpp\
	error.cpp\
	device_c.cpp\
	master_key_c.cpp

TESTSRC	:= keyGenTest.cpp\
	key_list_test.cpp\
	test.cpp\
	dynamicMemTest.cpp\
	test_log.cpp\
	deviceTest.cpp\
	cmdline.cpp\
	nonceTest.cpp\
	masterKeyTest.cpp

TESTDIR := src

OBJDIR := build

OBJS	:= ${SRCS:%.cpp=${OBJDIR}/%.o} ${TESTSRC:%.cpp=${OBJDIR}/%.o}

LDGFLAGS	:= -lpthread \
	-lgtest_main \
	-lgtest

LDFLAGS	:= -lssl \
	-ldl \
	-pthread \
	-Wl,-rpath=./ -lcrypto

CFLAGS	:= -Wall\
	-std=c++11

${TARGET}: ${OBJS}
	${CXX} -o $@ $^ ${LDGFLAGS} ${LDFLAGS}

${OBJDIR}/%.o: $(SRCDIR)/%.cpp
	mkdir -p build
	cd build;\
	${CXX} -c ../$^ ${CFLAGS}

${OBJDIR}/%.o: $(TESTDIR)/%.cpp
	mkdir -p build
	cd build;\
	${CXX} -c ../$^ ${CFLAGS}

# %.o: ${addprefix ${SRCDIR},${SRCS}} ${TESTSRC}
# 	mkdir -p build
# 	cd build;\
# 	${CXX} ${addprefix ../, ${TESTSRC}} -c ${addprefix ../${SRCDIR},${SRCS}} ${CFLAGS}



run: ${TARGET}
	cp /dev/null errorLog.txt
	./${TARGET}

clean:
	rm -rf ${OBJDIR}/*.o ${TARGET}

# Clang-format用コマンド
format:
	clang-format -i -style=file $(shell find ../src/ -type f -name "*.cpp" -or -name "*.c" -or -name "*.hpp" -or -name "*.h")
	clang-format -i -style=file $(shell find ../include/ -type f -name "*.cpp" -or -name "*.c" -or -name "*.hpp" -or -name "*.h")
	clang-format -i -style=file $(shell find ../qt_src/ -type f -name "*.cpp" -or -name "*.c" -or -name "*.hpp" -or -name "*.h")
	clang-format -i -style=file $(shell find ../test/ -path "*gtest" -prune -or -type f -name "*.cpp" -or -name "*.c" -or -name "*.hpp" -or -name "*.h" | grep -v "gtest")

# --------------------------

# Docker用コマンド

# --------------------------

build:
	make -s pre-exec
	-docker container exec -t ${ARG} ${CONTAINER-NAME} /bin/bash -c "cd ${BUILD_DIR} && make -j4"
	make -s post-exec

rebuild:
	make -s pre-exec
	-docker container exec -t ${ARG} ${CONTAINER-NAME} /bin/bash -c "cd ${BUILD_DIR} && make clean && make -j4 "
	make -s post-exec

debug:
	make -s pre-exec
	-make -s rebuild "CFLAGS = ${CFLAGS} -g -O0"
	make -s post-exec

bash:
	make -s pre-exec
	-docker container exec -it ${ARG} ${CONTAINER-NAME} /bin/bash
	make -s post-exec

docker-build:
	DOCKER_BUILDKIT=1 docker image build -t ${CONTAINER-NAME} \
	--force-rm=true .
	@if [[ -n "$(shell docker images -f 'dangling=true' -q)" ]]; then\
		docker rmi $(shell docker images -f 'dangling=true' -q);\
	fi
docker-rebuild:
	DOCKER_BUILDKIT=1 docker image build -t ${CONTAINER-NAME} \
	--pull \
	--force-rm=true \
	--no-cache=true .
	@if [[ -n "$(shell docker images -f 'dangling=true' -q)" ]]; then\
		docker rmi $(shell docker images -f 'dangling=true' -q);\
	fi


# コンテナ実行する際の前処理
# 起動，ファイルのコピーを行う
pre-exec:
ifneq ($(shell docker container ls -a 2>/dev/null | grep -c ${CONTAINER-NAME}),0)
	docker container stop ${CONTAINER-NAME}
endif
	@docker container run \
	-it \
	--rm \
	-d \
	--name ${CONTAINER-NAME} \
	${CONTAINER-NAME}:latest 1>/dev/null
	@-docker container cp ../ ${CONTAINER-NAME}:${DOCKER_HOME_DIR}

# コンテナ終了時の後処理
# コンテナ内のファイルをローカルへコピー，コンテナの削除を行う
post-exec:
	-docker container cp ${CONTAINER-NAME}:${DOCKER_HOME_DIR}/sechack365/test/build/ .
	-docker container cp ${CONTAINER-NAME}:${DOCKER_HOME_DIR}/sechack365/test/test.out .
	-docker container cp ${CONTAINER-NAME}:/lib/x86_64-linux-gnu/libcrypto.so.1.1 .
	@docker container stop ${CONTAINER-NAME} 1>/dev/null