<?php
	// @TODO this template file needs to be cleaned up
	hide($user_profile['summary']);
	$cols = 12;
	if ($user_profile['user_picture']['#markup']) {
		$cols = 10;
	}
?>
<div class="row first">
	<?php if ($user_profile['user_picture']['#markup']): ?>
		<div class="column large-3 profile-pic">
			<?php
			// display default photo if privacy on for picture
			// we use field_first_name because field_privacy may not exist
			if (isset($user_profile['field_first_name']['#object'])) {
				if (!sbac_user_privacy_check('picture', $user_profile['field_first_name']['#object'])) {
				  $filepath = variable_get('user_picture_default', '');
				  $alt = t("@user's picture", array('@user' => format_username($user_profile['field_first_name']['#object'])));
			      $user_profile['user_picture']['#markup'] = theme('image', array('path' => '' . $filepath, 'alt' => $alt, 'title' => $alt));
			    }
			}
		    echo drupal_render($user_profile['user_picture']);
			?>
		</div>
	<?php endif; ?>

	<div class="column large-9 user-profile">
		<h2 class="name clearfix">
			<?php echo drupal_render($user_profile['field_first_name']) . ' '; ?>
      <?php echo drupal_render($user_profile['field_last_name']); ?>
		</h2>

		<div class="profile-title">
			<?php
			// @TODO this needs to be fixed and use drupal_render
			if (isset($user_profile['field_position']['#access']) && $user_profile['field_position']['#access'] && isset($user_profile['field_position'][0]['#markup'])) {
				echo $user_profile['field_position'][0]['#markup'];
			}

			if (isset($user_profile['field_retired'][0]['#markup'])) {
				echo ' (Retired)';
			}
			?>
		</div>

		<div class="profile-school">
			<?php
				//$school = drupal_render($user_profile['field_school_name']);
				//$district = drupal_render($user_profile['field_district_name']);
				//$state = drupal_render($user_profile['field_state']);
        $school = $district = $state = '';
        if (isset($user_profile['field_state']) && sbac_user_privacy_check('field_school_name', $user_profile['field_school_name']['#object'])) {
          $school = $user_profile['field_school_name']['#items'][0]['value'];
        }
        if (isset($user_profile['field_district_name']) && sbac_user_privacy_check('field_district_name', $user_profile['field_district_name']['#object'])) {
          $district = $user_profile['field_district_name']['#items'][0]['value'];
        }
        if(isset($user_profile['field_state'])) {
          $state = $user_profile['field_state'][0]['#title'];// always shown
        }
        
				if ($school && $district && $state) {
					echo t('!school in !district, !state', array(
						'!school'    => $school,
						'!district'  => $district,
						'!state' => $state,
					));
				} else {
					echo $school;
          echo ($district)? ' ' : '';
					echo $district;
					echo (($school || $district) && $state)? ', ' : '';
					echo $state;
				}
			?>
		</div>

		<div class="introduction">
			<?php echo drupal_render($user_profile['field_introduction']); ?>
		</div>
		<div class="profile-details">
			<?php
        $grade = $subject = $sp = '';
        if(isset($user_profile['field_grade_level_s_']['#items']) && $user_profile['field_grade_level_s_']['#items']) {
          foreach ($user_profile['field_grade_level_s_']['#items'] as $key => $grade) {
            $grades[] = str_replace("&nbsp;", '', drupal_render($user_profile['field_grade_level_s_'][$key]));
            //print_r($key);
          }
          $grade = implode(', ', $grades);
        }
        if(isset($user_profile['field_subject_s_']['#items']) && $user_profile['field_subject_s_']['#items']) {
          foreach ($user_profile['field_subject_s_']['#items'] as $key1 => $subject) {
            $subjects[] = str_replace("&nbsp;", '', drupal_render($user_profile['field_subject_s_'][$key1]));
            //print_r($key);
          }
          $subject = implode(', ', $subjects);
        }
        if(isset($user_profile['field_special_populations']['#items']) && $user_profile['field_special_populations']['#items']) {
          foreach ($user_profile['field_special_populations']['#items'] as $key2 => $sp) {
            $sps[] = str_replace("&nbsp;", '', drupal_render($user_profile['field_special_populations'][$key2]));
            //print_r($key);
          }
          $sp = implode(', ', $sps);
        }

				echo '<div><span class="title">Grades: </span>'. $grade .'</div>';
				echo '<div><span class="title">Subjects: </span>'. $subject .'</div>';
				echo '<div><span class="title">Student Populations: </span>'. $sp .'</div>';
			?>
		</div>
	</div>
</div>
<div class="line"></div>
<div class="row second">
	<div class="column large-12">
		<?php
			if (isset($user_profile['sections'])) {
				echo theme('sections', array(
			    'sections' => $user_profile['sections'],
			    'name' => 'profile',
			  ));
			}
		?>
	</div>

</div>
<?php //drupal_render($form['field_feedback_flag']); ?>
<?php print drupal_render($form); ?>
