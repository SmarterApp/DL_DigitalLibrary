# vim: sw=2:ts=2:et
Feature: SBAC Help Taxonomy
	As an admin user I should be able to view the Help Page Topic and SBAC User Roles taxonomies 

  Scenario: Log in and go to "Help Page Topic taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/help_page_topic"
    Then I should see 3 ".term-id" elements

  Scenario: Log in and go to "SBAC User Roles taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/sbac_user_roles"
    Then I should see 17 ".term-id" elements

#As #1 user, view taxonomies, see the correct number of terms
