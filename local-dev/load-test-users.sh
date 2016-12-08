#!/bin/bash

# Create users and add appropriate roles using drush

cd $(dirname $0)

INPUT=config/users.csv

[ ! -f $INPUT ] && { echo "$INPUT file not found"; exit 1; }

while IFS=, read email role
do
  ./exec-drush user-create "$email" --mail="$email" </dev/null
  ./exec-drush user-add-role "$role" "$email" </dev/null
done < $INPUT
