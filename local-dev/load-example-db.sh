#!/bin/sh

cd $(dirname $0)

. ./.env

if [ ! -f cache/sbac.sql.gz ]; then
  docker run --rm -v "$(pwd)/cache:/dls:rw" appropriate/curl -fsSL -o /dls/sbac.sql.gz https://bitbucket.org/pcgsbacdev/sample-db/raw/4d22ba06bb7a5544ea81a32141ab54afdd1cb345/sbac.sql.gz
  if [ ! -f cache/sbac.sql.gz ]; then
    echo 'Error downloading sql file'
    exit 1
  fi
fi

./exec-drush sql-drop -y
gzip -dc cache/sbac.sql.gz \
  | docker exec -i ${COMPOSE_PROJECT_NAME}_db_1 sh -c 'exec mysql -uroot -p"${MYSQL_ROOT_PASSWORD}" cms'
