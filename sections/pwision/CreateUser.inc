<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2009,2010 Becheru Petru-Ioan

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
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
include_once('inc/PRedirectSection.inc');
/** 	The CreateUser class is designed to model the section that allows a user to create users of the website.
	*	\latexonly \label{PWision:Sections:CreateUser} \index{CreateUser} \index{user} \endlatexonly
	*	\brief an user creator.
	*	\version 1.1.1
	*/
class CreateUser extends PFormSection
	{
	function setParams()
		{
		$this
			->addParam("username",'/^[-@._a-z0-9 ]{1,64}$/i','')
			;
		}
	function ProcessOK()
		{
		$ret=Users::Create(
						$_REQUEST['username'],
						'password',
						$_SESSION['userID'],
						array()
						);
		switch ($ret)
			{
			case 0:
				$this->AddMessage("Username ". $_REQUEST['username']." allready exists");break;
			default:
				$this->AddMessage(
					"User Created with ID: $ret!".
					JSRedirect2Section(
						'EditUser',
						Object(new PURLAttributes)
							->setAtr( 'ID', $ret )
							->setAtr( 'action', 'edit' )
						)->Draw()
					);
			}
		return $ret>0;
		}
	function createForm()
		{
		$GroupBox=Groups::GroupsFieldSet();

		$T=new PTable();
				$T->AddCell()->Insert(new PText("User Name:"));
				$T->AddCell()->Insert(new PInput("text","","username"));
				$T->AddCell()->Insert(new PText("use [-@._a-z0-9 ]+ 63 chars max"));
			$T->AddRow();
				$T->AddCell();
				$T->AddCell()->Insert(new PInput("submit","Create!",""));
				$T->AddCell();

		return PFormSection::createForm()->Insert($T);
		}
	}

?>