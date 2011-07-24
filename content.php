<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2011 Becheru Petru-Ioan

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

// pwision files
include_once("pwision.inc");
// CSS Zen Garden Theme support
include_once("inc/PCSSZenWebPage.inc");

// include_once('.inc');

/** 	The PMyWebPage class is designed to model the webpage.
	*	\latexonly \label{PWision:PMyWebPage} \index{PMyWebPage} \endlatexonly
	*	\brief the webpage.
	*	\version 1.0.0
	*/
class PMyWebPage extends PSectionWebPage
	{
	function & setLanguage()
		{
		$this->Language='ro';
		PMainComponent::$Lang['']='';
		return parent::setLanguage();
		}
	/**	Settings for the webpage.
		*	\brief constructor.
		*/
	function PMyWebPage()
		{
		PSectionWebPage::PSectionWebPage();
		$this
			->setTitle("")
			->setMotto("")
			;
		}
	}

header ("Content-Type:text/xml"); 

$page=new PMyWebPage();
print( $page->Draw() );
?>