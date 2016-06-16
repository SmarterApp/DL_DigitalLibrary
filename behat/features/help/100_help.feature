# vim: sw=2:ts=2:et
Feature: Help Topics
	As a user I should be able to view help topics

  Scenario: Log in and go to "Help Topics" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage
    And I should see "What resources are you looking for?"

    When I follow "Help" in the "nav" region
    Then I should see "Help Topics"

    When I visit "/help-topics"
    Then I should see the text "Help Topics"

#As #1 user, validate help topics are viewable
