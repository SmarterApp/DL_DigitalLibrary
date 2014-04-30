/**
 * @file
 * README file for Google CDN.
 */

Google CDN

CONTENTS
--------

1.  Introduction
2.  Installation
3.  Configuration
4.  Using the module
5.  Troubleshooting
6.  Feature roadmap

----
1.  Introduction

Google CDN

----
1.1  Concepts

Google CDN allows you to replace the local file system with a cloud server via
Google Cloud Storage, utilizing their unlimited storage and blazing fast edge
caching. Files uploaded into Drupal will still be managed by Drupal, but
instead of being stored on the local server that is running Drupal, actual
files will be stored on Google Cloud Storage and delivered through there
high performance network.
----
2.  Installation

Install the module and enable it according to Drupal standards.

The module's configuration pages reside at:
- admin/config/media/google_cdn

The module's permissions are found at:
- admin/people/permissions

----
2.1  Requirements

OpenSSL Php Module - Required to handle Google authentication methods.
- http://www.php.net/manual/en/book.openssl.php
Private Directory
- The private directory must be configured as the p12 that is required
for Google's authentication is stored here for security reasons. As well,
a .pem file is created from this p12 key that is stored here. This file
is required for google's signing method.
https://developers.google.com/storage/docs/accesscontrol#Signed-URLs.

Google CDN requires:
- Libraries API
- XAutoLoad
- Google API PHP Client Library
(https://github.com/google/google-api-php-client)

----
3.  Configuration

Google CDN's configuration section is located at:

- Admin > Configuration > Media > Google CDN

This section allows the admin to configure settings that pertain to the
connection details and configuration of the module.

Download the two dependent modules and install them according to Drupal
standards. Download the Google API PHP library and place it in the
following location sites/all/libraries/google-api-php-client.
The main Google_Client.php file should be found at
sites/all/libraries/google-api-php-client/src/Google/Client.php.

----
3.1  Checking permissions

In order to configure the google cdn module the user must be given
the appropriate permission. Navigate to admin/people/permissions and
select Administer Google CDN under Google CDN for the
appropriate role.

----
4.  Using the module

Once the module is installed and permissions are configured, the administrator
should configure the Google CDN. Once the configuration options are inputted,
the admin can test the connection to ensure that the site is able to connect
to the Google bucket.

If the connection succeeds, the administrator can then select the File System
default download method to be the Google CDN. This makes the entire file system
upload and download all files to / from the Google Bucket.

As well, the admin can set the default download option on each file and image
field. This sets the specific field to use or not use the Google CDN as the
default upload and download method.

----
5.  Troubleshooting

* If the "Test Connection" admin button fails check the following:
- Check all details of the configuration and ensure they are correct
- Ensure the p12 key is saved on the file system
- Ensure the PEM file is created and saved on the file system

----
6.  Feature roadmap
- Create api to hook into specific areas
