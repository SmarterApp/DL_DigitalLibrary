# vim: sw=2:ts=2:et
Feature: Goals
	As a resource contributor, resource reviewer, and/or basic end user I should be able to log in and use the goal setting interface

  @javascript
  Scenario: Log in as a resource reviewer, see default goals, edit goals, and see goal meter
    Given I am on the homepage
    When I fill in the following:
      | Email Address | test_resource_reviewer |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage
    Then I should see a ".nav-goals" element
    And I should see an ".star-rating-complete" element
    And I should see an ".resources-reviewed-complete" element
    And I should not see an ".resources-posted-complete" element    

    When I click "goals-link"
    Then I should be on "/users/test_resource_reviewer#profile-goals"
    Given I wait for AJAX to finish
    Then I wait for the "goals" region to appear
    Then I should see "Resources Reviewed Goal"
    And the "field_resources_reviewed_goal[und][0][value]" field should contain "9"

    Then I fill in the following:
      | edit-field-resources-reviewed-goal-und-0-value--2 | 10 |
    And press "edit-submit--2"

    Given I wait for the "goals" region to appear
    Then I should see "0 out of 10 completed"

    Then I fill in the following:
      | edit-field-resources-reviewed-goal-und-0-value--2 | 0 |
    And press "edit-submit--2"
    Given I wait for the "goals" region to appear
    Then I should not see "0 out of 0 completed"

#As a resource contributor, resource reviewer, and/or basic end user I should be able to log in and use the goal setting interface