FROM ubuntu:20.04

# ユーザーを作成
ARG DOCKER_USER_=guest

ARG APT_LINK=http://www.ftp.ne.jp/Linux/packages/ubuntu/archive/
RUN sed -i "s-$(cat /etc/apt/sources.list | grep -v "#" | cut -d " " -f 2 | grep -v "security" | sed "/^$/d" | sed -n 1p)-${APT_LINK}-g" /etc/apt/sources.list

ENV DEBIAN_FRONTEND noninteractive

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