# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy License
	As an admin user I should be able to view the License taxonomy with correct terms

  Scenario: Log in and go to "License taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/license"
    Then I should see "Smarter Balanced Copyright Clearance Form (signed by the owner)"
    And I should see "Creative Commons Attribution"
    And I should see "Creative Commons Attribution No Derivatives"
    And I should see "Public Domain (free of copyright restrictions)"
    And I should see "Smarter Balanced Terms of Service (owned by the contributor)"
    And I should see "License Available at Approved Content Site (e.g., YouTube, Slideshare)"

#As #1 user, view License taxonomy, see the correct terms