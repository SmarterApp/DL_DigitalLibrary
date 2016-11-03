<!-- Custom TPL for the feedback block -->
<?php
  global $user;
  $class_feedback = (variable_get('enable_feedback') == 1 && !$user->field_feedback_flag['und'][0]['value'] ? ' open' : '');
?>

<div id="feedback-dropdown" class="f-dropdown content small <?php echo $class_feedback; ?>">
  <a href="#" title="Remove" id="disable-feedback" class="small right"> x </a>
  <?php print render($title_prefix); ?>
  <?php if ($block->subject): ?>
    <h2<?php print $title_attributes; ?>><?php print $block->subject ?></h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>
  <?php print $content ?>
</div>