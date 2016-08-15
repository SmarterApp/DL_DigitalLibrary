# vim: sw=2:ts=2:et
Feature: Playlist
	As an SLT Resource Reviewer I should be able to log in see the Quality Criteria workflow specific to playlists

  @javascript
  Scenario: Log in as an SLT resource reviewer and see the Quality Criteria workflow specific to playlists
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

		#Playlist is visible to review
		Given I wait for AJAX to finish
		Then I wait for the ".resource-card" element to Appear
    Then I should see "Playlist Test 12345"

		#Begin gate keeping review
		Then I click on the element ".playlist-test-12345"

    Given I wait for AJAX to finish
		And I wait for the ".ui-dialog-titlebar" element to Appear
		Then I wait for 4 seconds
    Then I press "Start Review (72 hrs)"

		Given I wait for AJAX to finish
		And I wait for the ".helpful-info-content" element to appear
		Then I should see "Gate-Keeping Guide"
		
    When I fill in the following:
      | field_quality_set[und][0][field_comments][und][0][value]  | Lorem ipsum dolor sit amet  |
      | field_quality_set[und][1][field_comments][und][0][value]  | Lorem ipsum dolor sit amet  |
      | field_quality_set[und][2][field_comments][und][0][value]  | Lorem ipsum dolor sit amet  |
		  | field_quality_set[und][3][field_comments][und][0][value]  | Lorem ipsum dolor sit amet  |
		  | field_quality_set[und][4][field_comments][und][0][value]  | Lorem ipsum dolor sit amet  |
		  | field_quality_set[und][5][field_comments][und][0][value]  | Lorem ipsum dolor sit amet  |
		  | field_quality_set[und][6][field_comments][und][0][value]  | Lorem ipsum dolor sit amet  |

		And I select "1" from "field_quality_set[und][0][field_meets_criterion][und]"
		And I select "1" from "field_quality_set[und][1][field_meets_criterion][und]"
		And I select "1" from "field_quality_set[und][2][field_meets_criterion][und]"
		And I select "1" from "field_quality_set[und][3][field_meets_criterion][und]"
		And I select "1" from "field_quality_set[und][4][field_meets_criterion][und]"
		And I select "1" from "field_quality_set[und][5][field_meets_criterion][und]"
		And I select "1" from "field_quality_set[und][6][field_meets_criterion][und]"

		Then I press "edit-meet-button"

		Given I wait for AJAX to finish
		And I wait for the "#feedback-gate-keeper-form" element to Appear
		Then I wait for 4 seconds
		Then I should see "This resource meets all Gate-Keeping criteria."
		Then I press "edit-submit--5"

		#Begin Quality Critera Review
    Given I wait for AJAX to finish
		And I wait for the "#eck-entity-form-edit-feedback-qc" element to Appear
    Then I should see "Educator Learning Guide and Resource Playlist"
    And I should see "The Playlist topic is aligned with the intent of the Common Core State Standards"
		And I should see "The Playlist has thoughtfully been put together"
    And I should see "Quality Criterion Level"
    And I should see "Comments"
    And I should see "Recommend"
		And I should see "Do Not Recommend"
    And I should see "Rationale for Recommendation"
    And I should see "Cancel Review"
		And I should see "Save and Close"
		And I should see "Complete Review"

#As an SLT Resource Reviewer I should be able to log in see the Quality Criteria workflow specific to playlists