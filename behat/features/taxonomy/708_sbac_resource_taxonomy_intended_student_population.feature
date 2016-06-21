# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Intended Student Populations
	As an admin user I should be able to view the Intended Student Populations taxonomy with correct terms

  Scenario: Log in and go to "Intended Student Populations taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/intended_student_populations"
    Then I should see "All Students"
    And I should see "English Language Learners (ELL)"
    And I should see "Students with Disabilities (SWD)"
    And I should see "Gifted & Talented (G&T)"

#As #1 user, view Intended Student Populations taxonomy, see the correct terms