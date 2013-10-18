
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

    <select name="user-groups" multiple>
      <?php foreach ($user_group_options as $user_group) { ?>
        <option value="<?php print "$user_group"?>"><?php print "$user_group"?></option>
      <?php } ?>

    </select>

<?php // The closing tags are attached to the date popup form element. ?>



