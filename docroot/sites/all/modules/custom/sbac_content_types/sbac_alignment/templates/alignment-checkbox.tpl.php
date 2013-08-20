<div class="standard">
		<label for="checkbox1"><input <?php print drupal_attributes($element['#attributes']); ?> /><?php print $element['#title']; ?></label>
		<p id="description-<?php print $element['term']->tid; ?>"><?php print $element['term']->description; ?></p>
</div>
