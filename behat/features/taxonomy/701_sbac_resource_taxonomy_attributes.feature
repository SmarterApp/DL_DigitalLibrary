# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Formative Assessment Attributes
	As an admin user I should be able to view the Formative Assessment Attributes taxonomy with correct terms

  Scenario: Log in and go to "Formative Assessment Attributes taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/attributes"
    Then I should see "Clarify Intended Learning"
    And I should see "Elicit Evidence"
    And I should see "Interpret Evidence"
    And I should see "Act on Evidence"

#As #1 user, view Formative Assessment Attributes taxonomy, see the correct terms