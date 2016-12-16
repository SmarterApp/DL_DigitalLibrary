<?php
/**
 * @file
 * sbac_self_registration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sbac_self_registration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function sbac_self_registration_default_message_type() {
  $items = array();
  $items['password_reset_digital_library_coordinator_email'] = entity_import('message_type', '{
    "name" : "password_reset_digital_library_coordinator_email",
    "description" : "Password Reset Digital Library Coordinator Email",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 1 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear [sbac:email]:\\u003C\\/p\\u003E\\u003Cp\\u003EYou have requested to reset your Digital Library password. A Digital Library account cannot be found for your email address.\\u003C\\/p\\u003E\\u003Cp\\u003EPlease contact your Digital Library coordinator for further assistance. Find local contact information by \\u003Ca title=\\u0022Smarter Balanced\\u0022 href=\\u0022http:\\/\\/www.smarterbalanced.org\\/member-resources\\/\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not request a password reset, please ignore this message.\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear [sbac:email]:\\u003C\\/p\\u003E\\n\\u003Cp\\u003EYou have requested to reset your Digital Library password. A Digital Library account cannot be found for your email address.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EPlease contact your Digital Library coordinator for further assistance. Find local contact information by \\u003Ca title=\\u0022Smarter Balanced\\u0022 href=\\u0022http:\\/\\/www.smarterbalanced.org\\/member-resources\\/\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not request a password reset, please ignore this message.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['password_reset_password_reset_email'] = entity_import('message_type', '{
    "name" : "password_reset_password_reset_email",
    "description" : "Password Reset Password Reset Email",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 1 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear [sbac:email]:\\u003C\\/p\\u003E\\u003Cp\\u003EYou have requested to reset your Digital Library password.\\u003C\\/p\\u003E\\u003Cp\\u003EIf you know your existing password, login to the Digital Library by \\u003Ca title=\\u0022Digital Library Login\\u0022 href=\\u0022[site:login-url]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\u003Cp\\u003EIf you have forgotten your password, reset your password by \\u003Ca title=\\u0022Password Reset\\u0022 href=\\u0022![sbac:reset-link]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E. This link will expire in 72 hours.\\u003C\\/p\\u003E\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not request a password reset, please ignore this message.\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear [sbac:email]:\\u003C\\/p\\u003E\\n\\u003Cp\\u003EYou have requested to reset your Digital Library password.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EIf you know your existing password, login to the Digital Library by \\u003Ca title=\\u0022Digital Library Login\\u0022 href=\\u0022[site:login-url]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EIf you have forgotten your password, reset your password by \\u003Ca title=\\u0022Password Reset\\u0022 href=\\u0022![sbac:reset-link]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E. This link will expire in 72 hours.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not request a password reset, please ignore this message.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['password_reset_register_email'] = entity_import('message_type', '{
    "name" : "password_reset_register_email",
    "description" : "Password Reset Register Email",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 1 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear [sbac:email]:\\u003C\\/p\\u003E\\u003Cp\\u003EYou have requested to reset your Digital Library password. A Digital Library account cannot be found for your email address.\\u003C\\/p\\u003E\\u003Cp\\u003EYou may register for the Digital Library by \\u003Ca title=\\u0022Digital Library Registration\\u0022 href=\\u0022[site:url]self-registration\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not complete the Digital Library registration form, please ignore this message.\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear [sbac:email]:\\u003C\\/p\\u003E\\n\\u003Cp\\u003EYou have requested to reset your Digital Library password. A Digital Library account cannot be found for your email address.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EYou may register for the Digital Library by \\u003Ca title=\\u0022Digital Library Registration\\u0022 href=\\u0022[site:url]self-registration\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not complete the Digital Library registration form, please ignore this message.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['self_registration_digital_library_coordinator_welcome_email'] = entity_import('message_type', '{
    "name" : "self_registration_digital_library_coordinator_welcome_email",
    "description" : "Self-Registration Digital Library Coordinator Welcome Email",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 1 },
      "purge" : { "override" : 0, "enabled" : 1, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear [sbac:first-name] [sbac:last-name]:\\u003C\\/p\\u003E\\u003Cp\\u003EThank you for completing the Digital Library registration form. Your email address does not match the authorized Digital Library email domains. Please contact your district Digital Library coordinator for further assistance.\\u003C\\/p\\u003E\\u003Cp\\u003EYou may also find local contact information by \\u003Ca title=\\u0022Smarter Balanced\\u0022 href=\\u0022http:\\/\\/www.smarterbalanced.org\\/member-resources\\/\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not complete the Digital Library registration form, please ignore this message.\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear [sbac:first-name] [sbac:last-name]:\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThank you for completing the Digital Library registration form. Your email address does not match the authorized Digital Library email domains. Please contact your district Digital Library coordinator for further assistance.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EYou may also find local contact information by \\u003Ca title=\\u0022Smarter Balanced\\u0022 href=\\u0022http:\\/\\/www.smarterbalanced.org\\/member-resources\\/\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not complete the Digital Library registration form, please ignore this message.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['self_registration_password_reset_welcome_email'] = entity_import('message_type', '{
    "name" : "self_registration_password_reset_welcome_email",
    "description" : "Self-Registration Password Reset Welcome Email",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 1 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear [sbac:first-name] [sbac:last-name]:\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003EThank you for completing the Digital Library registration form. Your email address is already registered with a Digital Library account.\\u003C\\/p\\u003E\\u003Cp\\u003ELogin to the Digital Library with your email and existing password by\\u0026nbsp;\\u003Ca title=\\u0022Digital Library Login\\u0022 href=\\u0022[site:login-url]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\u003Cp\\u003EIf you have forgotten your password, you may reset your password by \\u003Ca title=\\u0022Password Reset\\u0022 href=\\u0022![sbac:reset-link]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E. This link will expire in 72 hours.\\u003C\\/p\\u003E\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not complete the Digital Library registration form, please ignore this message.\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear [sbac:first-name] [sbac:last-name]:\\u0026nbsp;\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThank you for completing the Digital Library registration form. Your email address is already registered with a Digital Library account.\\u003C\\/p\\u003E\\n\\u003Cp\\u003ELogin to the Digital Library with your email and existing password by\\u0026nbsp;\\u003Ca title=\\u0022Digital Library Login\\u0022 href=\\u0022[site:login-url]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EIf you have forgotten your password, you may reset your password by \\u003Ca title=\\u0022Password Reset\\u0022 href=\\u0022![sbac:reset-link]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E. This link will expire in 72 hours.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not complete the Digital Library registration form, please ignore this message.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  $items['self_registration_welcome_to_existing_user_email'] = entity_import('message_type', '{
    "name" : "self_registration_welcome_to_existing_user_email",
    "description" : "Self-Registration Welcome To Existing User Email",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 1 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EMessage from Smarter Balanced Digital Library\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDear [sbac:first-name] [sbac:last-name]:\\u003C\\/p\\u003E\\u003Cp\\u003EWelcome to the Digital Library! Thank you for completing the registration form.\\u003C\\/p\\u003E\\u003Cp\\u003EAccess the Digital Library by \\u003Ca title=\\u0022Digital Library Login\\u0022 href=\\u0022[site:login-url]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\u003Cp\\u003EYour user name is: [sbac:email]\\u003C\\/p\\u003E\\u003Cp\\u003EYour password is the one you have previously used for other Smarter Balanced services. If you have forgotten the password, please click the \\u201cForgot Password\\u201d link on the login screen.\\u003C\\/p\\u003E\\u003Cp\\u003EPlease allow up to 24 hours for your Digital Library access to be set up. If you have trouble getting logged in, you may contact your district Digital Library coordinator for further assistance. Find local contact information by \\u003Ca title=\\u0022Smarter Balanced\\u0022 href=\\u0022http:\\/\\/www.smarterbalanced.org\\/member-resources\\/\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not complete the Digital Library registration form, please ignore this message.\\u003C\\/p\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003EDear [sbac:first-name] [sbac:last-name]:\\u003C\\/p\\u003E\\n\\u003Cp\\u003EWelcome to the Digital Library! Thank you for completing the registration form.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EAccess the Digital Library by \\u003Ca title=\\u0022Digital Library Login\\u0022 href=\\u0022[site:login-url]\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EYour user name is: [sbac:email]\\u003C\\/p\\u003E\\n\\u003Cp\\u003EYour password is the one you have previously used for other Smarter Balanced services. If you have forgotten the password, please click the \\u201cForgot Password\\u201d link on the login screen.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EPlease allow up to 24 hours for your Digital Library access to be set up. If you have trouble getting logged in, you may contact your district Digital Library coordinator for further assistance. Find local contact information by \\u003Ca title=\\u0022Smarter Balanced\\u0022 href=\\u0022http:\\/\\/www.smarterbalanced.org\\/member-resources\\/\\u0022\\u003Eclicking here\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis email was intended for [sbac:email]. If you did not complete the Digital Library registration form, please ignore this message.\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
