<div class="more-less-text">
  <?php
    $class_summary = '';
    $class_full = '';
    
    if ($show_open) {
      $class_summary = 'more-less-text-hidden';
      $class_full = 'more-less-text-open';
    }
  ?>

  <div class="more-less-text-summary <?php echo $class_summary; ?>">
    <?php echo $summary; ?>
  </div>
  <div class="more-less-text-full <?php echo $class_full; ?>">
    <?php echo $full; ?>
  </div>
</div>