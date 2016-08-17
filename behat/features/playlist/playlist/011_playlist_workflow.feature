# vim: sw=2:ts=2:et
Feature: Playlist
	As a playlist creator I should be able to create a playlist required for further playlist tests

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
    And I wait for the "#sbac-help-resource-help-form" element to Appear
    Then I wait for 2 seconds
    Then I should see "You're About to Create a Resource"
		Then I wait for 2 seconds
    Then I press "edit-submit--2"

    Given I wait for AJAX to finish
    Then I should see "Playlist" in the "resource_form" region
    When I select "78306" from "field_focus[und]"

    Given I wait for AJAX to finish
    Then I should see "You are About to Create a Playlist"
		And I should see "playlist template"
    Then I wait for 2 seconds
    Then I press "playlist-modal-continue"

    When I fill in the following:
      | title  | Playlist Test 12345  |
      | field_connection_to_fap[und][0][value]  | Lorem ipsum dolor sit amet  |
      | field_student_agency[und][0][value]  | Lorem ipsum dolor sit amet  |
      | field_alt_body[und][0][value]  | Lorem ipsum dolor sit amet  |

    And I the set the chosen element "edit-field-intended-end-user-und" to "Parent"
    And I check "field_attributes[und][81]"
    Then I press "edit-submit"

    Then I wait for 4 seconds
    Then I click "Materials"
    Given I wait for AJAX to finish
    Then I wait for the "#edit-field-embed-video" element to Appear
    Then I wait for 2 seconds
    Then I fill in the following:
      | field_embed_video | https://www.youtube.com/watch?v=qw_xBwkPAjo |
    Then I press "Add Embedded Video"
    Given I wait for AJAX to finish
    And I wait for the "#sbac-media-internet-confirm-form" element to Appear
    Then I wait for 2 seconds
    And I press "Embed Video"

    Given I wait for AJAX to finish
    And I wait for the ".delete-media" element to Appear
    Then I wait for 2 seconds
    Then I check "field_pii[und][1]"
    And I press "edit-save-continue"

    Given I wait for AJAX to finish
    And I wait for the "#submission-summary-guidelines" element to Appear
    Then I wait for 10 seconds
    Then I the set the chosen element "field_subject[und][]" to "ELA - Writing"
    And I the set the chosen element "field_grades[und][]" to "Grade 1"

    Then I fill in the following:
      | field_connection_to_ccss[und][0][value] | Lorem Ipsum dolor sit amet |
      | field_learning_goals[und][0][value] | Lorem Ipsum dolor sit amet |
      | field_success_criteria[und][0][value] | Lorem Ipsum dolor sit amet |
      | field_contexts[und][0][value] | Lorem Ipsum dolor sit amet |
      | field_supporting_evidence[und][0][value] | Lorem Ipsum dolor sit amet |
      | field_principles[und][0][value] | Lorem Ipsum dolor sit amet |
    Then I press "edit-save-continue"

    Given I wait for AJAX to finish
    And I wait for the "#submission-tags-guidelines" element to Appear
    Then I wait for 10 seconds
    Then I the set the chosen element "field_digital_media_type[und][]" to "Video"
    Then I press "Save"

    Given I wait for AJAX to finish
    Then I wait for 2 seconds
    Then I press "edit-save-continue"

    Given I wait for AJAX to finish
    And I wait for the "#sbac-resource-submit-resource-form" element to Appear
    Then I wait for 4 seconds
    Then I should see "To continue, confirm that you wish to submit this resource"
    Then I press "edit-submit-overlay"

#As a playlist creator I should be able to create a playlist required for further playlist tests.