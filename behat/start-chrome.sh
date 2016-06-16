#!/bin/bash

cd $(dirname $0)

. ./../local-dev/.env

exec docker run -d --net=${COMPOSE_PROJECT_NAME}_default \
    --name selenium \
    -v /dev/shm:/dev/shm \
    -p 5900:5900 \
    selenium/standalone-chrome-debug
