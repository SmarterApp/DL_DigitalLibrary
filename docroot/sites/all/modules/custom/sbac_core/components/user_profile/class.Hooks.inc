<?php
namespace sbac_core\components\user_profile;

class Hooks extends \devtools\Hooks {

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $base = array(
      'file' => 'user_profile.pages.inc',
      'file path' => $this->_path,
    );

    $items['admin/sbac/users/account'] = array(
        'title' => 'Account',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('user_profile_account_admin_form'),
        'access arguments' => array('configure sbac'),
        'file' => 'user_profile.admin.inc',
        'type' => MENU_LOCAL_TASK,
        'weight' => 0,
      ) + $base;

    $items['admin/sbac/users/activity'] = array(
        'title' => 'Activity',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('user_profile_activity_admin_form'),
        'access arguments' => array('configure sbac'),
        'file' => 'user_profile.admin.inc',
        'type' => MENU_LOCAL_TASK,
        'weight' => 1,
      ) + $base;

    $items['admin/sbac/users/notifications'] = array(
        'title' => 'Notifications',
        'page callback' => 'drupal_get_form',
        'page arguments' => array('user_profile_notifications_admin_form'),
        'access arguments' => array('configure sbac'),
        'file' => 'user_profile.admin.inc',
        'type' => MENU_LOCAL_TASK,
        'weight' => 2,
      ) + $base;

    return $items;
  }

  /**
   * Extends hook_user_view().
   */
  function hook_user_view($account, $view_mode, $langcode) {
    $account->content['view_mode'] = $view_mode;
    $account->content['account_info'] = $account;
    // we don't want to add tabs on any other view modes
    if ($view_mode !== 'full') {
      return;
    }

    // add profile edit form
    if (user_access('view and edit account information')) {
      drupal_add_js(drupal_get_path('module', 'sbac_user') . '/js/sbac_user.js');
      drupal_add_css(drupal_get_path('module', 'sbac_user') . '/css/profile.css');
      drupal_add_library('system', 'drupal.ajax');
      drupal_add_library('system', 'jquery.form');

      $help_content = variable_get('user_account_help', input_default_full_html());

      module_load_include('inc', 'user', 'user.pages');
      $profile_form = drupal_get_form('user_profile_form', $account);

      $profile_content = '';
      $profile_content .= '<div id="account">';
      $profile_content .= '<div class="helpful-info">';
      $profile_content .= '<h2>' . t('Helpful Information') . '</h2>';
      $profile_content .= more_less_text(filter_text($help_content));
      $profile_content .= '</div>';
      $profile_content .= drupal_render($profile_form);
      $profile_content .= '</div>';

      $account->content['sections']['edit'] = array(
        'title' => t('Account'),
        'content' => $profile_content,
        'disabled' => FALSE,
        'source' => 'people',
        'tab' => 'account',
        'section_loaded' => 'section-loaded',
      );
    }

    // add notificatons tab (pulled in via taskit module)
    if (taskit_task_access($account)) {
      drupal_add_js($this->_components_path . '/taskit/js/taskit.js');
      drupal_add_css($this->_components_path . '/taskit/css/taskit.css');

      $account->content['sections']['notifications'] = array(
        'title' => t('Notifications'),
        'content' => '',
        'disabled' => FALSE,
        'class' => 'section-notifications',
        'source' => 'people',
        'tab' => 'notifications',
        'section_loaded' => '',
      );
    }

    $account->content['sections']['favorites'] = array(
      'title' => t('Favorites'),
      'content' => '',
      'disabled' => FALSE,
      'class' => 'section-favorites',
      'weight' => -100,
      'source' => 'people',
      'tab' => 'favorites',
      'section_loaded' => '',
    );
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/
}



