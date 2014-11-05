<div id="profile-wrap">
	<table cellpadding="10">
		<tr>
			<td width="200" style="padding-right: 20px;">
    		<?php if (isset($node->resource_profile_left)) { ?>
		      <?php foreach($node->resource_profile_left as $profile_field) { ?>
		        <h4 style="border-bottom: 1px solid #ccc;"><?php echo $profile_field['title'] ?></h4>
		        <div style="margin-left: -20px;"><?php echo $profile_field['content'] ?></div>
		      <?php } ?>
		    <?php } ?>
			</td>

			<td width="300">
			  <?php if (isset($node->field_alt_body['und'][0])): ?>
			    <h2 class="about" valign="top">Summary</h2>
			    <div class="item-list" style="margin: 0;"><?php echo $node->field_alt_body['und'][0]['value']; ?></div>
			  <?php endif; ?>

			  <?php if (isset($node->resource_profile_right)): ?>
			    <h4 style="border-bottom: 1px solid #ccc; margin-bottom: 5px; padding-bottom: 0;"><?php echo $node->resource_profile_right['attributes']['title']; ?></h4>
			    <?php echo $node->resource_profile_right['attributes']['content']; ?>
			  <?php endif; ?>

			  <?php if (isset($node->field_connection_to_fap['und'][0])): ?>
			    <h2 class="about">Specific Connection to the Formative Assessment Process</h2>
			    <div class="item-list"><?php echo $node->field_connection_to_fap['und'][0]['value']; ?></div>
			  <?php endif; ?>

		    <?php if (isset($node->field_student_agency['und'][0])): ?>
		      <h2 class="about">Student Engagement to the Formative Assessment Process</h2>
		      <div class="item-list"><?php echo $node->field_student_agency['und'][0]['value']; ?></div>
		    <?php endif; ?>

			  <?php if (isset($node->field_connection_to_ccss['und'][0])): ?>
			    <h2 class="about">Specific Connection to the Common Core State Standards</h2>
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
			    <h2 class="about">Context(s) in Which the Resource Could Be Used</h2>
			    <div class="item-list"><?php echo $node->field_contexts['und'][0]['value']; ?></div>
			  <?php endif; ?>

			  <?php if (isset($node->field_supporting_evidence['und'][0])): ?>
			    <h2 class="about">Supporting Evidence</h2>
			    <div class="item-list"><?php echo $node->field_supporting_evidence['und'][0]['value']; ?></div>
			  <?php endif; ?>

			  <?php if (isset($node->field_principles['und'][0])): ?>
			    <h2 class="about">Principles, Literature, or Research</h2>
			    <div class="item-list"><?php echo $node->field_principles['und'][0]['value']; ?></div>
			  <?php endif; ?>
			</td>
		</tr>
	</table>
</div>