# vim: sw=2:ts=2:et
Feature: SBAC Resource Taxonomy Media Types
	As an admin user I should be able to view the Media Types taxonomy with correct terms

  Scenario: Log in and go to "Media Types taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/digital_media_type"
    Then I should see "Video"
    And I should see "Image"
    And I should see "Document"
	And I should see "Interactive"
	And I should see "Presentation"
	And I should see "Spreadsheet"
	And I should see "Audio"

#As #1 user, view Media Types taxonomy, see the correct terms