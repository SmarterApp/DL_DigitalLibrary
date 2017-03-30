<?php

/**
 * Menu callback for /admin/people.
 *
 * Overrides core callback to load different form for user_admin_account
 */
function sbac_user_admin($callback_arg = '') {
  module_load_include('inc', 'user', 'user.admin');

  $op = isset($_POST['op']) ? $_POST['op'] : $callback_arg;

  switch ($op) {
    case t('Create new account'):
    case 'create':
      $build['user_register'] = drupal_get_form('user_register_form');
      break;
    default:
      if (!empty($_POST['accounts']) && isset($_POST['operation']) && ($_POST['operation'] == 'cancel')) {
        $build['user_multiple_cancel_confirm'] = drupal_get_form('user_multiple_cancel_confirm');
      }
      else {
        $build['user_filter_form'] = drupal_get_form('sbac_user_filter_form');
        $build['user_admin_account'] = drupal_get_form('sbac_user_admin_account');
      }
  }
  return $build;
}

/**
 * Form builder; Return form for user administration filters.
 *
 * @ingroup forms
 * @see user_filter_form_submit()
 */
function sbac_user_filter_form() {
  $session = isset($_SESSION['user_overview_filter']) ? $_SESSION['user_overview_filter'] : array();
  $filters = sbac_user_combined_filters();

  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only users where'),
    '#theme' => 'exposed_filters__user',
  );
  
  foreach ($session as $filter) {
    list($type, $value) = $filter;
    if ($type == 'permission') {
      // Merge arrays of module permissions into one.
      // Slice past the first element '[any]' whose value is not an array.
      $options = call_user_func_array('array_merge', array_slice($filters[$type]['options'], 1));
      $value = $options[$value];
    }
    elseif ($type != 'email') {
      $value = $filters[$type]['options'][$value];
    }
    $t_args = array('%property' => $filters[$type]['title'], '%value' => $value);
    if ($i++) {
      $form['filters']['current'][] = array('#markup' => t('and where %property is %value', $t_args));
    }
    else {
      $form['filters']['current'][] = array('#markup' => t('%property is %value', $t_args));
    }
  }

  $form['filters']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix')),
  );
  
  $form['filters']['status']['filters'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filters')),
  );

  foreach ($filters as $key => $filter) {
    // our custom filters provide their own FAPI declarations in the 'element' key
    if (isset($filter['element'])) {
      // we don't allow selection of multiple options for our custom filters, so
      // we remove the filter when an option is present
      $default_value = NULL;

      foreach ($session as $session_filter) {
        list($type, $value) = $session_filter;

        if ($type == $key) {
          $default_value = $value;
        }
      }

      if (!is_null($default_value)) {
        $filter['element']['#default_value'] = $default_value;
        $filter['element']['#disabled'] = TRUE;
      }

      $form['filters']['status']['filters'][$key] = $filter['element'];
    }
    else {
      $form['filters']['status']['filters'][$key] = array(
        '#type' => 'select',
        '#options' => $filter['options'],
        '#title' => $filter['title'],
        '#default_value' => '[any]',
        '#attributes' => array(
          'class' => array(
            'chosen-widget',
          ),
        ),
      );
    }
  }

  $form['filters']['status']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['filters']['status']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => (count($session) ? t('Refine') : t('Filter')),
  );

  if (count($session)) {
    $form['filters']['status']['actions']['undo'] = array(
      '#type' => 'submit',
      '#value' => t('Undo'),
    );
    $form['filters']['status']['actions']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
    );
  }

  $form['#submit'][] = 'sbac_user_filter_form_submit';

  drupal_add_library('system', 'drupal.form');

  return $form;
}

/**
 * Form builder; User administration page.
 *
 * @ingroup forms
 * @see user_admin_account_validate()
 * @see user_admin_account_submit()
 */
function sbac_user_admin_account() {
  $header = array(
    'username' => array('data' => t('Username'), 'field' => 'u.name'),
    'status' => array('data' => t('Status'), 'field' => 'u.status'),
    'state' => array('data' => t('State'), 'field' => 'term.name'),
    'sne' => array('data' => t('Is SNE'), 'field' => 'sne.field_sne_member_value'),
    'slt' => array('data' => t('Is SLT'), 'field' => 'slt.field_slt_member_value'),
    'roles' => array('data' => t('Roles')),
    'member_for' => array('data' => t('Member for'), 'field' => 'u.created', 'sort' => 'desc'),
    'access' => array('data' => t('Last access'), 'field' => 'u.access'),
    'operations' => array('data' => t('Operations')),
  );

  $query = db_select('users', 'u');
  $query->condition('u.uid', 0, '<>');
  $guest_role = user_role_load_by_name('guest');
  if ($guest_role) {
    $query->leftJoin('users_roles', 'ur', 'u.uid = ur.uid');
    $query->condition(db_or()->condition('ur.rid', $guest_role->rid, '<>')->isNull('ur.rid'));
    $query->groupBy('u.uid');
  }
  
  // we join these tables so that the data can be displayed in the actual table, but we only do
  // a value restriction when the user filters by that
  $user_field_join_condition = "u.uid = %alias.entity_id AND %alias.entity_type = 'user' AND %alias.bundle = 'user'";
  $sne_alias   = $query->leftJoin('field_data_field_sne_member', 'sne', $user_field_join_condition);
  $slt_alias   = $query->leftJoin('field_data_field_slt_member', 'slt', $user_field_join_condition);
  $state_alias = $query->leftJoin('field_data_field_state', 'state', $user_field_join_condition);
  $term_alias  = $query->leftJoin('taxonomy_term_data', 'term', $state_alias . ".field_state_tid = %alias.tid");

  $filters = sbac_user_combined_filters();

  // Extend Query with filter conditions.
  foreach (isset($_SESSION['user_overview_filter']) ? $_SESSION['user_overview_filter'] : array() as $filter) {
    list($key, $value) = $filter;

    switch ($key) {
      case 'sne':
        $query->condition($sne_alias . '.field_sne_member_value', $value);
        break;

      case 'slt':
        $query->condition($slt_alias . '.field_slt_member_value', $value);
        break;

      case 'state':
        $query->condition($state_alias . '.field_state_tid', $value);
        break;

      case 'email':
        $query->condition('u.mail', "%%".$value."%%", 'LIKE');
        break;

      case 'permission':
        // This checks to see if this permission filter is an enabled permission for
        // the authenticated role. If so, then all users would be listed, and we can
        // skip adding it to the filter query.
        $account = new stdClass();
        $account->uid = 'user_filter';
        $account->roles = array(DRUPAL_AUTHENTICATED_RID => 1);
        if (user_access($value, $account)) {
          continue;
        }
        $users_roles_alias = $query->join('users_roles', 'ur', '%alias.uid = u.uid');
        $permission_alias = $query->join('role_permission', 'p', $users_roles_alias . '.rid = %alias.rid');
        $query->condition($permission_alias . '.permission', $value);

        break;

      case 'role':
        $users_roles_alias = $query->join('users_roles', 'ur', '%alias.uid = u.uid');
        $query->condition($users_roles_alias . '.rid' , $value);

        break;

      default:
        $query->condition($filters[$key]['field'], $value);

        break;
    }
  }

  // the count query only cares about the total number of results, so we clone the
  // original query before fields are added
  $count_query = $query;
  $count_query->addExpression('COUNT(u.uid)');

  // now that the query has been cloned for the count, we add fields and options 
  // specific to the displayed data
  $query = $query->extend('PagerDefault')->extend('TableSort');
  $query->fields('u', array('uid', 'name', 'status', 'created', 'access'))
        ->fields('term', array('name'))
        ->fields('sne', array('field_sne_member_value'))
        ->fields('slt', array('field_slt_member_value'))
        ->limit(50)
        ->orderByHeader($header)
        ->setCountQuery($count_query);

  $result = $query->execute();

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
  );

  $options = array();
  foreach (module_invoke_all('user_operations') as $operation => $array) {
    $options[$operation] = $array['label'];
  }

  $form['options']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#title_display' => 'invisible',
    '#options' => $options,
    '#default_value' => 'unblock',
  );

  $options = array();
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  $destination = drupal_get_destination();

  $status = array(t('blocked'), t('active'));
  $roles = array_map(function ($role) {
    $role = check_plain($role);

    // Note: These role names are to be displayed differently than the actual role names
    switch ($role) {
      case 'DLRB member':
        $role = 'Lead SLT';
        break;

      case 'moderator':
        $role = 'resource moderator';
        break;
    }

    return $role;
  }, user_roles(TRUE));

  $accounts = array();
  foreach ($result as $account) {
    $users_roles = array();
    $roles_result = db_query('SELECT rid FROM {users_roles} WHERE uid = :uid', array(':uid' => $account->uid));
    foreach ($roles_result as $user_role) {
      $users_roles[] = $roles[$user_role->rid];
    }
    asort($users_roles);

    $options[$account->uid] = array(
      'username' => theme('username', array('account' => $account)),
      'status' =>  $status[$account->status],
      'state' => $account->term_name,
      'sne' => $account->field_sne_member_value ? t('Yes') : t('No'),
      'slt' => $account->field_slt_member_value ? t('Yes') : t('No'),
      'roles' => theme('item_list', array('items' => $users_roles)),
      'member_for' => format_interval(REQUEST_TIME - $account->created),
      'access' =>  $account->access ? t('@time ago', array('@time' => format_interval(REQUEST_TIME - $account->access))) : t('never'),
      'operations' => array('data' => array('#type' => 'link', '#title' => t('edit'), '#href' => "user/$account->uid/edit", '#options' => array('query' => $destination))),
    );
  }

  $form['accounts'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No people available.'),
  );

  $form['pager'] = array('#markup' => theme('pager'));

  return $form;
}

/**
 * Submit the user administration update form.
 */
function sbac_user_admin_account_submit($form, &$form_state) {
  $operations = module_invoke_all('user_operations', $form, $form_state);
  $operation = $operations[$form_state['values']['operation']];
  // Filter out unchecked accounts.
  $accounts = array_filter($form_state['values']['accounts']);
  if ($function = $operation['callback']) {
    // Add in callback arguments if present.
    if (isset($operation['callback arguments'])) {
      $args = array_merge(array($accounts), $operation['callback arguments']);
    }
    else {
      $args = array($accounts);
    }
    call_user_func_array($function, $args);

    drupal_set_message(t('The update has been performed.'));
  }
}

/**
 * Process result from user administration filter form.
 */
function sbac_user_filter_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = sbac_user_combined_filters();

  switch ($op) {
    case t('Filter'):
    case t('Refine'):
      // Apply every filter that has a choice selected other than 'any'.
      foreach ($filters as $filter => $options) {
        if (isset($form_state['values'][$filter]) && $form_state['values'][$filter] != '[any]') {
          if ($filter == 'email') {
            if (!isset($form['filters']['status']['filters'][$filter]['#disabled']) || !$form['filters']['status']['filters'][$filter]['#disabled']) {
              $_SESSION['user_overview_filter'][] = array($filter, $form_state['values'][$filter]);
            }
          }
          else {
            // Merge an array of arrays into one if necessary.
            $options = ($filter == 'permission') ? form_options_flatten($filters[$filter]['options']) : $filters[$filter]['options'];
            // Only accept valid selections offered on the dropdown, block bad input.
            if (isset($options[$form_state['values'][$filter]])) {
              // disabled elements are showing previously-selected filters and we
              // don't want to stack them
              if (!isset($form['filters']['status']['filters'][$filter]['#disabled']) || !$form['filters']['status']['filters'][$filter]['#disabled']) {
                $_SESSION['user_overview_filter'][] = array($filter, $form_state['values'][$filter]);
              }
            }
          }
        }
      }
      break;
    case t('Undo'):
      array_pop($_SESSION['user_overview_filter']);
      break;
    case t('Reset'):
      $_SESSION['user_overview_filter'] = array();
      break;
    case t('Update'):
      return;
  }
}

/**
 * Returns the custom filters used on the /admin/people page
 * @return [type] [description]
 */
function sbac_user_filters() {
  $filters['state'] = array(
    'title' => t('state'),
    'field' => 'state.field_state_tid',
    'options' => sbac_state_options(),
    'element' => array(
      '#title' => t('state'),
      '#type' => 'select',
      '#options' => sbac_state_options(),
    ),
  );

  $filters['email'] = array(
    'title' => t('email'),
    'field' => 'user.mail',
    'element' => array(
      '#title' => t('email'),
      '#type' => 'textfield',
    ),
  );

  $radio_options = array(
    1 => t('yes'),
    0 => t('no'),
  );

  $filters['sne'] = array(
    'title' => 'is SNE',
    'field' => 'sne.field_sne_member_value',
    'options' => array(0, 1),
    'element' => array(
      '#title' => t('is SNE'),
      '#type' => 'radios',
      '#options' => $radio_options,
    ),
  );

  $filters['slt'] = array(
    'title' => 'is SLT',
    'field' => 'sne.field_sne_member_value',
    'options' => array(0, 1),
    'element' => array(
      '#title' => t('is SLT'),
      '#type' => 'radios',
      '#options' => $radio_options,
    ),
  );

  return $filters;
}

/**
 * Returns the combined list of filters for the /admin/people page
 * @return array
 */
function sbac_user_combined_filters() {
  $filters = user_filters() + sbac_user_filters();
  foreach ($filters['role']['options'] as $key => $role) {
    // Note: These role names are to be displayed differently than the actual role names
    switch ($role) {
      case 'DLRB member':
        $filters['role']['options'][$key] = 'Lead SLT';
        break;

      case 'moderator':
        $filters['role']['options'][$key] = 'resource moderator';
        break;
    }
  }

  return $filters;
}
