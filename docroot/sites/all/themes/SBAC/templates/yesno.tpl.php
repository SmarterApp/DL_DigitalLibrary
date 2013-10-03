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
      echo t('You may also !flag.', array(
        '!flag' => '<a href="#" class="flag-trigger">' . t('flag this review') .'</a>',
      ));
    ?>
  </span>
</span>
