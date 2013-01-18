<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2009,2010,2012 Becheru Petru-Ioan

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

// error_reporting(E_ALL);
// ini_set("display_errors", 1);

// pwision files
include_once("pwision.inc");
// CSS Zen Garden Theme support
include_once("inc/PCSSZenWebPage.inc");

/** 	The PMyWebPage class is designed to model the webpage.
	*	\latexonly \label{PWision:PMyWebPage} \index{PMyWebPage} \endlatexonly
	*	\brief the webpage.
	*	\version 1.0.0
	*/
class PMyWebPage extends PWebPageDefault
	{
	function & setLanguage()
		{
		$this->Language='en';
		parent::setLanguage();
		PMainComponent::$Lang['']='';
		return $this;
		}
		protected function website_css()
			{
			return null;
			return new PText(" @import \"css/pwision_kde.css\"; ");
			}
		function TranslateElement($id="google_translate_element")
			{
			return null;
			return parent::TranslateElement($id);
			}
	function SearchForm($query='')
		{
		return null;// no search form by default
		return PWebPageDefault::SearchForm($query);
		}
	function SkyAdd()
		{
		return null;// no sky add by default
		return PWebPageDefault::SkyAdd();
		}
	function LongAdd()
		{
		return null;// no long add by default
		return PWebPageDefault::LongAdd();
		}
	function reCAPTCHAprivatekey()
		{
		return '';
		}
	function reCAPTCHApublickey()
		{
		return '';
		}
	/**	Settings for the webpage.
		*	\brief constructor.
		*/
	function PMyWebPage()
		{
		PWebPageDefault::PWebPageDefault();
		$this
			->setTitle("PWision")
			->setMotto("change the code by extending it")
			;
		}
	}

$page=new PMyWebPage();
print( $page->Draw() );
?>