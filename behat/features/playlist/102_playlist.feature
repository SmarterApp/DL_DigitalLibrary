# vim: sw=2:ts=2:et
Feature: Playlist
	As a non-SLT Resource Contributor I should be able to log in and not add a resource as a Playlist resource type.

  @javascript
  Scenario: Log in as a non-SLT resource contributor and not see playlist option
    Given I am on the homepage
    When I fill in the following:
      # Update credentials for a non-SLT Resource Contributor when available
      | Email Address | noplaylist_contributor |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I click "My Resources"
    Then I should be on "/my-resources"
    Then I should see "Create New"
    Then I click "Create New"

    Given I wait for AJAX to finish
    Then I should see "You're About to Create a Resource"
		Then I wait for the "edit-submit--2" element to Appear
    Then I press "edit-submit--2"

    Given I wait for AJAX to finish
    Then I should not see "Playlist" in the "resource_form" region

#As a non-SLT Resource Contributor I should be able to log in and not add a resource as a Playlist resource type.