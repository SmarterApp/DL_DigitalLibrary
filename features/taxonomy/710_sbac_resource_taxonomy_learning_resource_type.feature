# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Learning Resource Type
	As an admin user I should be able to view the Learning Resource Type taxonomy with correct terms

  Scenario: Log in and go to "Learning Resource Type taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/learning_resource_type"
    Then I should see "Learning Task"
    And I should see "Lesson"
    And I should see "Interm/Summative Assessment"

#As #1 user, view Learning Resource Type taxonomy, see the correct terms