<?php
/**
 * @file
 * Administrative pages for the oauth2_login module.
 */

/**
 * Admin settings for the module oauth2_login.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function oauth2_login_admin_settings() {
  $form = array(
    '#type'  => 'fieldset',
    '#title' => t('OAuth2 Login Settings'),
  );

  $form['oauth2_login_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => variable_get('oauth2_login_enabled', FALSE),
    '#description' => t('Check to enable OAuth2 Login.'),
  );

  $form['oauth2_login_oauth2_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Server URL'),
    '#default_value' => variable_get('oauth2_login_oauth2_server', ''),
    '#description' => t('The URI of the OAuth2 Login Provider.'),
    '#states' => array(
      'visible' => array(
        ':input[name="oauth2_login_enabled"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['oauth2_login_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#default_value' => variable_get('oauth2_login_client_id', ''),
    '#description' => t('The Client ID that is registered on the OAuth2 server.'),
    '#states' => array(
      'visible' => array(
        ':input[name="oauth2_login_enabled"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['oauth2_login_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#default_value' => variable_get('oauth2_login_client_secret', ''),
    '#description' => t('The Client secret that is registered on the OAuth2 server.'),
    '#states' => array(
      'visible' => array(
        ':input[name="oauth2_login_enabled"]' => array('checked' => TRUE),
      ),
    ),
   );

  $form['testing'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Settings Useful for Development, Testing and Debug'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="oauth2_login_enabled"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['testing']['oauth2_login_skipssl'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip SSL'),
    '#description' => t('Skip checking the SSL certificate.'),
    '#default_value' => variable_get('oauth2_login_skipssl', FALSE),
  );

  $form['testing']['oauth2_login_proxy'] = array(
    '#type' => 'textfield',
    '#title' => t('HTTP Proxy'),
    '#description' => t('Use an HTTP proxy agent (like <a href="http://mitmproxy.org" target="_blank">http://mitmproxy.org</a>).'),
    '#default_value' => variable_get('oauth2_login_proxy', ''),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'oauth2_login_admin_set_settings';
  $form['#submit'][] = 'oauth2_login_update_login_link';
  return $form;
}

/**
 * Synchronize settings with hybridauth_DrupalOAuth2.
 */
function oauth2_login_admin_set_settings() {
  $oauth2_server = variable_get('oauth2_login_oauth2_server', '');
  $client_id = variable_get('oauth2_login_client_id', '');
  $client_secret = variable_get('oauth2_login_client_secret', '');
  $skipssl = variable_get('oauth2_login_skipssl', FALSE);
  $proxy = variable_get('oauth2_login_proxy', '');

  variable_set('hybridauth_provider_DrupalOAuth2_oauth2_server', $oauth2_server);
  variable_set('hybridauth_provider_DrupalOAuth2_keys_key', $client_id);
  variable_set('hybridauth_provider_DrupalOAuth2_keys_id', $client_id);
  variable_set('hybridauth_provider_DrupalOAuth2_keys_secret', $client_secret);
  variable_set('hybridauth_provider_DrupalOAuth2_skipssl', $skipssl);
  variable_set('hybridauth_provider_DrupalOAuth2_proxy', $proxy);
}

/**
 * Update (enable/disable) the oauth2 login link on the user menu.
 */
function oauth2_login_update_login_link() {
  $enabled = variable_get('oauth2_login_enabled', FALSE);
  db_update('menu_links')
    ->fields(array(
        'hidden' => ($enabled ? 0 : 1),
      ))
    ->condition('menu_name', 'user-menu')
    ->condition('link_path', 'user/oauth2_login')
    ->condition('router_path', 'user/oauth2_login')
    ->condition('plid', 0)
    ->condition('module', 'system')
    ->execute();

  // Call hook_oauth2_login_enabled() for all modules.
  module_invoke_all('oauth2_login_enabled', $enabled);

  // Clear the cache and rebuild the menu.
  menu_cache_clear('user-menu');
}