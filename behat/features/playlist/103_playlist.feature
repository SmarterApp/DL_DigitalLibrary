# vim: sw=2:ts=2:et
Feature: Playlist
	As an SLT Resource Reviewer I should be able to log in and complete a Gatekeeping Review and a Quality Criteria Review of a playlist.

  @javascript
  Scenario: Log in as an SLT resource reviewer and see playlist resource review option
    Given I am on the homepage
    When I fill in the following:
      | Email Address | playlist_reviewer |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I click "Resource Review"
    Then I should be on "/resource-review"
    Then I click on the element "#filter-header-14"
		Then I wait for the "#14:78306_anchor" element to Appear
		Then I click "14:78306_anchor"
		Then I wait for the "#sbac-search-filter-button" element to Appear

		Then I press "sbac-search-filter-button"

		Given I wait for AJAX to finish
		Then I wait for the ".resource-card" element to Appear
    Then I should see "Playlist Test 12345"

#As an SLT Resource Reviewer I should be able to log in and complete a Gatekeeping Review and a Quality Criteria Review of a playlist.