<?php
namespace taskit;

module_load_include('inc', 'taskit', 'includes/interface.iTask');

/**
 * Base Task class;
 */
class Task extends \taskit\Base implements iTask {
  // bitwise flags for visibility
  const VISIBILITY_DEFAULT  = 0;
  const VISIBILITY_USER     = 1;
  const VISIBILITY_ROLE     = 2;

  // bitwise flags for state
  const STATE_DEFAULT       = 0;
  const STATE_COMPLETED     = 1;

  // flags for search results
  const SEARCH_NOT_FOUND    = 0;
  const SEARCH_FOUND        = 1;
  const SEARCH_MULTIPLE     = 2;

  // task id
  protected $_task_id = 0;
  // the machine name of this task type
  protected $_type = '';
  // timestamp for when this task was created
  protected $_created = 0;
  // timestamp for when this task was viewed
  protected $_viewed = 0;
  // format for date output, suitable for date()
  protected $_date_format = 'F j Y, H:ia';
  // bitwise flag for the task state
  protected $_state = self::STATE_DEFAULT;
  // bitwise flag for the kind of visibility this task should have
  // (ie. is it shown to user(s), role(s), or both?)
  protected $_visibility = self::VISIBILITY_DEFAULT;
  // entities this task applies to - each task type is resposible
  // for handling its own entities
  protected $_entities = array();
  // user(s) that triggered creation/update of this task
  protected $_triggering_users = array();
  // user(s) that this task applies to (if it's that specific)
  protected $_owning_users = array();
  // user(s) that have viewed this task (if we're using user-specific task visibility)
  protected $_viewed_users = array();
  // html classes set on row wrapper
  protected $_classes = array();

  /**
   * Constructor
   * @param [type] $type [description]
   */
  public function __construct($type, $task_id = 0) {
    $this->_type = $type;
    $this->_task_id = $task_id;

    date_default_timezone_set(variable_get('date_default_timezone', 'America/Vancouver'));

    $this->addClass('taskit-new');

    if ($task_id) {
      $this->load();
    }
  }

  /**
   * Returns the task id.
   * @return [type] [description]
   */
  public function getTaskId() {
    return $this->_task_id;
  }

  /**
   * Sets the task id.
   * @return [type] [description]
   */
  public function setTaskId($id) {
    $this->_task_id = $id;

    return $this->getTaskId();;
  }

  /**
   * Return the task's created timestamp.
   * @return [type] [description]
   */
  public function setDateFormat($format) {
    $this->_date_format = $format;
  }

  /**
   * Adds referenced entity.
   * @param [type] $entity_type [description]
   * @param [type] $entity_id   [description]
   */
  public function addEntity($entity_type, $entity_id) {
    $this->_entities[$entity_type][$entity_id] = $entity_id;
  }

  /**
   * Removes referenced entity.
   * @param  [type] $entity_type [description]
   * @param  [type] $entity_id   [description]
   * @return [type]              [description]
   */
  public function removeEntity($entity_type, $entity_id = NULL) {
    if (!is_null($entity_id)) {
      unset($this->_entities[$entity_type][$entity_id]);
    }
    else {
      unset($this->_entities[$entity_types]);
    }
  }

  /**
   * Returns referenced entities.
   * @return [type] [description]
   */
  public function getEntities() {
    return $this->_entities;
  }

  /**
   * Returns the type.
   * @return [type] [description]
   */
  public function getType() {
    return $this->_type;
  }

  /**
   * Sets state flag.
   * @param [type] $state [description]
   */
  public function addState($state) {
    if (!($this->_state & $state)) {
      $this->_state += $state;
    }
  }

  /**
   * Unsets state flag.
   * @param  [type] $state [description]
   * @return [type]        [description]
   */
  public function removeState($state) {
    if ($this->_state & $state) {
      $this->_state -= $state;
    }
  }

  /**
   * Returns the state.
   * @return [type] [description]
   */
  public function getState() {
    return $this->_state;
  }

  /**
   * Returns the created date.
   * @return [type] [description]
   */
  public function getCreated() {
    return $this->_created;
  }

  /**
   * Sets the created date.
   * @param [type] $date [description]
   */
  public function setCreated($date) {
    $this->_created = $date;

    return $this->getCreated();
  } 

  /**
   * Sets the viewed date.
   * @param [type] $date [description]
   */
  public function setViewed($date = NULL) {
    $this->_viewed = !is_null($date) ? $date : time();

    return $this->getViewed();
  }

  /**
   * Returns the viewed timestamp.
   * @return [type] [description]
   */
  public function getViewed() {
    return $this->_viewed;
  }

   /**
   * Adds viewed user.
   * @param [type] $uid [description]
   */
  public function addViewedUser($uid) {
    $this->_viewed_users[$uid] = $uid;
  }

  /**
   * Checks whether the task is "viewed" in current context.
   * @return boolean [description]
   */
  public function isViewed() {
    switch (variable_get('taskit_visibility', 'global')) {
      case 'global':
        return (bool) $this->getViewed();
        break;

      case 'user':
        $uid = $this->currentUser();
        return isset($this->_viewed_users[$uid]);
        break;

      default:
        return FALSE;
        break;
    }
  }

  /**
   * Adds task class.
   * @param [type] $class [description]
   */
  public function addClass($class) {
    $this->_classes[] = $class;

    return $this->getClasses();
  }

  /**
   * Removes task class.
   * @param  [type] $class [description]
   * @return [type]        [description]
   */
  public function removeClass($class) {
    if (($key = array_search($class, $this->_classes)) !== FALSE) {
      unset($this->_classes[$key]);
    }

    return $this->getClasses();
  }

  /**
   * Sets the task classes.
   * @param [type] $classes [description]
   */
  public function setClasses($classes) {
    $this->_classes = $classes;

    return $this->getClasses();
  }

  /**
   * Returns HTML classes for taskit row wrapper
   * @return [type] [description]
   */
  public function getClasses() {
    return implode(' ', $this->_classes);
  }

  /**
   * Marks task as removed for specified user
   * @param  [type] $uid [description]
   * @return [type]      [description]
   */
  public function remove($uid = NULL) {
    if (is_null($uid)) {
      global $user;

      $uid = $user->uid;
    }

    // we shouldn't ever run into duplicates, but just in case...
      db_delete('taskit_removed')
        ->condition('task_id', $this->getTaskId())
        ->condition('user_id', $uid)
        ->execute();

    // insert record to mark this task as removed
      db_insert('taskit_removed')
        ->fields(array('task_id' => $this->getTaskId(), 'user_id' => $uid))
        ->execute();;
  }

  /**
   * Deletes the current task.
   * @return [type] [description]
   */
  public function delete() {
    $query = "  DELETE      t.*,
                            te.*,
                            tr.*,
                            tuo.*,
                            tut.*,
                            tv.*
                FROM        taskit t
                LEFT JOIN   taskit_entity te
                  ON        t.task_id = te.task_id
                LEFT JOIN   taskit_removed tr
                  ON        t.task_id = tr.task_id
                LEFT JOIN   taskit_user_owner tuo
                  ON        t.task_id = tuo.task_id
                LEFT JOIN   taskit_user_trigger tut
                  ON        t.task_id = tut.task_id
                LEFT JOIN   taskit_viewed tv
                  ON        t.task_id = tv.task_id
                WHERE       t.task_id = :tid
             ";

    db_query($query, array(':tid' => $this->getTaskId()));
  }

  /**
   * Sets visibility flag.
   * @param [type] $visibility [description]
   */
  public function addVisibility($visibility) {
    if (!($this->_visibility & $visibility)) {
      $this->_visibility += $visibility;
    }
  }

  /**
   * Unsets visibility flag.
   * @param  [type] $visibility [description]
   * @return [type]             [description]
   */
  public function removeVisibility($visibility) {
    if ($this->_visibility & $visibility) {
      $this->_visibility -= $visibility;
    }
  }

  /**
   * Returns current visibility.
   */
  public function getVisibility() {
    return $this->_visibility;
  }

  /**
   * Adds triggering user.
   * @param [type] $uid [description]
   */
  public function addTriggeringUser($uid) {
    $this->_triggering_users[$uid] = $uid;
  }

  /**
   * Removes triggering user.
   * @param  [type] $uid [description]
   * @return [type]      [description]
   */
  public function removeTriggeringUser($uid) {
    unset($this->_triggering_users[$uid]);
  }

  /**
   * Returns the users which triggered this task.
   * @return [type] [description]
   */
  public function getTriggeringUsers() {
    return $this->_triggering_users;
  }

  /**
   * Adds owning user.
   * @param [type] $uid [description]
   */
  public function addOwningUser($uid) {
    $this->_owning_users[$uid] = $uid;
  }

  /**
   * Removes owning user.
   * @param  [type] $uid [description]
   * @return [type]      [description]
   */
  public function removeOwningUser($uid) {
    unset($this->_owning_users[$uid]);
  }

  /**
   * Loads the task data and builds the object.
   * @return [type] [description]
   */
  protected function load() {
    $query = "  SELECT      t.task_id,
                            t.created,
                            t.viewed,
                            t.state,
                            t.visibility,
                            GROUP_CONCAT(DISTINCT CONCAT(te.entity_type, '/', te.entity_id)) AS entities,
                            GROUP_CONCAT(DISTINCT tut.user_id) AS triggering_users,
                            GROUP_CONCAT(DISTINCT tuo.user_id) AS owning_users,
                            GROUP_CONCAT(DISTINCT tv.user_id) AS viewed_users
                FROM        taskit t
                LEFT JOIN   taskit_entity te
                  ON        te.task_id = t.task_id
                LEFT JOIN   taskit_user_trigger tut
                  ON        tut.task_id = t.task_id
                LEFT JOIN   taskit_user_owner tuo
                  ON        tuo.task_id = t.task_id  
                LEFT JOIN   taskit_viewed tv
                  ON        tv.task_id = t.task_id
                WHERE       t.task_id = :tid
                GROUP BY    t.task_id
             ";

    $args = array(
      ':tid' => $this->getTaskId(),
    );

    $data = db_query($query, $args)->fetchObject();

    // set the referenced entities
    if ($data->entities) {
      foreach (explode(',', $data->entities) as $item) {
        $item = explode('/', $item);
        $this->addEntity($item[0], $item[1]);
      }
    }

    // set the triggering users
    if ($data->triggering_users) {
      foreach (explode(',', $data->triggering_users) as $uid) {
        $this->addTriggeringUser($uid);
      }
    }

    // set the owning users
    if ($data->owning_users) {
      foreach (explode(',', $data->owning_users) as $uid) {
        $this->addOwningUser($uid);
      }
    }

    // set the viewed users
    if ($data->viewed_users) {
      foreach (explode(',', $data->viewed_users) as $uid) {
        $this->addViewedUser($uid);
      }
    }

    // set created timestamp
    $this->setCreated($data->created);

    // set viewed timestamp
    $this->setViewed($data->viewed);

    if ($this->isViewed()) {
      $this->removeClass('taskit-new');
      $this->addClass('taskit-viewed');
    }

    // set the state
    $this->addState($data->state);

    // set the visibility
    $this->addVisibility($data->visibility);
  }

  /**
   * Searches for an existing task matching the currently available data,
   * and if found, sets the task id. Useful for updating existing task
   * with new triggering users, or other changes. 
   *
   * The search looks for tasks which match the currently set entities and
   * owning users. If a single matching task is found, the object's task id
   * is set to the found task's task id, so that subsequent calls to save()
   * will update the existing task, rather than create a new one.
   *
   * IMPORTANT: If an existing task is found, that task is loaded into the
   * current object, so that non-searchable data (like triggering users) is
   * loaded and not lost on the subsequent save(). Because of this, it's 
   * important to add triggering users and other such data *after* the
   * call to searchExisting().
   *
   * The return value can be used to determine how the search went by
   * comparing the returned value to the search result flags;
   * example: if ($task->searchExisting() === \taskit\Task::SEARCH_FOUND) { }
   * 
   * @return [type] [description]
   */
  function searchExisting() {
    $args = array();
    $conditions = array();

    // build conditions for type, state & visibility
      $conditions[] = 't.type = :type';
      $conditions[] = 't.state = :state';
      $conditions[] = 't.visibility = :visibility';

      $args[':type'] = $this->getType();
      $args[':state'] = $this->getState();
      $args[':visibility'] = $this->getVisibility();

    // build conditions for entities
      $entity_count = 0;
      foreach ($this->_entities as $entity_type => $entity_data) {
        foreach ($entity_data as $entity_id) {
          $table_alias = 'te_' . $entity_count;

          $entity_type_alias = ':entity_type_' . $entity_count;
          $entity_id_alias = ':entity_id_' . $entity_count;

          $conditions[] = $table_alias . '.entity_type = ' . $entity_type_alias;
          $conditions[] = $table_alias . '.entity_id = ' . $entity_id_alias;

          $args[$entity_type_alias] = $entity_type;
          $args[$entity_id_alias] = $entity_id;

          $entity_count++;
        }
      }

    // build joins for entities
      $entity_joins = array();
      for ($i = 0; $i < $entity_count; $i ++) {
        $table_alias = 'te_' . $i;

        $entity_joins[] = 'LEFT JOIN taskit_entity ' . $table_alias . ' ON ' . $table_alias . '.task_id = t.task_id';
      }

    // build conditions for owning users 
      $users_count = 0;
      foreach ($this->_owning_users as $uid) {
        $table_alias = 'tuo_' . $users_count;

        $user_id_alias = ':user_id_' . $users_count;

        $conditions[] = $table_alias . '.user_id = ' . $user_id_alias;

        $args[$user_id_alias] = $uid;

        $users_count++;
      }

    // build joins for owning users
      $owning_joins = array();
      for ($j = 0; $j < $users_count; $j ++) {
        $table_alias = 'tuo_' . $j;

        $owning_joins[] = 'LEFT JOIN taskit_user_owner ' . $table_alias . ' ON ' . $table_alias . '.task_id = t.task_id';
      }

    $query = "  SELECT      t.task_id
                FROM        taskit t

                " . implode(' ', $entity_joins) . "
                " . implode(' ', $owning_joins) . "

                LEFT JOIN   taskit_removed tr
                  ON        t.task_id = tr.task_id
                WHERE       " . implode(' AND ', $conditions) . "
                AND         tr.user_id IS NULL
                GROUP BY    t.task_id
             ";

    $result = db_query($query, $args);
    $count = $result->rowCount();

    if ($count == 1) {
      $this->setTaskId($result->fetchObject()->task_id);

      $this->load();

      return self::SEARCH_FOUND;
    }
    elseif ($count > 1) {
      return self::SEARCH_MULTIPLE;
    }

    return self::SEARCH_NOT_FOUND;
  }

  /**
   * Creates or updates the task, returning the task id.
   * @param  boolean $multi_update [description]
   * @param  [type]  $uid          [description]
   * @return [type]                [description]
   */
  public function save($multi_update = TRUE, $uid = NULL) {
    // insert new task
      if ($this->getTaskId() == 0) {
        $fields = array(
          'type' => $this->getType(),
          'created' => REQUEST_TIME,
          'state' => $this->getState(),
          'visibility' => $this->getVisibility(),
        );

        $this->setTaskId(db_insert('taskit')->fields($fields)->execute());
      }
    // update misc fields  
      else {
        $fields = array(
          'state' => $this->getState(),
          'visibility' => $this->getVisibility(),
          'viewed' => $this->getViewed(),
        );

        // by default we treat task updates as "stacking" of additional events on to the
        // same notification, but there are cases where we don't want to update any
        // timestamp data, so this flag allows us to bypass that code
        if ($multi_update) {
          // reset the viewed timestamp
          $this->setViewed(0);
          $fields['viewed'] = $this->getViewed();

          $fields['created'] = REQUEST_TIME; // update the created time so that subsequent updates
          // to this task will bump the task to the top of the user's notifications feed
        }

        db_update('taskit')
          ->fields($fields)
          ->condition('task_id', $this->getTaskId())
          ->execute();

        $visibility_type = variable_get('taskit_visibility', 'global');
        if ($visibility_type == 'user' && $uid) {
          db_merge('taskit_viewed')
            ->key(array(
              'task_id' => $this->getTaskId(),
              'user_id' => $uid,
            ))
            ->execute();
        }
      }

    // regardless of whether we insterted a new task or are updating
    // an existing one, we now have a task id to work with

    // remove old referenced entities and save new ones
      $this->removeOldRecords('taskit_entity');

      $table_fields = array();
      foreach ($this->_entities as $entity_type => $entity_ids) {
        foreach ($entity_ids as $entity_id) {
          $table_fields[] = array(
            'task_id' => $this->getTaskId(),
            'entity_type' => $entity_type,
            'entity_id' => $entity_id,
          );
        }
      }

      $this->saveNewRecords('taskit_entity', $table_fields);

    // remove old referenced triggering & owning users and save new ones
      $user_types = array(
        'taskit_user_trigger' => '_triggering_users',
        'taskit_user_owner'   => '_owning_users',
      );

      foreach ($user_types as $table => $field) {
        $this->removeOldRecords($table);

        $table_fields = array();
        foreach ($this->{$field} as $user_id) {
          $table_fields[] = array(
            'task_id' => $this->getTaskId(),
            'user_id' => $user_id,
          );
        }

        $this->saveNewRecords($table, $table_fields);
      }

      if ($this->_owning_users) {
        foreach ($this->_owning_users as $uid) {
          $user = user_load($uid);
          if ($user) {
            taskit_update_user_unread_count($uid);
          }
        }
      }

    return $this->getTaskId();
  }

  /**
   * Deletes all records in specified table which match the task id.
   */
  protected function removeOldRecords($table) {
    return db_delete($table)->condition('task_id', $this->getTaskId())->execute();
  }

  /**
   * Inserts new records in specified table.
   */
  protected function saveNewRecords($table, $records) {
    if ($records) {
      $query = db_insert($table);

      $query->fields(array_keys($records[0]));

      foreach ($records as $record) {
        $query->values($record);
      }

      return $query->execute();
    }

    return FALSE;
  }

  /**
   * Internal link processor; used to run all links within a task item through a
   * central handler which is used to mark the task as 'viewed'
   */
  protected function l($text, $path, array $options = array()) {
    $uid = $this->currentUser();

    return l($text, 'taskit/view/' . $uid . '/' . $path, $options);
  }

  /**
   * Generates the output for current item.
   */
  public function display($entities, $accounts) {
    $output = '';

    return $output;
  }

  /**
   * Prefix all relative links in the content with a custom callback url
   */
  public function processDisplay($entities, $accounts) {
    $output = $this->display($entities, $accounts);

    $uid = $this->currentUser();

    $pattern = '#(<a\s*href\s*=\s*[\'"])(/[^"]*)#';
    $replacement = '${1}/taskit/view/' . $this->getTaskId() . '/' . $uid . '${2}';

    $output = preg_replace($pattern, $replacement, $output);

    return $output;
  }

  /**
   * Returns the UID of the user being looked at.
   * @return [type] [description]
   */
  public function currentUser() {
    if (preg_match('#user/([0-9]+)#', $_GET['q'], $matches)) {
      $uid = $matches[1];
    }
    else {
      global $user;
      $uid = $user->uid;
    }

    return $uid;
  }
}