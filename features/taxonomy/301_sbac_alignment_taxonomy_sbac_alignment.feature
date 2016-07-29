# vim: sw=2:ts=2:et
Feature: SBAC Alignment Taxonomy SBAC Alignment
	As an admin user I should be able to view the SBAC Alignment taxonomy with correct terms

  Scenario: Log in and go to "SBAC Alignment taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/sbac_alignment"
    Then I should see "Assesses"
    And I should see "Requires"
    And I should see "Teaches"

#As #1 user, view SBAC Alignment taxonomy, see the correct terms