SAML Service Provider
=====================

This package provides two modules:
- SAML Service Provider API
- SAML Drupal Login


The API module lets other modules leverage SAML authentication.

The SAML Drupal Login module specifically enables Drupal to become a "Service
Provider" for an IDP, so users can authenticate to Drupal (without entering a
username or password) by delegating authenticate to a SAML IDP (Identity
Provider).


Dependencies
============

Requires the OneLogin SAML-PHP toolkit, downloaded to the 'saml_sp/lib' folder:

`cd lib`
`git clone https://github.com/onelogin/php-saml.git .`

