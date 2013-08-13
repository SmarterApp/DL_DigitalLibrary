<?php
/**
 * Variable Definitions
 */
define('SBAC_LDAP_QUERY_VAR_STATES', 'sbac_states');
define('SBAC_LDAP_QUERY_VAR_DISTRICTS', 'sbac_districts');
define('SBAC_LDAP_QUERY_VAR_SCHOOLS', 'sbac_schools');
define('SBAC_LDAP_QUERY_VAR_ROLES', 'sbac_roles');
define('SBAC_LDAP_QUERY_VAR_USERS', 'sbac_users');

/**
 * API Function
 * Gets the user structure from LDAP based on the username.
 *
 * @param string $uid - user's uid
 *
 * @return json array $user_struct
 */
function sbac_ldap__api_get_user_struct($uid) {
  $ldap_query = ldap_query_get_queries('sbac_user', 'all', TRUE);
  $ldap_query->filter = str_replace('[uid]', $uid, $ldap_query->filter);
  $results = $ldap_query->query();

  // get states, districts, schools
  $states = sbac_ldap__api_get_states();
  $districts = sbac_ldap__api_get_districts();
  $schools = sbac_ldap__api_get_schools();

  unset($results['count']);
  foreach($results as &$result) {
    $result['states'] = $result['districts'] = $result['schools'] =array();

    //adding states
    $state_ids = $result['stateidnumber'];
    unset($state_ids['count']);
    foreach($state_ids as $sid) {
      $result_states[$states[$sid]['title']] = $states[$sid];
    }
    $result['states'] = $result_states;

    //adding districts
    $district_ids = $result['districtidnumber'];
    unset($district_ids['count']);
    foreach($district_ids as $did) {
      $result_districts[$districts[$did]['title']] = $districts[$did];
    }
    $result['districts'] = $result_districts;

    //adding schools
    $school_ids = $result['schoolidnumber'];
    unset($school_ids['count']);
    foreach($school_ids as $sid) {
      $result_schools[$schools[$sid]['title']] = $schools[$sid];
    }
    $result['schools'] = $result_schools;
  }

  //dsm($results);
  return drupal_json_encode($results);
}
/**
 * API Function
 * Gets the state structure from LDAP.
 */
function sbac_ldap__api_get_states() {
  $ldap_query = ldap_query_get_queries(SBAC_LDAP_QUERY_VAR_STATES, 'all', TRUE);
  $results = $ldap_query->query();
  unset($results['count']);
  return sbac_ldap__helper_format_array($results);
}
/**
 * API Function
 * Gets the district structure from LDAP.
 */
function sbac_ldap__api_get_districts() {
  $ldap_query = ldap_query_get_queries(SBAC_LDAP_QUERY_VAR_DISTRICTS, 'all', TRUE);
  $results = $ldap_query->query();
  unset($results['count']);
  return sbac_ldap__helper_format_array($results);
}
/**
 * API Function
 * Gets the school structure from LDAP.
 */
function sbac_ldap__api_get_schools() {
  $ldap_query = ldap_query_get_queries(SBAC_LDAP_QUERY_VAR_SCHOOLS, 'all', TRUE);
  $results = $ldap_query->query();
  unset($results['count']);
  return sbac_ldap__helper_format_array($results);
}
/**
 * Helper Function
 * Reorder the results based on the gidNumber.
 */
function sbac_ldap__helper_format_array($results) {
  $reindexed_results = array();

  foreach($results as $result) {
    $result['title'] = $result['cn'][0];
    $reindexed_results[$result['gidnumber'][0]] = $result;
  }

  return $reindexed_results;
}