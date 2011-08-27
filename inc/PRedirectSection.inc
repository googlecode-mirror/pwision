<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2009--11 Becheru Petru-Ioan

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
	*	\version 1.1.0
	*	\param $URL redirect URL
	*	\param $time_out time out in ms, default 1 seconds
	*	\return an \<script\> element that contains a java-script code that redirects the browser.
	*/
function JSRedirect($URL,$time_out=1000)
	{
	return
		El("script")
				->setAtr("type","text/javascript")
			->Insert(
				new PText('setTimeout("redir()",'.$time_out.');'."\n".'function redir(){window.location="'.$URL.'";}')
				);
	}
/**	This function creates a script that redirects to a section.
	*	\brief redirect to a section.
	*	\version 3.0.0
	*	\param $section_name name of the section
	*	\param attr attributes(param) to URL, besides <b>section=<i>section_name</i></b>
	*	\param $time_out time out in ms, default 3 seconds
	*	\return an \<script\> element that contains a java-script code that redirects the browser.
	*/
function JSRedirect2Section($section_name="Root" , PURLAttributes $attr=null, $time_out=1000)
	{
	if($attr==null)$attr=new PURLAttributes();
	$attr->setSeparator('&');
	return JSRedirect( "/$section_name".$attr->Draw(), $time_out );
	}


include_once("inc/PSection.inc");

/** 	The PRedirect class is designed to model a section that is the base class for redirecting sections.
	*	\latexonly \label{PWision:PRedirect} \index{PRedirect} \label{redirect} \endlatexonly
	*	\brief a redirecting section.
	*	\version 1.0.0
	*	\note this class will be used to check if an object is an redirecting section
	*/
class PRedirect extends PSection
	{}


/** 	The PRedirectingSection class is designed to model a section that redirects the client browser to an url.
	*	\latexonly \label{PWision:PRedirectingSection} \index{PRedirectingSection} \label{redirect} \label{URL} \endlatexonly
	*	\brief a redirecting section.
	*	\version 1.3.1
	*/
class PRedirectingSection extends PRedirect
	{
	/// redirect URL
	private $URL;

	function Head()
		{
		return parent::Head()
			->Insert(
				Object(new PSimpleTag('meta'))
					->setAtr('http-equiv','refresh')
					->setAtr('content','1;url='.$this->URL)
				)
			->Insert(
				Object(new PSimpleTag("meta"))
					->setAtr("name","robots")
					->setAtr("content",'noindex')
			);
		}

	/**	Constructs a redirecting section.
		*	\brief constructor
		*	\param $URL redirect URL
		*/
	function PRedirectingSection($URL)
		{
		$this->URL=$URL;
		PRedirect::PRedirect();
		header('HTTP/1.1 301 Moved Permanently');
		header('Location: '.$URL
			); /* Redirect browser */
		}
	function Chapter1Title()
		{
		return PSection::Chapter1Title()
			->Insert(
				new PText(
					lang("You are now being redirected to").' '.
					$this->URL
					)
				);
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
	*	\version 2.0.1
	*/
class PRedirect2Section extends PRedirect
	{
	/// redirect section name
	private $section_name;
	/// attributes(param) to URL
	private $attr;

	function Head()
		{
		return parent::Head()->Insert(
				Object(new PSimpleTag("meta"))
					->setAtr("name","robots")
					->setAtr("content",'noindex')
			);
		}

	/**	Constructs a redirecting section.
		*	\brief constructor
		*	\param $section_name section name
		*	\param attr attributes(param) to URL, besides <b>section=<i>section_name</i></b>
		*/
	function PRedirect2Section($section_name="Root", PURLAttributes $attr=null)
		{
		$this->section_name=$section_name;
		$this->attr=$attr;
		PRedirect::PRedirect();
			if($attr==null)$attr=new PURLAttributes();
			$attr->setSeparator('&');
			header('HTTP/1.1 301 Moved Permanently');
			header('Location: http://'. 
				$_SERVER['SERVER_NAME']. "/$section_name". $attr->Draw()
				); /* Redirect browser */
		}
	function Chapter1Title()
		{
		return PSection::Chapter1Title()
			->Insert(
				new PText(
					lang("You are now being redirected to section").
						" '".lang($this->section_name)."'... "
					)
				);
		}
	function Chapter1()
		{
		return
			PSection::Chapter1()
				->Insert(
					JSRedirect2Section($this->section_name,$this->attr)
					);
		}
	}
?>