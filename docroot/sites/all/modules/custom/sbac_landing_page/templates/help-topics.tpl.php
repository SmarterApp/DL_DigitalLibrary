<?php if($topics): ?>
  <div id="show-hide-help-topics"></div>
  <?php if($edit_help):?>
  <div id="edit-help-topics"><?php print $edit_help; ?></div>
  <?php endif; ?>
  <div class="help-topics-header"><strong>Need help?</strong> Click on the topics below.</div>  
<?php
print $topics;
  endif;
