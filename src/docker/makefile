NAME := guest_container
TS := `date +%Y%m%d%H%M%S`
SCORE_FILE := score.csv
DOCKER_USER_NAME := RDocker
DOCKER_HOME_DIR := /home/${DOCKER_USER_NAME}
CURRENT_PATH := $(shell pwd)
RescueSRC := RIORescue

# キャッシュ有りでビルド
build:
	docker image build -t ${NAME} \
	--build-arg CACHEBUST=${TS} .

# コンテナ実行
run:
	docker container stop ${NAME} &2>/dev/null
	xhost local:
	docker container run \
	-it \
	--rm \
	-d \
	--name ${NAME} \
	-e DISPLAY=unix${DISPLAY} \
	-v /tmp/.X11-unix/:/tmp/.X11-unix \
	${NAME}:latest
	bash FileCopyToContainer.sh ../../errorLog.txt ${NAME}
	docker container exec -it ${NAME} bash
	docker container stop ${NAME}


rioneLauncher:
	xhost local:
	bash rescue2docker.sh
	bash dockerContainerStop.sh ${NAME}
	docker container run \
	-it \
	--rm \
	-d \
	--name ${NAME} \
	--mount type=bind,src=$(PWD)/${SCORE_FILE},dst=${DOCKER_HOME_DIR}/RioneLauncher/${SCORE_FILE} \
	-e DISPLAY=unix${DISPLAY} \
	-v /tmp/.X11-unix/:/tmp/.X11-unix \
	${NAME}:latest
	bash dockerCp.sh ${NAME} ${DOCKER_HOME_DIR}
	bash execRioneLauncherInDocker.sh ${NAME}


# dockerのリソースを開放
clean:
	docker system prune

# キャッシュを使わずにビルド
rebuild:
	@echo "コンテナの再構築には時間がかかります"
	@echo "コンテナを再構築しますか？ (y/n)"
	@read -p "->" ans;\
	if [ "$$ans" != y ]; then  \
      exit 1;\
    fi
	bash rescue2docker.sh
	docker image build -t ${NAME} \
	--build-arg CACHEBUST=${TS} \
	--pull \
	--no-cache=true .

# root権限で起動中のコンテナに接続
connect:
	docker exec -u root -it ${NAME} /bin/bash

sync:
	bash rescue2docker.sh
ifeq ($(shell docker container ls | grep "rescue_d:latest"),)
	@echo "コンテナが起動していません"
	exit 1
endif
	docker cp ${RescueSRC}/ ${NAME}:/${DOCKER_USER_NAME}/

update:
	git pull
	make build

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
	--name ${NAME} \
	--mount type=bind,src=$(PWD)/${SCORE_FILE},dst=${DOCKER_HOME_DIR}/RioneLauncher/${SCORE_FILE} \
	-e DISPLAY=unix${DISPLAY} \
	-v /tmp/.X11-unix/:/tmp/.X11-unix \
	${NAME}:latest