<?php

class sbacEmails {
  var $email;

  public function __construct($email) {
    $this->email = $email;
  }

  protected function email_send($type, $arguments) {
    $message = message_create($type, array('arguments' => $arguments));
    $wrapper = entity_metadata_wrapper('message', $message);
    $wrapper->save();
    message_notify_send_message($message, array('mail' => $this->email));
    message_delete_multiple(array($message->mid));
  }

  public function send_sr_unauthorized_mail($first_name, $last_name) {
    $type = 'self_registration_digital_library_coordinator_welcome_email';
    $arguments = array(
      '[sbac:first-name]' => $first_name,
      '[sbac:last-name]' => $last_name,
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  public function send_sr_user_exists_mail($first_name, $last_name, $reset_link) {
    $type = 'self_registration_password_reset_welcome_email';
    $arguments = array(
      '[sbac:first-name]' => $first_name,
      '[sbac:last-name]' => $last_name,
      '![sbac:reset-link]' => $reset_link,
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  public function send_sr_missing_role_mail($first_name, $last_name) {
    $type = 'self_registration_welcome_to_existing_user_email';
    $arguments = array(
      '[sbac:first-name]' => $first_name,
      '[sbac:last-name]' => $last_name,
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  public function send_pr_register_mail() {
    $type = 'password_reset_register_email';
    $arguments = array(
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  public function send_pr_unauthorized_mail() {
    $type = 'password_reset_digital_library_coordinator_email';
    $arguments = array(
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  public function send_pr_reset_mail($reset_link) {
    $type = 'password_reset_password_reset_email';
    $arguments = array(
      '![sbac:reset-link]' => $reset_link,
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }
}
