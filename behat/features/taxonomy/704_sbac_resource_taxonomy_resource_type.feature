# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Resource Type
	As an admin user I should be able to view the Resource Type taxonomy with correct terms

  Scenario: Log in and go to "Resource Type taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/focus"
    Then I should see "Instructional"
    And I should see "Instructional and Professional Learning"
    And I should see "Professional Learning"
    And I should see "Playlist"
    And I should see "Spotlight"

#As #1 user, view Resource Type taxonomy, see the correct terms