# vim: sw=2:ts=2:et
Feature: SBAC Lexicon Taxonomy Glossary Terms
	As an admin user I should be able to view the Glossary Terms taxonomy with correct terms

  Scenario: Log in and go to "Glossary Terms taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/glossary_terms"
    Then I should see "State Leadership Team (SLT)"
    And I should see "State Network of Educators (SNE)"
    And I should see "Smarter Balanced Claims"
	And I should see "Smarter Balanced Assessment Targets"
	And I should see "Quality Criteria"
	And I should see "Smarter Balanced Assessment Consortium"
	And I should see "Success Criteria"
	And I should see "Tag"
	And I should see "Universal Design for Learning (UDL)"
	And I should see "Professional Learning Resource"
	And I should see "Licensing Terms"
	And I should see "Content Specifications"
    And I should see "Copyright Clearance Form"
    And I should see "Cover Profile"
    And I should see "Comprehensible"
    And I should see "Common Core State Standards"
    And I should see "Combination of Instructional and Professional Learning Resource"
    And I should see "Commissioned Resource"
    And I should see "Depth of Knowledge"
    And I should see "Digital Library"
    And I should see "Instructional Resource"
    And I should see "Item Specifications"
    And I should see "Learning Target"
    And I should see "Governance Criteria"
    And I should see "Gate-Keeping Criteria"
    And I should see "Family Educational Rights and Privacy Act (FERPA)"
    And I should see "Formative Assessment Process"
    And I should see "Attributes of the Formative Assessment Process"

#As #1 user, view Glossary Terms taxonomy, see the correct terms