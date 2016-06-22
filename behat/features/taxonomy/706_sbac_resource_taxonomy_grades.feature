# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Grades
	As an admin user I should be able to view the Grades taxonomy with correct terms

  Scenario: Log in and go to "Grades taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/grades"
    Then I should see "Kindergarten"
    And I should see "Grade 1"
    And I should see "Grade 2"
    And I should see "Grade 3"
    And I should see "Grade 4"
    And I should see "Grade 5"
    And I should see "Grade 6"
    And I should see "Grade 7"
    And I should see "Grade 8"
    And I should see "Grade 9"
    And I should see "Grade 10"
    And I should see "Grade 11"
    And I should see "Grade 12"
    And I should see "Not Grade Specific"

#As #1 user, view Grades taxonomy, see the correct terms