# vim: sw=2:ts=2:et
Feature: Playlist user cleanup
	As an admin I should be able to delete users required for playlist tests

  @javascript
  Scenario: Log in as admin and delete test_basic_end_user user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/users/testbasicenduser"
    Then I press "Cancel account"
    Then I should see "When cancelling the account"

    Then I select "user_cancel_delete" from "user_cancel_method"
    
    Then I press "Cancel account"

    Given I wait for AJAX to finish
    Then I should be on "admin/people"

  @javascript
  Scenario: Log in as admin and delete test_resource_reviewer user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/users/testresourcereviewer"
    Then I press "Cancel account"
    Then I should see "When cancelling the account"

    Then I select "user_cancel_delete" from "user_cancel_method"
    
    Then I press "Cancel account"

    Given I wait for AJAX to finish
    Then I should be on "admin/people"

  @javascript
  Scenario: Log in as admin and delete test_resource_contributor user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/users/testresourcecontributor"
    Then I press "Cancel account"
    Then I should see "When cancelling the account"

    Then I select "user_cancel_delete" from "user_cancel_method"
    
    Then I press "Cancel account"

    Given I wait for AJAX to finish
    Then I should be on "admin/people"

  @javascript
  Scenario: Log in as admin and delete test_omni_user user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/users/testomniuser"
    Then I press "Cancel account"
    Then I should see "When cancelling the account"

    Then I select "user_cancel_delete" from "user_cancel_method"
    
    Then I press "Cancel account"

    Given I wait for AJAX to finish
    Then I should be on "admin/people"
#As an admin I delete users required for playlist tests