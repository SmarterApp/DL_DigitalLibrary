<?php

/*
 * @file block_users.php
 */

/*
 * Script to block all users with the exception of uids listed below.
 * Also resets emails to fake email to prevent flooding during testing.
 * Invoke with drush php-script block_users.php
 */
$user_update = db_update('users')

  ->condition('uid', 0, '<>')
  ->condition('uid', 1, '<>')
  ->condition('uid', 429522, '<>')
  ->condition('uid', 429521, '<>')
  ->condition('uid', 429496, '<>')
  ->condition('uid', 429421, '<>')
  ->condition('uid', 429426, '<>')
  ->condition('uid', 429436, '<>')
  ->condition('uid', 429446, '<>')
  ->condition('uid', 429451, '<>')
  ->condition('uid', 429461, '<>')
  ->expression('status', 'REPLACE(status, :old, :new)', array(
      ':old' => 1,
      ':new' => 0,
    ))
  ->expression('mail', ':mail', array(':mail' => 'fake@email.com'))
  ->execute();
