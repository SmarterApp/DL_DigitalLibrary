<?php

/**
 * Page Callback
 */
function sbac_admin_clean_flood() { 
  if (!$_GET['ip']) {
	$server = strtolower(array_shift(explode("/",$_SERVER['SERVER_PROTOCOL'])))."://".$_SERVER['SERVER_NAME'];
	$message = 'Please include an ip address in this form: ' . $server . '/admin/clean_flood?ip=10.1.1.1';
  } else {
	if ($_GET['ip']==strtolower('all')) {
		$where='';
		$message="All IP addresses have been cleaned from the flood table";
	} else {
		$where = " where identifier like '%" . $_GET['ip'] . "%'";
		$message ='IP address ' . $_GET['ip'] . ' has been cleaned from the flood table';
	}
	$query="delete from flood " . $where;
	$result=db_query($query);
  }
  return t($message);
}
