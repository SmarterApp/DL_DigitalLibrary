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
  $filters = user_filters() + sbac_user_filters();

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
    else {
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
    if (isset($filter['element'])) {
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
    '#value' => t('Filter'),
  );

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
    'roles' => array('data' => t('Roles')),
    'member_for' => array('data' => t('Member for'), 'field' => 'u.created', 'sort' => 'desc'),
    'access' => array('data' => t('Last access'), 'field' => 'u.access'),
    'operations' => array('data' => t('Operations')),
  );

  $query = db_select('users', 'u');
  $query->condition('u.uid', 0, '<>');

  $filters = user_filters() + sbac_user_filters();

  // Extend Query with filter conditions.
  foreach (isset($_SESSION['user_overview_filter']) ? $_SESSION['user_overview_filter'] : array() as $filter) {
    list($key, $value) = $filter;

    switch ($key) {
      case 'sne':

        break;

      case 'slt':

        break;

      case 'state':
        // $state_alias = $query->join('field_data_field_state', 'p', $users_roles_alias . '.rid = %alias.rid');
        // $query->condition($state_alias . '.permission', $value);


        break;
    }

    print_rr($key);

    continue;

    // This checks to see if this permission filter is an enabled permission for
    // the authenticated role. If so, then all users would be listed, and we can
    // skip adding it to the filter query.
    if ($key == 'permission') {
      $account = new stdClass();
      $account->uid = 'user_filter';
      $account->roles = array(DRUPAL_AUTHENTICATED_RID => 1);
      if (user_access($value, $account)) {
        continue;
      }
      $users_roles_alias = $query->join('users_roles', 'ur', '%alias.uid = u.uid');
      $permission_alias = $query->join('role_permission', 'p', $users_roles_alias . '.rid = %alias.rid');
      $query->condition($permission_alias . '.permission', $value);
    }
    elseif ($key == 'role') {
      $users_roles_alias = $query->join('users_roles', 'ur', '%alias.uid = u.uid');
      $query->condition($users_roles_alias . '.rid' , $value);
    }
    else {
      $query->condition($filters[$key]['field'], $value);
    }
  }




  $count_query = clone $query;
  $count_query->addExpression('COUNT(u.uid)');

  $query = $query->extend('PagerDefault')->extend('TableSort');
  $query
    ->fields('u', array('uid', 'name', 'status', 'created', 'access'))
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
  $roles = array_map('check_plain', user_roles(TRUE));

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
 * Process result from user administration filter form.
 */
function sbac_user_filter_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = user_filters() + sbac_user_filters();

  switch ($op) {
    case t('Filter'):
    case t('Refine'):
    dsmm($filters);

      // Apply every filter that has a choice selected other than 'any'.
      foreach ($filters as $filter => $options) {


        if (isset($form_state['values'][$filter]) && $form_state['values'][$filter] != '[any]') {
          // Merge an array of arrays into one if necessary.
          $options = ($filter == 'permission') ? form_options_flatten($filters[$filter]['options']) : $filters[$filter]['options'];
          // Only accept valid selections offered on the dropdown, block bad input.
          if (isset($options[$form_state['values'][$filter]])) {
            $_SESSION['user_overview_filter'][] = array($filter, $form_state['values'][$filter]);
          }
        }
      }
      break;
  }
}

function sbac_user_filters() {
  $filters['sne'] = array(
    'title' => 'is SNE',
    'field' => 'sne.field_sne_member_value',
    'options' => array(0, 1),
    'element' => array(
      '#title' => t('is SNE'),
      '#type' => 'checkbox',
    ),
  );

  $filters['slt'] = array(
    'title' => 'is SLT',
    'field' => 'sne.field_sne_member_value',
    'options' => array(0, 1),
    'element' => array(
      '#title' => t('is SLT'),
      '#type' => 'checkbox',
    ),
  );

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

  return $filters;
}