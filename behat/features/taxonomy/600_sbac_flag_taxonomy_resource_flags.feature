# vim: sw=2:ts=2:et
Feature: SBAC Flag Taxonomy Resource Flags
	As an admin user I should be able to view the Resource Flags taxonomy with correct terms

  Scenario: Log in and go to "Resource Flags taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/resource_flags"
    Then I should see "Outdated"
    And I should see "Duplicate"
    And I should see "Inaccurate / misleading"
    And I should see "Unintelligible / not viewable / technology does not function properly"
    And I should see "Biased, objectionable, or culturally insensitive material (e.g. related to race, culture, religion, political viewpoint, gender, or socioeconomic status)"
    And I should see "Contains personally identifiable information (PII)"
    And I should see "Summary information does not match the resource"
    And I should see "May be in violation of intellectual property rights (i.e., copyright infringement)"
    And I should see "Does not support implementation of Common Core State Standards"
    And I should see "Does not support the formative assessment process"
    And I should see "Resource is not available free of charge"

#As #1 user, view Resource Flags taxonomy, see the correct terms