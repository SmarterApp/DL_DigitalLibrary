# vim: sw=2:ts=2:et
Feature: Playlist
	As an SLT Resource Reviewer I should be able to log in and complete a Gatekeeping Review and a Quality Criteria Review of a playlist.

  Scenario: Log in as an SLT resource reviewer and see playlist resource review option
    Given I am on the homepage
    When I fill in the following:
      # Update credentials for an SLT Resource Reviewer when available
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I follow "Resource Review" in the "nav" region
    Then I should be on "/resource-review"
    
    #Update with correct resource name when available
    Then I should see "Playlist Resource"

#As an SLT Resource Reviewer I should be able to log in and complete a Gatekeeping Review and a Quality Criteria Review of a playlist.