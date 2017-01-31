<?php

/**
 * @file
 * Definition of views_handler_filter_field_variable_compare.
 */

/**
 * A handler to filter a view using field against system variable comparison.
 *
 * @ingroup views_filter_handlers
 */

class views_handler_filter_field_variable_compare extends views_handler_filter {

  function can_expose() {
    return FALSE;
  }

  /**
   * Overrides views_handler_filter#option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['left_field'] = $options['variable'] = array('default' => '');

    return $options;
  }

  /**
   * Provide a list of all operators.
   */
  function fields_operator_options() {
    return array(
      '<' => t('Is less than'),
      '<=' => t('Is less than or equal to'),
      '=' => t('Is equal to'),
      '<>' =>  t('Is not equal to'),
      '>=' => t('Is greater than or equal to'),
      '>' => t('Is greater than')
    );
  }

  /**
   * Provide a list of available fields.
   */
  function field_options() {
    $options = array();

    $field_handlers = $this->view->display_handler->get_handlers('field');
    foreach ($field_handlers as $field => $handler) {
      if ($handler->table != 'views') {
        $options[$field] = $handler->ui_name();
      }
    }

    return $options;
  }

  /**
   * Overrides views_handler_filter#options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $field_options = $this->field_options();

    $form['left_field'] = array(
      '#type' => 'select',
      '#title' => t('Left field'),
      '#default_value' => $this->options['left_field'],
      '#options' => $field_options,
      '#weight' => -3,
    );

    $form['operator'] = array(
      '#type' => 'select',
      '#title' => t('Operator'),
      '#default_value' => $this->options['operator'],
      '#options' => $this->fields_operator_options(),
      '#weight' => -2,
    );

    $form['variable'] = array(
      '#type' => 'textfield',
      '#title' => t('Variable'),
      '#default_value' => $this->options['variable'],
      '#required' => TRUE,
      '#weight' => -1,
    );
  }

  /**
   * Overrides views_handler_filter#validate().
   */
  function options_validate(&$form, &$form_state) {
    parent::options_validate($form, $form_state);
    $variable = variable_get($form_state['values']['options']['variable'], NULL);
    if (!isset($variable)) {
      form_error($form['variable'], t('Variable does not exist'));
    }
  }

  /**
   * Overrides views_handler_filter#query().
   *
   * Build extra condition from existing fields (from existing joins).
   */
  function query() {
    $left = $this->options['left_field'];
    $variable = variable_get($this->options['variable'], NULL);
    $variable = (is_array($variable) || is_object($variable)) ? serialize($variable) : $variable;

    // Get all existing field handlers.
    $field_handlers = $this->view->display_handler->get_handlers('field');

    // Make sure the selected fields still exist.
    if (!isset($field_handlers[$left], $variable)) {
      return;
    }

    // Get the left table and field.
    $left_handler = $field_handlers[$left];
    $left_handler->set_relationship();
    $left_table_alias = $this->query->ensure_table($left_handler->table, $left_handler->relationship);

    // Build piece of SQL.
    $snippet =
      $left_table_alias . '.' . $left_handler->real_field .
      ' ' . $this->options['operator'] . " '"  . db_like($variable). "'";

    $this->query->add_where($this->options['group'], $left_table_alias . '.' . $left_handler->real_field, db_like($variable), $this->options['operator']);

    //$this->query->add_where_expression($this->options['group'], $snippet);
  }

  /**
   * Overrides views_handler_filter#admin_summary().
   */
  function admin_summary() {
    return check_plain(
      $this->options['left_field'] . ' ' .
      $this->options['operator'] . ' ' .
      $this->options['variable']
    );
  }

}
