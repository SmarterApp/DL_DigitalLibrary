#!/bin/bash

cd $(dirname $0)

. ./.env

docker-compose create db
docker-compose stop db
sleep 15

if [ -f cache/initialized.tar.bz2 ]; then
  echo 'Loading cached database'
  docker run --rm \
    -v ${COMPOSE_PROJECT_NAME}_mysql-data:/db \
    -v $(pwd)/cache:/cache \
    alpine sh -c 'rm -rf  /db/*; tar -xjf /cache/initialized.tar.bz2 -C /db .'
else
  if [ -f rsync.pwd ]; then
    RSYNC_PASSWORD=$(<rsync.pwd)
    export RSYNC_PASSWORD
  else
    echo 'You need to add the rsync password to rsync.pwd'
    exit 1
  fi
  
  echo 'Downloading database -- this may take a while'
  DOCKERHOST=ci.dev.edplancms.com \
    docker run --rm \
      -e RSYNC_PASSWORD \
      -e DOCKERHOST \
      -v ${COMPOSE_PROJECT_NAME}_mysql-data:/db \
      vimagick/rsyncd sh -c 'exec rsync -vrlPz --sparse --no-times --delete --no-perms anonymous@${DOCKERHOST}::db-init/ /db/'
  
  docker run --rm \
    -v ${COMPOSE_PROJECT_NAME}_mysql-data:/db \
    alpine sh -c 'chown -R 999:999 /db'
  
  echo 'Storing a cached version of the database -- this will take a while'
  docker run --rm \
    -v ${COMPOSE_PROJECT_NAME}_mysql-data:/db \
    -v $(pwd)/cache:/cache \
    alpine sh -c 'tar -cjf /cache/initialized.tar.bz2 -C /db .'
fi

docker-compose start db
sleep 15
