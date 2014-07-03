<?php

/**
 * @file sbac_media/includes/MediaInterenetTeacherTubeHandler.inc
 *
 * Contains MediaInternetTeacherTubeHandler.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetTeacherTubeHandler extends MediaInternetBaseHandler {
  /**
   *
   * @return
   *   Boolean.
   */
  public function parse($embedCode) {
    if (preg_match('%teachertube\.com/video/.*-(\d+)$%ix', $embedCode, $matches)) {
      return file_stream_wrapper_uri_normalize('teachertube://v/' . $matches[1]);
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

    if (empty($file->fid) && $title = $this->getInfo()) {
      $file->filename = truncate_utf8($title, 255);
    }

    return $file;
  }

  /*
   * Just get title because there is no api or oembed data that I could find
   * @HACK - this could break pretty easily
   */
  public function getInfo() {
    $response = drupal_http_request($this->embedCode);
    if (!isset($response->error)) {
      preg_match('#<title>(.*?) - TeacherTube</title>#i', $response->data, $matches);
      if (isset($matches[1]) && $matches[1]) {
        return $matches[1];
      }
    }
    else {
      throw new Exception("Error Processing Request. (Error: {$response->code}, {$response->error})");
      return;
    }
  }

}
