<?php
/**
 * @file
 * sbac_lexicon_taxonomy.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function sbac_lexicon_taxonomy_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Gate-Keeping Criteria',
    'description' => '<p>The first set of criteria that reviewers use to screen resources to ensure that they meet critical expectations. &nbsp;Resources must meet all Gate-Keeping Criteria before reviewers evaluate the resource against the Quality Criteria (see full sets of Quality Criteria for instructional resources and professional learning resources in Help Topics). &nbsp;</p>',
    'format' => 'full_html',
    'weight' => 25,
    'uuid' => '0b29c93f-2511-41e9-9bfd-8550517673fa',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4011,
  );
  $terms[] = array(
    'name' => 'Commissioned Resource',
    'description' => '<p>A professional learning or instructional resource that contractors develop specifically for the Smarter Balanced Assessment Consortium Digital Library.</p>',
    'format' => 'full_html',
    'weight' => 18,
    'uuid' => '0c6b9772-4cf7-45c3-9316-983a65458f73',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4001,
  );
  $terms[] = array(
    'name' => 'Cover Profile',
    'description' => '<p>An electronic form that Digital Library contributors complete to submit resources. &nbsp;It contains information that is used for reviewers to vet the resources against the Quality Criteria. &nbsp;The information is also used to provide a summary of the resource once it is posted in the Digital Library.</p>',
    'format' => 'full_html',
    'weight' => 14,
    'uuid' => '1e28d04c-35e6-45ad-b24a-b3e43c538d2d',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4005,
  );
  $terms[] = array(
    'name' => 'Formative Assessment Process',
    'description' => '<p>&nbsp;A deliberate process used by teachers and students during instruction, which provides actionable feedback that is used to adjust ongoing teaching and learning strategies to improve students’ attainment of curricular learning targets/goals. &nbsp;</p>',
    'format' => 'full_html',
    'weight' => 27,
    'uuid' => '310b498d-271b-469a-9428-ba5af3e86053',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4009,
  );
  $terms[] = array(
    'name' => 'Biased and objectionable or culturally insensitive. <span>(e.g. related to race, culture, religion, political viewpoint, gender, or socioeconomic status)</span>',
    'description' => NULL,
    'format' => NULL,
    'weight' => -3,
    'uuid' => '32be672b-7a18-418b-aa78-d4e44563d85a',
    'vocabulary_machine_name' => 'forum_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60636,
  );
  $terms[] = array(
    'name' => 'Universal Design for Learning (UDL)',
    'description' => '<p>A set of principles for instructional design that gives all students equal opportunities to learn. &nbsp;UDL provides a blueprint for creating instructional goals, methods, materials, and assessments that work for a full range of learners. &nbsp;UDL is not a single, one-size-fits-all solution ,but rather a set of flexible approaches that can be customized and adjusted for individual needs.</p><p>To find more information about UDL, please follow the following link: <a href="http://www.udlcenter.org">www.udlcenter.org</a></p>',
    'format' => 'full_html',
    'weight' => 9,
    'uuid' => '37bef60f-8be0-4f5e-b0aa-f7de78ce0b33',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 6700,
  );
  $terms[] = array(
    'name' => 'Combination of Instructional and Professional Learning Resource',
    'description' => '<p>A resource that is both a professional learning resource and an instructional resource. Reviewers will evaluate it using both the Quality Criteria for Professional Learning Resources and the Quality Criteria for Instructional Resources. &nbsp;</p>',
    'format' => 'full_html',
    'weight' => 17,
    'uuid' => '3e8f9166-c058-44f4-9649-443309087ed8',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 3999,
  );
  $terms[] = array(
    'name' => 'Smarter Balanced Assessment Targets',
    'description' => '<p>Grade-level specific knowledge, skills, and abilities to be assessed through the Smarter Balanced Summative Assessment.</p>',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => '52f0940b-b1a9-4926-a326-130b03bbc583',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4208,
  );
  $terms[] = array(
    'name' => 'Licensing Terms',
    'description' => '<p class="p1">Permission that allows SLTs and members of the SNE to submit a resource to the Digital Library. &nbsp;The following licenses are included: &nbsp;</p><ul><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Digital Library Terms of Service (Section 6): Permission you can grant to Smarter Balanced if you have created and are the owner of the resource.&nbsp; See the footer below to access details of the Terms of Service.&nbsp;</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Creative Commons Attribution: Permission that allows anyone to distribute, revise, tweak, and build upon a resource, as long as you credit the owner of the original creation.</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Creative Commons Attribution No Derivatives: Permission that allows anyone to redistribute a resource, unchanged and in whole, as long as you credit the owner.&nbsp;</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Public domain: Permission that allows anyone to use the resource with no restrictions.</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Copyright Clearance Form: Permission a third-party owner of the resource gives to Smarter Balanced.&nbsp;</span></li></ul>',
    'format' => 'full_html',
    'weight' => 11,
    'uuid' => '54033ede-9968-4805-b08e-abeb30971743',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4015,
  );
  $terms[] = array(
    'name' => 'Outdated or inactive',
    'description' => NULL,
    'format' => NULL,
    'weight' => -6,
    'uuid' => '5b0740a8-c16f-422b-8937-578e232c095f',
    'vocabulary_machine_name' => 'forum_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60621,
  );
  $terms[] = array(
    'name' => 'Professional Learning Resource',
    'description' => '<p>A file or a set of files in the Digital Library that helps educators deepen their understanding of the Common Core State Standards, the formative assessment process, and a balanced assessment system.&nbsp;</p>',
    'format' => 'full_html',
    'weight' => 10,
    'uuid' => '5b8efa80-a698-44fa-a304-5e1ebc514823',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4016,
  );
  $terms[] = array(
    'name' => 'Common Core State Standards',
    'description' => '<p class="p1">States, territories, and the District of Columbia developed the Common Core State Standards (CCSS) voluntarily and cooperatively to offer schools, teachers, students and parents clear, understandable, and consistent standards in English Language Arts and mathematics. The CCSS define the knowledge and skills students need to be successfully prepared for postsecondary education and career opportunities.&nbsp;</p>',
    'format' => 'full_html',
    'weight' => 16,
    'uuid' => '5e9acf49-a537-4ac7-8e65-01e2c132cf57',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4000,
  );
  $terms[] = array(
    'name' => 'Instructional Resource',
    'description' => '<p>A file or a set of files in the Digital Library that helps educators focus their instruction on the Common Core State Standards using formative assessment practices and that help educators develop practices that support in-depth learning.&nbsp;</p>',
    'format' => 'full_html',
    'weight' => 21,
    'uuid' => '64685afa-4bc0-4d4c-b73c-d3817e3b2407',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4012,
  );
  $terms[] = array(
    'name' => 'Content Specifications',
    'description' => '<p class="p1">Developed in partnership with member states, leading researchers, content experts, and the authors of the Common Core State Standards, the Content Specifications are intended to ensure that the summative assessment accurately assesses the full range of the standards. &nbsp;The full Content Specifications for mathematics and for English language arts can be found online at &nbsp;the following link: <a href="http://www.smarterbalanced.org/smarter-balanced-assessments/">http://www.smarterbalanced.org/smarter-balanced-assessments/</a>.</p>',
    'format' => 'full_html',
    'weight' => 12,
    'uuid' => '7a3209d1-228c-4a3d-85d6-e803a86badcc',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4003,
  );
  $terms[] = array(
    'name' => 'Smarter Balanced Claims',
    'description' => '<p>A summary statement about the knowledge and skills students are expected to demonstrate on the assessment related to a particular domain of the Common Core State Standards. &nbsp;</p><p>For more information, please use the following link: <a href="http://www.smarterbalanced.org/wordpress/wp-content/uploads/2012/05/TaskItemSpecifications/ItemSpecifications/GeneralItemSpecifications.pdf">www.smarterbalanced.org/wordpress/wp-content/uploads/2012/05/TaskItemSpecifications/ItemSpecifications/GeneralItemSpecifications.pdf</a></p>',
    'format' => 'full_html',
    'weight' => 3,
    'uuid' => '8069211c-7c50-4067-81f1-bfdd1a553fa4',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4737,
  );
  $terms[] = array(
    'name' => 'Attributes of the Formative Assessment Process',
    'description' => '<p>Smarter Balanced has identified four attributes that are common to most frameworks/models for the formative assessment process. &nbsp;They are:</p><ul><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Clarify intended learning</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Elicit evidence</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Interpret evidence</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Act on evidence</span></li></ul>',
    'format' => 'full_html',
    'weight' => 28,
    'uuid' => '8753173d-116f-4cf3-90ee-a1030ecf8a41',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 3998,
  );
  $terms[] = array(
    'name' => 'Quality Criteria',
    'description' => '<p>A set of criteria for professional learning resources and instructional resources that reviewers use to ensure the Digital Library houses only the highest quality resources that integrate the Common Core State Standards and formative assessment practices.</p>',
    'format' => 'full_html',
    'weight' => 5,
    'uuid' => '9557fe3f-cb1c-4e46-b709-f9065dfd2879',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4017,
  );
  $terms[] = array(
    'name' => 'Copyright Clearance Form',
    'description' => '<p>A form that Digital Library contributors use to secure permission from the owner/author to post a copyrighted resource.</p>',
    'format' => 'full_html',
    'weight' => 13,
    'uuid' => '9abb6e6b-5ed5-4a96-8060-737b1f54fd15',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4004,
  );
  $terms[] = array(
    'name' => 'Unintelligible',
    'description' => NULL,
    'format' => NULL,
    'weight' => -4,
    'uuid' => '9af886bb-fdf9-4831-8651-87cfbe6180b5',
    'vocabulary_machine_name' => 'forum_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60631,
  );
  $terms[] = array(
    'name' => 'Family Educational Rights and Privacy Act (FERPA)',
    'description' => '<p class="p1">The rights of students and parents to keep student-level information private. Student information cannot be shared without the written consent of a parent or a student over 18. &nbsp;</p><p class="p2">For more information, please use the following link: <a href="http://www.ed.gov/policy/gen/guid/fpco/ferpa/index.html">www.ed.gov/policy/gen/guid/fpco/ferpa/index.html</a></p>',
    'format' => 'full_html',
    'weight' => 26,
    'uuid' => '9d091373-50ee-4b4f-9121-66152b93c2e2',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4008,
  );
  $terms[] = array(
    'name' => 'Learning Target',
    'description' => '<p>&nbsp;A statement that defines the intended student learning for a resource.&nbsp;</p>',
    'format' => 'full_html',
    'weight' => 23,
    'uuid' => 'a1a2bc89-fc7e-4aad-83d0-2f4369219ec9',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4014,
  );
  $terms[] = array(
    'name' => 'Inaccurate / misleading',
    'description' => NULL,
    'format' => NULL,
    'weight' => -5,
    'uuid' => 'ab267575-eb99-43d7-a883-06d0188befd7',
    'vocabulary_machine_name' => 'forum_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60626,
  );
  $terms[] = array(
    'name' => 'Tag',
    'description' => '<p>An attribute associated with a resource that allows users to quickly and effectively search, filter, and find resources.</p>',
    'format' => 'full_html',
    'weight' => 8,
    'uuid' => 'b6bd4bd3-f022-49c0-9ffa-335d88d4e4f3',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 6375,
  );
  $terms[] = array(
    'name' => 'State Network of Educators (SNE)',
    'description' => '<p>Each State Leadership Team (SLT) recruited and selected 60 to 150 &nbsp;K-12 educators and higher education faculty with diverse expertise and backgrounds—including CCSS for Mathematics, CCSS for ELA/literacy, science, social studies, general education, gifted and talented, English language learners, and students with disabilities—to serve on the SNE.</p><p>Members of the SNE will use the Quality Criteria to submit and review resources for the Digital Library. They will have early access to the library’s online tools that promote collaboration across Smarter Balanced states.&nbsp;</p>',
    'format' => 'full_html',
    'weight' => 2,
    'uuid' => 'bfbfb1fa-5df4-43a0-b8a8-5d7809d9c8df',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 6049,
  );
  $terms[] = array(
    'name' => 'Governance Criteria',
    'description' => '<p>The set of guidelines used to ensure that the portfolio of resources meets the diverse needs of educators and fulfills the purpose of the Digital Library.&nbsp;</p>',
    'format' => 'full_html',
    'weight' => 24,
    'uuid' => 'c1b3ec51-c98c-4238-bc58-d90ddb1253b3',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4010,
  );
  $terms[] = array(
    'name' => 'Depth of Knowledge',
    'description' => '<p class="p1">The level of cognitive rigor required in completing an activity, item, or task as detailed in Smarter Balanced Task Item Specifications. &nbsp;Based on the work of Norman Webb, Depth of Knowledge (DOK) is defined at four levels of cognitive demand:</p><ul><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Level 1: Recall and Reproduction</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Level 2: Basic Skills and Concepts</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Level 3: Strategic Thinking and Reasoning&nbsp;</span></li><li><span style="font-family: inherit; font-size: 0.75em; line-height: 1.6;">Level 4: Extended Thinking</span></li></ul><p class="p4">For more information, please use the following link: <a href="http://www.smarterbalanced.org/wordpress/wp-content/uploads/2012/05/TaskItemSpecifications/ItemSpecifications/GeneralItemSpecifications.pdf">www.smarterbalanced.org/wordpress/wp-content/uploads/2012/05/TaskItemSpecifications/ItemSpecifications/GeneralItemSpecifications.pdf</a>&nbsp;</p>',
    'format' => 'full_html',
    'weight' => 19,
    'uuid' => 'c575b4d7-c825-4705-ba3a-036222116303',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4006,
  );
  $terms[] = array(
    'name' => 'Success Criteria',
    'description' => '<p>Measures that determine whether a learner has met Learning Targets.</p>',
    'format' => 'full_html',
    'weight' => 7,
    'uuid' => 'dc47bbf4-0046-4be0-96fb-8544aa49ef23',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 6231,
  );
  $terms[] = array(
    'name' => 'State Leadership Team (SLT)',
    'description' => '<p>State Leadership Teams are made up of 8-12 K-12 educators and higher education faculty in positions of state leadership in each of the Governing States. They have expertise in the CCSS, formative assessment practices, curriculum and instruction, English language learners, students with disabilities, students with gifts and talents, and adult online learning. These teams build capacity in their states by training and supporting the members of their State Networks of Educators to contribute resources to the Digital Library. SLTs also provide feedback on &nbsp;commissioned resources, the review and posting process, and the usability of the library.</p>',
    'format' => 'full_html',
    'weight' => 1,
    'uuid' => 'dcac4e58-b4a6-4a56-8df8-b3db2b44fb04',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 5823,
  );
  $terms[] = array(
    'name' => 'Digital Library',
    'description' => '<p class="p1">The Digital Library is an online application that will focus on the formative assessment process and will contain differentiated resources aligned to the Common Core State Standards (CCSS) for educators with varying interests and professional learning needs. These resources include a series of commissioned assessment literacy and exemplar instructional modules in English language arts/literacy and mathematics. In addition, the library will include professional learning and instructional materials contributed by State Leadership Teams and members of the State Networks of Educators. The online library will be interactive, allowing users to rate materials and to share their expertise with educators across the state or across the country.&nbsp;</p>',
    'format' => 'full_html',
    'weight' => 20,
    'uuid' => 'e1693a4b-0ad1-4939-8c5c-28765d463a60',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4007,
  );
  $terms[] = array(
    'name' => 'Contains personally identifiable information (PII)',
    'description' => NULL,
    'format' => NULL,
    'weight' => -2,
    'uuid' => 'e92b20f7-5bed-45e0-b67b-544b76fed7df',
    'vocabulary_machine_name' => 'forum_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60641,
  );
  $terms[] = array(
    'name' => 'Appears to be spam',
    'description' => NULL,
    'format' => NULL,
    'weight' => -1,
    'uuid' => 'edacd1d0-6ede-4c9f-b64a-605adba3402e',
    'vocabulary_machine_name' => 'forum_flags',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 60646,
  );
  $terms[] = array(
    'name' => 'Item Specifications',
    'description' => '<p class="p1">Documents that use the Content Specifications to provide detailed guidance for developing summative and interim assessment items and performance tasks. &nbsp;&nbsp;</p><p class="p3">For more information, please use the following link: <a href="http://www.smarterbalanced.org/smarter-balanced-assessments/">www.smarterbalanced.org/smarter-balanced-assessments/</a></p>',
    'format' => 'full_html',
    'weight' => 22,
    'uuid' => 'ef1cc2f2-f143-4b5f-b6a2-fc8a1caee683',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4013,
  );
  $terms[] = array(
    'name' => 'Comprehensible',
    'description' => '<p>A Gate-Keeping criterion that means that a resource is clear and can be easily understood.</p>',
    'format' => 'full_html',
    'weight' => 15,
    'uuid' => 'f4c3445b-bda0-46b9-9340-64ce254ddaeb',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4002,
  );
  $terms[] = array(
    'name' => 'Smarter Balanced Assessment Consortium',
    'description' => '<p>A state-led consortium working collaboratively to develop next-generation assessments that accurately measure student progress toward college- and career-readiness. &nbsp;Smarter Balanced involves educators, researchers, policymakers, and community groups in a transparent and consensus-driven process to help all students thrive in a knowledge-driven global economy. &nbsp;A four-year, $175 million grant from the U.S. Department of Education funds 99% of activity resources for Smarter Balanced projects; generous contributions from charitable foundations provide the remaining support. &nbsp;</p><p>Smarter Balanced is developing an assessment system that measures mastery of the Common Core State Standards and provides timely information about student achievement and progress toward college and career readiness. &nbsp;Educators will also have access to a robust online library of formative assessment resources and tools for use in the classroom to address the needs of students.</p><p>For more information visit <a href="http://www.smarterbalanced.org">www.smarterbalanced.org</a></p>',
    'format' => 'full_html',
    'weight' => 6,
    'uuid' => 'feac2e46-beff-4c1c-af96-0042820a34d4',
    'vocabulary_machine_name' => 'glossary_terms',
    'entity_type' => 'taxonomy_term',
    'entity_id' => 4018,
  );
  return $terms;
}
