<?php
/**
 * @file
 * sbac_authorized_domains.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function sbac_authorized_domains_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_authorized-domains:admin/sbac_authorized_domains/authorized.
  $menu_links['management_authorized-domains:admin/sbac_authorized_domains/authorized'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/sbac_authorized_domains/authorized',
    'router_path' => 'admin/sbac_authorized_domains/authorized',
    'link_title' => 'Authorized Domains',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'management_authorized-domains:admin/sbac_authorized_domains/authorized',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -9,
    'customized' => 1,
    'parent_identifier' => 'management_domain-configuration:admin/sbac_authorized_domains/domains',
  );
  // Exported menu link: management_domain-configuration:admin/sbac_authorized_domains/domains.
  $menu_links['management_domain-configuration:admin/sbac_authorized_domains/domains'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/sbac_authorized_domains/domains',
    'router_path' => 'admin/sbac_authorized_domains/domains',
    'link_title' => 'Domain Configuration',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'management_domain-configuration:admin/sbac_authorized_domains/domains',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'management_sbac-configuration:admin/sbac',
  );
  // Exported menu link: management_import-domains:admin/sbac_authorized_domains/immportdomains.
  $menu_links['management_import-domains:admin/sbac_authorized_domains/immportdomains'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/sbac_authorized_domains/immportdomains',
    'router_path' => 'admin/sbac_authorized_domains/immportdomains',
    'link_title' => 'Import Domains',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'management_import-domains:admin/sbac_authorized_domains/immportdomains',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -5,
    'customized' => 1,
    'parent_identifier' => 'management_domain-configuration:admin/sbac_authorized_domains/domains',
  );
  // Exported menu link: management_unauthorized-domain-audit-log:admin/sbac_authorized_domains/domainlog.
  $menu_links['management_unauthorized-domain-audit-log:admin/sbac_authorized_domains/domainlog'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/sbac_authorized_domains/domainlog',
    'router_path' => 'admin/sbac_authorized_domains/domainlog',
    'link_title' => 'Unauthorized Domain Audit Log',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'management_unauthorized-domain-audit-log:admin/sbac_authorized_domains/domainlog',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'management_domain-configuration:admin/sbac_authorized_domains/domains',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Authorized Domains');
  t('Domain Configuration');
  t('Import Domains');
  t('Unauthorized Domain Audit Log');

  return $menu_links;
}
