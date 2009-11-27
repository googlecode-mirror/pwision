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
include_once("inc/PFormSection.inc");
include_once("inc/PRedirectSection.inc");
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
/** 	The login class is designed to model the login section. The login section is the section of the website where guest users can log in with their username and password.
	*	\latexonly \label{PWision:Sections:login} \index{login}  \index{guest} \index{user}\endlatexonly
	*	\brief the login section.
	*	\version 1.1.0
	*/
class login extends PFormSection
	{
	/**	This method is called by the constructor to set the arguments of the form, using addArgument(), for future extraction.
		*	\brief sets the arguments of the form.
		*/
	function setArguments()
		{
		$this
			->addArgument("username")
			->addArgument("password")
			;
		}
	function ProcessOK()
		{
		if(isset($_REQUEST['username']) && isset($_REQUEST['password']))
			Users::LogIn($_REQUEST['username'],$_REQUEST['password']);
		sleep( rand(1,5) );// ;)
		if( $_SESSION['userID']>0 )
			{
			$this->TheForm->Insert(
				JSRedirect2Section("Root")
				);
			return true;
			}
		$this->AddMessage("User/Password not ok! Try again");
		return false;
		}
	function createForm()
		{
		PFormSection::createForm()
			->setAtr("method","post")
			->Insert(
				Object(new PFieldSet(new PText("Please identify:")))
					->Insert(new PInput("text","","username"))->Insert(new PText(" UserName [use '-@._a-z0-9' ; 64 chars max]"))->Insert(new PSimpleTag("br"))
					->Insert(new PInput("password","","password"))->Insert(new PText(" Password [use 'a-z0-9' ; 64 chars max]"))->Insert(new PSimpleTag("br"))
					->Insert(new PInput("submit","Log in!",""))
				)
			;
		}
	}
?>