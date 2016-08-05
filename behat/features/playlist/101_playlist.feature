# vim: sw=2:ts=2:et
Feature: Playlist
	As any Resource Contributor I should see a link to the updated Cover Profile Guide (June 2016)

  @javascript
  Scenario: Log in as a resource contributor and see Cover Profile Guide link
    Given I am on the homepage
    When I fill in the following:
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
    # Update to check link is correct when it exists
    Then I should see "Cover Profile Guide"

#As any Resource Contributor I should see a link to the updated Cover Profile Guide (June 2016)