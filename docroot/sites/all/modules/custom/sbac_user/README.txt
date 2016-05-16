Adding a new Privacy Field

First, edit field_privacy in Configuration > People > Account Settings > Manage Fields > Privacy. Add your new field to the Allowed values list in the format of field_name|Display Name. 

If this is a required field to display but will be disabled such as field_first_name is, edit js/sbac_user/sbac_user.js and set the checkbox to disabled:

$("#edit-field-privacy-und-field-name").prop('disabled', true);

Now edit sbac_user/sbac_user.module:

- In the sbac_user_privacy_check function, add your new field_name to the $privacy_fields array.

- If the field is required, disabled and checked (such as field_first_name is), edit the sbac_user_privacy_after_build function and add:

$form['field_name']['#checked'] = TRUE;

- And finally, if the field is required, make sure new accounts get it by default in the sbac_user_entity_presave function inside the "if (isset($entity->is_new) && $entity->is_new) {" statement:

$entity->field_privacy['und'][]['value'] = 'field_name';