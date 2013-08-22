<?php

/**
 *  @file sbac_media/includes/MediaTeacherTubeStreamWrapper.inc
 *
 *  Create a TeacherTube Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $teachertube = new MediaTeacherTubeStreamWrapper('teachertube://v/[video-code]');
 */
class MediaTeacherTubeStreamWrapper extends MediaReadOnlyStreamWrapper {

  // Overrides $base_url defined in MediaReadOnlyStreamWrapper.
  protected $base_url = 'http://teachertube.com/embed';

  /**
   * Returns a url in the format "http://www.teachertube.com/embed.php?pg=video_294090".
   *
   * Overrides interpolateUrl() defined in MediaReadOnlyStreamWrapper.
   * This is an exact copy of the function in MediaReadOnlyStreamWrapper,
   * here in case that example is redefined or removed.
   */
  function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->base_url . '?pg=video_' . $this->parameters['v'];
    }
  }

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/teachertube';
  }

  function getTarget($f) {
    return FALSE;
  }
}
