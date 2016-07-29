# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Age Range
	As an admin user I should be able to view the Age Range taxonomy with correct terms

  Scenario: Log in and go to "Age Range taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/age_range"
    Then I should see "0 - 3"
    And I should see "4 - 6"
    And I should see "7 - 10"

#As #1 user, view Age Range taxonomy, see the correct terms