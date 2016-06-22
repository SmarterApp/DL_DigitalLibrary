# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Intended End Users
	As an admin user I should be able to view the Intended End User taxonomy with correct terms

  Scenario: Log in and go to "Intended End Users taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/intended_end_user"
    Then I should see "Administrator"
    And I should see "Parent"
    And I should see "Student"
    And I should see "Teacher"
    And I should see "Coach/Coordinator"
    And I should see "Professional Learning Community"

#As #1 user, view Intended End User taxonomy, see the correct terms