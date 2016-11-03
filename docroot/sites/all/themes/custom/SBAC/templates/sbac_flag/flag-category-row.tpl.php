<div class="flag-row">
  <div class="flag-user">By <?php echo $username; ?> on <?php echo $created; ?></div>
    <div class="flag-email-state">
	  <?php if (isset($user_email)): ?>
	  	<a href= "mailto:<?php echo $user_email; ?>"> <?php echo $user_email; ?></a>
	  <?php endif; ?>
	  <?php if (isset($user_state)): ?>
	  	, <?php echo $user_state; ?>
	  <?php endif; ?>
  </div>
  <div class="flag-message"><?php echo $flag_comment; ?></div>
</div>