<h1>Password Reset Confirmation Sent Successfully!</h1>

<p>We have sent an email to
<?php if($mail = $_GET['mail']):?>
<?php print $mail; ?>
<?php else:?>
<?php print 'you'; ?>
<?php endif; ?>
 containing a temporary link that will allow you to reset your password during the next 24 hours. Please check your spam folder if the email doesn't appear within a few minutes.</p>
<?php print l('<< return to login', '<front>'); ?>
