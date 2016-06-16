# vim: sw=2:ts=2:et
Feature: Forums
	As a user I should be able to view forums

  Scenario: Log in and go to "Forums" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I follow "Forums" in the "header" region
    Then I should be on "/forums"
    And I should see "Resource Forums provide opportunities to discuss" in the "forums" region


#As #1 user, view a forum, see something is there, post to a forum
