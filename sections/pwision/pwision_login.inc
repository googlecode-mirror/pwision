<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2009--12 Becheru Petru-Ioan

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
include_once("inc/PFormSection.inc");
include_once("inc/PRedirectSection.inc");
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
include_once("inc/PMainComponent.inc");
include_once("externalAPI/recaptchalib.php");
/** 	The pwision_login class is designed to model the login section. The login section is the section of the website where guest users can log in with their username and password. This class can be extended, for example, to change the redireting URL by modifying InsertOnSuccessfulLogin() method.
	*	\latexonly \label{PWision:Sections:pwision_login} \index{login}  \index{guest} \index{user}\endlatexonly
	*	\brief the pwision_login section.
	*	\version 1.1.0
	*/
class pwision_login extends PFormSection
	{
	function setParams()
		{
		$this
			->addParam("username",'/^[-@._a-z0-9 ]{1,64}$/i','')
			->addParam("password",'/^[a-z0-9 ]{1,64}$/i','')
			;
		}
	function & Head()
		{
		return
			parent::Head()
				->Insert(
					Object(new PSimpleTag("meta"))
						->setAtr("name","robots")
						->setAtr("content",'noindex')
					)
				;
		}
	function ProcessOK()
		{
		$captcha_ok=true;
		if($_SESSION['login_attempt']>3)
			{
			$resp = recaptcha_check_answer (Main()->reCAPTCHAprivatekey(),
										$_SERVER["REMOTE_ADDR"],
										$_POST["recaptcha_challenge_field"],
										$_POST["recaptcha_response_field"]);
			$captcha_ok=$resp->is_valid;
			}
		if ($captcha_ok)
			if(isset($_REQUEST['username']) && isset($_REQUEST['password']))
				Users::LogIn($_REQUEST['username'],$_REQUEST['password']);
		if( $_SESSION['userID']>0 )
			{
			$this->TheForm->Insert( $this->InsertOnSuccessfulLogin() );
			$_SESSION['login_attempt']=0;
			return true;
			}
			else
				$_SESSION['login_attempt']++;
		$this->AddMessage("User/Password not ok! Try again");
		return false;
		}
		protected function inside_form()
		{
		return 
				Object(new PFieldSet(PTextlang("Please identify")))
					->Insert(
						new PInput("text","","username",lang('username'),'','',true)
						)
						->Insert(new PSimpleTag("br"))
					->Insert(
						new PInput("password","","password",lang('password'),'','',true)
						)
						->Insert(new PSimpleTag("br"))
					->Insert($captcha)
					->Insert(new PInput("submit",lang("Log in!"),""))
				;
		}

	function & createForm()
		{
		if(!isset($_SESSION['login_attempt']))$_SESSION['login_attempt']=0;
		$captcha=($_SESSION['login_attempt']<3)?(new PDrawable):(new PText(recaptcha_get_html(Main()->reCAPTCHApublickey())) );
		return PFormSection::createForm()
			->setAtr("method","post")
			->Insert(
				$this->inside_form()
				)
			;
		}
	/**	This function sets the PDrawable that will be inserted on successful login.
		*	\brief PDrawable inserted on login.
		*	\return a PDrawable
		*/
	function InsertOnSuccessfulLogin()
		{
		return JSRedirect2Section("Root");
		}
	}
?>