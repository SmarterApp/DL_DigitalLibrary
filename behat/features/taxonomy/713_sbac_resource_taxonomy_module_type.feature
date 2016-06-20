# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Module Type
	As an admin user I should be able to view the Module Type taxonomy with correct terms

  Scenario: Log in and go to "Module Type taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/smarter_balanced_keyword"
    Then I should see "Assessment Literacy"
    And I should see "ELA Instructional"
    And I should see "Mathematics Instructional"
	And I should see "Score Report"

#As #1 user, view Module Type taxonomy, see the correct terms