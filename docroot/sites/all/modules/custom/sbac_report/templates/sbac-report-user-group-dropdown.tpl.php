
<?php
/**
 * @file
 * Date range dropdown template.
 */
?>
<div id="edit-user-group-dropdown" class="user-group-container">
  <label for="edit-state--3">
  <?php print t('Choose a user group'); ?>
  <span class="form-required" title="This field is required.">*</span>
  </label>
    <select id="edit-state--3" name="usergroups" multiple class="form-select required ajax-processed" >
      <?php foreach ($user_group_options as $user_group) { ?>
        <option value="<?php print "$user_group"?>"><?php print "$user_group"?></option>
      <?php } ?>

    </select>

<?php // The closing tags are attached to the date popup form element. ?>



