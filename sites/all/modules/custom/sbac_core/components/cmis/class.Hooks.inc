<?php
namespace sbac_core\components\cmis;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/


  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $items['admin/sbac/cmis-server-conf'] = array(
      'title' => 'CMIS Server Configuration',
      'page callback' => 'sbac_core_cmis_server_conf',
      'access arguments' => array('configure sbac cmis server'),
      'weight' => 9,
      'file' => 'cmis.forms.inc',
      'file path' => $this->_path,
    );

    return $items;
  }

  /**
   * Extends hook_permission().
   */
  function hook_permission() {
    return array(
      'configure sbac cmis server' => array(
        'title' => t('Configure CMIS Server Credentials.'),
        'description' => t('Grants permission to configure SBAC CMIS connection information.'),
      ),
    );
  }

}
