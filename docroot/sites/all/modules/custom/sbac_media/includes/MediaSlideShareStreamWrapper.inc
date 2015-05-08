<?php

/**
 *  @file sbac_media/includes/MediaSlideShareStreamWrapper.inc
 *
 *  Create a SlideShare Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $slideshare = new MediaSlideShareStreamWrapper('slideshare://v/[video-code]');
 */
class MediaSlideShareStreamWrapper extends MediaReadOnlyStreamWrapper {

  // Overrides $base_url defined in MediaReadOnlyStreamWrapper.
  protected $base_url = 'http://www.slideshare.net/slideshow/embed_code';

  /**
   * Returns a url in the format "http://www.slideshare.net/slideshow/embed_code/24653892?rel=0".
   *
   * Overrides interpolateUrl() defined in MediaReadOnlyStreamWrapper.
   * This is an exact copy of the function in MediaReadOnlyStreamWrapper,
   * here in case that example is redefined or removed.
   */
  function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->base_url . '/' . $this->parameters['v'] . '?rel=0';
    }
  }

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/slideshare';
  }

  function getTarget($f) {
    return FALSE;
  }
}
