<?php

function sbac_user_login_report_get_data($header) {
    $query = db_select('users', 'u');
    $query->condition('u.uid', 0, '<>');
    user_build_filter_query($query);

    $count_query = clone $query;
    $count_query->addExpression('COUNT(u.uid)');

    $query = $query->extend('PagerDefault')->extend('TableSort');
    $query
        ->fields('u', array('uid', 'name', 'status', 'created', 'access', 'login', 'data'))
        #->limit(500)
        ->orderByHeader($header)
        ->setCountQuery($count_query);
    $result = $query->execute();

    return $result;
}


function sbac_user_login_report($arg1='', $arg2='') {
    $datatable = array();

    $header = array(
        'username' => array('data' => t('Username'), 'field' => 'u.name'),
        'created_on' => array('data' => t('Created On'), 'field' => 'u.created', 'sort' => 'desc'),
        'first_login' => array('data' => t('First Login')),
        'last_login' => array('data' => t('Last Login'), 'field' => 'u.login'),
        'login_count' => array('data' => t('Login Count')),
        'status' => array('data' => t('Status'), 'field' => 'u.status'),
    );

    $result = sbac_user_login_report_get_data($header);

    $rowdata = array();
    $status = array(t('blocked'), t('active'));
    foreach ($result as $account) { 
        $first_login = 0;
        $login_count = 0;
        $account->data = unserialize($account->data);
        if ($account->data && isset($account->data['first_login'])) {
            $first_login = $account->data['first_login'];
        }
        if ($account->data && isset($account->data['login_count'])) {
            $login_count = $account->data['login_count'];
        }
        
        $rowdata[] = array(
            $account->name, 
            date("Y-m-d H:i", $account->created),
            $first_login ? date("Y-m-d H:i", $first_login) : t('never'),
            $account->login ? date("Y-m-d H:i", $account->login) : t('never'),
            $login_count,
            $status[$account->status]
        );
        
        /* alternative way with clickable username leading to user view screen
        $rowdata[$account->uid] = array(
            'username' => theme('username', array('account' => $account)),
            'created_on' => date("Y-m-d H:i", $account->created),
            'first_login' => $first_login ? date("Y-m-d H:i", $first_login) : t('never'), 
            'last_login' =>  $account->login ? date("Y-m-d H:i", $account->login) : t('never'),
            'login_count' => $login_count,
            'status' =>  $status[$account->status]
        );
        */
    } /* end for */


    $datatable = array(
        '#theme' => 'table',
        '#type' => 'tableselect',
        '#header' => $header,
        '#rows' => $rowdata,
        '#empty' => t('No people available.'),
    );

    return $datatable;
}

?>
