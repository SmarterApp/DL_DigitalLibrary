#!/bin/bash

# Create users and add appropriate roles using drush

if [ $# -eq 0 ]; then
  echo "Usage: $0 <drush_alias>"
  echo
  echo "drush_alias is of the form 'site.env' like 'sbac.dev'"
  exit 1
fi

drush_alias=$1

drush @$drush_alias sa
if [ $? -ne 0 ]; then
  echo "The alias '${drush_alias}' does not seem to exist"
  exit 2
fi

cd $(dirname $0)

INPUT=config/users.csv

[ ! -f $INPUT ] && { echo "$INPUT file not found"; exit 1; }

while IFS=, read email role
do
  drush @$drush_alias user-create "$email" --mail="$email" </dev/null
  drush @$drush_alias user-add-role $role "$email" </dev/null
done < $INPUT
