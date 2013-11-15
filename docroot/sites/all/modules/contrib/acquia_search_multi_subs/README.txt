This module allows you to switch between Acquia Search cores manually or
automatically.

To start you should go to admin/config/search/apachesolr/settings and click the
Acquia Search environment. Click "Edit" to modify the properties of this
environment. By default the module will be enabled and it will detect if you
are entitled to multiple cores.

To verify if you have multiple cores available, you can deselect the
"Automatically switch when an Acquia Environment is detected" checkbox and it
will show you a list of the search cores that are available for the subscription
that you connected with using the Acquia Connector.

If you want to test the switching locally add the following to your settings.php

$_ENV['AH_SITE_NAME'] = 'subscriptionnamedev';
$_ENV['AH_SITE_ENVIRONMENT'] = 'dev';

You can find this variable when you use your drush aliases to connect to your
Acquia Server like this.

dsm($_ENV['AH_SITE_ENVIRONMENT']);
dsm($_ENV['AH_SITE_NAME']);

Alternatively you could fill in data from another subscription so that it takes
over your Acquia Search environment without disturbing the connection to the
Acquia Connector / Acquia Insight.