<?php
/**
 * @file
 * Default theme implementation for displaying an alphabar in the Lexicon
 * overview page.
 *
 * This template renders an alphabar in the Lexicon overview page.
 *
 * Available variables:
 * - $lexicon_alphabar: alphabar object.
 *    - $lexicon_alphabar->instructions: The alphabar instructions text.
 *    - $lexicon_alphabar->separator: The separator to be used between the
 *      letters in the alphabar.
 *    - $lexicon_alphabar->letters: An array of letters to be used in the
 *      alphabar.
 */
?>
  <?php print theme_item_list(array(
      'title' => '',
      'items' => $lexicon_alphabar->letters,
      'type' => 'ul',
      'attributes' => array('class' => 'lexicon-links')
    )); ?>
<div class="lexicon-alphabar-instructions">
  <?php print $lexicon_alphabar->instructions; ?>
</div>
