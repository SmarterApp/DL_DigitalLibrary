<?php

/**
 * @file sbac_media/includes/MediaInterenetSchoolTubeHandler.inc
 *
 * Contains MediaInternetSchoolTubeHandler.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetSchoolTubeHandler extends MediaInternetBaseHandler {
  /**
   *
   * @return
   *   Boolean.
   */
  public function parse($embedCode) {
    $patterns = array(
      '@www\.schooltube\.com/video/(\w+).*@i',
    );
    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      // @TODO: Parse is called often. Refactor so that valid ID is checked
      // when a video is added, but not every time the embedCode is parsed.
      if (isset($matches[1])) {
        return file_stream_wrapper_uri_normalize('schooltube://v/' . $matches[1]);
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);
    return $file;
  }
}
