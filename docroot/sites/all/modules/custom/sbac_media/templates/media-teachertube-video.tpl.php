<?php

/**
 * !NOT USED BECAUSE EMBED CODE IS IMPLEMENTED IN JQUERY FUNCTION!
 *
 * @file sbac_media/templates/media-teachertube-video.tpl.php
 *
 * Template file for theme('media_teachertube_video').
 *
 * Variables available:
 *  $width - The width value.
 *  $height - The height value.
 */

?>
<div class="<?php print $classes; ?> media-teachertube-<?php print $id; ?>">
  <iframe width="<?php print $width; ?>" height="<?php print $height; ?>" src="<?php print $url; ?>" frameborder="0" allowfullscreen/></iframe>
</div>