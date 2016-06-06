#!/bin/sh

cd $(dirname $0)

. ./.env

if [ ! -f cache/sbac.sql.gz ]; then
  docker run --rm -v "$(pwd)/cache:/dls:rw" appropriate/curl -fsSL -o /dls/sbac.sql.gz https://s3.amazonaws.com/uploads.hipchat.com/519721/3548552/2KeuTLLk3OH2acM/local-db-20160606T1130.sql.gz
fi

./exec-drush sql-drop -y
gzip -dc cache/sbac.sql.gz \
  | docker exec -i ${COMPOSE_PROJECT_NAME}_db_1 sh -c 'exec mysql -uroot -p"${MYSQL_ROOT_PASSWORD}" cms'

