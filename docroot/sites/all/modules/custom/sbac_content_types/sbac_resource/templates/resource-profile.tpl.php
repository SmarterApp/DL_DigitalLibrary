<div class="left-side">
  <?php foreach($node->resource_profile_left as $profile_field) { ?>
    <?php echo $profile_field['title'] ?>
    <?php echo $profile_field['content'] ?>
  <?php } ?>
</div>

<div class="right-side">
  <?php if (isset($node->field_alt_body['und'][0])): ?>
    Summary
    <?php echo $node->field_alt_body['und'][0]['value']; ?>
  <?php endif; ?>

  <?php if (isset($node->resource_profile_right)): ?>
    <?php echo $node->resource_profile_right['focus']['title']; ?>
    <?php echo $node->resource_profile_right['focus']['content']; ?>
  <?php endif; ?>

  <?php if (isset($node->field_connection_to_fap['und'][0])): ?>
    Specific Connection To The Formative Assessment Process
    <?php echo $node->field_connection_to_fap['und'][0]['value']; ?>
  <?php endif; ?>

  <?php if (isset($node->field_connection_to_ccss['und'][0])): ?>
    Specific Connection To The Common Core State Standards
    <?php echo $node->field_connection_to_ccss['und'][0]['value']; ?>
  <?php endif; ?>

  <?php if (isset($node->field_learning_goals['und'][0])): ?>
    Learning Goals
    <?php echo $node->field_learning_goals['und'][0]['value']; ?>
  <?php endif; ?>

  <?php if (isset($node->field_success_criteria['und'][0])): ?>
    Success Criteria
    <?php echo $node->field_success_criteria['und'][0]['value']; ?>
  <?php endif; ?>

  <?php if (isset($node->field_contexts['und'][0])): ?>
    Context(s) Within Which The Resource Could Be Used
    <?php echo $node->field_contexts['und'][0]['value']; ?>
  <?php endif; ?>

  <?php if (isset($node->field_supporting_evidence['und'][0])): ?>
    Supporting Evidence
    <?php echo $node->field_supporting_evidence['und'][0]['value']; ?>
  <?php endif; ?>

  <?php if (isset($node->principles['und'][0])): ?>
    Principles, Literature, or Research
    <?php echo $node->principles['und'][0]['value']; ?>
  <?php endif; ?>
</div>