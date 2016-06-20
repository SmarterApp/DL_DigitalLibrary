# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Technologies for Classroom Use
	As an admin user I should be able to view the Technologies for Classroom Use taxonomy with correct terms

  Scenario: Log in and go to "Technologies for Classroom Use taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/technologies_for_classroom_use"
    Then I should see "Calculator"
    And I should see "Clickers"
    And I should see "Document Camera"
	And I should see "Internet"
	And I should see "Smartphone"
	And I should see "Tablets/Computers for Students"
	And I should see "Tablets/Computers for Teacher"
	And I should see "Video Camera"
	And I should see "Still Camera"
	And I should see "Interactive White Board"
	And I should see "LCD Projector"

#As #1 user, view Technologies for Classroom Use taxonomy, see the correct terms