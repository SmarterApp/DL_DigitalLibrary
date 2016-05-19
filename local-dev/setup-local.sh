#!/bin/bash

cd $(dirname $0)

. ./.env

cd ..

echo 'Install code via composer'
PWD=$(pwd)
DIR=/var/www/html
docker run --rm -v ${PWD}:${DIR} -w ${DIR} composer/composer install

echo 'Apply patches'
# Patch for issue where get_resources() is redefined
patch -p1 < local-dev/patches/001-sbac_report.patch
cp local-dev/templates/settings.php docroot/sites/default/
cp local-dev/templates/local_settings.inc docroot/sites/default/
ln -s contrib/zurb_foundation docroot/sites/all/themes/zurb_foundation
ln -s custom/SBAC docroot/sites/all/themes/SBAC
mkdir -m 0777 docroot/sites/default/files
mkdir -m 0777 docroot/sites/default/files-private

cd $(dirname $0)

echo 'Bring up containers'
docker-compose up -d

echo 'Load Example DB'
./load-example-db.sh

echo 'Adjust settings via drush'
./exec-drush dis google_analytics sbac_sso acquia_spi learning_registry
./exec-drush user-password admin --password="password"
./exec-drush vset reroute_email_address beads2nibs@mailinator.com
./exec-drush vset reroute_enable 1

./exec-drush cc all


echo
echo
echo 'Setup complete:'
echo
echo 'You can connect to http://localhost:' $(docker inspect --format '{{ (index (index .NetworkSettings.Ports "80/tcp") 0).HostPort }}' ${COMPOSE_PROJECT_NAME}_nginx_1) '//'
