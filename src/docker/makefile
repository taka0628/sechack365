CONTAINER_NAME := guest_container
TS := `date +%Y%m%d%H%M%S`
SCORE_FILE := score.csv
DOCKER_USER_NAME := RDocker
DOCKER_HOME_DIR := /home/${DOCKER_USER_NAME}
CURRENT_PATH := $(shell pwd)
RescueSRC := RIORescue

# キャッシュ有りでビルド
build:
	docker image build -t ${CONTAINER_NAME} \
	--build-arg CACHEBUST=${TS} .

# コンテナ実行
run:
	docker container stop ${CONTAINER_NAME} &2>/dev/null
	docker container run \
	-it \
	--rm \
	-d \
	--name ${CONTAINER_NAME} \
	${CONTAINER_NAME}:latest
	docker container cp ../../../2021_sec/ ${CONTAINER_NAME}:/home/guest
	docker container exec -it ${CONTAINER_NAME} /bin/bash -c "cd /home/guest/2021_sec/test/ && make -j$(nproc)" || :
	docker cp ${CONTAINER_NAME}:/home/guest/2021_sec/test/build/ ../../test/
	docker cp ${CONTAINER_NAME}:/home/guest/2021_sec/test/crypt_temp ../../test/
	docker container stop ${CONTAINER_NAME}


# dockerのリソースを開放
clean:
	docker system prune


# root権限で起動中のコンテナに接続
connect:
	docker exec -u root -it ${CONTAINER_NAME} /bin/bash

# 環境構築
install:
	sudo apt update
	sudo apt install -y apt-transport-https \
    ca-certificates \
    curl \
    gnupg-agent \
    software-properties-common
	curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
	sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu focal stable"
	sudo apt update
	apt-cache policy docker-ce
	sudo apt-get install -y docker-ce docker-ce-cli containerd.io
ifneq ($(shell getent group docker| cut -f 4 --delim=":"),$(shell whoami))
	sudo gpasswd -a $(shell whoami) docker
endif
	sudo chgrp docker /var/run/docker.sock
	sudo systemctl restart docker
	@echo "環境構築を完了するために再起動してください"

# デバッグ用
test:
	docker container run \
	-it \
	--rm \
	-d \
	--name ${CONTAINER_NAME} \
	--mount type=bind,src=$(PWD)/${SCORE_FILE},dst=${DOCKER_HOME_DIR}/RioneLauncher/${SCORE_FILE} \
	-e DISPLAY=unix${DISPLAY} \
	-v /tmp/.X11-unix/:/tmp/.X11-unix \
	${CONTAINER_NAME}:latest