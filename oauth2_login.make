api = 2
core = 7.x

defaults[projects][subdir] = "contrib"

projects[oauth2_client][version] = "1.x-dev"
;projects[oauth2_client][type] = "module"
;projects[oauth2_client][download][type] = "git"
;projects[oauth2_client][download][url] = "https://github.com/dashohoxha/oauth2_client.git"
;projects[oauth2_client][download][branch] = "7.x-1.x"

projects[hybridauth][version] = "2.9"

;libraries[hybridauth][directory_name] = "hybridauth-2.1.2"
;libraries[hybridauth][download][type] = "get"
;libraries[hybridauth][download][url] = "http://sourceforge.net/projects/hybridauth/files/hybridauth-2.1.2.zip"

;libraries[hybridauth-additional-providers][directory_name] = "hybridauth-additional-providers-1.8"
;libraries[hybridauth-additional-providers][download][type] = "get"
;libraries[hybridauth-additional-providers][download][url] = "http://sourceforge.net/projects/hybridauth/files/hybridauth-additional-providers-1.8.zip"

libraries[hybridauth][directory_name] = "hybridauth"
libraries[hybridauth][download][type] = "git"
libraries[hybridauth][download][url] = "https://github.com/dashohoxha/hybridauth.git"
