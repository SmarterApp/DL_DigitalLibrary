#!/bin/bash

cd $(dirname $0)

if [ -d /sbac ]; then
    eval $(weave env)
    . ../../../env.sh
    DOCKER_NET=""
    DOCKER_PHPFPM="${CMS_DEPLOYMENT}-phpfpm"
else
    . ./../local-dev/.env
    DOCKER_NET="--net=${COMPOSE_PROJECT_NAME}_default"
    DOCKER_PHPFPM="${COMPOSE_PROJECT_NAME}_phpfpm_1"
    MYSQL_HOST=db
fi

exec docker run -d ${DOCKER_NET} \
    --name selenium \
    -v /dev/shm:/dev/shm \
    -p 5900:5900 \
    selenium/standalone-chrome-debug
