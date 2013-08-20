<?php
/**
 * @file
 * sbac_ldap.ldap_query.inc
 */

/**
 * Implements hook_default_ldap_query().
 */
function sbac_ldap_default_ldap_query() {
  $export = array();

  $qid = new stdClass();
  $qid->disabled = FALSE; /* Edit this to true to make a default qid disabled initially */
  $qid->api_version = 1;
  $qid->qid = 'sbac_districts';
  $qid->name = 'SBAC Districts';
  $qid->sid = 'SBAC';
  $qid->status = FALSE;
  $qid->base_dn_str = 'ou=Districts,dc=incose,dc=com';
  $qid->filter = '(objectClass=posixGroup)';
  $qid->attributes_str = '';
  $qid->sizelimit = 0;
  $qid->timelimit = 0;
  $qid->deref = FALSE;
  $qid->scope = TRUE;
  $export['sbac_districts'] = $qid;

  $qid = new stdClass();
  $qid->disabled = FALSE; /* Edit this to true to make a default qid disabled initially */
  $qid->api_version = 1;
  $qid->qid = 'sbac_groups';
  $qid->name = 'Groups Structure';
  $qid->sid = 'SBAC';
  $qid->status = FALSE;
  $qid->base_dn_str = 'dc=incose,dc=com';
  $qid->filter = '(objectClass=posixGroup)';
  $qid->attributes_str = '';
  $qid->sizelimit = 0;
  $qid->timelimit = 0;
  $qid->deref = FALSE;
  $qid->scope = TRUE;
  $export['sbac_groups'] = $qid;

  $qid = new stdClass();
  $qid->disabled = FALSE; /* Edit this to true to make a default qid disabled initially */
  $qid->api_version = 1;
  $qid->qid = 'sbac_schools';
  $qid->name = 'SBAC Schools';
  $qid->sid = 'SBAC';
  $qid->status = FALSE;
  $qid->base_dn_str = 'ou=Schools,dc=incose,dc=com';
  $qid->filter = '(objectClass=posixGroup)';
  $qid->attributes_str = '';
  $qid->sizelimit = 0;
  $qid->timelimit = 0;
  $qid->deref = FALSE;
  $qid->scope = TRUE;
  $export['sbac_schools'] = $qid;

  $qid = new stdClass();
  $qid->disabled = FALSE; /* Edit this to true to make a default qid disabled initially */
  $qid->api_version = 1;
  $qid->qid = 'sbac_states';
  $qid->name = 'SBAC States';
  $qid->sid = 'SBAC';
  $qid->status = FALSE;
  $qid->base_dn_str = 'ou=States,dc=incose,dc=com';
  $qid->filter = '(objectClass=posixGroup)';
  $qid->attributes_str = '';
  $qid->sizelimit = 0;
  $qid->timelimit = 0;
  $qid->deref = FALSE;
  $qid->scope = TRUE;
  $export['sbac_states'] = $qid;

  $qid = new stdClass();
  $qid->disabled = FALSE; /* Edit this to true to make a default qid disabled initially */
  $qid->api_version = 1;
  $qid->qid = 'sbac_user';
  $qid->name = 'User Structure';
  $qid->sid = 'SBAC';
  $qid->status = FALSE;
  $qid->base_dn_str = 'ou=People,dc=incose,dc=com';
  $qid->filter = '(&(objectClass=sbacperson)(uid=[uid]))';
  $qid->attributes_str = '';
  $qid->sizelimit = 0;
  $qid->timelimit = 0;
  $qid->deref = FALSE;
  $qid->scope = TRUE;
  $export['sbac_user'] = $qid;

  return $export;
}
