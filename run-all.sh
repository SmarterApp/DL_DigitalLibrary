#!/bin/bash

cd $(dirname $0)

./exec-behat exec ../behat/behat "$@"
