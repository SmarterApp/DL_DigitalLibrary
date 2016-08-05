# vim: sw=2:ts=2:et
Feature: Playlist
	As a non-SLT Resource Contributor I should be able to log in and not add a resource as a Playlist resource type.

  @javascript
  Scenario: Log in as a non-SLT resource contributor and not see playlist option
    Given I am on the homepage
    When I fill in the following:
      # Update credentials for a non-SLT Resource Contributor when available
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I follow "My Resources" in the "nav" region
    Then I should be on "/my-resources"
    Then I should see "Create New"
    Then I press "Create New"
    Then I press "Resource"

    Given I wait for AJAX to finish
    Then I should see see "You're About to Create a Resource"
    Then I press "Continue"

    Given I wait for AJAX to finish
    Then I should not see "Playlist"

#As a non-SLT Resource Contributor I should be able to log in and not add a resource as a Playlist resource type.