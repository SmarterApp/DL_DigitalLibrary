# vim: sw=2:ts=2:et
Feature: SBAC Core Taxonomy Applied Category
	As an admin user I should be able to view the Applied Category taxonomy with correct terms

  Scenario: Log in and go to "Applied Category taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/applied_category"
    Then I should see "Elementary School"
    And I should see "Educators to Use During Instruction"
    And I should see "High Quality Professional Learning"
	And I should see "Middle School"
	And I should see "Students to Use During Learning"
	And I should see "Collaborative Learning"
	And I should see "High School"
	And I should see "Use with Families"

#As #1 user, view Applied Category taxonomy, see the correct terms