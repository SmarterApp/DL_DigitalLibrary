<?php
	hide($user_profile['summary']);
	$cols = 12;
	if ($user_profile['user_picture']['#markup']) {
		$cols = 10;
	}
?>
<div class="row first">
	<?php if ($user_profile['user_picture']['#markup']): ?>
		<div class="column large-3">
			<?php echo drupal_render($user_profile['user_picture']); ?>
		</div>
	<?php endif; ?>

	<div class="column large-9 user-profile">
		<?php
		//	echo l(t('Edit Profile'), 'user/' . $user->uid . '/edit', array(
		//		'attributes' => array(
		//			'class' => array(
		//				'small',
		//				'button',
		//				'right',
		//			)
		//		)
		//	));
		?>

		<h2 class="name">
			<?php
				echo drupal_render($user_profile['field_first_name'][0]) . ' ';
				echo drupal_render($user_profile['field_last_name'][0]);
			?>
		</h2>

		<div class="profile-title">
			<?php
			if (isset($user_profile['field_retired'][0]['#markup'])) {
				$user_profile['field_retired'][0]['#markup'] = "I am currently retired" ;
				echo  drupal_render($user_profile['field_position'][0]). ' (retired)';
			} else {
				echo  drupal_render($user_profile['field_position'][0]);
			}
			?>
		</div>

		<div class="profile-school">
			<?php
				echo t('!school in !district', array(
					'!school'    => drupal_render($user_profile['field_school_name'][0]),
					'!district'  => drupal_render($user_profile['field_district_name'][0]),
				));
			?>
		</div>

		<div class="introduction">
			<?php
				echo drupal_render($user_profile['field_introduction'][0]);
			?>
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
				echo '<div><span class="title">Special Populations: </span>'. $sp .'</div>';
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
