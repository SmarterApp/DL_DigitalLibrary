#!/bin/sh

cd $(dirname $0)

. ./.env

if [ ! -f cache/sbac.sql.gz ]; then
  docker run --rm -v "$(pwd)/cache:/dls:rw" appropriate/curl -fsSL -o /dls/sbac.sql.gz https://bitbucket.org/pcgsbacdev/sample-db/raw/4351aacd041c11a80887191be8c9d27c4f3844d2/sbac.sql.gz
  if [ ! -f cache/sbac.sql.gz ]; then
    echo 'Error downloading sql file'
    exit 1
  fi
fi

./exec-drush sql-drop -y
gzip -dc cache/sbac.sql.gz \
  | docker exec -i ${COMPOSE_PROJECT_NAME}_db_1 sh -c 'exec mysql -ucms -p"${MYSQL_PASSWORD}" cms'
