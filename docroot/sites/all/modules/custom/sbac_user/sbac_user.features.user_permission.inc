<?php
/**
 * @file
 * sbac_user.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function sbac_user_user_default_permissions() {
  $permissions = array();

  // Exported permission: access PDF version.
  $permissions['access PDF version'] = array(
    'name' => 'access PDF version',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'print_pdf',
  );

  // Exported permission: access administration menu.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'advanced end user' => 'advanced end user',
      'basic end user' => 'basic end user',
      'digital library administrator' => 'digital library administrator',
      'facilitator' => 'facilitator',
      'help desk' => 'help desk',
      'moderator' => 'moderator',
      'system administrator' => 'system administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: access administration pages.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'advanced end user' => 'advanced end user',
      'basic end user' => 'basic end user',
      'digital library administrator' => 'digital library administrator',
      'facilitator' => 'facilitator',
      'help desk' => 'help desk',
      'moderator' => 'moderator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'advanced end user' => 'advanced end user',
      'basic end user' => 'basic end user',
      'digital library administrator' => 'digital library administrator',
      'facilitator' => 'facilitator',
      'help desk' => 'help desk',
      'moderator' => 'moderator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: access content overview.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: access draggableviews.
  $permissions['access draggableviews'] = array(
    'name' => 'access draggableviews',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'help desk' => 'help desk',
    ),
    'module' => 'draggableviews',
  );

  // Exported permission: access site in maintenance mode.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: access site reports.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: access user profiles.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: access workbench.
  $permissions['access workbench'] = array(
    'name' => 'access workbench',
    'roles' => array(
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench',
  );

  // Exported permission: administer actions.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer content types.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: administer file types.
  $permissions['administer file types'] = array(
    'name' => 'administer file types',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: administer files.
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: administer menu.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'menu',
  );

  // Exported permission: administer modules.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer nodes.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: administer permissions.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: administer site configuration.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer software updates.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer taxonomy.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'digital library administrator' => 'digital library administrator',
      'help desk' => 'help desk',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: administer themes.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer url aliases.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: administer users.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: administer workbench.
  $permissions['administer workbench'] = array(
    'name' => 'administer workbench',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench',
  );

  // Exported permission: administer workbench emails.
  $permissions['administer workbench emails'] = array(
    'name' => 'administer workbench emails',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench_email',
  );

  // Exported permission: administer workbench moderation.
  $permissions['administer workbench moderation'] = array(
    'name' => 'administer workbench moderation',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: block IP addresses.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: bypass file access.
  $permissions['bypass file access'] = array(
    'name' => 'bypass file access',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: bypass node access.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: bypass workbench moderation.
  $permissions['bypass workbench moderation'] = array(
    'name' => 'bypass workbench moderation',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: cancel account.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: change own username.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: create files.
  $permissions['create files'] = array(
    'name' => 'create files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete any audio files.
  $permissions['delete any audio files'] = array(
    'name' => 'delete any audio files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: delete any document files.
  $permissions['delete any document files'] = array(
    'name' => 'delete any document files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: delete any image files.
  $permissions['delete any image files'] = array(
    'name' => 'delete any image files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: delete any video files.
  $permissions['delete any video files'] = array(
    'name' => 'delete any video files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: delete own audio files.
  $permissions['delete own audio files'] = array(
    'name' => 'delete own audio files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete own document files.
  $permissions['delete own document files'] = array(
    'name' => 'delete own document files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete own image files.
  $permissions['delete own image files'] = array(
    'name' => 'delete own image files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete own video files.
  $permissions['delete own video files'] = array(
    'name' => 'delete own video files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete revisions.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'resource publisher' => 'resource publisher',
    ),
    'module' => 'node',
  );

  // Exported permission: download any audio files.
  $permissions['download any audio files'] = array(
    'name' => 'download any audio files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download any document files.
  $permissions['download any document files'] = array(
    'name' => 'download any document files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download any image files.
  $permissions['download any image files'] = array(
    'name' => 'download any image files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download any video files.
  $permissions['download any video files'] = array(
    'name' => 'download any video files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download own audio files.
  $permissions['download own audio files'] = array(
    'name' => 'download own audio files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download own document files.
  $permissions['download own document files'] = array(
    'name' => 'download own document files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download own image files.
  $permissions['download own image files'] = array(
    'name' => 'download own image files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download own video files.
  $permissions['download own video files'] = array(
    'name' => 'download own video files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: download terms and conditions pdf.
  $permissions['download terms and conditions pdf'] = array(
    'name' => 'download terms and conditions pdf',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'sbac_user',
  );

  // Exported permission: edit any audio files.
  $permissions['edit any audio files'] = array(
    'name' => 'edit any audio files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: edit any document files.
  $permissions['edit any document files'] = array(
    'name' => 'edit any document files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: edit any image files.
  $permissions['edit any image files'] = array(
    'name' => 'edit any image files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: edit any video files.
  $permissions['edit any video files'] = array(
    'name' => 'edit any video files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: edit own audio files.
  $permissions['edit own audio files'] = array(
    'name' => 'edit own audio files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit own document files.
  $permissions['edit own document files'] = array(
    'name' => 'edit own document files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit own image files.
  $permissions['edit own image files'] = array(
    'name' => 'edit own image files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit own video files.
  $permissions['edit own video files'] = array(
    'name' => 'edit own video files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: moderate content from approved to needs_review.
  $permissions['moderate content from approved to needs_review'] = array(
    'name' => 'moderate content from approved to needs_review',
    'roles' => array(
      'resource publisher' => 'resource publisher',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from approved to published.
  $permissions['moderate content from approved to published'] = array(
    'name' => 'moderate content from approved to published',
    'roles' => array(
      'resource publisher' => 'resource publisher',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from being_reviewed to approved.
  $permissions['moderate content from being_reviewed to approved'] = array(
    'name' => 'moderate content from being_reviewed to approved',
    'roles' => array(
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from being_reviewed to needs_review.
  $permissions['moderate content from being_reviewed to needs_review'] = array(
    'name' => 'moderate content from being_reviewed to needs_review',
    'roles' => array(
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from being_reviewed to rejected.
  $permissions['moderate content from being_reviewed to rejected'] = array(
    'name' => 'moderate content from being_reviewed to rejected',
    'roles' => array(
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from creation to draft.
  $permissions['moderate content from creation to draft'] = array(
    'name' => 'moderate content from creation to draft',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from draft to needs_review.
  $permissions['moderate content from draft to needs_review'] = array(
    'name' => 'moderate content from draft to needs_review',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from needs_review to being_reviewed.
  $permissions['moderate content from needs_review to being_reviewed'] = array(
    'name' => 'moderate content from needs_review to being_reviewed',
    'roles' => array(
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from rejected to needs_review.
  $permissions['moderate content from rejected to needs_review'] = array(
    'name' => 'moderate content from rejected to needs_review',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: revert revisions.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'node',
  );

  // Exported permission: select account cancellation method.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: use workbench_moderation my drafts tab.
  $permissions['use workbench_moderation my drafts tab'] = array(
    'name' => 'use workbench_moderation my drafts tab',
    'roles' => array(
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: use workbench_moderation needs review tab.
  $permissions['use workbench_moderation needs review tab'] = array(
    'name' => 'use workbench_moderation needs review tab',
    'roles' => array(
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view all unpublished content.
  $permissions['view all unpublished content'] = array(
    'name' => 'view all unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view and edit account information.
  $permissions['view and edit account information'] = array(
    'name' => 'view and edit account information',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'sbac_user',
  );

  // Exported permission: view files.
  $permissions['view files'] = array(
    'name' => 'view files',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'advanced end user' => 'advanced end user',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'basic end user' => 'basic end user',
      'digital library administrator' => 'digital library administrator',
      'facilitator' => 'facilitator',
      'help desk' => 'help desk',
      'moderator' => 'moderator',
      'on-boarding' => 'on-boarding',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: view moderation history.
  $permissions['view moderation history'] = array(
    'name' => 'view moderation history',
    'roles' => array(
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view moderation messages.
  $permissions['view moderation messages'] = array(
    'name' => 'view moderation messages',
    'roles' => array(
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view own files.
  $permissions['view own files'] = array(
    'name' => 'view own files',
    'roles' => array(
      'resource contributor' => 'resource contributor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: view own private files.
  $permissions['view own private files'] = array(
    'name' => 'view own private files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'DLRB member' => 'DLRB member',
      'administrator' => 'administrator',
      'advanced end user' => 'advanced end user',
      'basic end user' => 'basic end user',
      'digital library administrator' => 'digital library administrator',
      'facilitator' => 'facilitator',
      'help desk' => 'help desk',
      'moderator' => 'moderator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
      'system administrator' => 'system administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: view private files.
  $permissions['view private files'] = array(
    'name' => 'view private files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: view revisions.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'resource contributor' => 'resource contributor',
      'resource publisher' => 'resource publisher',
      'resource reviewer' => 'resource reviewer',
    ),
    'module' => 'node',
  );

  // Exported permission: view the administration theme.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  return $permissions;
}
