AN OVERVIEW OF SBAC
-------------------
This project allows for instructors to share learning materials. Materials can be added by approved accounts, and then undergo a review process prior to publishing to be public on site. Multiple roles are defined by the codebase.

The logic is contained primarily in the sites/all/modules directory, and is comprised of contrib and custom modules. Some logic is handled in the theme layer, using a mixture of custom templates, and js to manipulate output. At present, the Digital Library Resources page is returning results from an instance of Apache Solr, with filters being placed via tpl, while the Forums page is using the previous iteration of search, comprised of custom logic created by development prior to CivicActions / Amplify engagement.

CIVICACTIONS CUSTOMIZATIONS
---------------------------
The majority of the work CivicActions performed was to the homepage, notifications, and the Digital Library Resources page search.

In order to make modifications or change the logic within the homepage, please see the sbac_landing_page module.

Notifications are controlled via contrib modules message stack, and sbac_email, which is used for pushing user notifications. There is the an unsupported contrib module, Taskit, which is used for creating some of the logic for populating user alerts and internal notifications.

The Digital Library Resources page is controlled by sbac_digital_library_resources, and pull data from an Apache Solr instance, defined in admin.

sbac_alerts is used for creating sitewide alerts that appear on the homepage, and can be added via Content -> Alerts in the admin menu.

sbac_content_types/sbac_help is used for creating help pages, with links appearing on the Homepage, and can be added via Content -> Help in the admin menu.


TESTING
-------
A formal testing framework needs to be implemented. Recommended approach is to use Behat in conjunction with Jenkins for task management.
A successful setup would use Gherkin for writing test steps, with classes provided by Behat, and user defined customizations. For javascript testing / dom traversal, it is recommended to use phantom.js and Selenium to assist Mink. Ideally, tests will be preserved in git, and trigger Jenkins builds when deployed. Jenkins will then indicate if steps defined have passed, and if not, point to the tests that have failed.

Helpful sources for setup:
http://docs.behat.org/en/v3.0/
https://jenkins-ci.org/
https://github.com/NuCivic/nucivic-process/wiki/Setup-Jenkins-Build-to-update-code-and-run-Behat-Test
