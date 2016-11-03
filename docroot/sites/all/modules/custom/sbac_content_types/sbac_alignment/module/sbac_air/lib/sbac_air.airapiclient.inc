<?php
/**
 * AIR API CLIENT
 */
class AIRAPIClient {
  var $URL = "https://cs.smarterbalanced.org/corestandards/api/"; //should end with a /
  var $curl = NULL;
  var $HEADERS = array("Accept: application/json", "Content-Type: application/json", "Connection: TE, close");

  /**
   * Constructor
   */
  function __construct() {
    $this->curl = curl_init();
    curl_setopt($this->curl, CURLOPT_URL, $this->URL);
    curl_setopt($this->curl, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($this->curl, CURLOPT_POST, 0);
    curl_setopt($this->curl, CURLOPT_CONNECTTIMEOUT, 10);
    curl_setopt($this->curl, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($this->curl, CURLOPT_HTTPHEADER, $this->HEADERS);
  }

  /**
   * Look at the data received and make sure the expected sections are there.
   * If not, throw exceptions.
   * Falling through indicates success.
   *
   * @param $dataarr API output as a hash.
   */
  private function _verify($dataarr = array()) {
    if (count($dataarr) == 0) {
      throw new Exception("No data received");
    }
    if (!isset($dataarr["status"]) ||
      (strtolower($dataarr["status"]) != "success")
    ) {
      throw new Exception("No status OR status != success.");
    }
    if (!isset($dataarr["payload"])) {
      throw new Exception("No payload section.");
    }
  }

  /**
   * Returns the payload section of the API ouput (array).
   */
  public function getSubjectsSBAC($publisher = 'SBAC') {
    $full_url = $this->URL . "subject?publisher=$publisher";
    curl_setopt($this->curl, CURLOPT_URL, $full_url);
    $output = curl_exec($this->curl);
    $data = json_decode($output, TRUE);
    $this->_verify($data);
    return $data["payload"];
  }

  /**
   * Get all the publications from a publisher for a subject_key.
   * Throw an exception on any error.
   * Returns data payload array.
   * @returns array
   */
  public function getPublications($publisher = '', $subject_key = '') {
    if (!$publisher || !$subject_key) {
      throw new Exception("Must provide publisher (ex: SBAC) and subject key (ex: ELA)");
    }
    $full_url = $this->URL . "publication?publisher=$publisher&subject=$subject_key";
    curl_setopt($this->curl, CURLOPT_URL, $full_url);
    $output = curl_exec($this->curl);
    $data = json_decode($output, TRUE);
    $this->_verify($data);
    return $data["payload"];
  }

  /**
   * Retrieves the tags,keys and descriptions for standard_key given.
   * Optionally, filters out all entries except tree_level. 0=no filtering
   */
  public function getStandards($standard_key = '', $tree_level = 0) {
    if (!$standard_key) {
      throw new Exception("Must pass standard_key to retrieve standards.");
    }

    $retarr = array();
    $full_url = $this->URL . "publication/$standard_key/standard";
    curl_setopt($this->curl, CURLOPT_URL, $full_url);
    $output = curl_exec($this->curl);
    $data = json_decode($output, TRUE);
    $this->_verify($data);

    // if nothing to filter return it all
    if (!$tree_level) {
      return $data["payload"];
    }

    // still here? filter it
    for ($a = 0; $a < count($data["payload"]); $a++) {
      $d = $data["payload"][$a];
      // TODO: filter out if name=='NA' ?
      if (intval($tree_level) == intval($d["treeLevel"])) {
        $retarr[] = $d;
      }
    }
    return $retarr; // return filtered subset of data
  }

  /**
   * Validate Function
   *
   * @return bool Returns TRUE if all checks are valid, FALSE otherwise.
   */
  public function validate($standard_key) {
    if (empty($standard_key)) {
      throw new Exception("Must pass standard_key to retrieve standards.");
    }

    $results = $this->test_data($standard_key);
    foreach ($results as $result) {
      if ($result['is_clean'] == FALSE) {
        return FALSE;
      }
    }

    return TRUE;
  }

  /**
   * Main test function
   */
  public function test_data($standard_key) {
    if (empty($standard_key)) {
      throw new Exception("Must pass standard_key to retrieve standards.");
    }

    $standards = $this->getStandards($standard_key);

    //test functions
    $results['empty_parents'] = $this->_sbac_air_check_empty_parents($standards);
    $results['empty_grades'] = $this->_sbac_air_check_empty_grades($standards);
    $results['parent_exists'] = $this->_sbac_air_check_parents_exist($standards);

    return $results;
  }

  /**
   * Private Function
   * Checks for empty parents that are not in tree level 1.
   */
  private function _sbac_air_check_empty_parents($items) {
    $is_clean = TRUE;
    $bad_items = array();

    foreach ($items as $item) {
      if (empty($item['fkParent']) && $item['treeLevel'] != 1) {
        $is_clean = FALSE;
        $bad_items[] = $item;
      }
    }

    if (!empty($bad_items)) {
      $bad_items['json'] = drupal_json_encode($bad_items);
    }

    return array('is_clean' => $is_clean, 'bad_items' => $bad_items);
  }

  /**
   * Private Function
   * Checks for null grades.
   */
  private function _sbac_air_check_empty_grades($items) {
    $is_clean = TRUE;
    $bad_items = array();

    foreach ($items as $item) {
      if (empty($item['fkGradeLevel'])) {
        $is_clean = FALSE;
        $bad_items[] = $item;
      }
    }

    if (!empty($bad_items)) {
      $bad_items['json'] = drupal_json_encode($bad_items);
    }

    return array('is_clean' => $is_clean, 'bad_items' => $bad_items);
  }

  /**
   * Private Function
   * Checks for null grades.
   */
  private function _sbac_air_check_parents_exist($items) {
    $is_clean = TRUE;
    $bad_items = array();
    $item_keys = $this->_sbac_air_get_keys($items);

    foreach ($items as $item) {
      if (empty($item['fkGradeLevel']) || $item['treeLevel'] < 2) {
        continue; //gradelevel empty is handled in _sbac_air_check_empty_grades
      }

      $parent_key = implode('|', array($item['fkGradeLevel'], $item['fkParent']));
      if (!in_array($parent_key, $item_keys)) {
        $is_clean = FALSE;
        $bad_items[] = $item;
      }
    }

    if (!empty($bad_items)) {
      $bad_items['json'] = drupal_json_encode($bad_items);
    }

    return array('is_clean' => $is_clean, 'bad_items' => $bad_items);
  }

  /**
   * Private Function - Helper
   * Re-key the array with the term['key']
   */
  function _sbac_air_get_keys($items) {
    $keyed_array = array();

    if (is_array($items)) {
      foreach ($items as $item) {
        //@TODO KS - should check if isset items. check if null?
        $key = implode('|', array($item['fkGradeLevel'], $item['key']));
        $keyed_array[] = $key;
      }
    }

    return $keyed_array;
  }


} // end class