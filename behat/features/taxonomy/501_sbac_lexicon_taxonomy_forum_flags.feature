# vim: sw=2:ts=2:et
Feature: SBAC Lexicon Taxonomy Forum Flags
	As an admin user I should be able to view the Forum Flags taxonomy with correct terms

  Scenario: Log in and go to "Forum Flags taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/forum_flags"
    Then I should see "Outdated or inactive"
    And I should see "Inaccurate / misleading"
    And I should see "Unintelligible"
	And I should see "Biased and objectionable or culturally insensitive. <span>(e.g. related to race, culture, religion, political viewpoint, gender, or socioeconomic status)</span>"
	And I should see "Contains personally identifiable information (PII)"
	And I should see "Appears to be spam"

#As #1 user, view Forum Flags taxonomy, see the correct terms