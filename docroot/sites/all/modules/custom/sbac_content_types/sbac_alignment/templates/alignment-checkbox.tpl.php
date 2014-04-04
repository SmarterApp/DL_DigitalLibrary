<div class="standard">
    <?php $term_id = $element['term']->tid; ?>
		<label for="checkbox1"><input <?php print drupal_attributes($element['#attributes']); ?> /><?php print $element['term']->field_alignment_shortname[LANGUAGE_NONE][0]['value']; ?></label>
    <p id="description-<?php print $term_id; ?>">
      <div class="checkbox-less-<?php print $term_id; ?> checkbox-more-less short active">
        <?php print sbac_resource_truncate($element['term']->description, 140) ?>
        <a title='Read More' href="#" onclick="javascript:read_more_less(this); return false;" class="alignment-more alignment-more-<?php print $term_id; ?>" term="<?php print $term_id; ?>">Read More</a>
      </div>
      <div class="checkbox-more-<?php print $term_id; ?> checkbox-more-less long" style="display:none">
        <?php print $element['term']->description ?>
        <a title='Read Less' href="#" onclick="javascript:read_more_less(this); return false;" class="alignment-less alignment-less-<?php print $term_id; ?>" term="<?php print $term_id; ?>">Read Less</a>
      </div>
    </p>
</div>
