
CONTENTS OF THIS FILE
---------------------

 * About Drupal
 * Configuration and features
 * Installation Instructions
 * Appearance
 * Developing for Drupal

ABOUT DRUPAL
------------

Drupal is an open source content management platform supporting a variety of
websites ranging from personal weblogs to large community-driven websites. For
more information, see the Drupal website at http://drupal.org/, and join the
Drupal community at http://drupal.org/community.

Legal information about Drupal:
 * Know your rights when using Drupal:
   See LICENSE.txt in the same directory as this document.
 * Learn about the Drupal trademark and logo policy:
   http://drupal.com/trademark

CONFIGURATION AND FEATURES
--------------------------

Drupal core (what you get when you download and extract a drupal-x.y.tar.gz or
drupal-x.y.zip file from http://drupal.org/project/drupal) has what you need to
get started with your website. It includes several modules (extensions that add
functionality) for common website features, such as managing content, user
accounts, image uploading, and search. Core comes with many options that allow
site-specific configuration. In addition to the core modules, there are
thousands of contributed modules (for functionality not included with Drupal
core) available for download.

More about configuration:
 * Install, upgrade, and maintain Drupal:
   See INSTALL.txt and UPGRADE.txt in the same directory as this document.
 * Learn about how to use Drupal to create your site:
   http://drupal.org/documentation
 * Download contributed modules to sites/all/modules to extend Drupal's
   functionality:
   http://drupal.org/project/modules
 * See also: "Developing for Drupal" for writing your own modules, below.

INSTALLATION INSTRUCTIONS
---------------------

To install this edition of the Digital Library first ensure you have PHP 5.2.5 or higher (5.4 or higher recommended) as well as MySQL 5.0.15 or higher (or MySQL 5.1.30 or higher), and the PDO database extension for PHP installed to your web server.

The root of this GIT contains a SQL dump which you must then restore to a database on your MySQL Server as follows:

mysql -u root -p[root_password] [database_name] < DigitalLibrary.sql

Subsequently, direct your web browser to the root of the site which will activate the installation script. Choose a “Standard” installation.

Next, direct the installation process to the database you preformed the SQL dump restore to and provide login credentials then click “Save and Continue”.

You’ll see a message which says “Drupal already installed”. From there simply click the link “View your existing site.” and you’ll be directed to the Digital Library login screen. The user credentials “admin/password” will provide you access.

The Digital Library relies on Google Cloud Storage to deliver content and this dependency requires these configuration additions (with set values) to be added to the site’s settings.php file to function.


$conf['google_cdn_bucket_name'] = '';
$conf['google_cdn_extensions'] = '';
$conf['google_cdn_client_id'] = '';
$conf['google_cdn_service_account_name'] = '';
$conf['google_cdn_signed_url_expiry'] = 300;
$conf['google_cdn_library_version'] = 2;
$conf['oscaddie_gcs_bucket_name'] = '';
$conf['oscaddie_gcs_extensions'] = '';
$conf['oscaddie_gcs_client_id'] = '';
$conf['oscaddie_gcs_service_account_name'] = '';


APPEARANCE
----------

In Drupal, the appearance of your site is set by the theme (themes are
extensions that set fonts, colors, and layout). Drupal core comes with several
themes. More themes are available for download, and you can also create your own
custom theme.

More about themes:
 * Download contributed themes to sites/all/themes to modify Drupal's
   appearance:
   http://drupal.org/project/themes
 * Develop your own theme:
   http://drupal.org/documentation/theme

DEVELOPING FOR DRUPAL
---------------------

Drupal contains an extensive API that allows you to add to and modify the
functionality of your site. The API consists of "hooks", which allow modules to
react to system events and customize Drupal's behavior, and functions that
standardize common operations such as database queries and form generation. The
flexible hook architecture means that you should never need to directly modify
the files that come with Drupal core to achieve the functionality you want;
instead, functionality modifications take the form of modules.

When you need new functionality for your Drupal site, search for existing
contributed modules. If you find a module that matches except for a bug or an
additional needed feature, change the module and contribute your improvements
back to the project in the form of a "patch". Create new custom modules only
when nothing existing comes close to what you need.

More about developing:
 * Search for existing contributed modules:
   http://drupal.org/project/modules
 * Contribute a patch:
   http://drupal.org/patch/submit
 * Develop your own module:
   http://drupal.org/developing/modules
 * Follow best practices:
   http://drupal.org/best-practices
 * Refer to the API documentation:
   http://api.drupal.org/api/drupal/7
