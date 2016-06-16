# vim: sw=2:ts=2:et
Feature: Search
	As a user I should be able to search for resources

  Scenario: Log in and search as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage
    And I should see "What resources are you looking for?"

    When I click "Digital Library Resources"
		Then I should be on "/digital-library-resources"
    And I should see "Subjects:" in the "resource_list" region
    And I should see "Grades:" in the "resource_list" region
    And I should see "Media Types:" in the "resource_list" region

#As #1 user, find a resource, select a resource, make sure some metadata shows up
