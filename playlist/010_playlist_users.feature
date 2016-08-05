# vim: sw=2:ts=2:et
Feature: Playlist user creation
	As an admin I should be able to set up users required for playlist tests

  @javascript
  Scenario: Log in as admin and create playlist_creator user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/admin/people/create"
    When I fill in the following:
    | Name | Playlist Creator |
    | field_last_name[und][0][value] | Creator |
    | Username | playlist_creator |
    | E-mail address | playlist_creator@mailinator.com |
    | edit-pass-pass1 | password |
    | edit-pass-pass2 | password |
		And I check "roles[15]"
    And I check "roles[16]"
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
      | Email Address | playlist_creator |
      | Password | password |
    And press "Log into the Digital Library"

    Then I should see "Terms of Service"
    Then I check "legal_accept"
    Then I press "Continue to Digital Library"
    
    Then I should be on the homepage

  @javascript
  Scenario: Log in as admin and create playlist_reviewer user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/admin/people/create"
    When I fill in the following:
    | Name | Playlist Reviewer |
    | field_last_name[und][0][value] | Reviewer |
    | Username | playlist_reviewer |
    | E-mail address | playlist_reviewer@mailinator.com |
    | edit-pass-pass1 | password |
    | edit-pass-pass2 | password |
		And I check "roles[15]"
    And I check "roles[16]"
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
      | Email Address | playlist_reviewer |
      | Password | password |
    And press "Log into the Digital Library"

    Then I should see "Terms of Service"
    Then I check "legal_accept"
    Then I press "Continue to Digital Library"
    
    Then I should be on the homepage

  @javascript
  Scenario: Log in as admin and create resource_contributor user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/admin/people/create"
    When I fill in the following:
    | Name | No Playlist Contributor |
    | field_last_name[und][0][value] | Reviewer |
    | Username | noplaylist_contributor |
    | E-mail address | noplaylist_contributor@mailinator.com |
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
      | Email Address | noplaylist_contributor |
      | Password | password |
    And press "Log into the Digital Library"

    Then I should see "Terms of Service"
    Then I check "legal_accept"
    Then I press "Continue to Digital Library"
    
    Then I should be on the homepage

  @javascript
  Scenario: Log in as admin and create No Playlist Reviewer user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    Then I go to "/admin/people/create"
    When I fill in the following:
    | Name | No Playlist Reviewer |
    | field_last_name[und][0][value] | Reviewer |
    | Username | noplaylist_reviewer |
    | E-mail address | noplaylist_reviewer@mailinator.com |
    | edit-pass-pass1 | password |
    | edit-pass-pass2 | password |
		And I check "roles[17]"

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
      | Email Address | noplaylist_reviewer |
      | Password | password |
    And press "Log into the Digital Library"

    Then I should see "Terms of Service"
    Then I check "legal_accept"
    Then I press "Continue to Digital Library"
    
    Then I should be on the homepage
#As an admin I create users required for playlist tests