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

error_reporting(E_ALL);
ini_set("display_errors", 1);

/**
\mainpage PWision toolkit
<a href='http://pwision.googlecode.com/'>PWision</a> is an advanced toolkit that is used to make HTML webpages. It is an object oriented hierarchy of PHP classes that is used for building webpages using the information from the database and the HTML outputting classes, that it defines.
\author Becheru Petru-Ioan
\note The source code is released under <a href="http://www.gnu.org/licenses/gpl.txt" title='text of GNU GENERAL PUBLIC LICENSE Version 3'>GNU GENERAL PUBLIC LICENSE Version 3</a>.
	\version 4.2.0
*	\todo replace eregi by preg_match
*/

/** 	The PWision class is designed to be a model class for documentation of the code.
	*	\latexonly \label{PWision:PWision} \index{PWision} \endlatexonly
	*	\brief a model class.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PWision.inc");
print( );
\endcode
	*	\par Output:
\verbatim
\endverbatim
	*/
class PWision
	{
	/**	Constructs
		*	\brief constructor
		*	\param $a
		*/
	function PWision($a)
		{
		}
	/**	YY
		*	\brief a
		*	\version 1.0.0
		*	\param $a
		*	\return reference to $this
		*/
	function & Y($a)
		{
		return $this;
		}
	}

/*header("Vary: Accept");
if (stristr($_SERVER["HTTP_ACCEPT"], "application/xhtml+xml"))
    header("Content-Type: application/xhtml+xml; charset=utf-8");
else
    header("Content-Type: text/html; charset=utf-8");*/
session_start();

/** 	The PautoloadPaths class is designed to hold the $paths array.
	*	\latexonly \label{PWision:PautoloadPaths} \index{PautoloadPaths} \index{autoload} \endlatexonly
	*	\brief holder of __autoload() paths.
	*	\version 2.1.0
	*/
final class PautoloadPaths
	{
	/// autoload paths
	static public $paths=array();
	/**	Adds a path to autoload $paths array. The path is added as the first element so the __autoload() function will find a class from this path before others because this is the important one.
		*	\brief add a path to autoload paths.
		*	\param $path a text string(example: 'sections/sections_pw-newspaper' )
		*	\return nothing
		*/
	static function AddPath($path)
		{
		array_unshift(PautoloadPaths::$paths,$path);
		}
	}
/**	Load the php file that contains the section class definition. The file is searched first in <b>sections</b> directory, then in <b>PautoloadPaths::$paths</b> and finally in <b>sections/pwision</b>, thus allowing redefitions of the default classes like login.
	*	\latexonly \label{PWision:autoload} \index{autoload} \index{__autoload} \endlatexonly
	*	\brief Load a section.
	*	\version 3.0.0
	*	\param $class_name the name of the class
	*	\note may be triggered from PBasicWebPage::setSection()
	*/
function __autoload($class_name)
	{
	//first in 'sections'
	$path='sections';
		$filename = $path."/".$class_name.".inc";
		if(file_exists($filename))
			{
			include($filename);
			return;
			}
	//then in PautoloadPaths::$paths
	foreach(PautoloadPaths::$paths as $path)
		{
		$filename = $path."/".$class_name.".inc";
		if(file_exists($filename))
			{
			include($filename);
			return;
			}
		}
	//finally in 'sections/pwision'
	$path='sections/pwision';
		$filename = $path."/".$class_name.".inc";
		if(file_exists($filename))
			{
			include($filename);
			return;
			}
	}


include_once("inc/PBasicWebPage.inc");
?>