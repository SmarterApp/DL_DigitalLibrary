# Behat Testing

## Introduction

With this project we will use [behat](https://behat.org) for some automated testing.

In order to run the tests on OSX one will need to install and run [Selenium](http://www.seleniumhq.org/download/)
and until Selenium is updated beyond v2.53.0 be sure to have [Firefox v45](https://download.mozilla.org/?product=firefox-45.2.0esr-SSL&os=osx&lang=en-US) installed.

When using Linux (local or Dimensions Data) one can start a Selenium docker instance
by running `./start-chrome.sh` in order to run the javascript tests inside a container.

To run the tests use `run-all.sh` in the behat/ directory.
  - `./run-all.sh` will run all the tests
  - `./run-all.sh --tags=@smoketest` will run the tests marked as smoke tests
  - `./run-all.sh --tags=~@javascript` will run the tests that do not need Selenium

The features to be tested are all under the behat/features directory and have been
broken up into more generalized categories to make it easier to create test suites.
