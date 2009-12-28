<?php
include_once("pwision.inc");
class PMySitemap extends PSitemap
	{
	protected function StartDBConnection()
		{
		$this->DB=new PMySQLConsole("DBuserName","DBPassword","sql server url");
			$this->DB->SelectDB("DBName");
		}
	function SiteURL()
		{
		return 'http://localhost/';
		}
	}

print( new PMySitemap );

?>