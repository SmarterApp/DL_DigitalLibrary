# vim: sw=2:ts=2:et
Feature: Notifications
	As a user I should be able to get notifications

  @javascript
  Scenario: Log in and go to "Notifications" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I follow "Notifications" in the "nav" region
    Then I should be on "/users/consortium#profile-notifications"
    Given I wait for AJAX to finish
    Then I wait for the "notifications" region to appear
    #Then I wait for "5" seconds
    Then I should see "Load More Notifications" in the "notifications" region


#As #1 user, validate notifications show up
