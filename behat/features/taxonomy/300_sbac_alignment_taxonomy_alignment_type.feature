# vim: sw=2:ts=2:et
Feature: SBAC Alignment Taxonomy Alignment Type
	As an admin user I should be able to view the Alignment Type taxonomy with correct terms

  Scenario: Log in and go to "Alignment Type taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/alignment_type"
    Then I should see "Assesses"
    And I should see "Requires"
    And I should see "Teaches"

#As #1 user, view Alignment Type taxonomy, see the correct terms