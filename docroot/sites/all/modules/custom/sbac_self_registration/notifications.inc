<?php

/**
 * Class sbacEmails send email class
 */
class sbacEmails {
  var $email;

  /**
   * sbacEmails constructor.
   *
   * @param string $email The Email address
   */
  public function __construct($email) {
    $this->email = $email;
  }

  /**
   * Send Email
   *
   * @param string $type Email template
   * @param array $arguments Email template arguments
   */
  protected function email_send($type, $arguments) {
    $message = message_create($type, array('arguments' => $arguments));
    $wrapper = entity_metadata_wrapper('message', $message);
    $wrapper->save();
    message_notify_send_message($message, array('mail' => $this->email));
    message_delete_multiple(array($message->mid));
  }

  /**
   * Send Self-Registration Digital Library Coordinator Welcome Email when registered without an ART account and with Unauthorized domain Email
   *
   * @param string $first_name user first name
   * @param string $last_name user last name
   */
  public function send_sr_unauthorized_mail($first_name, $last_name) {
    $type = 'self_registration_digital_library_coordinator_welcome_email';
    $arguments = array(
      '[sbac:first-name]' => $first_name,
      '[sbac:last-name]' => $last_name,
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  /**
   * Send Self-Registration Password Reset Welcome Email when registered with an ART account and with DL_EndUser Role Email
   *
   * @param string $first_name user first name
   * @param string $last_name user last name
   * @param string $reset_link rest link
   */
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

  /**
   * Send Self-Registration Welcome To Existing User Email when registered with an ART account and without DL-EndUser role
   *
   * @param string $first_name user first name
   * @param string $last_name user last name
   */
  public function send_sr_missing_role_mail($first_name, $last_name) {
    $type = 'self_registration_welcome_to_existing_user_email';
    $arguments = array(
      '[sbac:first-name]' => $first_name,
      '[sbac:last-name]' => $last_name,
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  /**
   * Send Password Reset Register Email when registered with an authorized domain Email
   */
  public function send_pr_register_mail() {
    $type = 'password_reset_register_email';
    $arguments = array(
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  /**
   * Send Password Reset Digital Library Coordinator Email when registered without an ART account and with Unauthorized domain Email
   */
  public function send_pr_unauthorized_mail() {
    $type = 'password_reset_digital_library_coordinator_email';
    $arguments = array(
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }

  /**
   * Send Password Reset Email when registered with an ART account
   *
   * @param $reset_link Reset password link
   */
  public function send_pr_reset_mail($reset_link) {
    $type = 'password_reset_password_reset_email';
    $arguments = array(
      '![sbac:reset-link]' => $reset_link,
      '[sbac:email]' => $this->email
    );
    $this->email_send($type, $arguments);
  }
}
