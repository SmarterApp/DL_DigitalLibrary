<?php
namespace sbac_core\components\feedback;

// $data = 'a:501:{s:15:"status_messages";a:4:{s:8:"function";s:29:"sbac_resource_status_messages";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:9:"variables";a:1:{s:7:"display";N;}}s:23:"links__system_main_menu";a:5:{s:8:"function";s:28:"SBAC_links__system_main_menu";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:9:"variables";a:3:{s:5:"links";N;s:10:"attributes";a:1:{s:5:"class";a:1:{i:0;s:5:"links";}}s:7:"heading";a:0:{}}s:9:"base hook";s:5:"links";}s:18:"form_element_label";a:4:{s:8:"function";s:35:"label_help_theme_form_element_label";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:7:"element";}s:8:"checkbox";a:4:{s:8:"function";s:13:"SBAC_checkbox";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:7:"element";}s:10:"checkboxes";N;s:8:"textarea";a:4:{s:8:"function";s:13:"SBAC_textarea";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:7:"element";}s:12:"form_element";a:6:{s:8:"function";s:27:"feedback_theme_form_element";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:54:"sites/all/modules/custom/sbac_core/components/feedback";s:14:"render element";s:7:"element";s:4:"file";s:18:"feedback.theme.inc";s:8:"includes";a:1:{i:0;s:73:"sites/all/modules/custom/sbac_core/components/feedback/feedback.theme.inc";}}s:27:"ds_3col_stacked_equal_width";a:7:{s:8:"template";s:27:"ds-3col-stacked-equal-width";s:4:"path";s:31:"sites/all/themes/SBAC/templates";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:8:"elements";s:20:"preprocess functions";a:4:{i:0;s:19:"template_preprocess";i:1;s:21:"contextual_preprocess";i:2;s:15:"sbac_preprocess";i:3;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:4:"html";a:7:{s:8:"template";s:4:"html";s:4:"path";s:31:"sites/all/themes/SBAC/templates";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:4:"page";s:20:"preprocess functions";a:9:{i:0;s:19:"template_preprocess";i:1;s:24:"template_preprocess_html";i:2;s:23:"context_preprocess_html";i:3;s:21:"contextual_preprocess";i:4;s:29:"sbac_resource_preprocess_html";i:5;s:21:"views_preprocess_html";i:6;s:15:"sbac_preprocess";i:7;s:31:"zurb_foundation_preprocess_html";i:8;s:15:"SBAC_preprocess";}s:17:"process functions";a:4:{i:0;s:16:"template_process";i:1;s:21:"template_process_html";i:2;s:14:"ctools_process";i:3;s:11:"rdf_process";}}s:4:"page";a:7:{s:8:"template";s:4:"page";s:4:"path";s:31:"sites/all/themes/SBAC/templates";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:4:"page";s:20:"preprocess functions";a:10:{i:0;s:19:"template_preprocess";i:1;s:24:"template_preprocess_page";i:2;s:23:"context_preprocess_page";i:3;s:21:"contextual_preprocess";i:4;s:25:"sbac_help_preprocess_page";i:5;s:29:"sbac_resource_preprocess_page";i:6;s:15:"sbac_preprocess";i:7;s:31:"zurb_foundation_preprocess_page";i:8;s:15:"SBAC_preprocess";i:9;s:22:"ctools_preprocess_page";}s:17:"process functions";a:5:{i:0;s:16:"template_process";i:1;s:21:"template_process_page";i:2;s:14:"ctools_process";i:3;s:11:"rdf_process";i:4;s:18:"title_process_page";}}s:17:"search_block_form";a:7:{s:8:"template";s:17:"search-block-form";s:4:"path";s:31:"sites/all/themes/SBAC/templates";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:4:"form";s:20:"preprocess functions";a:5:{i:0;s:19:"template_preprocess";i:1;s:37:"template_preprocess_search_block_form";i:2;s:21:"contextual_preprocess";i:3;s:15:"sbac_preprocess";i:4;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:13:"search_result";N;s:14:"search_results";N;s:12:"user_profile";a:8:{s:8:"template";s:12:"user-profile";s:4:"path";s:31:"sites/all/themes/SBAC/templates";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:8:"includes";a:1:{i:0;s:27:"modules/user/user.pages.inc";}s:14:"render element";s:8:"elements";s:20:"preprocess functions";a:9:{i:0;s:40:"sbac_user_theme__preprocess_user_profile";i:1;s:19:"template_preprocess";i:2;s:32:"template_preprocess_user_profile";i:3;s:21:"contextual_preprocess";i:4;s:27:"rdf_preprocess_user_profile";i:5;s:15:"sbac_preprocess";i:6;s:15:"SBAC_preprocess";i:9;s:31:"field_group_build_entity_groups";i:10;s:19:"ds_entity_variables";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:24:"page__admin__help_topics";N;s:21:"page__change_password";N;s:43:"views_view_field__help_topics__page_1__body";N;s:52:"views_view_field__help_topics__page_1__field_summary";N;s:60:"views_view_field__help_topics__page_2__field_help_page_topic";N;s:43:"views_view_field__help_topics__page_3__body";N;s:52:"views_view_field__help_topics__page_3__field_summary";N;s:44:"views_view_field__help_topics__page_4__nid_1";N;s:31:"views_view__help_topics__page_1";N;s:31:"views_view__help_topics__page_3";N;s:10:"breadcrumb";a:4:{s:8:"function";s:26:"zurb_foundation_breadcrumb";s:4:"type";s:17:"base_theme_engine";s:10:"theme path";s:32:"sites/all/themes/zurb-foundation";s:9:"variables";a:1:{s:10:"breadcrumb";N;}}s:15:"menu_local_task";N;s:16:"menu_local_tasks";N;s:6:"button";a:4:{s:8:"function";s:22:"zurb_foundation_button";s:4:"type";s:17:"base_theme_engine";s:10:"theme path";s:32:"sites/all/themes/zurb-foundation";s:14:"render element";s:7:"element";}s:30:"field__taxonomy_term_reference";a:5:{s:8:"function";s:46:"zurb_foundation_field__taxonomy_term_reference";s:14:"render element";s:7:"element";s:9:"base hook";s:5:"field";s:4:"type";s:17:"base_theme_engine";s:10:"theme path";s:32:"sites/all/themes/zurb-foundation";}s:5:"field";a:6:{s:8:"function";s:21:"zurb_foundation_field";s:4:"type";s:17:"base_theme_engine";s:10:"theme path";s:32:"sites/all/themes/zurb-foundation";s:14:"render element";s:7:"element";s:20:"preprocess functions";a:3:{i:0;s:25:"template_preprocess_field";i:1;s:20:"rdf_preprocess_field";i:3;s:32:"zurb_foundation_preprocess_field";}s:17:"process functions";a:1:{i:0;s:22:"template_process_field";}}s:5:"block";a:7:{s:8:"template";s:5:"block";s:4:"path";s:42:"sites/all/themes/zurb-foundation/templates";s:4:"type";s:17:"base_theme_engine";s:10:"theme path";s:32:"sites/all/themes/zurb-foundation";s:14:"render element";s:8:"elements";s:20:"preprocess functions";a:8:{i:0;s:19:"template_preprocess";i:1;s:25:"template_preprocess_block";i:2;s:24:"context_preprocess_block";i:3;s:21:"contextual_preprocess";i:4;s:23:"system_preprocess_block";i:5;s:15:"sbac_preprocess";i:6;s:32:"zurb_foundation_preprocess_block";i:7;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:4:"node";a:7:{s:8:"template";s:4:"node";s:4:"path";s:42:"sites/all/themes/zurb-foundation/templates";s:4:"type";s:17:"base_theme_engine";s:10:"theme path";s:32:"sites/all/themes/zurb-foundation";s:14:"render element";s:8:"elements";s:20:"preprocess functions";a:13:{i:0;s:19:"template_preprocess";i:1;s:24:"template_preprocess_node";i:2;s:21:"contextual_preprocess";i:3;s:22:"ctools_preprocess_node";i:4;s:21:"print_preprocess_node";i:5;s:19:"rdf_preprocess_node";i:6;s:29:"sbac_resource_preprocess_node";i:7;s:21:"views_preprocess_node";i:8;s:15:"sbac_preprocess";i:9;s:31:"zurb_foundation_preprocess_node";i:10;s:15:"SBAC_preprocess";i:12;s:31:"field_group_build_entity_groups";i:13;s:19:"ds_entity_variables";}s:17:"process functions";a:4:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";i:3;s:18:"title_process_node";}}s:6:"region";a:7:{s:8:"template";s:6:"region";s:4:"path";s:42:"sites/all/themes/zurb-foundation/templates";s:4:"type";s:17:"base_theme_engine";s:10:"theme path";s:32:"sites/all/themes/zurb-foundation";s:14:"render element";s:8:"elements";s:20:"preprocess functions";a:5:{i:0;s:19:"template_preprocess";i:1;s:26:"template_preprocess_region";i:2;s:21:"contextual_preprocess";i:3;s:15:"sbac_preprocess";i:4;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:16:"admin_menu_links";a:4:{s:14:"render element";s:8:"elements";s:4:"type";s:6:"module";s:10:"theme path";s:36:"sites/all/modules/contrib/admin_menu";s:8:"function";s:22:"theme_admin_menu_links";}s:15:"admin_menu_icon";a:7:{s:9:"variables";a:2:{s:3:"src";N;s:3:"alt";N;}s:4:"file";s:14:"admin_menu.inc";s:4:"type";s:6:"module";s:10:"theme path";s:36:"sites/all/modules/contrib/admin_menu";s:8:"function";s:21:"theme_admin_menu_icon";s:8:"includes";a:1:{i:0;s:51:"sites/all/modules/contrib/admin_menu/admin_menu.inc";}s:20:"preprocess functions";a:1:{i:0;s:35:"template_preprocess_admin_menu_icon";}}s:22:"features_module_status";N;s:19:"features_components";N;s:22:"features_component_key";N;s:23:"features_component_list";N;s:21:"features_storage_link";N;s:21:"features_form_package";N;s:20:"features_form_export";N;s:24:"features_form_components";N;s:21:"features_form_buttons";N;s:25:"features_admin_components";N;s:20:"ds_forms_custom_form";N;s:16:"views_mini_pager";N;s:16:"views_view_field";a:9:{s:4:"file";s:9:"theme.inc";s:4:"path";s:37:"sites/all/modules/contrib/views/theme";s:7:"pattern";s:18:"views_view_field__";s:9:"variables";a:3:{s:4:"view";N;s:5:"field";N;s:3:"row";N;}s:4:"type";s:6:"module";s:10:"theme path";s:31:"sites/all/modules/contrib/views";s:8:"function";s:22:"theme_views_view_field";s:8:"includes";a:1:{i:0;s:47:"sites/all/modules/contrib/views/theme/theme.inc";}s:20:"preprocess functions";a:3:{i:0;s:36:"template_preprocess_views_view_field";i:1;s:39:"sbac_report_preprocess_views_view_field";i:2;s:37:"workbench_preprocess_views_view_field";}}s:19:"views_view_grouping";N;s:10:"views_view";a:10:{s:7:"pattern";s:12:"views_view__";s:4:"file";s:9:"theme.inc";s:4:"path";s:37:"sites/all/modules/contrib/views/theme";s:9:"variables";a:2:{s:10:"view_array";a:0:{}s:4:"view";N;}s:8:"template";s:10:"views-view";s:4:"type";s:6:"module";s:10:"theme path";s:32:"sites/all/themes/zurb-foundation";s:8:"includes";a:1:{i:0;s:47:"sites/all/modules/contrib/views/theme/theme.inc";}s:20:"preprocess functions";a:7:{i:0;s:19:"template_preprocess";i:1;s:30:"template_preprocess_views_view";i:2;s:21:"contextual_preprocess";i:3;s:30:"views_ui_preprocess_views_view";i:4;s:15:"sbac_preprocess";i:5;s:37:"zurb_foundation_preprocess_views_view";i:6;s:15:"SBAC_preprocess";}s:17:"process functions";a:4:{i:0;s:16:"template_process";i:1;s:27:"template_process_views_view";i:2;s:14:"ctools_process";i:3;s:11:"rdf_process";}}s:22:"views_view_unformatted";a:10:{s:7:"pattern";s:24:"views_view_unformatted__";s:4:"file";s:9:"theme.inc";s:4:"path";s:37:"sites/all/modules/contrib/views/theme";s:9:"variables";a:4:{s:4:"view";N;s:7:"options";N;s:4:"rows";N;s:5:"title";N;}s:8:"template";s:22:"views-view-unformatted";s:4:"type";s:6:"module";s:10:"theme path";s:31:"sites/all/modules/contrib/views";s:8:"includes";a:1:{i:0;s:47:"sites/all/modules/contrib/views/theme/theme.inc";}s:20:"preprocess functions";a:5:{i:0;s:19:"template_preprocess";i:1;s:42:"template_preprocess_views_view_unformatted";i:2;s:21:"contextual_preprocess";i:3;s:15:"sbac_preprocess";i:4;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:10:"flexslider";N;s:30:"media_views_view_media_browser";N;s:15:"views_view_list";a:10:{s:7:"pattern";s:17:"views_view_list__";s:4:"file";s:9:"theme.inc";s:4:"path";s:37:"sites/all/modules/contrib/views/theme";s:9:"variables";a:4:{s:4:"view";N;s:7:"options";N;s:4:"rows";N;s:5:"title";N;}s:8:"template";s:15:"views-view-list";s:4:"type";s:6:"module";s:10:"theme path";s:31:"sites/all/modules/contrib/views";s:8:"includes";a:1:{i:0;s:47:"sites/all/modules/contrib/views/theme/theme.inc";}s:20:"preprocess functions";a:6:{i:0;s:19:"template_preprocess";i:1;s:35:"template_preprocess_views_view_list";i:2;s:21:"contextual_preprocess";i:3;s:41:"draggableviews_preprocess_views_view_list";i:4;s:15:"sbac_preprocess";i:5;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:15:"views_view_grid";N;s:16:"views_view_table";N;s:18:"views_view_summary";N;s:30:"views_view_summary_unformatted";N;s:14:"views_view_rss";N;s:28:"views_view_summary_jump_menu";N;s:20:"views_view_jump_menu";N;s:22:"views_view_row_comment";N;s:18:"views_view_row_rss";N;s:17:"views_view_fields";a:10:{s:7:"pattern";s:19:"views_view_fields__";s:4:"file";s:9:"theme.inc";s:4:"path";s:37:"sites/all/modules/contrib/views/theme";s:9:"variables";a:4:{s:4:"view";N;s:7:"options";N;s:3:"row";N;s:11:"field_alias";N;}s:8:"template";s:17:"views-view-fields";s:4:"type";s:6:"module";s:10:"theme path";s:31:"sites/all/modules/contrib/views";s:8:"includes";a:1:{i:0;s:47:"sites/all/modules/contrib/views/theme/theme.inc";}s:20:"preprocess functions";a:5:{i:0;s:19:"template_preprocess";i:1;s:37:"template_preprocess_views_view_fields";i:2;s:21:"contextual_preprocess";i:3;s:15:"sbac_preprocess";i:4;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:13:"ds_row_entity";N;s:21:"views_form_views_form";N;s:18:"views_exposed_form";N;s:10:"views_more";N;s:21:"feedback_helpful_info";a:7:{s:9:"variables";a:1:{s:12:"helpful_info";N;}s:8:"template";s:21:"feedback_helpful_info";s:4:"path";s:64:"sites/all/modules/custom/sbac_core/components/feedback/templates";s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/custom/sbac_core";s:20:"preprocess functions";a:4:{i:0;s:19:"template_preprocess";i:1;s:21:"contextual_preprocess";i:2;s:15:"sbac_preprocess";i:3;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:9:"qc_teaser";N;s:14:"more_less_text";a:7:{s:9:"variables";a:3:{s:7:"summary";N;s:4:"full";N;s:9:"show_open";N;}s:8:"template";s:14:"more_less_text";s:4:"path";s:70:"sites/all/modules/custom/sbac_core/components/more_less_text/templates";s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/custom/sbac_core";s:20:"preprocess functions";a:4:{i:0;s:19:"template_preprocess";i:1;s:21:"contextual_preprocess";i:2;s:15:"sbac_preprocess";i:3;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:8:"sections";a:7:{s:9:"variables";a:2:{s:8:"sections";N;s:4:"name";N;}s:8:"template";s:8:"sections";s:20:"preprocess functions";a:2:{i:0;s:19:"sections_preprocess";i:1;s:15:"SBAC_preprocess";}s:4:"path";s:64:"sites/all/modules/custom/sbac_core/components/sections/templates";s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/custom/sbac_core";s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:38:"workbench_moderation_admin_states_form";N;s:43:"workbench_moderation_admin_transitions_form";N;s:21:"print_pdf_format_link";a:4:{s:9:"variables";a:0:{}s:4:"type";s:6:"module";s:10:"theme path";s:41:"sites/all/modules/contrib/print/print_pdf";s:8:"function";s:27:"theme_print_pdf_format_link";}s:23:"print_pdf_dompdf_footer";N;s:22:"print_pdf_tcpdf_header";N;s:20:"print_pdf_tcpdf_page";N;s:23:"print_pdf_tcpdf_content";N;s:22:"print_pdf_tcpdf_footer";N;s:23:"print_pdf_tcpdf_footer2";N;s:15:"horizontal_tabs";N;s:9:"multipage";N;s:14:"multipage_pane";N;s:7:"ds_1col";N;s:15:"ds_1col_wrapper";N;s:7:"ds_2col";N;s:13:"ds_2col_fluid";N;s:15:"ds_2col_stacked";N;s:21:"ds_2col_stacked_fluid";N;s:7:"ds_3col";N;s:19:"ds_3col_equal_width";N;s:15:"ds_3col_stacked";a:7:{s:14:"render element";s:8:"elements";s:8:"template";s:15:"ds-3col-stacked";s:4:"path";s:52:"sites/all/modules/contrib/ds/layouts/ds_3col_stacked";s:4:"type";s:6:"module";s:10:"theme path";s:28:"sites/all/modules/contrib/ds";s:20:"preprocess functions";a:4:{i:0;s:19:"template_preprocess";i:1;s:21:"contextual_preprocess";i:2;s:15:"sbac_preprocess";i:3;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:21:"ds_3col_stacked_fluid";N;s:7:"ds_4col";N;s:8:"ds_reset";N;s:11:"theme_field";N;s:20:"theme_ds_field_reset";N;s:22:"theme_ds_field_minimal";N;s:21:"theme_ds_field_expert";N;s:24:"wysiwyg_profile_overview";N;s:26:"wysiwyg_admin_button_table";N;s:19:"wysiwyg_dialog_page";N;s:32:"workbench_email_transitions_form";N;s:17:"workbench_element";N;s:28:"views_ui_display_tab_setting";N;s:27:"views_ui_display_tab_bucket";N;s:18:"views_ui_edit_item";N;s:23:"views_ui_rearrange_form";N;s:30:"views_ui_rearrange_filter_form";N;s:27:"views_ui_expose_filter_form";N;s:18:"views_ui_view_info";N;s:32:"views_ui_build_group_filter_form";N;s:12:"views_tabset";N;s:9:"views_tab";N;s:30:"views_ui_reorder_displays_form";N;s:27:"views_ui_style_plugin_table";N;s:29:"views_ui_view_preview_section";N;s:15:"views_container";N;s:28:"views_pdf_plugin_style_table";N;s:14:"views_pdf_icon";N;s:21:"views_load_more_pager";N;s:12:"user_picture";a:6:{s:9:"variables";a:1:{s:7:"account";N;}s:8:"template";s:25:"modules/user/user-picture";s:4:"type";s:6:"module";s:10:"theme path";s:12:"modules/user";s:20:"preprocess functions";a:5:{i:0;s:19:"template_preprocess";i:1;s:32:"template_preprocess_user_picture";i:2;s:21:"contextual_preprocess";i:3;s:15:"sbac_preprocess";i:4;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:21:"user_profile_category";N;s:17:"user_profile_item";N;s:9:"user_list";N;s:22:"user_admin_permissions";N;s:16:"user_admin_roles";N;s:27:"user_permission_description";N;s:14:"user_signature";N;s:26:"update_manager_update_form";N;s:17:"update_last_check";N;s:13:"update_report";N;s:14:"update_version";N;s:19:"update_status_label";N;s:10:"tree_table";N;s:10:"token_tree";N;s:15:"token_tree_link";N;s:30:"taxonomy_overview_vocabularies";N;s:23:"taxonomy_overview_terms";N;s:13:"taxonomy_term";N;s:11:"taskit_tabs";N;s:15:"taskit_interval";N;s:10:"taskit_row";N;s:21:"taskit_row_historical";N;s:4:"link";a:4:{s:9:"variables";a:3:{s:4:"text";N;s:4:"path";N;s:7:"options";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:10:"theme_link";}s:5:"links";a:4:{s:9:"variables";a:3:{s:5:"links";N;s:10:"attributes";a:1:{s:5:"class";a:1:{i:0;s:5:"links";}}s:7:"heading";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:11:"theme_links";}s:5:"image";a:5:{s:9:"variables";a:6:{s:4:"path";N;s:5:"width";N;s:6:"height";N;s:3:"alt";s:0:"";s:5:"title";N;s:10:"attributes";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:11:"theme_image";s:20:"preprocess functions";a:1:{i:0;s:20:"rdf_preprocess_image";}}s:4:"help";N;s:5:"table";a:4:{s:9:"variables";a:7:{s:6:"header";N;s:4:"rows";N;s:10:"attributes";a:0:{}s:7:"caption";N;s:9:"colgroups";a:0:{}s:6:"sticky";b:1;s:5:"empty";s:0:"";}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:11:"theme_table";}s:19:"tablesort_indicator";N;s:4:"mark";N;s:9:"item_list";a:4:{s:9:"variables";a:4:{s:5:"items";a:0:{}s:5:"title";N;s:4:"type";s:2:"ul";s:10:"attributes";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:15:"theme_item_list";}s:14:"more_help_link";N;s:9:"feed_icon";N;s:9:"more_link";N;s:8:"username";a:6:{s:9:"variables";a:1:{s:7:"account";N;}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:14:"theme_username";s:20:"preprocess functions";a:2:{i:0;s:28:"template_preprocess_username";i:1;s:23:"rdf_preprocess_username";}s:17:"process functions";a:1:{i:0;s:25:"template_process_username";}}s:12:"progress_bar";N;s:11:"indentation";N;s:8:"html_tag";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:14:"theme_html_tag";}s:16:"maintenance_page";N;s:11:"update_page";N;s:12:"install_page";N;s:9:"task_list";N;s:17:"authorize_message";N;s:16:"authorize_report";N;s:5:"pager";a:4:{s:9:"variables";a:4:{s:4:"tags";a:0:{}s:7:"element";i:0;s:10:"parameters";a:0:{}s:8:"quantity";i:9;}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:11:"theme_pager";}s:11:"pager_first";a:4:{s:9:"variables";a:3:{s:4:"text";N;s:7:"element";i:0;s:10:"parameters";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:17:"theme_pager_first";}s:14:"pager_previous";a:4:{s:9:"variables";a:4:{s:4:"text";N;s:7:"element";i:0;s:8:"interval";i:1;s:10:"parameters";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:20:"theme_pager_previous";}s:10:"pager_next";a:4:{s:9:"variables";a:4:{s:4:"text";N;s:7:"element";i:0;s:8:"interval";i:1;s:10:"parameters";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:16:"theme_pager_next";}s:10:"pager_last";a:4:{s:9:"variables";a:3:{s:4:"text";N;s:7:"element";i:0;s:10:"parameters";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:16:"theme_pager_last";}s:10:"pager_link";N;s:9:"menu_link";N;s:9:"menu_tree";N;s:17:"menu_local_action";N;s:6:"select";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:12:"theme_select";}s:8:"fieldset";N;s:5:"radio";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:11:"theme_radio";}s:6:"radios";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:12:"theme_radios";}s:4:"date";N;s:15:"exposed_filters";N;s:12:"image_button";N;s:6:"hidden";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:12:"theme_hidden";}s:9:"textfield";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:15:"theme_textfield";}s:4:"form";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:10:"theme_form";}s:8:"password";N;s:4:"file";N;s:11:"tableselect";N;s:20:"form_required_marker";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:26:"theme_form_required_marker";}s:13:"vertical_tabs";N;s:9:"container";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:14:"modules/system";s:8:"function";s:15:"theme_container";}s:18:"system_themes_page";N;s:20:"system_settings_form";N;s:12:"confirm_form";N;s:23:"system_modules_fieldset";N;s:27:"system_modules_incompatible";N;s:24:"system_modules_uninstall";N;s:13:"status_report";N;s:10:"admin_page";N;s:11:"admin_block";N;s:19:"admin_block_content";N;s:18:"system_admin_index";N;s:17:"system_powered_by";N;s:19:"system_compact_link";N;s:25:"system_date_time_settings";N;s:10:"user_login";N;s:9:"user_pass";N;s:30:"sbac_user_change_password_form";N;s:22:"user_pass_confirmation";N;s:31:"sbac_digital_library_categories";N;s:28:"sbac_my_resources_categories";N;s:31:"sbac_resource_review_categories";N;s:14:"node__resource";a:7:{s:14:"render element";s:8:"elements";s:4:"path";s:67:"sites/all/modules/custom/sbac_content_types/sbac_resource/templates";s:8:"template";s:14:"node--resource";s:20:"preprocess functions";a:3:{i:0;s:19:"template_preprocess";i:1;s:24:"template_preprocess_node";i:2;s:15:"SBAC_preprocess";}s:4:"type";s:6:"module";s:10:"theme path";s:57:"sites/all/modules/custom/sbac_content_types/sbac_resource";s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:18:"resource_node_form";N;s:23:"resource_alignment_item";N;s:15:"digital_library";N;s:12:"my_resources";N;s:15:"resource_review";N;s:39:"views_view_fields__resources__grid_view";N;s:32:"views_view__resources__grid_view";N;s:39:"views_view_fields__resources__list_view";N;s:32:"views_view__resources__list_view";N;s:43:"views_view_fields__all_resources__grid_view";N;s:36:"views_view__all_resources__grid_view";N;s:43:"views_view_fields__all_resources__list_view";N;s:48:"views_view_unformatted__all_resources__list_view";N;s:36:"views_view__all_resources__list_view";N;s:42:"views_view_fields__my_resources__grid_view";N;s:35:"views_view__my_resources__grid_view";N;s:42:"views_view_fields__my_resources__list_view";N;s:35:"views_view__my_resources__list_view";N;s:46:"views_view_fields__all_my_resources__grid_view";N;s:39:"views_view__all_my_resources__grid_view";N;s:46:"views_view_fields__all_my_resources__list_view";N;s:51:"views_view_unformatted__all_my_resources__list_view";N;s:39:"views_view__all_my_resources__list_view";N;s:45:"views_view_fields__resource_review__grid_view";N;s:38:"views_view__resource_review__grid_view";N;s:45:"views_view_fields__resource_review__list_view";N;s:38:"views_view__resource_review__list_view";N;s:49:"views_view_fields__all_resource_review__grid_view";N;s:42:"views_view__all_resource_review__grid_view";N;s:49:"views_view_fields__all_resource_review__list_view";N;s:54:"views_view_unformatted__all_resource_review__list_view";N;s:42:"views_view__all_resource_review__list_view";N;s:22:"sbac_report_individual";N;s:29:"sbac_csv_report_user_activity";N;s:30:"sbac_csv_report_resource_stats";N;s:31:"sbac_report_date_range_dropdown";N;s:31:"sbac_report_user_group_dropdown";N;s:30:"views_view_fields__sne_details";N;s:33:"views_view__contributed_resources";N;s:27:"media_sbac_schooltube_video";N;s:28:"media_sbac_teachertube_video";N;s:30:"views_view__help_topics__block";a:7:{s:8:"template";s:94:"sites/all/modules/custom/sbac_content_types/sbac_help/templates/views-view--help-topics--block";s:9:"arguments";a:1:{s:4:"view";N;}s:13:"original hook";s:10:"views_view";s:20:"preprocess functions";a:4:{i:0;s:19:"template_preprocess";i:1;s:30:"template_preprocess_views_view";i:2;s:51:"sbac_help_preprocess_views_view__help_topics__block";i:3;s:15:"SBAC_preprocess";}s:4:"type";s:6:"module";s:10:"theme path";s:53:"sites/all/modules/custom/sbac_content_types/sbac_help";s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:13:"help_dropdown";a:6:{s:4:"path";s:63:"sites/all/modules/custom/sbac_content_types/sbac_help/templates";s:8:"template";s:14:"help-drop-down";s:4:"type";s:6:"module";s:10:"theme path";s:53:"sites/all/modules/custom/sbac_content_types/sbac_help";s:20:"preprocess functions";a:4:{i:0;s:19:"template_preprocess";i:1;s:21:"contextual_preprocess";i:2;s:15:"sbac_preprocess";i:3;s:15:"SBAC_preprocess";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:14:"alignment_tags";N;s:21:"alignment_breadcrumbs";N;s:18:"alignment_checkbox";N;s:29:"sbac_alignment_alignment_form";N;s:48:"views_view_table__alignment__resource_admin_view";N;s:29:"rdf_template_variable_wrapper";a:4:{s:9:"variables";a:4:{s:7:"content";N;s:10:"attributes";a:0:{}s:7:"context";a:0:{}s:6:"inline";b:1;}s:4:"type";s:6:"module";s:10:"theme path";s:11:"modules/rdf";s:8:"function";s:35:"theme_rdf_template_variable_wrapper";}s:12:"rdf_metadata";N;s:11:"rate_widget";N;s:11:"rate_button";a:5:{s:7:"pattern";s:13:"rate_button__";s:9:"variables";a:3:{s:4:"text";N;s:4:"href";N;s:5:"class";N;}s:4:"type";s:6:"module";s:10:"theme path";s:30:"sites/all/modules/contrib/rate";s:8:"function";s:17:"theme_rate_button";}s:16:"rate_admin_types";N;s:18:"rate_admin_options";N;s:23:"rate_template_thumbs_up";N;s:28:"rate_template_thumbs_up_down";N;s:28:"rate_template_number_up_down";N;s:22:"rate_template_fivestar";N;s:21:"rate_template_emotion";N;s:19:"rate_template_yesno";a:7:{s:9:"variables";a:7:{s:5:"links";N;s:7:"results";N;s:4:"mode";N;s:10:"just_voted";b:0;s:12:"content_type";N;s:10:"content_id";N;s:15:"display_options";N;}s:8:"template";s:5:"yesno";s:4:"path";s:31:"sites/all/themes/SBAC/templates";s:4:"type";s:6:"module";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:20:"preprocess functions";a:6:{i:0;s:19:"template_preprocess";i:1;s:21:"contextual_preprocess";i:2;s:15:"sbac_preprocess";i:3;s:35:"sbac_preprocess_rate_template_yesno";i:4;s:15:"SBAC_preprocess";i:5;s:35:"SBAC_preprocess_rate_template_yesno";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:17:"print_format_link";a:4:{s:9:"variables";a:0:{}s:4:"type";s:6:"module";s:10:"theme path";s:31:"sites/all/modules/contrib/print";s:8:"function";s:23:"theme_print_format_link";}s:5:"print";N;s:12:"options_none";a:4:{s:9:"variables";a:2:{s:8:"instance";N;s:6:"option";N;}s:4:"type";s:6:"module";s:10:"theme path";s:29:"modules/field/modules/options";s:8:"function";s:18:"theme_options_none";}s:17:"node_search_admin";N;s:13:"node_add_list";N;s:12:"node_preview";N;s:19:"node_admin_overview";N;s:17:"node_recent_block";N;s:19:"node_recent_content";N;s:27:"module_filter_modules_table";N;s:33:"module_filter_system_modules_tabs";N;s:18:"menu_overview_form";N;s:19:"menu_admin_overview";N;s:15:"media_file_list";N;s:15:"media_thumbnail";N;s:17:"media_dialog_page";N;s:13:"media_element";N;s:26:"media_formatter_large_icon";N;s:27:"link_formatter_link_default";N;s:25:"link_formatter_link_plain";N;s:28:"link_formatter_link_absolute";N;s:26:"link_formatter_link_domain";N;s:31:"link_formatter_link_title_plain";N;s:23:"link_formatter_link_url";N;s:25:"link_formatter_link_short";N;s:25:"link_formatter_link_label";N;s:28:"link_formatter_link_separate";N;s:10:"link_field";N;s:16:"lexicon_alphabar";N;s:16:"lexicon_overview";N;s:24:"lexicon_overview_section";N;s:21:"lexicon_overview_item";N;s:18:"lexicon_block_term";N;s:17:"lexicon_mark_term";N;s:20:"legal_administration";N;s:13:"legal_display";N;s:10:"legal_page";N;s:11:"legal_login";N;s:18:"legal_accept_label";N;s:17:"ldap_servers_list";N;s:19:"ldap_servers_server";N;s:27:"ldap_servers_https_required";N;s:23:"ldap_server_token_table";N;s:28:"ldap_server_ldap_entry_table";N;s:15:"ldap_query_list";N;s:10:"ldap_query";N;s:18:"ldap_query_results";N;s:31:"ldap_authorization_test_results";N;s:30:"ldap_authorization_admin_index";N;s:42:"ldap_authentication_user_login_block_links";N;s:37:"ldap_authentication_user_pass_message";N;s:57:"ldap_authentication_user_pass_validate_ldap_authenticated";N;s:33:"ldap_authentication_login_message";N;s:37:"ldap_authentication_message_not_found";N;s:45:"ldap_authentication_message_not_authenticated";N;s:12:"joyride_tips";N;s:12:"joyride_help";N;s:12:"joyride_demo";N;s:18:"joyride_start_link";N;s:10:"imce_admin";N;s:16:"imce_directories";N;s:15:"imce_thumbnails";N;s:14:"imce_root_text";N;s:14:"imce_user_page";N;s:14:"imce_file_list";N;s:12:"imce_content";N;s:9:"imce_page";N;s:11:"image_style";a:4:{s:9:"variables";a:7:{s:10:"style_name";N;s:4:"path";N;s:5:"width";N;s:6:"height";N;s:3:"alt";s:0:"";s:5:"title";N;s:10:"attributes";a:0:{}}s:4:"type";s:6:"module";s:10:"theme path";s:13:"modules/image";s:8:"function";s:17:"theme_image_style";}s:16:"image_style_list";N;s:19:"image_style_effects";N;s:19:"image_style_preview";N;s:12:"image_anchor";N;s:20:"image_resize_summary";N;s:19:"image_scale_summary";N;s:18:"image_crop_summary";N;s:20:"image_rotate_summary";N;s:12:"image_widget";N;s:15:"image_formatter";N;s:38:"googleanalytics_admin_custom_var_table";N;s:15:"flexslider_list";N;s:20:"flexslider_list_item";N;s:8:"fivestar";N;s:15:"fivestar_select";N;s:15:"fivestar_static";a:6:{s:9:"variables";a:4:{s:6:"rating";N;s:5:"stars";i:5;s:3:"tag";s:4:"vote";s:6:"widget";a:2:{s:4:"name";s:7:"default";s:3:"css";s:0:"";}}s:4:"file";s:27:"includes/fivestar.theme.inc";s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/fivestar";s:8:"function";s:21:"theme_fivestar_static";s:8:"includes";a:1:{i:0;s:62:"sites/all/modules/contrib/fivestar/includes/fivestar.theme.inc";}}s:23:"fivestar_static_element";a:6:{s:9:"variables";a:3:{s:12:"star_display";N;s:5:"title";N;s:11:"description";N;}s:4:"file";s:27:"includes/fivestar.theme.inc";s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/fivestar";s:8:"function";s:29:"theme_fivestar_static_element";s:8:"includes";a:1:{i:0;s:62:"sites/all/modules/contrib/fivestar/includes/fivestar.theme.inc";}}s:16:"fivestar_summary";a:6:{s:9:"variables";a:5:{s:11:"user_rating";N;s:14:"average_rating";N;s:5:"votes";i:0;s:5:"stars";i:5;s:9:"microdata";a:0:{}}s:4:"file";s:27:"includes/fivestar.theme.inc";s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/fivestar";s:8:"function";s:22:"theme_fivestar_summary";s:8:"includes";a:1:{i:0;s:62:"sites/all/modules/contrib/fivestar/includes/fivestar.theme.inc";}}s:16:"fivestar_preview";N;s:23:"fivestar_preview_widget";N;s:24:"fivestar_preview_wrapper";N;s:17:"fivestar_settings";N;s:19:"fivestar_color_form";N;s:26:"fivestar_formatter_default";a:6:{s:14:"render element";s:7:"element";s:4:"file";s:27:"includes/fivestar.theme.inc";s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/fivestar";s:8:"function";s:32:"theme_fivestar_formatter_default";s:8:"includes";a:1:{i:0;s:62:"sites/all/modules/contrib/fivestar/includes/fivestar.theme.inc";}}s:25:"fivestar_formatter_rating";N;s:29:"fivestar_formatter_percentage";N;s:21:"filter_admin_overview";N;s:32:"filter_admin_format_filter_order";N;s:11:"filter_tips";N;s:19:"text_format_wrapper";N;s:21:"filter_tips_more_info";N;s:17:"filter_guidelines";N;s:11:"file_entity";N;s:24:"file_entity_search_admin";N;s:30:"file_entity_file_type_overview";N;s:30:"file_entity_file_display_order";N;s:21:"file_entity_file_link";N;s:25:"file_entity_download_link";N;s:22:"file_entity_file_audio";N;s:22:"file_entity_file_video";N;s:9:"file_link";N;s:9:"file_icon";N;s:17:"file_managed_file";N;s:11:"file_widget";N;s:20:"file_widget_multiple";N;s:20:"file_formatter_table";N;s:16:"file_upload_help";N;s:14:"field_ui_table";N;s:21:"field_collection_item";N;s:21:"field_collection_view";N;s:25:"field_multiple_value_form";a:4:{s:14:"render element";s:7:"element";s:4:"type";s:6:"module";s:10:"theme path";s:13:"modules/field";s:8:"function";s:31:"theme_field_multiple_value_form";}s:14:"facetapi_title";N;s:22:"facetapi_facet_missing";N;s:14:"facetapi_count";N;s:22:"facetapi_link_inactive";N;s:20:"facetapi_link_active";N;s:26:"facetapi_deactivate_widget";N;s:26:"facetapi_accessible_markup";N;s:29:"facetapi_realm_settings_table";N;s:28:"facetapi_sort_settings_table";N;s:30:"facetapi_filter_settings_table";N;s:13:"entity_status";N;s:6:"entity";a:10:{s:14:"render element";s:8:"elements";s:8:"template";s:6:"entity";s:7:"pattern";s:57:"(feedback|review|media|flag|field_collection_item)(\.|__)";s:4:"path";s:38:"sites/all/modules/contrib/entity/theme";s:4:"file";s:16:"entity.theme.inc";s:4:"type";s:6:"module";s:10:"theme path";s:32:"sites/all/modules/contrib/entity";s:8:"includes";a:1:{i:0;s:55:"sites/all/modules/contrib/entity/theme/entity.theme.inc";}s:20:"preprocess functions";a:7:{i:0;s:19:"template_preprocess";i:1;s:26:"template_preprocess_entity";i:2;s:21:"contextual_preprocess";i:3;s:15:"sbac_preprocess";i:4;s:15:"SBAC_preprocess";i:6;s:31:"field_group_build_entity_groups";i:7;s:19:"ds_entity_variables";}s:17:"process functions";a:3:{i:0;s:16:"template_process";i:1;s:14:"ctools_process";i:2;s:11:"rdf_process";}}s:15:"entity_property";N;s:23:"entity_ui_overview_item";N;s:14:"ds_search_page";N;s:32:"ds_search_group_by_type_settings";N;s:19:"diff_node_revisions";N;s:16:"diff_header_line";N;s:17:"diff_content_line";N;s:15:"diff_empty_line";N;s:16:"diff_inline_form";N;s:20:"diff_inline_metadata";N;s:17:"diff_inline_chunk";N;s:13:"dblog_message";N;s:10:"date_popup";N;s:14:"date_nav_title";N;s:13:"date_timezone";N;s:11:"date_select";N;s:9:"date_text";N;s:19:"date_select_element";N;s:22:"date_textfield_element";N;s:21:"date_part_hour_prefix";N;s:23:"date_part_minsec_prefix";N;s:20:"date_part_label_year";N;s:21:"date_part_label_month";N;s:19:"date_part_label_day";N;s:20:"date_part_label_hour";N;s:22:"date_part_label_minute";N;s:22:"date_part_label_second";N;s:20:"date_part_label_ampm";N;s:24:"date_part_label_timezone";N;s:20:"date_part_label_date";N;s:20:"date_part_label_time";N;s:22:"date_views_filter_form";N;s:17:"date_calendar_day";N;s:13:"date_time_ago";N;s:10:"date_combo";N;s:15:"date_text_parts";N;s:19:"date_display_single";N;s:18:"date_display_range";N;s:24:"date_display_combination";N;s:21:"date_display_interval";N;s:33:"ctools_menu_local_actions_wrapper";N;s:18:"ctools_collapsible";N;s:29:"ctools_collapsible_remembered";N;s:19:"ctools_context_list";N;s:28:"ctools_context_list_no_table";N;s:24:"ctools_context_item_form";N;s:23:"ctools_context_item_row";N;s:23:"ctools_access_admin_add";N;s:24:"links__ctools_dropbutton";N;s:15:"ctools_dropdown";N;s:33:"ctools_stylizer_color_scheme_form";N;s:28:"ctools_stylizer_preview_form";N;s:17:"ctools_style_icon";N;s:19:"ctools_wizard_trail";N;s:15:"context_ui_form";N;s:18:"context_ui_plugins";N;s:17:"context_ui_editor";N;s:18:"context_block_form";N;s:26:"context_block_regions_form";N;s:20:"context_block_editor";N;s:21:"context_block_browser";N;s:26:"context_block_browser_item";N;s:32:"context_block_script_placeholder";N;s:13:"comment_block";N;s:15:"comment_preview";N;s:7:"comment";N;s:22:"comment_post_forbidden";N;s:15:"comment_wrapper";N;s:18:"cmis_query_results";N;s:18:"cmis_browser_popup";N;s:12:"cmis_browser";N;s:24:"cmis_browser_browse_form";N;s:28:"cmis_browser_browse_children";N;s:30:"cmis_browser_browse_breadcrumb";N;s:31:"cmis_browser_content_properties";N;s:26:"cmis_browser_folder_picker";N;s:31:"apachesolr_search_browse_blocks";N;s:26:"apachesolr_search_snippets";N;s:27:"apachesolr_search_noresults";N;s:29:"apachesolr_search_suggestions";N;s:42:"apachesolr_search_mlt_recommendation_block";N;s:32:"apachesolr_search_snippets__file";N;s:20:"apachesolr_sort_list";N;s:20:"apachesolr_sort_link";N;s:25:"apachesolr_settings_title";N;s:24:"acquia_agent_banner_form";N;s:19:"ldap_user_conf_form";N;s:24:"block_admin_display_form";N;s:18:"resource_slideshow";a:10:{s:3:"key";s:18:"resource_slideshow";s:4:"name";s:18:"Resource Slideshow";s:8:"ui_limit";a:1:{i:0;s:10:"resource|*";}s:4:"path";s:54:"sites/all/modules/custom/sbac_core/components/feedback";s:4:"file";s:18:"feedback.theme.inc";s:9:"variables";a:0:{}s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/devtools";s:8:"function";s:24:"theme_resource_slideshow";s:8:"includes";a:1:{i:0;s:73:"sites/all/modules/custom/sbac_core/components/feedback/feedback.theme.inc";}}s:13:"flagging_form";a:9:{s:3:"key";s:13:"flagging_form";s:4:"name";s:13:"Flagging Form";s:4:"path";s:50:"sites/all/modules/custom/sbac_core/components/flag";s:4:"file";s:14:"flag.theme.inc";s:9:"variables";a:0:{}s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/devtools";s:8:"function";s:19:"theme_flagging_form";s:8:"includes";a:1:{i:0;s:65:"sites/all/modules/custom/sbac_core/components/flag/flag.theme.inc";}}s:13:"review_author";a:9:{s:3:"key";s:13:"review_author";s:4:"name";s:13:"Review Author";s:4:"path";s:52:"sites/all/modules/custom/sbac_core/components/review";s:4:"file";s:16:"review.theme.inc";s:9:"variables";a:0:{}s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/devtools";s:8:"function";s:19:"theme_review_author";s:8:"includes";a:1:{i:0;s:69:"sites/all/modules/custom/sbac_core/components/review/review.theme.inc";}}s:18:"review_helpfulness";a:9:{s:3:"key";s:18:"review_helpfulness";s:4:"name";s:18:"Review Helpfulness";s:4:"path";s:52:"sites/all/modules/custom/sbac_core/components/review";s:4:"file";s:16:"review.theme.inc";s:9:"variables";a:0:{}s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/devtools";s:8:"function";s:24:"theme_review_helpfulness";s:8:"includes";a:1:{i:0;s:69:"sites/all/modules/custom/sbac_core/components/review/review.theme.inc";}}s:11:"review_vote";a:9:{s:3:"key";s:11:"review_vote";s:4:"name";s:19:"Helpful Vote Widget";s:4:"path";s:52:"sites/all/modules/custom/sbac_core/components/review";s:4:"file";s:16:"review.theme.inc";s:9:"variables";a:0:{}s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/devtools";s:8:"function";s:17:"theme_review_vote";s:8:"includes";a:1:{i:0;s:69:"sites/all/modules/custom/sbac_core/components/review/review.theme.inc";}}s:13:"review_delete";a:9:{s:3:"key";s:13:"review_delete";s:4:"name";s:13:"Delete Button";s:4:"path";s:52:"sites/all/modules/custom/sbac_core/components/review";s:4:"file";s:16:"review.theme.inc";s:9:"variables";a:0:{}s:4:"type";s:6:"module";s:10:"theme path";s:34:"sites/all/modules/contrib/devtools";s:8:"function";s:19:"theme_review_delete";s:8:"includes";a:1:{i:0;s:69:"sites/all/modules/custom/sbac_core/components/review/review.theme.inc";}}s:20:"strongarm_admin_form";N;s:20:"form_element_label_x";a:4:{s:8:"function";s:23:"SBAC_form_element_label";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:7:"element";}s:21:"form_element_original";a:4:{s:8:"function";s:17:"SBAC_form_element";s:4:"type";s:12:"theme_engine";s:10:"theme path";s:21:"sites/all/themes/SBAC";s:14:"render element";s:7:"element";}}';
// $data = unserialize($data);
// print_rr($data);
// exit();

class Hooks extends \devtools\Hooks {
  protected $_info = '';
  protected $_bundles = array();

  function __construct() {
    $this->_info = field_info_bundles('feedback');
    $this->_bundles = array_keys($this->_info);
  }

  /**
   * Post-initialization operations.
   * @return [type] [description]
   */
  function postInit() {
    // add custom Display Suite fields
    $ds_args = array(
      'path' => $this->_path,
      'file' => 'feedback.theme.inc',
      'variables' => array(),
    );

    add_ds_field('node',  array(
      'key' => 'resource_slideshow',
      'name' => t('Resource Slideshow'),
      'ui_limit' => array(
        'resource|*', // limit to displaying on Resource bundles
      ),
    ) + $ds_args);
  }

  /*----------------------------------------------------------------------------
      DRUPAL HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_init().
   */
  function hook_init() {
    // redirect gate keeper entities to their appropriate resource node;
    // in the "natural" user-flow, the user will only end up here after
    // submitting a Gate Keeper entity as either "meets" or "doesn't meet."
    // we can use that info to direct the user to an appropriate tab
    if ($feedback = current_feedback()) {
      if (!isset($feedback->node_id)) {
        return;
      }

      if ($feedback->type == 'gate_keeper') {
        // figure out which review tab we want to default to
        $fragment = 'about';

        if ($feedback->completed) {
          if ($feedback->met_criteria) {
            $fragment = 'qc'; // quality review tab
          }
          else {
            $fragment = 'gk'; // gate keeper tab
          }
        }

        drupal_goto('node/' . $feedback->node_id, array(
          'fragment' => 'review-' . $fragment,
        ));
      }
      elseif ($feedback->type == 'qc') {
        drupal_goto('node/' . $feedback->node_id, array(
          'fragment' => 'review-qc',
        ));
      }
    }
    elseif (preg_match('#node/(\d+)/edit#', $_GET['q'], $matches)) {
      // can't edit resources unless they're in draft state
      $node = node_load($matches[1]);

      if ($node && $node->type == 'resource') {
        $states = array(
          'needs_review',
          'being_reviewed',
          'rejected',
          'approved',
          'published',
        );

        if (in_array($node->workbench_moderation['current']->state, $states) && !user_access('administer nodes')) {
          drupal_access_denied();
          exit();
        }
      }
    }

    // we need to re-arrange some hook calls to call our stuff *after* workbench, and
    // workbench attempts to set itself to run after everything else, so we run
    // workbench's stuff, and then our own.
    $hooks_cache = &drupal_static('module_implements');
    unset($hooks_cache['module_implements_alter']['workbench_email']);
    
    foreach ($hooks_cache as $hook => &$implementations) {
      if (strpos($hook, 'form') !== FALSE) {
        // call workbench's code
        if (module_exists('workbench_email')) {
          workbench_email_module_implements_alter($implementations, $hook);
        }

        // now move our hook to the end
        if ($hook == 'form_node_form_alter' && isset($implementations['sbac_core'])) {
          $group = $implementations['sbac_core'];
          unset($implementations['sbac_core']);
          $implementations['sbac_core'] = $group;
        }
      }
    }
  }

  /**
   * Extends hook_menu().
   */
  function hook_menu() {
    $base = array(
      'file' => 'feedback.pages.inc',
      'file path' => $this->_path,
    );

    $items['admin/sbac/feedback'] = array(
      'title' => 'Feedback Flow', 
      'page callback' => 'sbac_core_index_page',
      'access arguments' => array('configure sbac'), 
    ) + $base;

    $items['admin/sbac/feedback/gate_keeper'] = array(
      'title' => 'Gate Keeper', 
      'page callback' => 'drupal_get_form', 
      'page arguments' => array('feedback_gate_keeper_admin_form'),
      'access arguments' => array('configure sbac'), 
      'file' => 'feedback.admin.inc',
      'weight' => 0,
    ) + $base;

    $items['admin/sbac/feedback/quality_review'] = array(
      'title' => 'Quality Review', 
      'page callback' => 'drupal_get_form', 
      'page arguments' => array('feedback_quality_review_admin_form'),
      'access arguments' => array('configure sbac'), 
      'file' => 'feedback.admin.inc',
      'weight' => 1,
    ) + $base;

    $items['admin/sbac/feedback/post'] = array(
      'title' => 'Post', 
      'page callback' => 'drupal_get_form', 
      'page arguments' => array('feedback_post_admin_form'),
      'access arguments' => array('configure sbac'), 
      'file' => 'feedback.admin.inc',
      'weight' => 2,
    ) + $base;

    $items['node/%node/feedback'] = array(
      'title' => 'Feedback',
      'page callback' => 'resource_feedback_page',
      'page arguments' => array(1),
      'access callback' => 'resource_access',
      'access arguments' => array('view about', 1),
      'weight' => 2,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    ) + $base;

    $items['node/%node/feedback/gate-keeper'] = array(
      'title' => 'Gate Keeper',
      'page callback' => 'resource_feedback_ajax_page',
      'page arguments' => array('gate_keeper', 1),
      'access callback' => 'resource_access',
      'access arguments' => array('edit gate keeper', 1),
      'weight' => 2,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CALLBACK,
    ) + $base;
    
    $items['node/%node/feedback/qc'] = array(
      'title' => 'Quality Criteria Review',
      'page callback' => 'resource_feedback_ajax_page',
      'page arguments' => array('qc', 1),
      'access callback' => 'resource_access',
      'access arguments' => array('edit quality criteria', 1),
      'weight' => 2,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CALLBACK,
    ) + $base;

    $items['node/%node/feedback/post'] = array(
      'title' => 'Post',
      'page callback' => 'resource_feedback_ajax_page',
      'page arguments' => array('post', 1),
      'access callback' => 'resource_access',
      'access arguments' => array('edit post', 1),
      'weight' => 3,
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CALLBACK,
    ) + $base;

    $items['node/%node/feedback/redirect'] = array(
      'title' => 'Gate Keeper',
      'page callback' => 'resource_redirect_page',
      'page arguments' => array(1, 4),
      'access callback' => TRUE,
      'weight' => 2,
      'type' => MENU_CALLBACK,
    ) + $base;

    return $items;
  }

  /**
   * Extends hook_theme().
   */
  function hook_theme($existing, $type, $theme, $path) {
    $base = array(
      'path' => $this->_path . '/templates',
    );

    $items = array(
      'feedback_helpful_info' => array(
        'variables' => array(
          'helpful_info' => NULL,
        ),
        'template' => 'feedback_helpful_info',
      ),
      'qc_teaser' => array(
        'variables' => array(
          'id' => NULL,
          'author' => NULL,
          'created' => NULL,
          'headline' => NULL,
          'comments' => NULL,
        ),
        'template' => 'qc_teaser',
      ),
    );

    foreach ($items as &$item) {
      $item += $base;
    }

    return $items;
  }

  /**
   * Extends hook_permission().
   */
  function hook_permission() {
    return array(
      'edit feedback properties' => array(
        'title' => t('Edit Feedback properties.'),
        'description' => t('Grants permission to edit the properties on existing Feedback entities.'),
      ),
    );
  }

  /**
   * Extends hook_form_alter().
   */
  function hook_form_alter(&$form, &$form_state, $form_id) {
    $args = func_get_args();

    // feedback add/edit form
    if (preg_match('/^eck__entity__form_(edit|add)_feedback_(' . implode('|', $this->_bundles) . ')$/', $form_id, $matches)) {
      // basic form data
        $bundle = $matches[2];

      // build form utility object to take care of the heavy lifting
        switch ($bundle) {
          case 'gate_keeper':
            $class_name = 'GateKeeper';
            break;

          case 'qc':
            $class_name = 'Qc';
            break;

          case 'post':
            $class_name = 'Post';
            break;
        }

        if ($class_name) {
          module_load_include('inc', 'sbac_core', 'components/feedback/includes/form_utility/class.Base');
          module_load_include('inc', 'sbac_core', 'components/feedback/includes/form_utility/class.' . $class_name);

          $full_class_name = 'sbac_core\\components\\feedback\\form_utility\\' . $class_name;
          $form_utility = new $full_class_name($form, $form_state, $this->_info[$bundle]);

          $form_utility->attachHelpfulInfo();
          $form_utility->process();
          $form_utility->postProcess();
        }
    }
    // resource node form on the main resource profile page (ie. edit tags)
    elseif ($form_id == 'resource_node_form' && isset($form_state['build_info']['args'][1]) && $form_state['build_info']['args'][1] == 'edit_tags') {
      $data = entity_load('feedback', FALSE, array(
        'type' => 'post',
        'completed' => 0,
        'status' => 1,
      ));

      if ($data) {
        $post = array_shift($data);

        // remove data we're not interested in
          $remove = array(
            'group_basic',
            'group_materials',
            'group_summary',
            'group_advanced',
            'group_paradata'
          );

          foreach ($remove as $group) {
            unset($form['#groups'][$group], $form['#fieldgroups'][$group]);
          }

          foreach (array_keys($form) as $key) {
            $conditions = implode('|', array(
              'container_close',
              'container_open',
              'completed_flag',
              '_guidelines',
              'title_of_resource_',
            ));

            if (preg_match('#' . $conditions . '#', $key)) {
              unset($form[$key]);
            }
          }

          foreach ($form['#group_children'] as $field => $group) {
            if (in_array($group, $remove)) {
              unset($form['#group_children'][$field]);
              unset($form[$field]);
            }
          }

          unset($form['actions']);
          unset($form['#after_build']);
          unset($form['#validate']);
          unset($form['#submit']);

        // build the new submit buttons
          // cancel button
          $form['actions']['#weight'] = 999;

          $trigger_id = 'edit-tags-cancel';

          $text = t('Cancel review (!hours hrs)', array(
                    '!hours' => feedback_hours_left($post),
                  ));

          $url = implode('/', array(
            'node',
            $post->node_id,
            'feedback',
            'post',
            'cancel',
            $trigger_id,
            $post->id,
          ));

          $options = array(
            'attributes' => array(
              'class' => array(
                'use-ajax',
                'use-dialog',
                'button',
                'radius',
              ),
              'id' => $trigger_id,
            ),
          );

          $form['actions']['cancel'] = array(
            '#markup' => l($text, $url, $options),
          );

        // submit button
          $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Save and Close'),
            '#ajax' => array(
              'callback' => 'feedback_edit_tags_ajax_save',
              'wrapper' => 'sbac-resource-form',
            ),
            '#attributes' => array(
              'class' => array(
                'action-save',
              ),
            ),
            '#submit' => array(
              'feedback_edit_tags_form_submit',
            ),
          );

        // continue button
          $form['actions']['continue'] = array(
            '#type' => 'submit',
            '#value' => t('Save and Continue'),
            '#ajax' => array(
              'callback' => 'feedback_edit_tags_ajax_continue',
              'wrapper' => 'sbac-resource-form',
            ),
            '#attributes' => array(
              'class' => array(
                'action-continue',
                'secondary',
                'button',
              ),
            ),
            '#validate' => array(
              'feedback_edit_tags_form_validate',
            ),
            '#submit' => array(
              'feedback_edit_tags_form_submit',
            ),
          );
            
          $form['workbench_moderation_state_new'] = array(
            '#type' => 'value',
            '#value' => 'approved',
          );
      }
    }
  }

  /**
   * Extends hook_cron().
   */
  function hook_cron() {
    // send out reminder notifications for resources which are approaching expiry time
      $notification_time = strtotime('-' . FEEDBACK_REVIEW_NOTIFICATION . ' hours');

      $query =  " SELECT    id, uid, node_id
                  FROM      eck_feedback
                  WHERE     status = 1
                  AND       completed = 0
                  AND       created  <= :time
                  AND       type = 'post'
                  AND       reminder = 0
                ";

      $args = array(
        ':time' => $notification_time,
      );

      $result = db_query($query, $args);

      foreach ($result as $row) {
        $task = taskit_get_object('review_reminder');
        $task->addVisibility($task::VISIBILITY_USER);
        $task->addEntity('node', $row->node_id);
        $task->addEntity('feedback', $row->id);
        $task->addOwningUser($row->uid);
        $task->addTriggeringUser(1);
        $task->save();
      }

    // disable feedback entities which have reached the expiry time
      // don't simply subtract seconds from the current timestamp - that'll get messed up
      // during daylight time changes
      $expiry_time = strtotime('-' . FEEDBACK_REVIEW_TIMEOUT . ' hours');

      $args = array(
        ':time' => $expiry_time,
      );

      // pull up active, yet incomplete gate keeper entities which are past the time limitation
      $query = "  SELECT    id, node_id
                  FROM      eck_feedback
                  WHERE     status = 1
                  AND       completed = 0
                  AND       created <= :time 
                  AND       type = 'gate_keeper'
               ";

      $result = db_query($query, $args)->fetchAll();
      foreach ($result as $row) {
        if ($node = node_load($row->node_id)) {
          // if this is an incomplete gate keeper, then the resource won't have any reviews
          // and we can safely bump it back to draft; we don't need to worry about
          // review entities, because to have one of those in the system, the resource must
          // have a completed gate keeper, meaning we don't need to change any node workflow
          // properties
          workbench_moderation_moderate($node, 'draft');
        }
      }

      // now disable all incomplete feedback entities
      $query = "  UPDATE  eck_feedback
                  SET     status = 0
                  WHERE   status = 1
                  AND     completed = 0
                  AND     created <= :time
               ";

      db_query($query, $args);
  }

  /**
   * Extends hook_node_view_alter().
   */
  function hook_node_view_alter(&$build) {
    // add the review tabs to resource nodes
    if ($build['#node']->type == 'resource' && $build['#view_mode'] == 'full') {
      module_load_include('inc', 'sbac_core', 'components/feedback/feedback.pages');

      $build['review'] = array(
        '#markup' => resource_feedback_page($build['#node']),
      );
    }
  }

  /**
   * Extends hook_js_alter().
   */
  function hook_js_alter(&$javascript) {
    // this JS is throwing errors and is breaking everything; we don't need it
    unset($javascript['sites/all/themes/SBAC/js/vendor/jquery.migrate.1.1.1.js']);
  }

  /**
   * Extends hook_theme_registry_alter().
   */
  function hook_theme_registry_alter(&$theme_registry) {
    // We alter the registry and add a new theme callback so we can append a div
    // right before the regular theme element; this div gets the 'error' class
    // whenever the subsequent element contains a validation error. By not 
    // wrapping the original element we don't break any selectors or markup,
    // and can still use CSS siblings selector to target it.
    // 
    // All this headache is required to add the red 'x' (validation fail icon)
    // on form elements, yet outside the element's immediate DOM structure

    $theme_registry['form_element_original'] = $theme_registry['form_element'];

    $theme_registry['form_element']['function'] = 'feedback_theme_form_element';
    $theme_registry['form_element']['file'] = 'feedback.theme.inc';
    $theme_registry['form_element']['theme path'] = $this->_path;
    $theme_registry['form_element']['includes'] = array(
      $this->_path . '/feedback.theme.inc',
    );
  }

  /**
   * Exends hook_field_attach_form().
   */
  function hook_field_attach_form($entity_type, $entity, &$form, &$form_state, $langcode) {
    // required to do proper field validation on Field Collection items;
    // see https://drupal.org/node/1289062#comment-7584113 for more info
    if ($entity_type == 'field_collection_item') {
      $info = entity_get_info($entity_type);
      $bundle_key = $info['entity keys']['bundle'];

      if (in_array($entity->{$bundle_key}, array('field_quality_set', 'field_review_set'))) {
        $form['#required'] = TRUE;
      }
    }
  }

  /**
   * Extends hook_entity_presave();
   */
  function hook_entity_presave($entity, $type) {
    // set active status for new Review entities
    if ($type == 'feedback' && $entity->type == 'qc' && (!isset($entity->id) || !$entity->id)) {
      $entity->status = 1;
    }
  }

  /**
   * Extends hook_entity_insert().
   */
  function hook_entity_insert($entity, $type) {
    if ($type == 'feedback') {
      $this->_check_resource_review_state($entity);
    }
  }

  /**
   * Extends hook_entity_update().
   */
  function hook_entity_update($entity, $type) {
    if ($type == 'feedback') {
      $this->_check_resource_review_state($entity);
    }
  }

  /**
   * Extemds hook_entity_view_alter().
   */
  function hook_entity_view_alter(&$build, $type) {

  }

  /**
   * Extends hook_form_BASE_FORM_ID_alter().
   */
  function hook_form_node_form_alter(&$form, $form_state) {
    // this must be a node form and a type that has moderation enabled
    if (!workbench_moderation_node_type_moderated($form['type']['#value'])) {
      return;
    }

    // get current state
    if (isset($form['#node']->workbench_moderation['current']->state)) {
      $moderation_state = $form['#node']->workbench_moderation['current']->state;
    }
    else {
      $moderation_state = variable_get('workbench_moderation_default_state_' . $form['type']['#value'], workbench_moderation_state_none());
    }

    // if the current state is published, then workbench_moderation will have changed
    // the form's default value to Draft, in order to force the creation of a new
    // revision. We don't need/want this workflow, so we change the form's state back
    // to published.

    if ($moderation_state == workbench_moderation_state_published()) {
      $form['options']['workbench_moderation_state_new']['#default_value'] = $moderation_state;

      // workbench replaces the revision checkbox with a hardcoded value, let's put
      // the original back
      $form['revision_information']['revision'] = array(
        '#type' => 'checkbox',
        '#title' => t('Create new revision'),
        '#default_value' => 1,
        '#access' => user_access('administer nodes'),
      );
    }
    elseif (in_array($moderation_state, array('creation', workbench_moderation_state_none()))) {
      _sbac_resource_clean_workbench_moderation($form, $form_state);
    }
  }

  /*----------------------------------------------------------------------------
      MODULE HOOKS
  ----------------------------------------------------------------------------*/

  /**
   * Extends hook_workbench_moderation_transition().
   */
  function hook_workbench_moderation_transition($node, $previous_state, $new_state) {
    if ($node->type == 'resource' && $new_state == 'needs_review') {
      $query = "  UPDATE    eck_feedback
                  SET       status = 0,
                            current = 0
                  WHERE     node_id = :node_id
               ";

      db_query($query, array(':node_id' => $node->nid));
    }
  }

  /*----------------------------------------------------------------------------
      INTERNAL / HELPERS
  ----------------------------------------------------------------------------*/

  protected function _check_resource_review_state($review) {
    if ($node = node_load($review->node_id)) {
      // if the node isn't in review yet, set it to being_reviewed
      if (isset($node->workbench_moderation['current']->state) && $node->workbench_moderation['current']->state == 'needs_review') {
        workbench_moderation_moderate($node, 'being_reviewed');

        // rebuild permissions
        node_access_acquire_grants($node, TRUE);
      }
    }
  }  
}



