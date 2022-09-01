.PHONY : build

# コンテナ名
CONTAINER-NAME := build-container
# コンテナのホームディレクトリ
DOCKER_HOME_DIR := /home/guest
# ビルドディレクトリ
BUILD_DIR := build


build:
	@make -s pre-exec
	-docker container exec -t ${CONTAINER-NAME} /bin/bash -c "cd ${BUILD_DIR} && make -j4"
	@make -s post-exec

rebuild:
	make -s pre-exec
	-docker container exec -t ${CONTAINER-NAME}  /bin/bash -c "cd ${BUILD_DIR} && make clean &&  make -j$(nproc) "
	make -s post-exec

bash:
	make -s pre-exec
	-docker container exec -it ${CONTAINER-NAME} /bin/bash
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
ifneq ($(shell docker container ls -a | grep -c ${CONTAINER-NAME}),0)
	docker container stop ${CONTAINER-NAME}
endif
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
	@docker container stop ${CONTAINER-NAME} 1>/dev/null
