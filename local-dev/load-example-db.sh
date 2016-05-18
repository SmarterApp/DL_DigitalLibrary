#!/bin/sh

cd $(dirname $0)

. ./.env

if [ ! -f cache/sbac.sql.gz ]; then
  docker run --rm -v "$(pwd)/cache:/dls:rw" appropriate/curl -fsSL -o /dls/sbac.sql.gz https://github.com/SmarterApp/DigitalLibrary/raw/59ff35278b6c82273105af88f340079434f522a5/docroot/profiles/sbac/sbac.sql.gz
fi

./exec-drush sql-drop -y
gzip -dc cache/sbac.sql.gz \
  | docker exec -i ${COMPOSE_PROJECT_NAME}_db_1 sh -c 'exec mysql -uroot -p"${MYSQL_ROOT_PASSWORD}" cms'

