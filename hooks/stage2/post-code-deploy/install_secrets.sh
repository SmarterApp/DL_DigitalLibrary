#!/bin/bash
# vim: ts=4:sw=4:et

if [ "${AH_SITE_ENVIRONMENT:-x}" != "x" ]; then
    D_SYSTEM=acquia
    D_GROUP=$AH_SITE_GROUP
    D_ENV=$AH_SITE_ENVIRONMENT
    D_DEST=/mnt/files/$D_GROUP.$D_ENV/files-private
    D_TMP=/mnt/tmp/$D_GROUP.$D_ENV
elif [ -d /sbac ]; then
    D_SYSTEM=dd
    D_GROUP=sbac
    D_ENV=dev
    D_DEST=/sbac/$D_ENV/cms/src/docroot/sites/default/files-private
    D_TMP=/tmp
else
    echo 'ERROR: Could not determine system.'
    exit 1
fi

D_SITE=$D_GROUP.$D_ENV
D_SRC=$D_SYSTEM/$D_GROUP/$D_ENV
D_KEY=${D_SRC//\//-}


cd $D_TMP
if [ -d configs ]; then
    cd configs
    git pull
    cd ..
else
    ssh-keygen -F bitbucket.org >&/dev/null
    if [ $? -ne 0 ]; then
      ssh-keyscan bitbucket.org >> $HOME/.ssh/known_hosts
    fi
    git clone git@bitbucket.org:pcgsbacdev/sbac-configs.git configs/
fi

if [ ! -d configs ]; then
    echo 'The configs directory could not be found'
    exit 1
fi

cd configs

cp $HOME/$D_KEY.key ./

./bin/decrypt.sh
rsync -a --exclude '*.enc' --exclude '.*' secrets/$D_SRC/ $D_DEST/
