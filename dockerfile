FROM ubuntu:20.04

# ユーザーを作成
ARG DOCKER_USER_=guest

COPY --chown=root:root sources.list /etc/apt/sources.list

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezon

RUN apt-get update \
	&&  apt-get install -y \
	g++\
	make\
	libssl-dev\
	qtbase5-dev\
	qttools5-dev-tools

ENV DIRPATH home/${DOCKER_USER_}
WORKDIR $DIRPATH

# ユーザ設定
RUN useradd ${DOCKER_USER_}\
	&& chown -R ${DOCKER_USER_} /${DIRPATH}
USER ${DOCKER_USER_}