api = 2
core = 7.x

defaults[projects][subdir] = "contrib"

projects[oauth2_client][version] = "1.x-dev"

projects[hybridauth][version] = "2.9"

libraries[hybridauth][directory_name] = "hybridauth"
libraries[hybridauth][download][type] = "get"
libraries[hybridauth][download][url] = "https://github.com/hybridauth/hybridauth/archive/v2.2.1.tar.gz"
