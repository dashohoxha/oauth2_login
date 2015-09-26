<?php
/**
 * @file
 * Misc utility functions.
 */

/**
 * Return true if oauth2_user is installed on the server.
 */
function oauth2_user_installed_on_server() {
  return module_exists('oauth2_loginprovider');
}

/**
 * Return true if the user is authenticated.
 */
function oauth2_user_is_authenticated() {
  if (oauth2_user_installed_on_server()) {
    return user_is_logged_in();
  }
  else {
    return oauth2_user_has_token();
  }
}

/**
 * Return true if the user has an oauth2 access_token.
 */
function oauth2_user_has_token() {
  $server_url = variable_get('oauth2_login_oauth2_server', '');
  $token_endpoint = $server_url . '/oauth2/token';
  $client_id = variable_get('oauth2_login_client_id', '');
  $auth_flow = 'server-side';

  // Get the current access_token.
  $id = md5($token_endpoint . $client_id . $auth_flow);
  $token = oauth2_client_get_token($id);

  // Check the access token.
  return !empty($token['access_token']);
}

/**
 * Authenticate the user (redirect to login).
 * But first save the given form_state in session.
 */
function oauth2_user_authenticate($form_state, $redirection = FALSE) {
  if ($redirection) {
    // We are in a redirect-after-login, but login has failed or was cancelled.
    // In this case we clear the session variable so that it does not keep
    // redirecting.
    unset($_SESSION['oauth2_user']['form_state']);
    return;
  }

  $_SESSION['oauth2_user']['form_state'] = $form_state;

  if (oauth2_user_installed_on_server()) {
    drupal_goto('user/login', array('query' => drupal_get_destination()));
  }
  else {
    oauth2_login();
  }
}

/**
 * If there is a $_SESSION['oauth2_user']['form_state'],
 * then this is a redirect after login. Call the submit function again.
 */
function oauth2_user_form_resubmit() {
  $form_state = $_SESSION['oauth2_user']['form_state'];
  unset($_SESSION['oauth2_user']['form_state']);
  $form_id = $form_state['values']['form_id'];
  $submit = $form_id . '_submit';
  if (function_exists($submit)) {
    $submit(NULL, $form_state);
  }
}
