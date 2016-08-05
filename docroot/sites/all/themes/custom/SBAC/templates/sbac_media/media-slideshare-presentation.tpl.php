<?php

/**
 * !NOT USED BECAUSE EMBED CODE IS IMPLEMENTED IN JQUERY FUNCTION!
 *
 * @file sbac_media/templates/media-slideshare-presentation.tpl.php
 *
 * Template file for theme('media_slideshare_presentation').
 *
 * Variables available:
 *  $width - The width value.
 *  $height - The height value.
 * 	$url - The source URL of the presentation.
 */

?>
<div class="<?php print $classes; ?> media-slideshare-<?php print $id; ?>">
  <iframe src="<?php print $url; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" frameborder="0" marginwidth="0" marginheight="0" scrolling="no" style="border:1px solid #CCC;border-width:1px 1px 0;margin-bottom:5px" allowfullscreen webkitallowfullscreen mozallowfullscreen> </iframe>
  <!-- Missing slideshare author information from presentation -->
</div>