<span class="rate-info">
  <?php 
    if ($info) {
      echo '<span class="text">' . $info . '</span>';
    }
    else {
      echo '<span class="text">' . t('Was this review helpful?') . '</span>';
      echo '<span class="vote">' . $buttons[0] . ' / ' . $buttons[1] . '</span>';
    }
  ?>

  <span class="flag"> - 
    <?php
      echo t('You may also !flag', array(
        '!flag' => l(t('flag this review'), ''),
      ));
    ?>
  </span>
</span>
