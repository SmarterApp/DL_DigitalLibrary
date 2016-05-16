<?php
/**
 * @file
 * sbac_acquia.default_elysia_cron_rules.inc
 */

/**
 * Implements hook_default_elysia_cron_rules().
 */
function sbac_acquia_default_elysia_cron_rules() {
  $cron_rules = array();

  $cron_rule = new stdClass;
  $cron_rule->disabled = FALSE; /* Edit this to true to make a default cron_rule disabled initially */
  $cron_rule->api_version = 1;
  $cron_rule->name = 'acquia_agent_cron';
  $cron_rule->disable = NULL;
  $cron_rule->rule = '1 4 * * *';
  $cron_rule->weight = NULL;
  $cron_rule->context = NULL;
  $cron_rules['acquia_agent_cron'] = $cron_rule;

  $cron_rule = new stdClass;
  $cron_rule->disabled = FALSE; /* Edit this to true to make a default cron_rule disabled initially */
  $cron_rule->api_version = 1;
  $cron_rule->name = 'acquia_spi_cron';
  $cron_rule->disable = NULL;
  $cron_rule->rule = '2 4 * * *';
  $cron_rule->weight = NULL;
  $cron_rule->context = NULL;
  $cron_rules['acquia_spi_cron'] = $cron_rule;

  return $cron_rules;

}
