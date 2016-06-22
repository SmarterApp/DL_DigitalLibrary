# vim: sw=2:ts=2:et
Feature: SBAC Help Taxonomy Help Page Topic
	As an admin user I should be able to view the Help Page Topic taxonomy with correct terms

  Scenario: Log in and go to "Help Page Topic taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/help_page_topic"
    Then I should see "Help Desk Contacts"
    And I should see "Resource Tutorial"
    And I should see "Welcome Tutorial"

#As #1 user, view Help Page Topic taxonomy, see the correct terms
