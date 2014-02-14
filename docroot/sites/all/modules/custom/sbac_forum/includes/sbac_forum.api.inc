<?php

// Used for implementing helper functions that will be used throughout module


function sbac_forum__api__get_active_subnav() {
  $active_subnav = '';

  if (isset($_SESSION[SBAC_FORUM_SUBNAV_ACTIVE])) {
    if (!empty($_SESSION[SBAC_FORUM_SUBNAV_ACTIVE])) {
      $active_subnav = $_SESSION[SBAC_FORUM_SUBNAV_ACTIVE];
    }
  }

  return $active_subnav;
}

function sbac_forum__api__set_active_subnav($value = NULL) {
  if (!empty($value)) {
    $_SESSION[SBAC_FORUM_SUBNAV_ACTIVE] = $value;
  } else {
    $_SESSION[SBAC_FORUM_SUBNAV_ACTIVE] = '';
  }
}
