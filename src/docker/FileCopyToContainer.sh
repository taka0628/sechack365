# !/bin/bash

FILE_PATH=$1
CONTAINER_NAME=$2

if [[ -z $FILE_PATH || -z $CONTAINER_NAME ]]; then

	echo "引数が空"
	exit 1

fi

docker container cp $FILE_PATH $CONTAINER_NAME:/home/guest/temp/
