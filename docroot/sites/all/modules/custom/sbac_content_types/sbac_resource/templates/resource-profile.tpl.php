<div id="profile-wrap">
	<div class="col narrow">
	  <?php foreach($node->resource_profile_left as $profile_field) { ?>
	    <div class="title-tags"><?php echo $profile_field['title'] ?></div>
	    <?php echo $profile_field['content'] ?>
	  <?php } ?>
	</div>

	<div class="col wide">
	  <?php if (isset($node->field_alt_body['und'][0])): ?>
	    <h2 class="about">Summary</h2>
	    <div class="item-list"><?php echo $node->field_alt_body['und'][0]['value']; ?></div>
	  <?php endif; ?>

	  <?php if (isset($node->resource_profile_right)): ?>
	    <div class="title-tags"><?php echo $node->resource_profile_right['focus']['title']; ?></div>
	    <?php echo $node->resource_profile_right['focus']['content']; ?>
	  <?php endif; ?>

	  <?php if (isset($node->field_connection_to_fap['und'][0])): ?>
	    <h2 class="about">Specific Connection To The Formative Assessment Process</h2>
	    <div class="item-list"><?php echo $node->field_connection_to_fap['und'][0]['value']; ?></div>
	  <?php endif; ?>

	  <?php if (isset($node->field_connection_to_ccss['und'][0])): ?>
	    <h2 class="about">Specific Connection To The Common Core State Standards</h2>
	    <div class="item-list"><?php echo $node->field_connection_to_ccss['und'][0]['value']; ?></div>
	  <?php endif; ?>

	  <?php if (isset($node->field_learning_goals['und'][0])): ?>
	    <h2 class="about">Learning Goals</h2>
	    <div class="item-list"><?php echo $node->field_learning_goals['und'][0]['value']; ?></div>
	  <?php endif; ?>

	  <?php if (isset($node->field_success_criteria['und'][0])): ?>
	    <h2 class="about">Success Criteria</h2>
	    <div class="item-list"><?php echo $node->field_success_criteria['und'][0]['value']; ?></div>
	  <?php endif; ?>

	  <?php if (isset($node->field_contexts['und'][0])): ?>
	    <h2 class="about">Context(s) Within Which The Resource Could Be Used</h2>
	    <div class="item-list"><?php echo $node->field_contexts['und'][0]['value']; ?></div>
	  <?php endif; ?>

	  <?php if (isset($node->field_supporting_evidence['und'][0])): ?>
	    <h2 class="about">Supporting Evidence</h2>
	    <div class="item-list"><?php echo $node->field_supporting_evidence['und'][0]['value']; ?></div>
	  <?php endif; ?>

	  <?php if (isset($node->principles['und'][0])): ?>
	    <h2 class="about">Principles, Literature, or Research</h2>
	    <div class="item-list"><?php echo $node->principles['und'][0]['value']; ?></div>
	  <?php endif; ?>
	</div>
</div>