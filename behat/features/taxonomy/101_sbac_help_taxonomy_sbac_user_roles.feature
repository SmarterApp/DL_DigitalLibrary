# vim: sw=2:ts=2:et
Feature: SBAC Help Taxonomy SBAC User Roles
	As an admin user I should be able to view the SBAC User Roles taxonomy with correct terms
  Scenario: Log in and go to "SBAC User Roles taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/sbac_user_roles"
    Then I should see "All User Roles"
	And I should see "anonymous user"
	And I should see "authenticated user"
	And I should see "administrator"
	And I should see "basic end user"
	And I should see "advanced end user"
	And I should see "resource contributor"
	And I should see "resource reviewer"
	And I should see "resource publisher"
	And I should see "facilitator"
	And I should see "moderator"
	And I should see "DLRB memeber"
	And I should see "help desk"
	And I should see "digital library administrator"
	And I should see "system administrator"
	And I should see "onboarding"
	And I should see "guest"
	
#As #1 user, view SBAC Roles taxonomy, see the correct terms