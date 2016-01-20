# Introduction #

Installing PWision is easy: just follow the steps bellow!

# Requirements #
  * a web server with PHP module
  * a SQL server

# Steps #
  1. get PWision using svn checkout or by downloading a release.
  1. copy files from trunk/ into the webserver directory
  1. create a database on the SQL server
  1. run the script SQL/initDB.mysql on the SQL server
  1. edit StartDBConnection.inc with the SQL server username, password, server url and database name