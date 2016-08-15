# vim: sw=2:ts=2:et
Feature: Playlist
	As an SLT Resource Contributor I should be able to log in and add a resource as a Playlist resource type.

  @javascript
  Scenario: Log in as an SLT resource contributor and see playlist option
    Given I am on the homepage
    When I fill in the following:
      | Email Address | playlist_creator |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I click "My Resources"
    Then I should be on "/my-resources"
    Then I should see "Create New"
    Then I click "Create New"

    Given I wait for AJAX to finish
    Then I should see "You're About to Create a Resource"
		Then I wait for 2 seconds
    Then I press "edit-submit--2"

    Given I wait for AJAX to finish
    Then I should see "Playlist" in the "resource_form" region
    When I select "78306" from "field_focus[und]"

    Given I wait for AJAX to finish
    Then I should see "You are About to Create a Playlist"
		And I should see "playlist template"

#As an SLT Resource Contributor user, I should be able to log in and add a resource as a Playlist resource type.