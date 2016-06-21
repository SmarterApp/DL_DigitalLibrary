# vim: sw=2:ts=2:et
Feature: SBAC User Taxonomy Title
  As an admin user I should be able to view the Title taxonomy with correct terms

  Scenario: Log in and go to "Title taxonomy page" as a known admin user
    Given I am on the homepage
    When I fill in the following:
      | Email Address | admin |
      | Password | password |
    And press "Log into the Digital Library"
    Then I should be on the homepage

    When I am on "admin/structure/taxonomy/title"
    Then I should see "State Personnel"
    And I should see "Regional Learning Consultant"
    And I should see "District Administrator"
    And I should see "Building Administrator"
    And I should see "Teacher"
    And I should see "School Counselor"
    And I should see "Librarian / Media Specialist"
    And I should see "Instructional Coach"
    And I should see "Instructional Coordinator"
    And I should see "Higher Education Personnel"
    And I should see "Student Teacher"
    And I should see "Other"

#As #1 user, view Title taxonomy, see the correct terms