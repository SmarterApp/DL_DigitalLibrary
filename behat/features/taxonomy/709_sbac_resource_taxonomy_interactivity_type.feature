# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Interactivity Type
	As an admin user I should be able to view the Interactivity Type taxonomy with correct terms

  Scenario: Log in and go to "Interactivity Type taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/interactivity_type"
    Then I should see "Active"
    And I should see "Expositive"
    And I should see "Mixed"

#As #1 user, view Interactivity Type taxonomy, see the correct terms