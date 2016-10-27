<?php

/**
 *  @file sbac_media/includes/MediaSchoolTubeStreamWrapper.inc
 *
 *  Create a SchoolTube Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $schooltube = new MediaSchoolTubeStreamWrapper('schooltube://v/[video-code]');
 */
class MediaSchoolTubeStreamWrapper extends MediaReadOnlyStreamWrapper {

  // Overrides $base_url defined in MediaReadOnlyStreamWrapper.
  protected $base_url = 'http://schooltube.com/embed';

  /**
   * Returns a url in the format "http://schooltube.com/watch?v=qsPQN4MiTeE".
   *
   * Overrides interpolateUrl() defined in MediaReadOnlyStreamWrapper.
   * This is an exact copy of the function in MediaReadOnlyStreamWrapper,
   * here in case that example is redefined or removed.
   */
  function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->base_url . '/' . $this->parameters['v'];
    }
  }

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/schooltube';
  }

  function getTarget($f) {
    return FALSE;
  }
}
