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
/** 	The PMySQLConsole class is designed to be used for SQL queries.
	*	\latexonly \label{PWision:PMySQLConsole} \index{PMySQLConsole} \index{MySQL} \index{database} \index{query} \index{SQL} \endlatexonly
	*	\brief a sql connection class.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("inc/PMySQLConsole.inc");
$DB=new PMySQLConsole("username","password","sql server");
$DB->SelectDB("database name");
$section_name='Root';
$subsections=$DB->fetch_all_query( "SELECT * FROM Sections WHERE Owner='$section_name'");
print_r($subsections);
\endcode
	*	\par Output:
	*		The subsections of section <i>Root</i>.
	*/
class PMySQLConsole
	{
	/// sql connection
	protected $connection;
	/**	starts the connection to the sql server
		*	\brief constructor.
		*	\param $user sql server user
		*	\param $password the password of the $user
		*	\param server MySQL server location(ip)
		*/
	function PMySQLConsole($user,$password,$server="localhost")
		{
		$this->connection=mysql_pconnect($server,$user,$password);
			if (!$this->connection)die('Could not connect: ' . mysql_error());
		}
	
	/**	\brief selects a database 
		*	\param $db database name
		*/
	function & SelectDB($db)
		{
		if(! mysql_select_db($db,$this->connection))
			die('db not selected: '.mysql_error());
		return $this;
		}
	
	///\brief closes the connection
	function & Close()
		{
		mysql_close($this->connection);
		return $this;
		}
	/**	Closes the connection.
		*	\brief destructor
		*/
	function __destruct()
		{
		$this->Close();
		}
		
	/**	Make a SQL query using the connection.
		*	\brief make a query.
		*	\param $query query text
		*	\return sql resource
		*/
	function query($query)
		{
		//print("{query [$query]");
		$ret=mysql_query($query,$this->connection);
		//print($ret." "); print(mysql_error().mysql_num_rows($ret)." query}<hr/>");
		return $ret;
		}
	/**	Gets the next result row from a sql resource,
		*	\brief Gets the next result row.
		*	\param $sql_res the result resource returned by PMySQLConsole::query
		*	\return an array
		*/
	function fetch_array($sql_res)
		{
		return mysql_fetch_array($sql_res);
		}
	/**	Gets the next result row from an query.
		*	\brief Gets the next result row.
		*	\param $query the query
		*	\return an array
		*/
	function fetch_array_query($query)
		{
		return $this->fetch_array($this->query($query));
		}
	/**	Gets all the rows of an query.
		*	\brief Gets the result.
		*	\param $sql_res the result resource from PMySQLConsole::query
		*	\return an array
		*/
	function fetch_all_array($sql_res)
		{
		$ret;
		if($sql_res)
			{
			//print("{fetch_all_array $sql_res ".mysql_num_rows($sql_res)." ");
			$ret=array();
			while($row=$this->fetch_array($sql_res))
				{
				array_push($ret,$row);
				//print_r($row."<hr/>");
				}
			//print_r($ret);
			//print(mysql_error()."fetch_all_array}<br/>");
			}
		return $ret;
		}
	/**	Gets all the rows of an query.
		*	\brief Gets the result.
		*	\param $query the query
		*	\return an array
		*/
	function fetch_all_query($query)
		{
		//print("fetch_all_query:<br/>");
		return $this->fetch_all_array($this->query($query));
		//return true;
		}
	}
?>