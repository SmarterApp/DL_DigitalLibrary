# vim: sw=2:ts=2:et
Feature: Playlist
	As any Resource Contributor I should see a link to the updated Cover Profile Guide (June 2016)

  @javascript
  Scenario: Log in as a resource contributor and see Cover Profile Guide link
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
    Then I should see "Cover Profile Guide"
		
		Then the "#submission-general-guidelines .MsoNormal" element should contain "href=\"/sites/all/themes/custom/sbac/workflow_resources/Cover_Profile_Guide_Playlists_June2016.pdf\""

#As any Resource Contributor I should see a link to the updated Cover Profile Guide (June 2016)