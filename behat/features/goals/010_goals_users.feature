# vim: sw=2:ts=2:et
Feature: Playlist user creation
	As an admin I should be able to set up users required for playlist tests

  @javascript
  Scenario: Log in as admin and create test_basic_end_user user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/admin/people/create"
    When I fill in the following:
    | Name | Test Basic End User |
    | field_last_name[und][0][value] | Basic |
    | Username | test_basic_end_user |
    | E-mail address | test_basic_end_user@mailinator.com |
    | edit-pass-pass1 | password |
    | edit-pass-pass2 | password |
		And I check "roles[25]"
    And I select "229" from "field_position[und]"

    And I click "Expertise"

    Given I wait for AJAX to finish
		When I the set the chosen element "edit-field-subject-s-und" to "ELA - Reading Literature"
		And I the set the chosen element "edit-field-grade-level-s-und" to "Grade 1"
		And I the set the chosen element "edit-field-special-populations-und" to "All Students"

    And I press "Create new account"

    Then I should see "Created a new user account"

    Then I go to "/user/logout"
    
    Given I am on the homepage
    When I fill in the following:
      | Email Address | test_basic_end_user |
      | Password | password |
    And press "Log into the Digital Library"

    Then I should see "Terms of Service"
    Then I check "legal_accept"
    Then I press "Continue to Digital Library"
    
    Then I should be on the homepage

  @javascript
  Scenario: Log in as admin and create test_resource_reviewer user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/admin/people/create"
    When I fill in the following:
    | Name | Test Resource Reviewer |
    | field_last_name[und][0][value] | Reviewer |
    | Username | test_resource_reviewer |
    | E-mail address | test_resource_reviewer@mailinator.com |
    | edit-pass-pass1 | password |
    | edit-pass-pass2 | password |
		And I check "roles[17]"
    And I check "field_slt_member[und]"
    And I select "229" from "field_position[und]"

    And I click "Expertise"

    Given I wait for AJAX to finish
		When I the set the chosen element "edit-field-subject-s-und" to "ELA - Reading Literature"
		And I the set the chosen element "edit-field-grade-level-s-und" to "Grade 1"
		And I the set the chosen element "edit-field-special-populations-und" to "All Students"

    And I press "Create new account"

    Then I should see "Created a new user account"

    Then I go to "/user/logout"
    
    Given I am on the homepage
    When I fill in the following:
      | Email Address | test_resource_reviewer |
      | Password | password |
    And press "Log into the Digital Library"

    Then I should see "Terms of Service"
    Then I check "legal_accept"
    Then I press "Continue to Digital Library"
    
    Then I should be on the homepage

  @javascript
  Scenario: Log in as admin and create test_resource_contributor user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/admin/people/create"
    When I fill in the following:
    | Name | Test Resource Contributor |
    | field_last_name[und][0][value] | Contributor |
    | Username | test_resource_contributor |
    | E-mail address | test_resource_contributor@mailinator.com |
    | edit-pass-pass1 | password |
    | edit-pass-pass2 | password |
		And I check "roles[15]"

    And I select "229" from "field_position[und]"

    And I click "Expertise"

    Given I wait for AJAX to finish
		When I the set the chosen element "edit-field-subject-s-und" to "ELA - Reading Literature"
		And I the set the chosen element "edit-field-grade-level-s-und" to "Grade 1"
		And I the set the chosen element "edit-field-special-populations-und" to "All Students"

    And I press "Create new account"

    Then I should see "Created a new user account"

    Then I go to "/user/logout"
    
    Given I am on the homepage
    When I fill in the following:
      | Email Address | test_resource_contributor |
      | Password | password |
    And press "Log into the Digital Library"

    Then I should see "Terms of Service"
    Then I check "legal_accept"
    Then I press "Continue to Digital Library"
    
    Then I should be on the homepage

  @javascript
  Scenario: Log in as admin and create test_omni_user user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/admin/people/create"
    When I fill in the following:
    | Name | Test Omni User |
    | field_last_name[und][0][value] | Reviewer |
    | Username | test_omni_user |
    | E-mail address | test_omni_user@mailinator.com |
    | edit-pass-pass1 | password |
    | edit-pass-pass2 | password |
		And I check "roles[17]"
		And I check "roles[25]"
		And I check "roles[15]"

    And I select "229" from "field_position[und]"

    And I click "Expertise"

    Given I wait for AJAX to finish
		When I the set the chosen element "edit-field-subject-s-und" to "ELA - Reading Literature"
		And I the set the chosen element "edit-field-grade-level-s-und" to "Grade 1"
		And I the set the chosen element "edit-field-special-populations-und" to "All Students"

    And I press "Create new account"

    Then I should see "Created a new user account"

    Then I go to "/user/logout"
    
    Given I am on the homepage
    When I fill in the following:
      | Email Address | test_omni_user |
      | Password | password |
    And press "Log into the Digital Library"

    Then I should see "Terms of Service"
    Then I check "legal_accept"
    Then I press "Continue to Digital Library"
    
    Then I should be on the homepage
#As an admin I create users required for playlist tests