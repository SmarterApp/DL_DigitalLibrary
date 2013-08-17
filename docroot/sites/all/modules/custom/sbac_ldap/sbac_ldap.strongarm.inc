<?php
/**
 * @file
 * sbac_ldap.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function sbac_ldap_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_authentication_conf';
  $strongarm->value = array(
    'sids' => array(
      'SBAC Internal' => 'SBAC Internal',
    ),
    'authenticationMode' => 1,
    'loginUIUsernameTxt' => NULL,
    'loginUIPasswordTxt' => NULL,
    'ldapUserHelpLinkUrl' => NULL,
    'ldapUserHelpLinkText' => 'Logon Help',
    'emailOption' => 3,
    'emailUpdate' => 1,
    'passwordOption' => 2,
    'allowOnlyIfTextInDn' => array(),
    'excludeIfTextInDn' => array(),
    'allowTestPhp' => '',
    'excludeIfNoAuthorizations' => NULL,
    'ssoRemoteUserStripDomainName' => NULL,
    'ssoExcludedPaths' => array(),
    'ssoExcludedHosts' => array(),
    'seamlessLogin' => NULL,
    'ldapImplementation' => NULL,
    'cookieExpire' => NULL,
  );
  $export['ldap_authentication_conf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_help_watchdog_detail';
  $strongarm->value = 1;
  $export['ldap_help_watchdog_detail'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_encryption';
  $strongarm->value = '10';
  $export['ldap_servers_encryption'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_encrypt_key';
  $strongarm->value = 'pidXB49YQ4';
  $export['ldap_servers_encrypt_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_require_ssl_for_credentails';
  $strongarm->value = 0;
  $export['ldap_servers_require_ssl_for_credentails'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_test_servers';
  $strongarm->value = array(
    0 => 'activedirectory1',
    1 => 'openldap1',
  );
  $export['ldap_test_servers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_test_server__activedirectory1';
  $strongarm->value = array(
    'properties' => array(
      'sid' => 'activedirectory1',
      'name' => 'Test Active Directory LDAP',
      'inDatabase' => TRUE,
      'status' => 1,
      'ldap_type' => 'activedirectory',
      'address' => 'ldap.hogwarts.edu',
      'port' => 389,
      'tls' => FALSE,
      'bind_method' => 1,
      'basedn' => array(
        0 => 'dc=hogwarts,dc=edu',
      ),
      'binddn' => 'cn=service-account,ou=people,dc=hogwarts,dc=edu',
      'bindpw' => 'goodpwd',
      'user_dn_expression' => NULL,
      'user_attr' => 'samaccountname',
      'mail_attr' => 'mail',
      'mail_template' => NULL,
      'unique_persistent_attr' => 'guid',
      'unique_persistent_attr_binary' => FALSE,
      'ldap_to_drupal_user' => FALSE,
      'ldapToDrupalUserPhp' => NULL,
      'groupNested' => 0,
      'groupObjectClass' => 'group',
      'groupUserMembershipsAttrExists' => TRUE,
      'groupUserMembershipsAttr' => 'memberof',
      'groupMembershipsAttr' => 'member',
      'groupMembershipsAttrMatchingUserAttr' => 'dn',
      'search_pagination' => 0,
      'searchPageSize' => NULL,
    ),
    'methodResponses' => array(
      'connect' => 0,
    ),
    'clones' => 7,
    'search_results' => array(
      '(&(objectClass=group)(member=cn=hpotter,ou=people,dc=hogwarts,dc=edu))' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          ),
          1 => array(
            'count' => 1,
            'dn' => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          ),
          2 => array(
            'count' => 1,
            'dn' => 'cn=honors students,ou=groups,dc=hogwarts,dc=edu',
          ),
          'count' => 3,
        ),
      ),
      '(&(objectClass=group)(|(member=cn=gryffindor,ou=groups,dc=hogwarts,dc=edu)(member=cn=students,ou=groups,dc=hogwarts,dc=edu)(member=cn=honors students,ou=groups,dc=hogwarts,dc=edu)))' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=users,ou=groups,dc=hogwarts,dc=edu',
          ),
          'count' => 1,
        ),
      ),
      '(cn=hpotter)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(samaccountname=hpotter)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(cn=hgrainger)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(samaccountname=hgrainger)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(cn=ssnape)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(samaccountname=ssnape)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(cn=adumbledore)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(samaccountname=adumbledore)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(samaccountname=hpotter-granger)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
    ),
    'users' => array(
      'cn=hpotter,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'hpotter',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'hpotter@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '1',
            'count' => 1,
          ),
          'guid' => array(
            0 => '101',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'hpotter',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=hgrainger,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'hgrainger',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'hgrainger@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '2',
            'count' => 1,
          ),
          'guid' => array(
            0 => '102',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Granger',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Hermione',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '4',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'hgrainger',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=rweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'rweasley',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'rweasley@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '3',
            'count' => 1,
          ),
          'guid' => array(
            0 => '103',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Weasley',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Ron',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.6',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'rweasley',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=fweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'fweasley',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'fweasley@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '4',
            'count' => 1,
          ),
          'guid' => array(
            0 => '104',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Weasley',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Fred',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'fweasley',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=gweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'gweasley',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'gweasley@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '5',
            'count' => 1,
          ),
          'guid' => array(
            0 => '105',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Weasley',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'George',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '2.7',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'gweasley',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'dmalfoy',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'dmalfoy@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '6',
            'count' => 1,
          ),
          'guid' => array(
            0 => '106',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Malfoy',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Draco',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Slytherin',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.7',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'dmalfoy',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=triddle,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'triddle',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'triddle@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '7',
            'count' => 1,
          ),
          'guid' => array(
            0 => '107',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Riddle',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Tom',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Slytherin',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.6',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'triddle',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=triddle,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=ggoyle,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'ggoyle',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'ggoyle@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '8',
            'count' => 1,
          ),
          'guid' => array(
            0 => '108',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Goyle',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Gregory',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Slytherin',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.3',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'ggoyle',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=ssnape,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'ssnape',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'ssnape@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '9',
            'count' => 1,
          ),
          'guid' => array(
            0 => '109',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Snape',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Severus ',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Slytherin',
            'count' => 1,
          ),
          'department' => array(
            0 => 'Defence Against the Dark Arts professor ',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'ssnape',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=adumbledore,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'adumbledore',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'adumbledore@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '10',
            'count' => 1,
          ),
          'guid' => array(
            0 => '110',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Dumbledore',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Albus',
            'count' => 1,
          ),
          'house' => array(
            0 => '',
            'count' => 1,
          ),
          'department' => array(
            0 => 'Head Master Of Hogwarts',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'adumbledore',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'mmcgonagall',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'mmcgonagall@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '11',
            'count' => 1,
          ),
          'guid' => array(
            0 => '111',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'McGonagall',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Minerva',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => 'Tranfiguration/ Deputy Head Mistress',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'mmcgonagall',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=spomana,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'spomana',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'spomana@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '12',
            'count' => 1,
          ),
          'guid' => array(
            0 => '112',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Pomona',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Sprout',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Hufflepuff',
            'count' => 1,
          ),
          'department' => array(
            0 => 'Herbology',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'spomana',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=rhagrid,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'rhagrid',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'rhagrid@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '13',
            'count' => 1,
          ),
          'guid' => array(
            0 => '113',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Hagrid',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Rubeus',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'rhagrid',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=service-account,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'service-account',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'service-account@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '19',
            'count' => 1,
          ),
          'guid' => array(
            0 => '119',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Service',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Account',
            'count' => 1,
          ),
          'house' => array(
            0 => '',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 0,
            'count' => 1,
          ),
          'staff' => array(
            0 => 0,
            'count' => 1,
          ),
          'student' => array(
            0 => 0,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'service-account',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=service-account,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=clone0,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'clone0',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'clone0@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => 20,
            'count' => 1,
          ),
          'guid' => array(
            0 => 120,
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter_0',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'clone0',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=clone0,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=clone1,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'clone1',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'clone1@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => 21,
            'count' => 1,
          ),
          'guid' => array(
            0 => 121,
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter_1',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'clone1',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=clone1,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=clone2,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'clone2',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'clone2@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => 22,
            'count' => 1,
          ),
          'guid' => array(
            0 => 122,
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter_2',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'clone2',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=clone2,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=clone3,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'clone3',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'clone3@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => 23,
            'count' => 1,
          ),
          'guid' => array(
            0 => 123,
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter_3',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'clone3',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=clone3,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=clone4,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'clone4',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'clone4@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => 24,
            'count' => 1,
          ),
          'guid' => array(
            0 => 124,
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter_4',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'clone4',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=clone4,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=clone5,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'clone5',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'clone5@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => 25,
            'count' => 1,
          ),
          'guid' => array(
            0 => 125,
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter_5',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'clone5',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=clone5,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=clone6,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'clone6',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'clone6@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => 26,
            'count' => 1,
          ),
          'guid' => array(
            0 => 126,
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter_6',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
          'samaccountname' => array(
            0 => 'clone6',
            'count' => 1,
          ),
          'distinguishedname' => array(
            0 => 'cn=clone6,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
    ),
    'groups' => array(
      'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'gryffindor',
            'count' => 1,
          ),
          'gid' => array(
            0 => '1',
            'count' => 1,
          ),
          'guid' => array(
            0 => 201,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            2 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
            3 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
            4 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
            5 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
            6 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
            'count' => 7,
          ),
        ),
      ),
      'cn=slytherin,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'slytherin',
            'count' => 1,
          ),
          'gid' => array(
            0 => '2',
            'count' => 1,
          ),
          'guid' => array(
            0 => 202,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=triddle,ou=people,dc=hogwarts,dc=edu',
            2 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
            3 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
            4 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            'count' => 5,
          ),
        ),
      ),
      'cn=hufflepuff,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'hufflepuff',
            'count' => 1,
          ),
          'gid' => array(
            0 => '3',
            'count' => 1,
          ),
          'guid' => array(
            0 => 203,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=students,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'students',
            'count' => 1,
          ),
          'gid' => array(
            0 => '4',
            'count' => 1,
          ),
          'guid' => array(
            0 => 204,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            2 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
            3 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
            4 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
            5 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            6 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
            'count' => 7,
          ),
        ),
      ),
      'cn=honors students,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'honors students',
            'count' => 1,
          ),
          'gid' => array(
            0 => '5',
            'count' => 1,
          ),
          'guid' => array(
            0 => 205,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            'count' => 2,
          ),
        ),
      ),
      'cn=probation students,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'probation students',
            'count' => 1,
          ),
          'gid' => array(
            0 => '6',
            'count' => 1,
          ),
          'guid' => array(
            0 => 206,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
            'count' => 2,
          ),
        ),
      ),
      'cn=faculty,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'faculty',
            'count' => 1,
          ),
          'gid' => array(
            0 => '7',
            'count' => 1,
          ),
          'guid' => array(
            0 => 207,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
            2 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
            3 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
            'count' => 4,
          ),
        ),
      ),
      'cn=staff,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'staff',
            'count' => 1,
          ),
          'gid' => array(
            0 => '8',
            'count' => 1,
          ),
          'guid' => array(
            0 => 208,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=users,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'users',
            'count' => 1,
          ),
          'gid' => array(
            0 => '9',
            'count' => 1,
          ),
          'guid' => array(
            0 => 209,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
            1 => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
            2 => 'cn=staff,ou=groups,dc=hogwarts,dc=edu',
            'count' => 3,
          ),
        ),
      ),
    ),
    'ldap' => array(
      'cn=hpotter,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'hpotter',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'hpotter@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '1',
          'count' => 1,
        ),
        'guid' => array(
          0 => '101',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'hpotter',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          2 => 'cn=honors students,ou=groups,dc=hogwarts,dc=edu',
          'count' => 3,
        ),
      ),
      'cn=hgrainger,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'hgrainger',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'hgrainger@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '2',
          'count' => 1,
        ),
        'guid' => array(
          0 => '102',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Granger',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Hermione',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '4',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'hgrainger',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          2 => 'cn=honors students,ou=groups,dc=hogwarts,dc=edu',
          'count' => 3,
        ),
      ),
      'cn=rweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'rweasley',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'rweasley@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '3',
          'count' => 1,
        ),
        'guid' => array(
          0 => '103',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Weasley',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Ron',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.6',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'rweasley',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=fweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'fweasley',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'fweasley@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '4',
          'count' => 1,
        ),
        'guid' => array(
          0 => '104',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Weasley',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Fred',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'fweasley',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=gweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'gweasley',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'gweasley@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '5',
          'count' => 1,
        ),
        'guid' => array(
          0 => '105',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Weasley',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'George',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '2.7',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'gweasley',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'dmalfoy',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'dmalfoy@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '6',
          'count' => 1,
        ),
        'guid' => array(
          0 => '106',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Malfoy',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Draco',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Slytherin',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.7',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'dmalfoy',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=slytherin,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=slytherin,ou=groups,dc=hogwarts,dc=edu',
          2 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          3 => 'cn=probation students,ou=groups,dc=hogwarts,dc=edu',
          'count' => 4,
        ),
      ),
      'cn=triddle,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'triddle',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'triddle@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '7',
          'count' => 1,
        ),
        'guid' => array(
          0 => '107',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Riddle',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Tom',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Slytherin',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.6',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'triddle',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=triddle,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=slytherin,ou=groups,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
      ),
      'cn=ggoyle,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'ggoyle',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'ggoyle@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '8',
          'count' => 1,
        ),
        'guid' => array(
          0 => '108',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Goyle',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Gregory',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Slytherin',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.3',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'ggoyle',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=slytherin,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          2 => 'cn=probation students,ou=groups,dc=hogwarts,dc=edu',
          'count' => 3,
        ),
      ),
      'cn=ssnape,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'ssnape',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'ssnape@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '9',
          'count' => 1,
        ),
        'guid' => array(
          0 => '109',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Snape',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Severus ',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Slytherin',
          'count' => 1,
        ),
        'department' => array(
          0 => 'Defence Against the Dark Arts professor ',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'ssnape',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=slytherin,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=adumbledore,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'adumbledore',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'adumbledore@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '10',
          'count' => 1,
        ),
        'guid' => array(
          0 => '110',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Dumbledore',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Albus',
          'count' => 1,
        ),
        'house' => array(
          0 => '',
          'count' => 1,
        ),
        'department' => array(
          0 => 'Head Master Of Hogwarts',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'adumbledore',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
      ),
      'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'mmcgonagall',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'mmcgonagall@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '11',
          'count' => 1,
        ),
        'guid' => array(
          0 => '111',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'McGonagall',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Minerva',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => 'Tranfiguration/ Deputy Head Mistress',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'mmcgonagall',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=spomana,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'spomana',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'spomana@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '12',
          'count' => 1,
        ),
        'guid' => array(
          0 => '112',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Pomona',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Sprout',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Hufflepuff',
          'count' => 1,
        ),
        'department' => array(
          0 => 'Herbology',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'spomana',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=hufflepuff,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=rhagrid,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'rhagrid',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'rhagrid@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '13',
          'count' => 1,
        ),
        'guid' => array(
          0 => '113',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Hagrid',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Rubeus',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'rhagrid',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
        'memberof' => array(
          0 => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=staff,ou=groups,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=service-account,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'service-account',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'service-account@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '19',
          'count' => 1,
        ),
        'guid' => array(
          0 => '119',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Service',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Account',
          'count' => 1,
        ),
        'house' => array(
          0 => '',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 0,
          'count' => 1,
        ),
        'staff' => array(
          0 => 0,
          'count' => 1,
        ),
        'student' => array(
          0 => 0,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'service-account',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=service-account,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
      ),
      'cn=clone0,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'clone0',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'clone0@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => 20,
          'count' => 1,
        ),
        'guid' => array(
          0 => 120,
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter_0',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'clone0',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=clone0,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
      ),
      'cn=clone1,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'clone1',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'clone1@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => 21,
          'count' => 1,
        ),
        'guid' => array(
          0 => 121,
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter_1',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'clone1',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=clone1,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
      ),
      'cn=clone2,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'clone2',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'clone2@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => 22,
          'count' => 1,
        ),
        'guid' => array(
          0 => 122,
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter_2',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'clone2',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=clone2,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
      ),
      'cn=clone3,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'clone3',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'clone3@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => 23,
          'count' => 1,
        ),
        'guid' => array(
          0 => 123,
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter_3',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'clone3',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=clone3,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
      ),
      'cn=clone4,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'clone4',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'clone4@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => 24,
          'count' => 1,
        ),
        'guid' => array(
          0 => 124,
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter_4',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'clone4',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=clone4,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
      ),
      'cn=clone5,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'clone5',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'clone5@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => 25,
          'count' => 1,
        ),
        'guid' => array(
          0 => 125,
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter_5',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'clone5',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=clone5,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
      ),
      'cn=clone6,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'clone6',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'clone6@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => 26,
          'count' => 1,
        ),
        'guid' => array(
          0 => 126,
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter_6',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'samaccountname' => array(
          0 => 'clone6',
          'count' => 1,
        ),
        'distinguishedname' => array(
          0 => 'cn=clone6,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'count' => 16,
      ),
      'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'gryffindor',
          'count' => 1,
        ),
        'gid' => array(
          0 => '1',
          'count' => 1,
        ),
        'guid' => array(
          0 => 201,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
          2 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
          3 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
          4 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
          5 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
          6 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
          'count' => 7,
        ),
      ),
      'cn=slytherin,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'slytherin',
          'count' => 1,
        ),
        'gid' => array(
          0 => '2',
          'count' => 1,
        ),
        'guid' => array(
          0 => 202,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=triddle,ou=people,dc=hogwarts,dc=edu',
          2 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
          3 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
          4 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          'count' => 5,
        ),
      ),
      'cn=hufflepuff,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'hufflepuff',
          'count' => 1,
        ),
        'gid' => array(
          0 => '3',
          'count' => 1,
        ),
        'guid' => array(
          0 => 203,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
      ),
      'cn=students,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'students',
          'count' => 1,
        ),
        'gid' => array(
          0 => '4',
          'count' => 1,
        ),
        'guid' => array(
          0 => 204,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
          2 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
          3 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
          4 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
          5 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          6 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
          'count' => 7,
        ),
        'memberof' => array(
          0 => 'cn=users,ou=groups,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
      ),
      'cn=honors students,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'honors students',
          'count' => 1,
        ),
        'gid' => array(
          0 => '5',
          'count' => 1,
        ),
        'guid' => array(
          0 => 205,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=probation students,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'probation students',
          'count' => 1,
        ),
        'gid' => array(
          0 => '6',
          'count' => 1,
        ),
        'guid' => array(
          0 => 206,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=faculty,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'faculty',
          'count' => 1,
        ),
        'gid' => array(
          0 => '7',
          'count' => 1,
        ),
        'guid' => array(
          0 => 207,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
          2 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
          3 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
          'count' => 4,
        ),
        'memberof' => array(
          0 => 'cn=users,ou=groups,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
      ),
      'cn=staff,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'staff',
          'count' => 1,
        ),
        'gid' => array(
          0 => '8',
          'count' => 1,
        ),
        'guid' => array(
          0 => 208,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
        'memberof' => array(
          0 => 'cn=users,ou=groups,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
      ),
      'cn=users,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'users',
          'count' => 1,
        ),
        'gid' => array(
          0 => '9',
          'count' => 1,
        ),
        'guid' => array(
          0 => 209,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
          2 => 'cn=staff,ou=groups,dc=hogwarts,dc=edu',
          'count' => 3,
        ),
      ),
    ),
    'csv' => array(
      'groups' => array(
        201 => array(
          'guid' => '201',
          'gid' => '1',
          'cn' => 'gryffindor',
          'dn' => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
        ),
        202 => array(
          'guid' => '202',
          'gid' => '2',
          'cn' => 'slytherin',
          'dn' => 'cn=slytherin,ou=groups,dc=hogwarts,dc=edu',
        ),
        203 => array(
          'guid' => '203',
          'gid' => '3',
          'cn' => 'hufflepuff',
          'dn' => 'cn=hufflepuff,ou=groups,dc=hogwarts,dc=edu',
        ),
        204 => array(
          'guid' => '204',
          'gid' => '4',
          'cn' => 'students',
          'dn' => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
        ),
        205 => array(
          'guid' => '205',
          'gid' => '5',
          'cn' => 'honors students',
          'dn' => 'cn=honors students,ou=groups,dc=hogwarts,dc=edu',
        ),
        206 => array(
          'guid' => '206',
          'gid' => '6',
          'cn' => 'probation students',
          'dn' => 'cn=probation students,ou=groups,dc=hogwarts,dc=edu',
        ),
        207 => array(
          'guid' => '207',
          'gid' => '7',
          'cn' => 'faculty',
          'dn' => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
        ),
        208 => array(
          'guid' => '208',
          'gid' => '8',
          'cn' => 'staff',
          'dn' => 'cn=staff,ou=groups,dc=hogwarts,dc=edu',
        ),
        209 => array(
          'guid' => '209',
          'gid' => '9',
          'cn' => 'users',
          'dn' => 'cn=users,ou=groups,dc=hogwarts,dc=edu',
        ),
      ),
      'users' => array(
        101 => array(
          'guid' => '101',
          'uid' => '1',
          'cn' => 'hpotter',
          'lname' => 'Potter',
          'fname' => 'Harry',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.8',
          'probation' => 'N',
          'dn' => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
        ),
        102 => array(
          'guid' => '102',
          'uid' => '2',
          'cn' => 'hgrainger',
          'lname' => 'Granger',
          'fname' => 'Hermione',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '4',
          'probation' => 'N',
          'dn' => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
        ),
        103 => array(
          'guid' => '103',
          'uid' => '3',
          'cn' => 'rweasley',
          'lname' => 'Weasley',
          'fname' => 'Ron',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.6',
          'probation' => 'N',
          'dn' => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
        ),
        104 => array(
          'guid' => '104',
          'uid' => '4',
          'cn' => 'fweasley',
          'lname' => 'Weasley',
          'fname' => 'Fred',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3',
          'probation' => 'N',
          'dn' => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
        ),
        105 => array(
          'guid' => '105',
          'uid' => '5',
          'cn' => 'gweasley',
          'lname' => 'Weasley',
          'fname' => 'George',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '2.7',
          'probation' => 'N',
          'dn' => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
        ),
        106 => array(
          'guid' => '106',
          'uid' => '6',
          'cn' => 'dmalfoy',
          'lname' => 'Malfoy',
          'fname' => 'Draco',
          'house' => 'Slytherin',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.7',
          'probation' => 'Y',
          'dn' => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
        ),
        107 => array(
          'guid' => '107',
          'uid' => '7',
          'cn' => 'triddle',
          'lname' => 'Riddle',
          'fname' => 'Tom',
          'house' => 'Slytherin',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.6',
          'probation' => 'N',
          'dn' => 'cn=triddle,ou=people,dc=hogwarts,dc=edu',
        ),
        108 => array(
          'guid' => '108',
          'uid' => '8',
          'cn' => 'ggoyle',
          'lname' => 'Goyle',
          'fname' => 'Gregory',
          'house' => 'Slytherin',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.3',
          'probation' => 'Y',
          'dn' => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
        ),
        109 => array(
          'guid' => '109',
          'uid' => '9',
          'cn' => 'ssnape',
          'lname' => 'Snape',
          'fname' => 'Severus ',
          'house' => 'Slytherin',
          'department' => 'Defence Against the Dark Arts professor ',
          'faculty' => 'Y',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
        ),
        110 => array(
          'guid' => '110',
          'uid' => '10',
          'cn' => 'adumbledore',
          'lname' => 'Dumbledore',
          'fname' => 'Albus',
          'house' => '',
          'department' => 'Head Master Of Hogwarts',
          'faculty' => 'Y',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
        ),
        111 => array(
          'guid' => '111',
          'uid' => '11',
          'cn' => 'mmcgonagall',
          'lname' => 'McGonagall',
          'fname' => 'Minerva',
          'house' => 'Gryffindor',
          'department' => 'Tranfiguration/ Deputy Head Mistress',
          'faculty' => 'Y',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
        ),
        112 => array(
          'guid' => '112',
          'uid' => '12',
          'cn' => 'spomana',
          'lname' => 'Pomona',
          'fname' => 'Sprout',
          'house' => 'Hufflepuff',
          'department' => 'Herbology',
          'faculty' => 'Y',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
        ),
        113 => array(
          'guid' => '113',
          'uid' => '13',
          'cn' => 'rhagrid',
          'lname' => 'Hagrid',
          'fname' => 'Rubeus',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
        ),
        119 => array(
          'guid' => '119',
          'uid' => '19',
          'cn' => 'service-account',
          'lname' => 'Service',
          'fname' => 'Account',
          'house' => '',
          'department' => '',
          'faculty' => '',
          'staff' => '',
          'student' => '',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=service-account,ou=people,dc=hogwarts,dc=edu',
        ),
      ),
      'memberships' => array(
        1 => array(
          'membershipid' => '1',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '101',
          'group_guid' => '201',
        ),
        2 => array(
          'membershipid' => '2',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '102',
          'group_guid' => '201',
        ),
        3 => array(
          'membershipid' => '3',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '103',
          'group_guid' => '201',
        ),
        4 => array(
          'membershipid' => '4',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '104',
          'group_guid' => '201',
        ),
        5 => array(
          'membershipid' => '5',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '105',
          'group_guid' => '201',
        ),
        6 => array(
          'membershipid' => '6',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '111',
          'group_guid' => '201',
        ),
        7 => array(
          'membershipid' => '7',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '113',
          'group_guid' => '201',
        ),
        8 => array(
          'membershipid' => '8',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '106',
          'group_guid' => '202',
        ),
        9 => array(
          'membershipid' => '9',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '107',
          'group_guid' => '202',
        ),
        10 => array(
          'membershipid' => '10',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '108',
          'group_guid' => '202',
        ),
        11 => array(
          'membershipid' => '11',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '109',
          'group_guid' => '202',
        ),
        12 => array(
          'membershipid' => '12',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '106',
          'group_guid' => '202',
        ),
        13 => array(
          'membershipid' => '13',
          'gid' => '3',
          'group_cn' => 'hufflepuff',
          'member_guid' => '112',
          'group_guid' => '203',
        ),
        14 => array(
          'membershipid' => '14',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '101',
          'group_guid' => '204',
        ),
        15 => array(
          'membershipid' => '15',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '102',
          'group_guid' => '204',
        ),
        16 => array(
          'membershipid' => '16',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '103',
          'group_guid' => '204',
        ),
        17 => array(
          'membershipid' => '17',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '104',
          'group_guid' => '204',
        ),
        18 => array(
          'membershipid' => '18',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '105',
          'group_guid' => '204',
        ),
        19 => array(
          'membershipid' => '19',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '106',
          'group_guid' => '204',
        ),
        20 => array(
          'membershipid' => '20',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '108',
          'group_guid' => '204',
        ),
        21 => array(
          'membershipid' => '21',
          'gid' => '5',
          'group_cn' => 'honors students',
          'member_guid' => '101',
          'group_guid' => '205',
        ),
        22 => array(
          'membershipid' => '22',
          'gid' => '5',
          'group_cn' => 'honors students',
          'member_guid' => '102',
          'group_guid' => '205',
        ),
        23 => array(
          'membershipid' => '23',
          'gid' => '6',
          'group_cn' => 'probation students',
          'member_guid' => '106',
          'group_guid' => '206',
        ),
        24 => array(
          'membershipid' => '24',
          'gid' => '6',
          'group_cn' => 'probation students',
          'member_guid' => '108',
          'group_guid' => '206',
        ),
        25 => array(
          'membershipid' => '25',
          'gid' => '7',
          'group_cn' => 'faculty',
          'member_guid' => '109',
          'group_guid' => '207',
        ),
        26 => array(
          'membershipid' => '26',
          'gid' => '7',
          'group_cn' => 'faculty',
          'member_guid' => '110',
          'group_guid' => '207',
        ),
        27 => array(
          'membershipid' => '27',
          'gid' => '7',
          'group_cn' => 'faculty',
          'member_guid' => '111',
          'group_guid' => '207',
        ),
        28 => array(
          'membershipid' => '28',
          'gid' => '7',
          'group_cn' => 'faculty',
          'member_guid' => '112',
          'group_guid' => '207',
        ),
        29 => array(
          'membershipid' => '29',
          'gid' => '8',
          'group_cn' => 'staff',
          'member_guid' => '113',
          'group_guid' => '208',
        ),
        30 => array(
          'membershipid' => '30',
          'gid' => '9',
          'group_cn' => 'users',
          'member_guid' => '204',
          'group_guid' => '209',
        ),
        31 => array(
          'membershipid' => '31',
          'gid' => '9',
          'group_cn' => 'users',
          'member_guid' => '207',
          'group_guid' => '209',
        ),
        32 => array(
          'membershipid' => '32',
          'gid' => '9',
          'group_cn' => 'users',
          'member_guid' => '208',
          'group_guid' => '209',
        ),
      ),
      'conf' => array(
        'hogwarts' => array(
          'id' => 'hogwarts',
          'mailhostname' => 'hogwarts.edu',
          'userbasedn' => 'ou=people,dc=hogwarts,dc=edu',
          'groupbasedn' => 'ou=groups,dc=hogwarts,dc=edu',
        ),
      ),
    ),
  );
  $export['ldap_test_server__activedirectory1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_test_server__openldap1';
  $strongarm->value = array(
    'properties' => array(
      'sid' => 'openldap1',
      'name' => 'Test Open LDAP',
      'inDatabase' => TRUE,
      'status' => 1,
      'ldap_type' => 'openldap',
      'address' => 'ldap.hogwarts.edu',
      'port' => 389,
      'tls' => FALSE,
      'bind_method' => 1,
      'basedn' => array(
        0 => 'dc=hogwarts,dc=edu',
      ),
      'binddn' => 'cn=service-account,ou=people,dc=hogwarts,dc=edu',
      'bindpw' => 'goodpwd',
      'user_dn_expression' => NULL,
      'user_attr' => 'cn',
      'mail_attr' => 'mail',
      'mail_template' => NULL,
      'unique_persistent_attr' => 'guid',
      'unique_persistent_attr_binary' => FALSE,
      'ldap_to_drupal_user' => FALSE,
      'ldapToDrupalUserPhp' => NULL,
      'groupObjectClass' => 'groupofnames',
      'groupUserMembershipsAttrExists' => FALSE,
      'groupUserMembershipsAttr' => NULL,
      'groupMembershipsAttr' => 'member',
      'groupMembershipsAttrMatchingUserAttr' => 'dn',
      'search_pagination' => 0,
      'searchPageSize' => NULL,
    ),
    'methodResponses' => array(
      'connect' => 0,
    ),
    'search_results' => array(
      '(&(objectClass=group)(|(member=cn=gryffindor,ou=groups,dc=hogwarts,dc=edu)(member=cn=students,ou=groups,dc=hogwarts,dc=edu)(member=cn=honors students,ou=groups,dc=hogwarts,dc=edu)))' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=users,ou=groups,dc=hogwarts,dc=edu',
          ),
          'count' => 1,
        ),
      ),
      '(cn=hpotter)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(cn=hpotter-granger)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(cn=ssnape)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(cn=adumbledore)' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
            'FULLENTRY' => TRUE,
          ),
          'count' => 1,
        ),
      ),
      '(&(objectClass=groupofnames)(member=cn=hpotter,ou=people,dc=hogwarts,dc=edu))' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
          ),
          1 => array(
            'count' => 1,
            'dn' => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          ),
          2 => array(
            'count' => 1,
            'dn' => 'cn=honors students,ou=groups,dc=hogwarts,dc=edu',
          ),
          'count' => 3,
        ),
      ),
      '(&(objectClass=groupofnames)(|(member=cn=gryffindor,ou=groups,dc=hogwarts,dc=edu)(member=cn=students,ou=groups,dc=hogwarts,dc=edu)(member=cn=honors students,ou=groups,dc=hogwarts,dc=edu)))' => array(
        'dc=hogwarts,dc=edu' => array(
          0 => array(
            'count' => 1,
            'dn' => 'cn=users,ou=groups,dc=hogwarts,dc=edu',
          ),
          'count' => 1,
        ),
      ),
    ),
    'users' => array(
      'cn=hpotter,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'hpotter',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'hpotter@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '1',
            'count' => 1,
          ),
          'guid' => array(
            0 => '101',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Potter',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Harry',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.8',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=hgrainger,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'hgrainger',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'hgrainger@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '2',
            'count' => 1,
          ),
          'guid' => array(
            0 => '102',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Granger',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Hermione',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '4',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=rweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'rweasley',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'rweasley@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '3',
            'count' => 1,
          ),
          'guid' => array(
            0 => '103',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Weasley',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Ron',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.6',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=fweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'fweasley',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'fweasley@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '4',
            'count' => 1,
          ),
          'guid' => array(
            0 => '104',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Weasley',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Fred',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=gweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'gweasley',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'gweasley@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '5',
            'count' => 1,
          ),
          'guid' => array(
            0 => '105',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Weasley',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'George',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '2.7',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'dmalfoy',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'dmalfoy@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '6',
            'count' => 1,
          ),
          'guid' => array(
            0 => '106',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Malfoy',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Draco',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Slytherin',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.7',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=triddle,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'triddle',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'triddle@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '7',
            'count' => 1,
          ),
          'guid' => array(
            0 => '107',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Riddle',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Tom',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Slytherin',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.6',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=ggoyle,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'ggoyle',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'ggoyle@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '8',
            'count' => 1,
          ),
          'guid' => array(
            0 => '108',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Goyle',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Gregory',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Slytherin',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '3.3',
            'count' => 1,
          ),
          'probation' => array(
            0 => 1,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=ssnape,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'ssnape',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'ssnape@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '9',
            'count' => 1,
          ),
          'guid' => array(
            0 => '109',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Snape',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Severus ',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Slytherin',
            'count' => 1,
          ),
          'department' => array(
            0 => 'Defence Against the Dark Arts professor ',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=adumbledore,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'adumbledore',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'adumbledore@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '10',
            'count' => 1,
          ),
          'guid' => array(
            0 => '110',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Dumbledore',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Albus',
            'count' => 1,
          ),
          'house' => array(
            0 => '',
            'count' => 1,
          ),
          'department' => array(
            0 => 'Head Master Of Hogwarts',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'mmcgonagall',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'mmcgonagall@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '11',
            'count' => 1,
          ),
          'guid' => array(
            0 => '111',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'McGonagall',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Minerva',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => 'Tranfiguration/ Deputy Head Mistress',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=spomana,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'spomana',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'spomana@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '12',
            'count' => 1,
          ),
          'guid' => array(
            0 => '112',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Pomona',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Sprout',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Hufflepuff',
            'count' => 1,
          ),
          'department' => array(
            0 => 'Herbology',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=rhagrid,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'rhagrid',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'rhagrid@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '13',
            'count' => 1,
          ),
          'guid' => array(
            0 => '113',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Hagrid',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Rubeus',
            'count' => 1,
          ),
          'house' => array(
            0 => 'Gryffindor',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 1,
            'count' => 1,
          ),
          'staff' => array(
            0 => 1,
            'count' => 1,
          ),
          'student' => array(
            0 => 1,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
      'cn=service-account,ou=people,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'service-account',
            'count' => 1,
          ),
          'mail' => array(
            0 => 'service-account@hogwarts.edu',
            'count' => 1,
          ),
          'uid' => array(
            0 => '19',
            'count' => 1,
          ),
          'guid' => array(
            0 => '119',
            'count' => 1,
          ),
          'sn' => array(
            0 => 'Service',
            'count' => 1,
          ),
          'givenname' => array(
            0 => 'Account',
            'count' => 1,
          ),
          'house' => array(
            0 => '',
            'count' => 1,
          ),
          'department' => array(
            0 => '',
            'count' => 1,
          ),
          'faculty' => array(
            0 => 0,
            'count' => 1,
          ),
          'staff' => array(
            0 => 0,
            'count' => 1,
          ),
          'student' => array(
            0 => 0,
            'count' => 1,
          ),
          'gpa' => array(
            0 => '',
            'count' => 1,
          ),
          'probation' => array(
            0 => 0,
            'count' => 1,
          ),
          'password' => array(
            0 => 'goodpwd',
            'count' => 1,
          ),
        ),
      ),
    ),
    'groups' => array(
      'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'gryffindor',
            'count' => 1,
          ),
          'gid' => array(
            0 => '1',
            'count' => 1,
          ),
          'guid' => array(
            0 => 201,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            2 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
            3 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
            4 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
            5 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
            6 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
            'count' => 7,
          ),
        ),
      ),
      'cn=slytherin,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'slytherin',
            'count' => 1,
          ),
          'gid' => array(
            0 => '2',
            'count' => 1,
          ),
          'guid' => array(
            0 => 202,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=triddle,ou=people,dc=hogwarts,dc=edu',
            2 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
            3 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
            4 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            'count' => 5,
          ),
        ),
      ),
      'cn=hufflepuff,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'hufflepuff',
            'count' => 1,
          ),
          'gid' => array(
            0 => '3',
            'count' => 1,
          ),
          'guid' => array(
            0 => 203,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=students,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'students',
            'count' => 1,
          ),
          'gid' => array(
            0 => '4',
            'count' => 1,
          ),
          'guid' => array(
            0 => 204,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            2 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
            3 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
            4 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
            5 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            6 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
            'count' => 7,
          ),
        ),
      ),
      'cn=honors students,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'honors students',
            'count' => 1,
          ),
          'gid' => array(
            0 => '5',
            'count' => 1,
          ),
          'guid' => array(
            0 => 205,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
            'count' => 2,
          ),
        ),
      ),
      'cn=probation students,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'probation students',
            'count' => 1,
          ),
          'gid' => array(
            0 => '6',
            'count' => 1,
          ),
          'guid' => array(
            0 => 206,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
            'count' => 2,
          ),
        ),
      ),
      'cn=faculty,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'faculty',
            'count' => 1,
          ),
          'gid' => array(
            0 => '7',
            'count' => 1,
          ),
          'guid' => array(
            0 => 207,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
            1 => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
            2 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
            3 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
            'count' => 4,
          ),
        ),
      ),
      'cn=staff,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'staff',
            'count' => 1,
          ),
          'gid' => array(
            0 => '8',
            'count' => 1,
          ),
          'guid' => array(
            0 => 208,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
            'count' => 1,
          ),
        ),
      ),
      'cn=users,ou=groups,dc=hogwarts,dc=edu' => array(
        'attr' => array(
          'cn' => array(
            0 => 'users',
            'count' => 1,
          ),
          'gid' => array(
            0 => '9',
            'count' => 1,
          ),
          'guid' => array(
            0 => 209,
            'count' => 1,
          ),
          'member' => array(
            0 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
            1 => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
            2 => 'cn=staff,ou=groups,dc=hogwarts,dc=edu',
            'count' => 3,
          ),
        ),
      ),
    ),
    'ldap' => array(
      'cn=hpotter,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'hpotter',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'hpotter@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '1',
          'count' => 1,
        ),
        'guid' => array(
          0 => '101',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Potter',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Harry',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.8',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=hgrainger,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'hgrainger',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'hgrainger@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '2',
          'count' => 1,
        ),
        'guid' => array(
          0 => '102',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Granger',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Hermione',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '4',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=rweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'rweasley',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'rweasley@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '3',
          'count' => 1,
        ),
        'guid' => array(
          0 => '103',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Weasley',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Ron',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.6',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=fweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'fweasley',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'fweasley@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '4',
          'count' => 1,
        ),
        'guid' => array(
          0 => '104',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Weasley',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Fred',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=gweasley,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'gweasley',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'gweasley@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '5',
          'count' => 1,
        ),
        'guid' => array(
          0 => '105',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Weasley',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'George',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '2.7',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'dmalfoy',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'dmalfoy@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '6',
          'count' => 1,
        ),
        'guid' => array(
          0 => '106',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Malfoy',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Draco',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Slytherin',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.7',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=triddle,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'triddle',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'triddle@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '7',
          'count' => 1,
        ),
        'guid' => array(
          0 => '107',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Riddle',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Tom',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Slytherin',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.6',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=ggoyle,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'ggoyle',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'ggoyle@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '8',
          'count' => 1,
        ),
        'guid' => array(
          0 => '108',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Goyle',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Gregory',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Slytherin',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '3.3',
          'count' => 1,
        ),
        'probation' => array(
          0 => 1,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=ssnape,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'ssnape',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'ssnape@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '9',
          'count' => 1,
        ),
        'guid' => array(
          0 => '109',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Snape',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Severus ',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Slytherin',
          'count' => 1,
        ),
        'department' => array(
          0 => 'Defence Against the Dark Arts professor ',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=adumbledore,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'adumbledore',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'adumbledore@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '10',
          'count' => 1,
        ),
        'guid' => array(
          0 => '110',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Dumbledore',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Albus',
          'count' => 1,
        ),
        'house' => array(
          0 => '',
          'count' => 1,
        ),
        'department' => array(
          0 => 'Head Master Of Hogwarts',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'mmcgonagall',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'mmcgonagall@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '11',
          'count' => 1,
        ),
        'guid' => array(
          0 => '111',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'McGonagall',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Minerva',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => 'Tranfiguration/ Deputy Head Mistress',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=spomana,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'spomana',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'spomana@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '12',
          'count' => 1,
        ),
        'guid' => array(
          0 => '112',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Pomona',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Sprout',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Hufflepuff',
          'count' => 1,
        ),
        'department' => array(
          0 => 'Herbology',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=rhagrid,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'rhagrid',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'rhagrid@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '13',
          'count' => 1,
        ),
        'guid' => array(
          0 => '113',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Hagrid',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Rubeus',
          'count' => 1,
        ),
        'house' => array(
          0 => 'Gryffindor',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 1,
          'count' => 1,
        ),
        'staff' => array(
          0 => 1,
          'count' => 1,
        ),
        'student' => array(
          0 => 1,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=service-account,ou=people,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'service-account',
          'count' => 1,
        ),
        'mail' => array(
          0 => 'service-account@hogwarts.edu',
          'count' => 1,
        ),
        'uid' => array(
          0 => '19',
          'count' => 1,
        ),
        'guid' => array(
          0 => '119',
          'count' => 1,
        ),
        'sn' => array(
          0 => 'Service',
          'count' => 1,
        ),
        'givenname' => array(
          0 => 'Account',
          'count' => 1,
        ),
        'house' => array(
          0 => '',
          'count' => 1,
        ),
        'department' => array(
          0 => '',
          'count' => 1,
        ),
        'faculty' => array(
          0 => 0,
          'count' => 1,
        ),
        'staff' => array(
          0 => 0,
          'count' => 1,
        ),
        'student' => array(
          0 => 0,
          'count' => 1,
        ),
        'gpa' => array(
          0 => '',
          'count' => 1,
        ),
        'probation' => array(
          0 => 0,
          'count' => 1,
        ),
        'password' => array(
          0 => 'goodpwd',
          'count' => 1,
        ),
        'count' => 14,
      ),
      'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'gryffindor',
          'count' => 1,
        ),
        'gid' => array(
          0 => '1',
          'count' => 1,
        ),
        'guid' => array(
          0 => 201,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
          2 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
          3 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
          4 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
          5 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
          6 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
          'count' => 7,
        ),
      ),
      'cn=slytherin,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'slytherin',
          'count' => 1,
        ),
        'gid' => array(
          0 => '2',
          'count' => 1,
        ),
        'guid' => array(
          0 => 202,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=triddle,ou=people,dc=hogwarts,dc=edu',
          2 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
          3 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
          4 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          'count' => 5,
        ),
      ),
      'cn=hufflepuff,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'hufflepuff',
          'count' => 1,
        ),
        'gid' => array(
          0 => '3',
          'count' => 1,
        ),
        'guid' => array(
          0 => 203,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
      ),
      'cn=students,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'students',
          'count' => 1,
        ),
        'gid' => array(
          0 => '4',
          'count' => 1,
        ),
        'guid' => array(
          0 => 204,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
          2 => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
          3 => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
          4 => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
          5 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          6 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
          'count' => 7,
        ),
      ),
      'cn=honors students,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'honors students',
          'count' => 1,
        ),
        'gid' => array(
          0 => '5',
          'count' => 1,
        ),
        'guid' => array(
          0 => 205,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=probation students,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'probation students',
          'count' => 1,
        ),
        'gid' => array(
          0 => '6',
          'count' => 1,
        ),
        'guid' => array(
          0 => 206,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
          'count' => 2,
        ),
      ),
      'cn=faculty,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'faculty',
          'count' => 1,
        ),
        'gid' => array(
          0 => '7',
          'count' => 1,
        ),
        'guid' => array(
          0 => 207,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
          1 => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
          2 => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
          3 => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
          'count' => 4,
        ),
      ),
      'cn=staff,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'staff',
          'count' => 1,
        ),
        'gid' => array(
          0 => '8',
          'count' => 1,
        ),
        'guid' => array(
          0 => 208,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
          'count' => 1,
        ),
      ),
      'cn=users,ou=groups,dc=hogwarts,dc=edu' => array(
        'cn' => array(
          0 => 'users',
          'count' => 1,
        ),
        'gid' => array(
          0 => '9',
          'count' => 1,
        ),
        'guid' => array(
          0 => 209,
          'count' => 1,
        ),
        'member' => array(
          0 => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
          1 => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
          2 => 'cn=staff,ou=groups,dc=hogwarts,dc=edu',
          'count' => 3,
        ),
      ),
    ),
    'csv' => array(
      'groups' => array(
        201 => array(
          'guid' => '201',
          'gid' => '1',
          'cn' => 'gryffindor',
          'dn' => 'cn=gryffindor,ou=groups,dc=hogwarts,dc=edu',
        ),
        202 => array(
          'guid' => '202',
          'gid' => '2',
          'cn' => 'slytherin',
          'dn' => 'cn=slytherin,ou=groups,dc=hogwarts,dc=edu',
        ),
        203 => array(
          'guid' => '203',
          'gid' => '3',
          'cn' => 'hufflepuff',
          'dn' => 'cn=hufflepuff,ou=groups,dc=hogwarts,dc=edu',
        ),
        204 => array(
          'guid' => '204',
          'gid' => '4',
          'cn' => 'students',
          'dn' => 'cn=students,ou=groups,dc=hogwarts,dc=edu',
        ),
        205 => array(
          'guid' => '205',
          'gid' => '5',
          'cn' => 'honors students',
          'dn' => 'cn=honors students,ou=groups,dc=hogwarts,dc=edu',
        ),
        206 => array(
          'guid' => '206',
          'gid' => '6',
          'cn' => 'probation students',
          'dn' => 'cn=probation students,ou=groups,dc=hogwarts,dc=edu',
        ),
        207 => array(
          'guid' => '207',
          'gid' => '7',
          'cn' => 'faculty',
          'dn' => 'cn=faculty,ou=groups,dc=hogwarts,dc=edu',
        ),
        208 => array(
          'guid' => '208',
          'gid' => '8',
          'cn' => 'staff',
          'dn' => 'cn=staff,ou=groups,dc=hogwarts,dc=edu',
        ),
        209 => array(
          'guid' => '209',
          'gid' => '9',
          'cn' => 'users',
          'dn' => 'cn=users,ou=groups,dc=hogwarts,dc=edu',
        ),
      ),
      'users' => array(
        101 => array(
          'guid' => '101',
          'uid' => '1',
          'cn' => 'hpotter',
          'lname' => 'Potter',
          'fname' => 'Harry',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.8',
          'probation' => 'N',
          'dn' => 'cn=hpotter,ou=people,dc=hogwarts,dc=edu',
        ),
        102 => array(
          'guid' => '102',
          'uid' => '2',
          'cn' => 'hgrainger',
          'lname' => 'Granger',
          'fname' => 'Hermione',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '4',
          'probation' => 'N',
          'dn' => 'cn=hgrainger,ou=people,dc=hogwarts,dc=edu',
        ),
        103 => array(
          'guid' => '103',
          'uid' => '3',
          'cn' => 'rweasley',
          'lname' => 'Weasley',
          'fname' => 'Ron',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.6',
          'probation' => 'N',
          'dn' => 'cn=rweasley,ou=people,dc=hogwarts,dc=edu',
        ),
        104 => array(
          'guid' => '104',
          'uid' => '4',
          'cn' => 'fweasley',
          'lname' => 'Weasley',
          'fname' => 'Fred',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3',
          'probation' => 'N',
          'dn' => 'cn=fweasley,ou=people,dc=hogwarts,dc=edu',
        ),
        105 => array(
          'guid' => '105',
          'uid' => '5',
          'cn' => 'gweasley',
          'lname' => 'Weasley',
          'fname' => 'George',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '2.7',
          'probation' => 'N',
          'dn' => 'cn=gweasley,ou=people,dc=hogwarts,dc=edu',
        ),
        106 => array(
          'guid' => '106',
          'uid' => '6',
          'cn' => 'dmalfoy',
          'lname' => 'Malfoy',
          'fname' => 'Draco',
          'house' => 'Slytherin',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.7',
          'probation' => 'Y',
          'dn' => 'cn=dmalfoy,ou=people,dc=hogwarts,dc=edu',
        ),
        107 => array(
          'guid' => '107',
          'uid' => '7',
          'cn' => 'triddle',
          'lname' => 'Riddle',
          'fname' => 'Tom',
          'house' => 'Slytherin',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.6',
          'probation' => 'N',
          'dn' => 'cn=triddle,ou=people,dc=hogwarts,dc=edu',
        ),
        108 => array(
          'guid' => '108',
          'uid' => '8',
          'cn' => 'ggoyle',
          'lname' => 'Goyle',
          'fname' => 'Gregory',
          'house' => 'Slytherin',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'N',
          'student' => 'Y',
          'gpa' => '3.3',
          'probation' => 'Y',
          'dn' => 'cn=ggoyle,ou=people,dc=hogwarts,dc=edu',
        ),
        109 => array(
          'guid' => '109',
          'uid' => '9',
          'cn' => 'ssnape',
          'lname' => 'Snape',
          'fname' => 'Severus ',
          'house' => 'Slytherin',
          'department' => 'Defence Against the Dark Arts professor ',
          'faculty' => 'Y',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=ssnape,ou=people,dc=hogwarts,dc=edu',
        ),
        110 => array(
          'guid' => '110',
          'uid' => '10',
          'cn' => 'adumbledore',
          'lname' => 'Dumbledore',
          'fname' => 'Albus',
          'house' => '',
          'department' => 'Head Master Of Hogwarts',
          'faculty' => 'Y',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=adumbledore,ou=people,dc=hogwarts,dc=edu',
        ),
        111 => array(
          'guid' => '111',
          'uid' => '11',
          'cn' => 'mmcgonagall',
          'lname' => 'McGonagall',
          'fname' => 'Minerva',
          'house' => 'Gryffindor',
          'department' => 'Tranfiguration/ Deputy Head Mistress',
          'faculty' => 'Y',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=mmcgonagall,ou=people,dc=hogwarts,dc=edu',
        ),
        112 => array(
          'guid' => '112',
          'uid' => '12',
          'cn' => 'spomana',
          'lname' => 'Pomona',
          'fname' => 'Sprout',
          'house' => 'Hufflepuff',
          'department' => 'Herbology',
          'faculty' => 'Y',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=spomana,ou=people,dc=hogwarts,dc=edu',
        ),
        113 => array(
          'guid' => '113',
          'uid' => '13',
          'cn' => 'rhagrid',
          'lname' => 'Hagrid',
          'fname' => 'Rubeus',
          'house' => 'Gryffindor',
          'department' => '',
          'faculty' => 'N',
          'staff' => 'Y',
          'student' => 'N',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=rhagrid,ou=people,dc=hogwarts,dc=edu',
        ),
        119 => array(
          'guid' => '119',
          'uid' => '19',
          'cn' => 'service-account',
          'lname' => 'Service',
          'fname' => 'Account',
          'house' => '',
          'department' => '',
          'faculty' => '',
          'staff' => '',
          'student' => '',
          'gpa' => '',
          'probation' => '',
          'dn' => 'cn=service-account,ou=people,dc=hogwarts,dc=edu',
        ),
      ),
      'memberships' => array(
        1 => array(
          'membershipid' => '1',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '101',
          'group_guid' => '201',
        ),
        2 => array(
          'membershipid' => '2',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '102',
          'group_guid' => '201',
        ),
        3 => array(
          'membershipid' => '3',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '103',
          'group_guid' => '201',
        ),
        4 => array(
          'membershipid' => '4',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '104',
          'group_guid' => '201',
        ),
        5 => array(
          'membershipid' => '5',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '105',
          'group_guid' => '201',
        ),
        6 => array(
          'membershipid' => '6',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '111',
          'group_guid' => '201',
        ),
        7 => array(
          'membershipid' => '7',
          'gid' => '1',
          'group_cn' => 'gryffindor',
          'member_guid' => '113',
          'group_guid' => '201',
        ),
        8 => array(
          'membershipid' => '8',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '106',
          'group_guid' => '202',
        ),
        9 => array(
          'membershipid' => '9',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '107',
          'group_guid' => '202',
        ),
        10 => array(
          'membershipid' => '10',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '108',
          'group_guid' => '202',
        ),
        11 => array(
          'membershipid' => '11',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '109',
          'group_guid' => '202',
        ),
        12 => array(
          'membershipid' => '12',
          'gid' => '2',
          'group_cn' => 'slytherin',
          'member_guid' => '106',
          'group_guid' => '202',
        ),
        13 => array(
          'membershipid' => '13',
          'gid' => '3',
          'group_cn' => 'hufflepuff',
          'member_guid' => '112',
          'group_guid' => '203',
        ),
        14 => array(
          'membershipid' => '14',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '101',
          'group_guid' => '204',
        ),
        15 => array(
          'membershipid' => '15',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '102',
          'group_guid' => '204',
        ),
        16 => array(
          'membershipid' => '16',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '103',
          'group_guid' => '204',
        ),
        17 => array(
          'membershipid' => '17',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '104',
          'group_guid' => '204',
        ),
        18 => array(
          'membershipid' => '18',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '105',
          'group_guid' => '204',
        ),
        19 => array(
          'membershipid' => '19',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '106',
          'group_guid' => '204',
        ),
        20 => array(
          'membershipid' => '20',
          'gid' => '4',
          'group_cn' => 'students',
          'member_guid' => '108',
          'group_guid' => '204',
        ),
        21 => array(
          'membershipid' => '21',
          'gid' => '5',
          'group_cn' => 'honors students',
          'member_guid' => '101',
          'group_guid' => '205',
        ),
        22 => array(
          'membershipid' => '22',
          'gid' => '5',
          'group_cn' => 'honors students',
          'member_guid' => '102',
          'group_guid' => '205',
        ),
        23 => array(
          'membershipid' => '23',
          'gid' => '6',
          'group_cn' => 'probation students',
          'member_guid' => '106',
          'group_guid' => '206',
        ),
        24 => array(
          'membershipid' => '24',
          'gid' => '6',
          'group_cn' => 'probation students',
          'member_guid' => '108',
          'group_guid' => '206',
        ),
        25 => array(
          'membershipid' => '25',
          'gid' => '7',
          'group_cn' => 'faculty',
          'member_guid' => '109',
          'group_guid' => '207',
        ),
        26 => array(
          'membershipid' => '26',
          'gid' => '7',
          'group_cn' => 'faculty',
          'member_guid' => '110',
          'group_guid' => '207',
        ),
        27 => array(
          'membershipid' => '27',
          'gid' => '7',
          'group_cn' => 'faculty',
          'member_guid' => '111',
          'group_guid' => '207',
        ),
        28 => array(
          'membershipid' => '28',
          'gid' => '7',
          'group_cn' => 'faculty',
          'member_guid' => '112',
          'group_guid' => '207',
        ),
        29 => array(
          'membershipid' => '29',
          'gid' => '8',
          'group_cn' => 'staff',
          'member_guid' => '113',
          'group_guid' => '208',
        ),
        30 => array(
          'membershipid' => '30',
          'gid' => '9',
          'group_cn' => 'users',
          'member_guid' => '204',
          'group_guid' => '209',
        ),
        31 => array(
          'membershipid' => '31',
          'gid' => '9',
          'group_cn' => 'users',
          'member_guid' => '207',
          'group_guid' => '209',
        ),
        32 => array(
          'membershipid' => '32',
          'gid' => '9',
          'group_cn' => 'users',
          'member_guid' => '208',
          'group_guid' => '209',
        ),
      ),
      'conf' => array(
        'hogwarts' => array(
          'id' => 'hogwarts',
          'mailhostname' => 'hogwarts.edu',
          'userbasedn' => 'ou=people,dc=hogwarts,dc=edu',
          'groupbasedn' => 'ou=groups,dc=hogwarts,dc=edu',
        ),
      ),
    ),
  );
  $export['ldap_test_server__openldap1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_user_conf';
  $strongarm->value = array(
    'drupalAcctProvisionServer' => 'SBAC Internal',
    'ldapEntryProvisionServer' => 0,
    'drupalAcctProvisionTriggers' => array(
      2 => 0,
      1 => 0,
    ),
    'ldapEntryProvisionTriggers' => array(
      6 => 0,
      7 => 0,
      8 => 0,
      3 => 0,
    ),
    'orphanedDrupalAcctBehavior' => 'ldap_user_orphan_do_not_check',
    'orphanedCheckQty' => '0',
    'userConflictResolve' => 2,
    'manualAccountConflict' => '2',
    'acctCreation' => 4,
    'ldapUserSynchMappings' => array(
      1 => array(
        '[field.field_first_name]' => array(
          'ldap_attr' => '[firstName]',
          'user_attr' => '[field.field_first_name]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
            1 => 1,
          ),
        ),
        '[field.field_last_name]' => array(
          'ldap_attr' => '[lastName]',
          'user_attr' => '[field.field_last_name]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
            1 => 1,
          ),
        ),
        '[field.field_district_name]' => array(
          'ldap_attr' => '[districtIDNumber]',
          'user_attr' => '[field.field_district_name]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
            1 => 1,
          ),
        ),
        '[field.field_school_name]' => array(
          'ldap_attr' => '[schoolIDNumber]',
          'user_attr' => '[field.field_school_name]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
            1 => 1,
          ),
        ),
        '[field.field_state]' => array(
          'ldap_attr' => '[stateIDNumber]',
          'user_attr' => '[field.field_state]',
          'convert' => 0,
          'direction' => '1',
          'user_tokens' => NULL,
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 2,
            1 => 1,
          ),
        ),
      ),
      2 => array(
        '[firstName]' => array(
          'ldap_attr' => '[firstName]',
          'user_attr' => '[field.field_first_name]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
        ),
        '[cn]' => array(
          'ldap_attr' => '[cn]',
          'user_attr' => '[property.name]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
        ),
        '[dn]' => array(
          'ldap_attr' => '[dn]',
          'user_attr' => '[field.ldap_user_current_dn]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
        ),
        '[uid]' => array(
          'ldap_attr' => '[uid]',
          'user_attr' => '[property.name]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
        ),
        '[lastName]' => array(
          'ldap_attr' => '[lastName]',
          'user_attr' => '[field.field_last_name]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
        ),
      ),
    ),
  );
  $export['ldap_user_conf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_user_cron_last_uid_checked';
  $strongarm->value = 1;
  $export['ldap_user_cron_last_uid_checked'] = $strongarm;

  return $export;
}
