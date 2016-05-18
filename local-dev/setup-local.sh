#!/bin/bash

cd $(dirname $0)
cd ..

# Patch for issue where get_resources() is redefined
patch -p1 < local-dev/patches/001-sbac_report.patch


cd $(dirname $0)

./exec-drush dis google_analytics sbac_sso acquia_spi learning_registry
./exec-drush user-password admin --password="password"
./exec-drush vset reroute_email_address beads2nibs@mailinator.com
./exec-drush vset reroute_enable TRUE

./exec-drush cc all
