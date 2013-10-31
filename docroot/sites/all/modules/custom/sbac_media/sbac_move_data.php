<?php
/* author: bart@appnovation.com
* date: 2013.10
*
* purpose: post-launch data move between old disk structure and new one.  See pdf in this repo for details.
*/


$MAX_PROCESS = 0; // 0=all, +int=exit after that many rows
$live_delay = 5;  // in seconds
$DEBUG = 1;

// This is stuff you need to change for EACH migration!
$LOGFILE = "/mnt//tmp/sbac/sbac_migration.". date("Ymd-His", time()) .".log";
$dbhost = 'ded-6151.prod.hosting.acquia.com';
$dbuser = 's6063';
$dbpass = 'TuW9m7VqTHNnHpG';
$dbname = 'sbac';
$fs_private_basedir = '/mnt/files/sbac/files-private/'; // with ending slash
$fs_public_basedir = '/mnt/files/sbac/sites/default/files/'; // with ending slash

print "LOGGING to: $LOGFILE\n";

// test if directories exists and if they are writable - abort if not
check_dir($fs_public_basedir);
check_dir($fs_private_basedir);


function syntax() {
	global $argv;
	print "\nsyntax: $argv[0] [--live]\n";
}


function show_vars() {
	global $DEBUG, $dbhost, $dbuser, $dbpass, $dbname, $fs_private_basedir, $fs_public_basedir, $MAX_PROCESS, $LOGFILE;
	$logmsg = "******* VARS: *****\n* DEBUG=$DEBUG\n";
	$logmsg .= "* dbhost=$dbhost\n";
	$logmsg .= "* dbuser=$dbuser\n";
	$logmsg .= "* dbpass=$dbpass\n";
	$logmsg .= "* dbname=$dbname\n";
	$logmsg .= "* private basedir = $fs_private_basedir\n";
	$logmsg .= "* public basedir  = $fs_public_basedir\n";
	$logmsg .= "* MAX_PROCESS = $MAX_PROCESS  (0=all, N=stop after N rows)\n";
	$logmsg .= "*******\n";

	print $logmsg;
    error_log($logmsg, 3, $LOGFILE);
}


function check_dir($path) {
	if (!file_exists($path)) {
	    print "Error. [$path] does not exist.\n";
	    exit(1);
    }
    if (!is_writeable($path)) {
    	print "Error. [$path] is not writeable, check permissions\n";
    	exit(1);
    }
}


function get_dbconnection() {
  global $dbhost, $dbuser, $dbpass, $dbname;

  $conn = mysql_connect($dbhost, $dbuser, $dbpass);
  if (!$conn) {
    throw new Exception('Could not connect to db: '. mysql_error());
  }
  if (!mysql_select_db($dbname, $conn)) {
  	throw new Exception('Could not select db: '. mysql_error());
  }
  return $conn;
}


// This implementation assumes the result set is not too large.
// Current estimation for production run is about 500 rows.
// Should this be needed for tens of thousands of resources or more, this will need to be rewritten to be batched.
function load_file_info($dbconn) {

	$retarr = array();
	$sql = "SELECT field_data_field_file.entity_id AS eid, ".
		"field_data_field_file.field_file_fid AS fid, ".
		"field_data_field_file.delta AS delta, ".
		"file_managed.uri AS uri, ".
		"file_managed.filesize AS size, ".
		"file_managed.type AS type ".
		"FROM field_data_field_file join file_managed on field_data_field_file.field_file_fid=file_managed.fid";
	
    $result = mysql_query($sql, $dbconn);
    if (!$result) {
      throw new Exception('MySQL Error: '. mysql_error());
    }

    while ($row = mysql_fetch_assoc($result)) {
      //print $row['eid'].",". $row['uri'];
      array_push($retarr, $row);
    }
    mysql_free_result($result);

	return $retarr;
}


/*
* Convert 'public://' or 'private://' uri into a full local file name.
* If we can't match public or private return an empty string to indicate an error.
*/
function construct_local_filename($uri = "") {
	global $fs_private_basedir, $fs_public_basedir;

	$local_filename = $uri;

	$pattern = '/^public\:\//'; # match single slash only
	if (preg_match($pattern, $uri)) {
		$local_filename = preg_replace($pattern, $fs_public_basedir, $uri);
		return $local_filename;
	}

    $pattern = '/^private\:\//'; # match single slash only
	if (preg_match($pattern, $uri)) {
		$local_filename = preg_replace($pattern, $fs_private_basedir, $uri);
		return $local_filename;
	}

	return ""; // fallback value
}


function is_hosted_remotely($uri) {
	if (!$uri) {
		throw new Exception("URI not passed, cannot determine location.");
	}

	$remote_list = array('youtube','schooltube','teachertube','slideshare','vimeo');

	for ($i=0; $i<count($remote_list); $i++) {
		$findme = $remote_list[$i];
    	$pattern = '/^'. $findme .'/';
		if (preg_match($pattern, $uri)) {
    		return true;
		}
	}

	return false;
}


/* Converts uri (ex: youtube://XYZ to a watchable URL)
 * Currently production only has a few Youtube and Teachertube vids.
 */
function construct_url_for_video($uri) {
	if (preg_match('/^youtube/', $uri)) {
		return "http://www.youtube.com/watch?v=".basename($uri);
	}

	if (preg_match('/^teachertube/', $uri)) {
		return "http://www.teachertube.com/viewVideo.php?video_id=".basename($uri);
	}
	return "";
}


function save_new_record($dbh, $item) {
	global $DEBUG, $LOGFILE;

	$sql = "INSERT INTO eck_media (type, fid, filename, file_hash, file_size, nid, weight, embed_url) VALUES (".
		"'". mysql_real_escape_string($item['type']) ."',".
		"'". mysql_real_escape_string($item['fid']) ."',".
		"'". mysql_real_escape_string(basename($item['uri'])) ."',".
		"'". mysql_real_escape_string($item['hash']) ."',".
		"'". mysql_real_escape_string($item['size']) ."',".
		"'". mysql_real_escape_string($item['eid']) ."',".
		"'". mysql_real_escape_string($item['weight']) ."',".
		"'". $item['embed_url'] ."'".
		")";
	if ($DEBUG) {
    	print "WOULD HAVE executed SQL=[$sql]\n";
	} else {
	    print "EXECUTING: $sql\n";
		if (!mysql_query($sql, $dbh)) {
			throw new Exception("Mysql error: ". mysql_error());
		}
	}
}


/*
* fl = list of entries to process
* dbh = database handle for saving new records
*/
function process_file_list($fl, $dbh) {
	global $fs_private_basedir, $fs_public_basedir, $DEBUG, $MAX_PROCESS, $LOGFILE;

	print "******* VARS: *****\n* DEBUG=$DEBUG\n";
	print "Starting processing of ". count($fl) ." items\n";

	$count_remote = 0;
	$count_local = 0;

	$count_found_local = 0;
	$count_error_local = 0;
    $count_error_unknown = 0;

	
    for ($i=0; $i<count($fl); $i++) {
    	if ($MAX_PROCESS && $MAX_PROCESS < ($i + 1)) {
    		$logmsg = "-------\n";
    		$logmsg .= "***** BAILING, seen $MAX_PROCESS rows - to change open script and look for constant MAX_PROCESS\n";
    		print $logmsg;
    		error_log($logmsg, 3, $LOGFILE);
    		break;
    	}
    	$logmsg = "----------------\n";
    	print $logmsg;
    	error_log($logmsg, 3, $LOGFILE);
    	//var_dump($fl[$i]);
    	$item = $fl[$i];
    	$md5sum = "";
    	
    	// compute new filesystem path and virtual path for Drupal db
    	$hashdir = floor($item['eid']/32000) ."/". floor($item['eid']);
    	$fs_newdir = $fs_private_basedir ."/resource/". $hashdir;
    	$virtual_newdir = "private://resource/". $hashdir; // for/ database
    	$logmsg = "DEBUG[$DEBUG] HASHDIR: [$hashdir] virtual_newdir[$virtual_newdir] fs_newdir[$fs_newdir]\n";
    	print $logmsg;
    	error_log($logmsg, 3, $LOGFILE);

		// create directory
	    if (!file_exists($fs_newdir)) {
	    	if (!$DEBUG) {
	    		// remember to later adjust permissions and ownership on production system manually
	    		$ok = mkdir($fs_newdir, 0777, true);
	    		if (!$ok) {
	    		  	throw new Exception("Could not create directory [$fs_newdir]");
	    		}
	    	} else {
	    		$logmsg = "WOULD HAVE CREATED DIR [$fs_newdir]\n";
	    		print $logmsg;
    			error_log($logmsg, 3, $LOGFILE);
	    	}
	    } else {
	    	$logmsg = "Directory [$fs_newdir] ALREADY EXISTS\n";
	    	print $logmsg;
    		error_log($logmsg, 3, $LOGFILE);
	    }
	    // end create directory
    	

    	if (is_hosted_remotely($item['uri'])) {
    		$count_remote += 1;
    		$logmsg = "REMOTE: ". $item['uri'] ."\n";
    		print $logmsg;
    		error_log($logmsg, 3, $LOGFILE);

    		// update db
    		$sitem = $item;
    		$sitem['hash'] = "";
    		$sitem['uri'] = $virtual_newdir ."/". basename($item['uri']);
    		$sitem['weight'] = $item['delta'];
    		$sitem['fid'] = 0; // Brandon says for remote files this _must_ be 0
    		$sitem['embed_url'] = construct_url_for_video($item['uri']);

    		if (!$DEBUG) {
    			save_new_record($dbh, $sitem);
    			$logmsg = "SAVED REMOTE ENTRY OK: ". json_encode($sitem) ."\n";
    		} else {
    			$logmsg = "WOULD SAVED REMOTE ENTRY: ". json_encode($sitem) ."\n";
    		}

    		print $logmsg;
    		error_log($logmsg, 3, $LOGFILE);

    	} else { // local files get processed here
    		$count_local += 1;
    		$logmsg = "\nLOCAL: ". $item['uri'] ."\n";
    		print $logmsg;
    		error_log($logmsg, 3, $LOGFILE);
    		
    		$full_file_name = construct_local_filename($item['uri']);
    		if (!$full_file_name) {
    			$count_error_unknown += 1;
    			throw new Exception("Could not create local filename for eid[".$item['eid']."] uri[".$item['uri']."]");
    		}
    		if (!file_exists($full_file_name)) {
    			$logmsg = "ERROR: could not find file on disk, SKIPPING.  eid[".$item['eid']."] uri[".$item['uri']."] fs_filename[$full_file_name]\n";
    			print $logmsg;
    			error_log($logmsg, 3, $LOGFILE);
    			$count_error_local += 1;
    			continue;
    		}
    		
    		$md5sum = md5_file($full_file_name);
    		$logmsg = "FFN: $full_file_name ; md5[$md5sum]\n";
    		print $logmsg;
    		error_log($logmsg, 3, $LOGFILE);
    		$count_found_local += 1;


	    	// copy the file. This used to be a move op but we decided (for safety reasons) to just make a copy.
	    	$newname = $fs_newdir ."/". basename($item['uri']);
	    	if (!$DEBUG) {
	    		$ok = copy($full_file_name, $newname);
	    		if (!$ok) {
	    		  throw new Exception("Could not copy file from [$full_file_name] to [$newname]");
	    		}
	    		$logmsg = "COPIED [$full_file_name] TO [$newname]\n";
	    		print $logmsg;
    			error_log($logmsg, 3, $LOGFILE);
	    	} else {
	    		$logmsg = "WOULD HAVE COPIED [$full_file_name] TO [$newname]\n";
	    		print $logmsg;
    			error_log($logmsg, 3, $LOGFILE);
	    	}
	    	// end file copy


    		// update db
    		$sitem = $item;
        $sitem['type'] = 'media';
    		$sitem['hash'] = $md5sum;
    		$sitem['uri'] = $virtual_newdir ."/". basename($item['uri']);
    		$sitem['weight'] = $item['delta'];
    		$sitem['embed_url'] = "";

    		if (!$DEBUG) {
    			save_new_record($dbh, $sitem);
    			// CMIS/Alfresco insert? - save output from this script to file.
    			// Write a small cmis-insert script later that will parse the json output and act as needed.
    			// UPDATE re cmis: no need for it, there are no published resources on production. No harm in loggin this though.
    			$sitem['full_file_name'] = $full_file_name;
    			$logmsg = "SAVED LOCAL OK: ". json_encode($sitem) ."\n";
    		} else {
    			$sitem['full_file_name'] = $full_file_name;
    			$logmsg = "WOULD HAVE SAVED LOCAL: ". json_encode($sitem) ."\n";
    		}
    		print $logmsg;
    		error_log($logmsg, 3, $LOGFILE);

    		// Brandon says no cleanup of old rows needed.
    	}
    }

    $logmsg = "-----------------\n";
    $logmsg .= "---- SUMMARY ----\n";
    $logmsg .= "Db entries found: ". count($fl) ."\n";
    $logmsg .= "MAX_PROCESS = $MAX_PROCESS  (0=all, N=stop after N rows)\n";
    $logmsg .= "Processed: ". ($MAX_PROCESS >0 ? $MAX_PROCESS : count($fl)) ."\n";
    $logmsg .= "FILES: Remote[$count_remote] Local[$count_local]\n";
    $logmsg .= "Local files found: $count_found_local\n";
    $logmsg .= "Local files not found: $count_error_local\n";
    $logmsg .= "Errors (unmatched uri type): $count_error_unknown\n";
    print $logmsg;
    error_log($logmsg, 3, $LOGFILE);

    print "LOG: $LOGFILE\n";
}

// ****************************
// ******** main section ******

// make sure we're running from command line, if not abort
if (php_sapi_name() != 'cli') {
  print "ERROR: this script should only be used from command line.\n"; 
  exit(1);
}

// quick and crude
for ($i=0; $i<count($argv); $i++) {
  //print "Parsed argument: ". $argv[$i] ."\n";
  if ($argv[$i] == '--live') { $DEBUG = 0; }
}

// for live runs delay a few seconds to give chance to abort in case of accidental run
if (!$DEBUG) {
  print "LIVE RUN, will move data. Last chance to hit Ctrl-C . Continuing in $live_delay seconds\n";
  sleep($live_delay);
}


try {
  show_vars();
  $db = get_dbconnection();
  $file_list = load_file_info($db);
  process_file_list($file_list, $db);
  mysql_close($db);
} catch (Exception $e) { 
  print $e ."\n"; 
  var_dump(debug_backtrace());
  error_log($e, 3, $LOGFILE);
  exit(1); 
}
syntax();
exit(0);
?>