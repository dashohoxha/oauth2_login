<?php
/**
 * @file
 * The programing interface provided by the module oauth2_login.
 */

/**
 * Login with OAuth2.
 */
function oauth2_login($destination =NULL, $destination_error =NULL) {
  if ($destination === NULL) {
    $destination = drupal_get_destination();
    $destination = $destination['destination'];
  }
  if ($destination_error === NULL) {
    $destination_error = 'user/login';
  }
  drupal_goto('hybridauth/window/DrupalOAuth2', array(
      'query' => array(
        'destination' => $destination,
        'destination_error' => $destination_error,
      )
    ));
}

/**
 * Implements hook_oauth2_login_enabled().
 *
 * This hook is called when the configuration on
 * admin/config/people/oauth2_login is saved.  It gives a chance to
 * the other modules to change their configuration depending on
 * whether oauth2 login is enabled or disabled. The example below
 * hides or shows the menu link for local login.
 */
function hook_oauth2_login_enabled($enabled) {
  db_update('menu_links')
    ->fields(array(
        'hidden' => ($enabled ? 1 : 0),
      ))
    ->condition('menu_name', 'user-menu')
    ->condition('link_path', 'user/login')
    ->condition('router_path', 'user/login')
    ->condition('plid', 0)
    ->condition('module', 'menu')
    ->execute();
}