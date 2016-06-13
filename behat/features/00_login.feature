# vim: sw=2:ts=2:et
Feature: Login
	As a user I should be able to log in

	Scenario: Anonymous user on homepage
		Given I am an anonymous user
		And I am on the homepage
		Then I should see "Enter the password that accompanies your username."
		And I should see the button "edit-submit"

