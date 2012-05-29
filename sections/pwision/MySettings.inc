<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2012 Becheru Petru-Ioan

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

include_once ('inc/PBBCodeInput.inc');
include_once('inc/BBCode.inc');
include_once("inc/PFormSection.inc");
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
include_once("inc/Groups.inc");



/** 	The MySettings class is designed to model the section that allows a user to configure its account.
	*	\latexonly \label{PWision:Sections:MySettings} \index{MySettings} \endlatexonly
	*	\brief a user editor.
	*	\version 1.0.0
	*/
class MySettings extends PFormSection
	{
	protected function preprocessParam($param_name)
		{
		$_REQUEST[$param_name]=charset_decode_utf_8($_REQUEST[$param_name]);
		}
	function setParams()
		{
		$this
			->addParam("Password",'/^[a-z0-9 ]{1,64}$/i','')
			;
		}
	function if_not_all_parameters_are_set()
		{
		$this->ConstructLocation();
		parent::if_not_all_parameters_are_set();
		}
/*	function getTitle()
		{
		return lang($this->getName()).' '.lang($this->getParam('sectionname'));
		}*/
	function ProcessOK()
		{
// 		return true;
		Users::SetPassword( $_SESSION['userID'], $this->getParam('Password') );
		$this->AddMessage("The password was changed!");
		return false;
		}
	function createForm()
		{
		$FormContent=new PContent();
		$FormContent
				->Insert(
					new PInput("password","","Password",lang('enter a new password'))
					)
					->Insert(new PSimpleTag("br"))
				->Insert(new PInput("submit",lang("Save"),""))
				;

		return PFormSection::createForm()
				->setAtr("method",'post')

			->Insert($FormContent)
			;
		}
	}
?>