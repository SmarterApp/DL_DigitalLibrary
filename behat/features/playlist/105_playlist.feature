# vim: sw=2:ts=2:et
Feature: Playlist
	As an SLT Resource Reviewer I should be able to log in see the Quality Criteria workflow specific to playlists

  @javascript
  Scenario: Log in as an SLT resource reviewer and see the Quality Criteria workflow specific to playlists
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
    #update target for correct resource when available
    Then I press "Start Review"

    Given I wait for AJAX to finish
    Then I should see "You are about to start reviewing this resource"
    Then I press "Start Review"

    Given I wait for AJAX to finish
    Then I should see "Playlist Quality Criteria Review Guide"
    
    #Replace with actual targets
    And I should see 2 "Playlist quality criteria containers"
    And I should see number options 1-5 for both criteria
    And I should see a “Comments” field for both criteria
    And I should see the Recommend Options “Recommend” or “Do Not Recommend”
    And I should see a “Rationale for Recommendation” field
    And I should see the buttons “Cancel Review, “Save and close,” and “Complete Review”



#As an SLT Resource Reviewer I should be able to log in see the Quality Criteria workflow specific to playlists