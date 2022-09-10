.PHONY : build

SHELL := /bin/bash

TARGET := fileEncSysCmd.out

# コンテナ名
CONTAINER-NAME := build-container
# コンテナのホームディレクトリ
DOCKER_HOME_DIR := /home/guest
# ビルドディレクトリ
BUILD_DIR := build

SRCDIR := src

# Docker exec用オプション
ARG :=

CLEAN_FILE := pass_hash\
	key_hash


build:
	make guiadd -s
	make cmdapp -s

rebuild:
	make -s pre-exec
	-docker container exec -t ${ARG} ${CONTAINER-NAME}  /bin/bash -c "cd ${BUILD_DIR} && make clean &&  make -j4 "
	make -s post-exec
	make cmdapp -s

bash:
	make -s pre-exec
	-docker container exec -it ${CONTAINER-NAME} /bin/bash
	make -s post-exec

clean:
	-cd ${BUILD_DIR} && rm *.o *.out ${CLEAN_FILE} 2>/dev/null
	-make -C ${SRCDIR} clean -s

cmdapp:
	@make -s pre-exec
	-docker container exec -t ${ARG} ${CONTAINER-NAME} /bin/bash -c "cd ${SRCDIR} && make -j4 && mv ${TARGET} ../build "
	@make -s post-exec

guiadd:
	@make -s pre-exec
	-docker container exec -t ${ARG} ${CONTAINER-NAME} /bin/bash -c "cd ${BUILD_DIR} && make -j4"
	@make -s post-exec

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
ifneq ($(shell docker container ls -a | grep -c ${CONTAINER-NAME}),0)
	docker container stop ${CONTAINER-NAME}
endif
	sed -i "s/LOCAL_TEST 0/LOCAL_TEST 1/g" include/macro.hpp
	@docker container run \
	-it \
	--rm \
	--network none \
	-d \
	--name ${CONTAINER-NAME} \
	${CONTAINER-NAME}:latest 1>/dev/null
	@-docker container cp . ${CONTAINER-NAME}:${DOCKER_HOME_DIR}

# コンテナ終了時の後処理
# コンテナ内のファイルをローカルへコピー，コンテナの削除を行う
post-exec:
	docker container cp ${CONTAINER-NAME}:${DOCKER_HOME_DIR}/build .
	docker container cp ${CONTAINER-NAME}:${DOCKER_HOME_DIR}/src .
	-docker container cp ${CONTAINER-NAME}:/lib/x86_64-linux-gnu/libcrypto.so.1.1 build/
	@docker container stop ${CONTAINER-NAME} 1>/dev/null

install:
	sudo apt update
	sudo apt install \
	qtbase5-dev \
	qttools5-dev-tools

installDev:
	sudo apt update
	sudo apt install \
	libssl-dev \
	qtbase5-dev \
	qttools5-dev-tools \
	qtcreator \
	make \
	cmake \
	clang-format
	make googletest -s

googletest:
	wget https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
	tar xaf release-1.12.1.tar.gz
	rm release-1.12.1.tar.gz
	cd googletest-release-1.12.1 && \
	mkdir build && \
	cd build &&\
	cmake .. &&\
	make &&\
	sudo make install
	rm -rf googletest-release-1.12.1