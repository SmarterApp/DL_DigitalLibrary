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
      '@schooltube\.com/video/(\w+).*@i',
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
    if (empty($file->fid) && $info = $this->getOEmbed()) {
      $file->filename = truncate_utf8($info['title'], 255);
    }
    return $file;
  }

  /**
   * Returns information about the media. See http://www.oembed.com/.
   *
   * @return
   *   If oEmbed information is available, an array containing 'title', 'type',
   *   'url', and other information as specified by the oEmbed standard.
   *   Otherwise, NULL. Note: Only title because their return json is malformed.
   */
  public function getOEmbed() {
    $oembed_url = url('http://www.schooltube.com/oembed.json', array('query' => array('url' => $this->embedCode)));
    $response = drupal_http_request($oembed_url);
    // @HACK @TODO - SchoolTube oembed returns malformed JSON, re-investigate
    // Only getting title back for now
    if (!isset($response->error)) {
      // fix malformatted json, only putting in title
      preg_match('#"title":".*?"#i', $response->data, $matches);
      if (isset($matches[0])) {
        $json = "{" . $matches[0] . "}";
        return drupal_json_decode($json);
      }
    }
    else {
      throw new Exception("Error Processing Request. (Error: {$response->code}, {$response->error})");
      return;
    }
  }

}

