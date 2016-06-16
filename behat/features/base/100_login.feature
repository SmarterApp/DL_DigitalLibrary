# vim: sw=2:ts=2:et
Feature: Login
	As a user I should be able to log in

  @smoketest
	Scenario: Not logged in user on homepage
		Given I am not logged in
		And I am on the homepage
		Then I should see "Enter the password that accompanies your username."
		And I should see the button "edit-submit"

  @smoketest
	Scenario: Anonymous user on homepage
		Given I am an anonymous user
		And I am on the homepage
		Then I should see "Enter the password that accompanies your username."
		And I should see the button "edit-submit"

  @smoketest
  Scenario: Log in as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage
    And I should see the button "Find Resources"
    And I should see the link "Help"
    And I should see the link "Edit Features"

    #TODO: We need to figure out how to create users or log in as users from information in a local file
