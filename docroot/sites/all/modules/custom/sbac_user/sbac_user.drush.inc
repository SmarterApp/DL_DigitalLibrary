<?php

/**
 * @file
 * Drush-related callbacks for SBAC User module.
 */

/**
 * Implementation of hook_drush_command()
 *
 */
function sbac_user_drush_command() {
  $items = array();

  $items['sbac-user-accept-terms'] = array(
    'description' => "Accept terms of service for test users on sbacloadtest environment.",
    'examples' => array(
      'drush sbac-user-accept-terms',
    ),
    'callback' => 'drush_sbac_user_accept_terms',
  );

  return $items;
}


/**
 * Accept the terms of service for the test users that we created
 * on the sbacloadtest environment.
 */
function drush_sbac_user_accept_terms() {
  $sql = "SELECT * FROM {users} WHERE name like 'appnovation_%'";
  $result = db_query($sql);
  foreach ($result as $row) {
    $insert = "INSERT INTO {legal_accepted} VALUES (NULL, 30, 1, 'en', " . $row->uid . ", " . time() . ")";
    db_query($insert);
  }
}