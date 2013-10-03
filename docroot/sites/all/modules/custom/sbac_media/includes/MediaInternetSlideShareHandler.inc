<?php

/**
 * @file sbac_media/includes/MediaInterenetSlideShareHandler.inc
 *
 * Contains MediaInternetSlideShareHandler.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetSlideShareHandler extends MediaInternetBaseHandler {
  /**
   *
   * @return
   *   Boolean.
   */
  public function parse($embedCode) {
    $patterns = array(
      '@slideshare\.net/.+/(.+)@i',
    );
    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      if (isset($matches[1])) {
        // Temporary, override the uri later with the slideshare id
        return file_stream_wrapper_uri_normalize('slideshare://v/' . $matches[1]);
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
      $file->uri = file_stream_wrapper_uri_normalize('slideshare://v/' . $info['slideshow_id']);
      if (isset($info['total_slides']) && $info['total_slides']) {
        $file->duration = $info['total_slides'];
      }
    }

    return $file;
  }

  /**
   * Returns information about the media. See http://www.oembed.com/.
   *
   * @return
   *   If oEmbed information is available, an array containing 'title', 'type',
   *   'url', and other information as specified by the oEmbed standard.
   *   Otherwise, NULL.
   */
  public function getOEmbed() {
    $oembed_url = url('http://www.slideshare.net/api/oembed/2', array('query' => array('url' => $this->embedCode, 'format' => 'json')));
    $response = drupal_http_request($oembed_url);
    if (!isset($response->error)) {
      return drupal_json_decode($response->data);
    }
    else {
      throw new Exception("Error Processing Request. (Error: {$response->code}, {$response->error})");
      return;
    }
  }
}