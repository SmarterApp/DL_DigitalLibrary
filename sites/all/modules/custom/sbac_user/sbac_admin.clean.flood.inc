<?php

function sbac_admin_clean_flood() { 
  if (!$_GET['ip']) {
	$server = strtolower(array_shift(explode("/",$_SERVER['SERVER_PROTOCOL'])))."://".$_SERVER['SERVER_NAME'];
	$message = 'Please include an IP address in one of these forms:<br /><br /><ul><li>' . $server . '/admin/clean_flood?ip=10.1.1.1 (to clean a single ip address)</li><li>' . $server . '/admin/clean_flood?ip=10.1.1 (to clean a range of ip addresses)</li><li>' . $server . '/admin/clean_flood?ip=all (to clean all ip addresses)</li></ul>';
  } else {
	if ($_GET['ip']==strtolower('all')) {
		$where='';
		$message="All IP addresses have been cleaned from the flood table";
	} else {
		$where = " where identifier like :ip";
		$message ='IP address ' . check_plain($_GET['ip']) . ' has been cleaned from the flood table';
	}
	$query="delete from flood " . $where;
	$result=db_query($query, array(':ip' => '%' . $_GET['ip'] . '%'));
  }
  return t($message);
}
