<?php

/**
 * @file
 * Definition of contextual_filter_range_handler_argument_numeric_range.
 */

/**
 * Argument handler for arguments that are numeric or numeric ranges.
 *
 * @ingroup views_argument_handlers
 */
class contextual_range_filter_handler_argument_date_range extends views_handler_argument_date {

  /**
   * Constructor implementation.
   */
  public function construct() {
    parent::construct();

    switch ($this->definition['title']) {

      case 'Created year':
      case 'Updated year':
        $this->arg_format = 'Y';
        $this->formula = views_date_sql_extract('YEAR', "***table***.$this->real_field");
        break;

      case 'Created year + month':
      case 'Updated year + month':
        $this->format = 'F Y';
        $this->arg_format = 'Ym';
        $this->formula = views_date_sql_format($this->arg_format, "***table***.$this->real_field");
        break;

      case 'Created month':
      case 'Updated month':
        $this->format = 'F';
        $this->arg_format = 'm';
        $this->formula = views_date_sql_extract('MONTH', "***table***.$this->real_field");
        break;

      case 'Created day':
      case 'Updated day':
        $this->format = 'j';
        $this->arg_format = 'd';
        $this->formula = views_date_sql_extract('DAY', "***table***.$this->real_field");
        break;

      case 'Created week':
      case 'Updated week':
        $this->arg_format = 'w';
        $this->formula = views_date_sql_extract('WEEK', "***table***.$this->real_field");
        break;

      default:
        // Assume full date.
        $this->format = 'F j, Y';
        $this->arg_format = 'Ymd';
        $this->formula = views_date_sql_format($this->arg_format, "***table***.$this->real_field");
        break;
    }
  }

  /**
   * Create the option definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['break_phrase'] = array('default' => FALSE);
    $options['not'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Create the options form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['description']['#markup'] = t('Contextual date range filter values are taken from the URL.');

    $form['more']['#collapsed'] = FALSE;

    // Allow passing multiple values.
    $form['break_phrase'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow multiple date ranges'),
      '#description' => t('If selected, multiple ranges may be specified by stringing them together with plus signs.<br/>Example: <strong>19990101--20051231+20130701--20140630</strong>'),
      '#default_value' => $this->options['break_phrase'],
      '#fieldset' => 'more',
    );

    $form['not'] = array(
      '#type' => 'checkbox',
      '#title' => t('Exclude'),
      '#description' => t('Negate the range. If selected, output matching the specified date range(s) will be excluded, rather than included.'),
      '#default_value' => !empty($this->options['not']),
      '#fieldset' => 'more',
    );
  }

  /**
   * Title override.
   *
   * Required because of range version of views_break_phrase() in this function.
   */
  public function title() {
    if (!$this->argument) {
      return !empty($this->definition['empty field name']) ? $this->definition['empty field name'] : t('Uncategorized');
    }
    if (!empty($this->options['break_phrase'])) {
      $this->views_break_phrase_range($this->argument);
    }
    else {
      $this->value = array($this->argument);
      $this->operator = 'or';
    }
    if ($this->value === FALSE) {
      return !empty($this->definition['invalid input']) ? $this->definition['invalid input'] : t('Invalid input');
    }
    if (empty($this->value)) {
      return !empty($this->definition['empty field name']) ? $this->definition['empty field name'] : t('Uncategorized');
    }
    return implode($this->operator == 'or' ? ' + ' : ', ', $this->value);
  }

  /**
   * Prepare the range query where clause.
   */
  public function query($group_by = FALSE) {
    $this->ensure_my_table();

    if (!empty($this->options['break_phrase'])) {
      // From "Allow multple ranges" checkbox.
      $this->views_break_phrase_range($this->argument);
    }
    else {
      $this->value = array($this->argument);
    }
    contextual_range_filter_build_range_query($this, $this->get_formula());
  }

  /**
   * Break xfrom--xto+yfrom--yto+zfrom--zto into an array or ranges.
   *
   * @param string $str
   *   The string to parse.
   */
  public function views_break_phrase_range($str) {
    if (empty($str)) {
      return;
    }
    $this->value = preg_split('/[+ ]/', $str);
    $this->operator = 'or';
    // Keep an 'error' value if invalid ranges were given.
    // A single non-empty value is ok, but a plus sign without values is not.
    if (count($this->value) > 1 && (empty($this->value[0]) || empty($this->value[1]))) {
      // Used in $this->title().
      $this->value = FALSE;
    }
  }
}
