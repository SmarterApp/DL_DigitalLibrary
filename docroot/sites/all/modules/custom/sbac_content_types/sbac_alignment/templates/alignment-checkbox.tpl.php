<div class="standard">
		<label for="checkbox1"><input <?php print drupal_attributes($element['#attributes']); ?> /><?php print $element['#title']; ?></label>
				<p><?php print substr($element['term']->description, 0, 200);?>
				<?php if(strlen($element['term']->description)>200):?>...<?php endif; ?></p>
		<div class="more-info">
			<?php print l(t('Read More'), '#'); ?>
			<div class="more">
				<p><?php print $element['term']->description;?></p>
			</div>
		</div>
</div>
