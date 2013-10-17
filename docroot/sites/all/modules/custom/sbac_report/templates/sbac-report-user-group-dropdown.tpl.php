<!--
<?php
/**
 * @file
 * Date range dropdown template.
 */
?>
<div id="edit-user-group-dropdown" class="user-group-container">
  <label>
  <?php print t('Choose a user group'); ?>
  <span class="form-required" title="This field is required.">*</span>
  </label>
  <a href="#" id="user-group-selected" class="report-dropdown-toggle">User Group</a>
  <div id="user-group-dropdown" class="report-dropdown hide">

    <ul>

      <?php foreach ($user_group_options as $user_group) { ?>
         <li><a class="user-group-item report-dropdown-toggle" data-value="<?php print $user_group; ?>">
         <?php print t($user_group); ?>
      </a></li>'
      <?php } ?>
    </ul>

    <div><?php print t('User Group'); ?></div>
<?php // The closing tags are attached to the date popup form element. ?>
    -->
