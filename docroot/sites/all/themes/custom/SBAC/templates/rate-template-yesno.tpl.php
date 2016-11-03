<?php
  global $user;

  $review = entity_load_single($content_type, $content_id); 

  // can't flag own content
  if ($review->uid != $user->uid):
?>

<span class="rate-info">
  <?php
    if ($info) {
      echo '<span class="text">' . $info . '</span>';
    }
    else {
      echo '
            <span class="text">' . t('Was this review helpful?') . '</span>
            <span class="vote">
              <a href="#" class="vote-yes">' . t('Yes') . '</a> /
              <a href="#" class="vote-no">' . t('No') . '</a>
              
              <span class="action-triggers">
                <span class="action-yes">' . $buttons[0] . '</span>
                <span class="action-no">' . $buttons[1] . '</span>
              </span>
            </span>
           ';
    }
  ?>

  <span class="flag">
    <?php
      $flags = entity_load_multiple_by_name('flag', FALSE, array(
        'type' => 'review_end_use',
        'target_type' => $content_type,
        'target_id' => $content_id,
        'uid' => $user->uid,
      ));
      
      if (sizeof($flags)) {
        $flag = current($flags);
        $issue_type = field_get_value($flag, 'field_issue_type');
        echo flag_flagged_message($issue_type);
      }
      else {
        echo t('You may also !flag.', array(
          '!flag' => '<a href="#" class="flag-trigger">' . t('flag this review') .'</a>',
        ));
      }
    ?>
  </span>
</span>

<?php endif;
