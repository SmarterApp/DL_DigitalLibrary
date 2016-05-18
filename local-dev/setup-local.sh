#!/bin/bash

cd $(dirname $0)

echo 'Bring up containers'
docker-compose up -d


cd ..

echo 'Install code via composer'
PWD=$(pwd)
DIR=/var/www/html
docker run --rm -v ${PWD}:${DIR} -w ${DIR} geshan/php-composer-alpine "composer install"

echo 'Apply patches'
# Patch for issue where get_resources() is redefined
patch -p1 < local-dev/patches/001-sbac_report.patch


cd $(dirname $0)

echo 'Load Example DB'
./load-example-db.sh

echo 'Adjust settings via drush'
./exec-drush dis google_analytics sbac_sso acquia_spi learning_registry
./exec-drush user-password admin --password="password"
./exec-drush vset reroute_email_address beads2nibs@mailinator.com
./exec-drush vset reroute_enable 1

./exec-drush cc all
