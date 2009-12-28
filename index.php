<?php
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
	function SearchForm()
		{
		return null;
		return PWebPageDefault::SearchForm();
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
	/**	Settings for the webpage.
		*	\brief constructor.
		*/
	function PMyWebPage()
		{
		PCSSZenWebPage::PCSSZenWebPage();
		$this
			->setLanguage("en")
			->setTitle("PWision")
			->setMotto("change the code by extending it")
			->setRootName("&#x27F0;")
			;
		}
	protected function StartDBConnection()
		{
		$this->DB=new PMySQLConsole("DBuserName","DBPassword","sql server url");
			$this->DB->SelectDB("DBName");
		}
	}

$page=new PMyWebPage();
print( $page->Draw() );
?>