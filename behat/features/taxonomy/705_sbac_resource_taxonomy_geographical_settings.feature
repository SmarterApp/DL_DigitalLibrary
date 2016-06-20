# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Geographic Settings
	As an admin user I should be able to view the Geographic Settings taxonomy with correct terms

  Scenario: Log in and go to "Geographic Settings taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/geographical_settings"
    Then I should see "Urban"
    And I should see "Suburban"
    And I should see "Rural"

#As #1 user, view Geographic Settings taxonomy, see the correct terms