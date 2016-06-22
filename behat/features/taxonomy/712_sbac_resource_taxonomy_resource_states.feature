# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Resource States
	As an admin user I should be able to view the Resource States taxonomy with correct terms

  Scenario: Log in and go to "Resource States taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/resource_states"
    Then I should see "Being Reviewed"
    And I should see "Draft"
    And I should see "In Review"
    And I should see "Needs Posting"
    And I should see "Needs Review"
    And I should see "Posted"
    And I should see "Removed"
    And I should see "Returned"
    And I should see "Submitted"

#As #1 user, view Resource States taxonomy, see the correct terms