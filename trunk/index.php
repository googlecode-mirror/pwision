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
	function setLanguage()
		{
		$this->Language='en';
		parent::setLanguage();
		}
		/**	Gives the <b>style</b> tag with the text/css type.
			*	\brief the css.
			*	\return \<style type="text/css"\> tag
			*/
		protected function Head_Css()
			{
			// get theme number from UserInfo
			//$no=$this->UserInfo["Theme"];
			return PBasicWebPage::Head_Css()
				->Insert(new PText(" @import \"css/pwision_lightgray.css\"; "))
				;
			}
	function SearchForm($query='')
		{
		return null;
		return PWebPageDefault::SearchForm($query);
		}
	function SkyAdd()
		{
		return null;
		return PWebPageDefault::SkyAdd();
		}
	function LongAdd()
		{
		return null;
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
		PCSSZenWebPage::PCSSZenWebPage();
		$this
			->setTitle("PWision")
			->setMotto("change the code by extending it")
			->setRootName("&#x27F0;")
			;
		}
	}

$page=new PMyWebPage();
print( $page->Draw() );
?>