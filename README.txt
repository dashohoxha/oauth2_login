The module OAuth2 Login is used to allow the users of another Drupal
site to login to your site. This is done through OAuth2
authentication. On login the users are redirected to the login of the
other Drupal site, and after they login there, they are redirected
back to this site.

For this to work, the module OAuth2 Login Provider
(https://github.com/dashohoxha/oauth2_loginprovider) must be installed
on the other site, and a client that corresponds to this site must be
registered there (on the path
'admin/structure/oauth2-servers/manage/oauth2/clients').
On that client, you must set the Redirect URI to:
https://client.example.org/oauth2/authorized

The file 'oauth2_login.make' can be useful for downloading the
dependencies.  The configuration of this module is done on:
admin/config/people/oauth2_login

The test file helps to understand the configurations that should be
done on the server and on the client:
https://github.com/dashohoxha/oauth2_login/blob/7.x-1.x/tests/oauth2_login.test#L22
