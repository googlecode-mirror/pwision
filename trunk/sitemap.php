<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2009 Becheru Petru-Ioan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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