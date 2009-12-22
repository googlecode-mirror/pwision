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
include_once("inc/PElement.inc");
/**	This function creates a redirecting script.
	*	\brief a redirecting script.
	*	\version 1.0.0
	*	\param $URL redirect URL
	*	\return an \<script\> element that contains a java-script code that redirects the browser.
	*/
function JSRedirect($URL)
	{
	return
		El("script")
				->setAtr("type","text/javascript")
			->Insert(
				new PText('window.location="'.$URL.'"')
				);
	}
/**	This function creates a script that redirects to a section.
	*	\brief redirect to a section.
	*	\version 1.0.0
	*	\param $section_name name of the section
	*	\param $webpage name of the webpage
	*	\return an \<script\> element that contains a java-script code that redirects the browser.
	*/
function JSRedirect2Section($section_name="Root", $webpage="index.php")
	{
	return JSRedirect("$webpage?section=$section_name");
	}


include_once("inc/PSection.inc");
/** 	The PRedirectingSection class is designed to model a section that redirects the client browser to an url.
	*	\latexonly \label{PWision:PRedirectingSection} \index{PRedirectingSection} \label{redirect} \label{URL} \endlatexonly
	*	\brief a redirecting section.
	*	\version 1.0.0
	*/
class PRedirectingSection extends PSection
	{
	/// redirect URL
	private $URL;
	/**	Constructs a redirecting section.
		*	\brief constructor
		*	\param $URL redirect URL
		*/
	function PRedirectingSection($URL)
		{
		$this->URL=$URL;
		PSection::PSection();
		}
	function Chapter1Title()
		{
		return PSection::Chapter1Title()
			->Insert( new PText("You are now being redirected to ".$this->URL) );
		}
	function Chapter1()
		{
		return
			PSection::Chapter1()
				->Insert(JSRedirect($this->URL));
		}
	}
/** 	The PRedirect2Section class is designed to model a section that redirects the client browser to the url of a section.
	*	\latexonly \label{PWision:PRedirect2Section} \index{PRedirect2Section} \label{redirect} \label{section} \endlatexonly
	*	\brief a section that redirects to a section.
	*	\version 1.0.0
	*/
class PRedirect2Section extends PSection
	{
	/// redirect section name
	private $section_name;
	/**	Constructs a redirecting section.
		*	\brief constructor
		*	\param $section_name section name
		*/
	function PRedirect2Section($section_name="Root")
		{
		$this->section_name=$section_name;
		PSection::PSection();
		}
	function Chapter1Title()
		{
		return PSection::Chapter1Title()
			->Insert( new PText("You are now being redirected to section '".$this->section_name."'... ") );
		}
	function Chapter1()
		{
		return
			PSection::Chapter1()
				->Insert(
					JSRedirect2Section($this->section_name)
					);
		}
	}
?>