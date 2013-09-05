<?php
namespace devtools;

class Core extends \devtools\Base {
  const module = 'devtools';

  /**
   * Triggers the specified hook in implementing components; aggregates and
   * returns data.
   *
   * TODO: find a way to dynamically pass arguments to the hook callback while preserving
   * references to get rid of the $a[1...10] monstrosity below!
   * 
   * @param  [type] $name           [description]
   * @param  [type] $default_return [description]
   * @return [type]                 [description]
   */
  public static function hook($name, $default_return = NULL, &$a1 = NULL, &$a2 = NULL, &$a3 = NULL, &$a4 = NULL, &$a5 = NULL, &$a6 = NULL, &$a7 = NULL, &$a8 = NULL, &$a9 = NULL, &$a10 = NULL) {
    // build an array of components that extend hooks
      static $hook_classes;

      if (is_null($hook_classes[static::module]) || empty($hook_classes[static::module])) {
        $hook_classes[static::module] = array();

        foreach (array_keys(devtools_components(static::module)) as $component) {
          $class_pieces = array(
            '',
            static::module,
            'components',
            $component,
            'Hooks'
          );

          $full_class_name = implode('\\', $class_pieces);

          if (class_exists($full_class_name)) {
            $hook_classes[static::module][$component] = $full_class_name;
          }
        }
      }

    // call the hook in components which declare it
      $return_data = $default_return;
      $module_path = drupal_get_path('module', static::module);

      if (!empty($hook_classes[static::module])) {
        foreach ($hook_classes[static::module] as $component => $class) {
          $method = 'hook_' . $name;

          if (method_exists($class, $method)) {
            $hooksObj = new $class();
            $hooksObj->setPath($module_path . '/components/' . $component);
            $hooksObj->setComponentsPath($module_path . '/components');
            $hooksObj->setModulePath($module_path);

            $return_value = $hooksObj->{$method}($a1, $a2, $a3, $a4, $a5, $a6, $a7, $a8, $a9, $a10);

            /*
              // this approach will not preserve arguments passed by reference; temporarily replaced by
              // the line above

              // removes the hook name & default return vaue from the arguments passed to the
              // hook call and aggregates the returned data
              $args = func_get_args();
              array_shift($args);
              array_shift($args);

              $return_value = call_user_func_array(array($hooksObj, $method), array($args));
            */
           
            if (!is_null($return_value)) {
              if (!is_array($return_data)) {
                $return_data = array();
              }

              $return_data = array_merge_recursive($return_data, $return_value);
            }
          }
        }
      }

      if ($name == 'menu') {
        // dsmm($return_data);
      }

      return $return_data;
  }
}