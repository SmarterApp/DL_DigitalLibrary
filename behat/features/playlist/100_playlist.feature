# vim: sw=2:ts=2:et
Feature: Playlist
	As an SLT Resource Contributor I should be able to log in and add a resource as a Playlist resource type.

  @javascript
  Scenario: Log in as an SLT resource contributor and see playlist option
    Given I am on the homepage
    When I fill in the following:
      # Update credentials for an SLT Resource Contributor when available
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
    Then I should see "Playlist"
    Then I should press "Playlist"

    Given I wait for AJAX to finish
    I should see "You're About to Create a Playlist"
    Then I press "Continue"

    When I fill in the following:
      | Title | Playlist Test |
      | Specific Connection to the Formative Assessment Process | Lorem ipsum |
      | Student Engagement in the Formative Assessment Process | Lorem ipsum |
      | Resource Summary | Lorem Ipsum |
    And I select the following:
      | Intended End User(s) | Administrator |
    And I check the following:
      | Attributes of Formative Assessment Process | Elicit Evidence |
    Then I press "Continue"

    Given I wait for AJAX to finish
    I should see "Educator Learning Guide and Digital Library Resource Playlist Template"

#As an SLT Resource Contributor user, I should be able to log in and add a resource as a Playlist resource type.