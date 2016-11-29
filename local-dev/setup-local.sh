#!/bin/bash

cd $(dirname $0)
LDIR=$(pwd)

. ./.env

cd ..

echo 'Install code via composer'
./bin/composer install

echo 'Ensure files match what is in the repository'
git checkout -- docroot

echo 'Apply patches'
# Now committed as part of the module
## Patch for issue where get_resources() is redefined
#if [ "$(grep -c sbac_report_get_resources docroot/sites/all/modules/custom/sbac_report/sbac_report.resource_stats.inc)" -eq 0 ]; then
#  patch -p1 < local-dev/patches/001-sbac_report.patch
#fi

echo 'Install settings files'
if [ ! -d docroot/sites/default ]; then
  mkdir -m 0777 docroot/sites/default
fi
cp local-dev/templates/settings.php docroot/sites/default/
cp local-dev/templates/local_settings.inc docroot/sites/default/

# This appears to no longer be needed
## Create symlinks as currently the themes need to be at .../themes/ instead of .../themes/{contrib,custom}/
#if [ ! -h docroot/sites/all/themes/zurb_foundation ]; then
#  ln -s contrib/zurb_foundation docroot/sites/all/themes/zurb_foundation
#fi
#if [ ! -h docroot/sites/all/themes/SBAC ]; then
#  ln -s custom/SBAC docroot/sites/all/themes/SBAC
#fi

# Make sure the files directory exists
echo 'Ensure files and files-private exists'
if [ ! -d docroot/sites/default/files ]; then
  mkdir -m 0777 docroot/sites/default/files
fi
if [ ! -d docroot/sites/default/files-private ]; then
  mkdir -m 0777 docroot/sites/default/files-private
fi


cd $LDIR

echo 'Bring up containers'
docker-compose up -d

#echo 'Load Example DB'
#./load-example-db.sh
echo 'Load Pre-initialized DB'
./rsync-db.sh

echo 'Adjust settings via drush'
./exec-drush dis google_analytics acquia_spi learning_registry
#./exec-drush user-password admin --password="password"
./exec-drush vset reroute_email_address beads2nibs@mailinator.com
./exec-drush vset reroute_enable 1

./exec-drush updb -y
./exec-drush fra -y
./exec-drush cc all

#echo 'Load test users'
#./load-test-users.sh


echo
echo
echo 'Setup complete:'
echo
echo 'You can connect to the local MySQL instance using the IP 127.0.0.1 and the port '$(docker inspect --format '{{ (index (index .NetworkSettings.Ports "3306/tcp") 0).HostPort }}' ${COMPOSE_PROJECT_NAME}_db_1)
echo 'You can connect to http://localhost:'$(docker inspect --format '{{ (index (index .NetworkSettings.Ports "80/tcp") 0).HostPort }}' ${COMPOSE_PROJECT_NAME}_nginx_1)
