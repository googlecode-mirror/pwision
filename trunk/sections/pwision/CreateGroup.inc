<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2010 Becheru Petru-Ioan

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
include_once("inc/Groups.inc");
include_once('inc/PRedirectSection.inc');
/** 	The CreateGroup class is designed to model the section that allows a user to create groups.
	*	\latexonly \label{PWision:Sections:CreateGroup} \index{CreateGroup} \index{groups} \endlatexonly
	*	\brief a group creator.
	*	\version 1.0.0
	*/
class CreateGroup extends PFormSection
	{
	function setParams()
		{
		$this
			->addParam("name",'/^[-@._a-z0-9 ]{1,64}$/i','')
			;
		}
	function ProcessOK()
		{
		$ret=Groups::Create( $this->getParam('name') );
		$this->AddMessage(
			"Group Created with ID: $ret!".
			JSRedirect2Section(
				'EditGroup',
				Object(new PURLAttributes)
					->setAtr( 'ID', $ret )
					->setAtr( 'action', 'edit' )
				)->Draw()
			);
		return $ret>0;
		}
	function createForm()
		{
		$GroupBox=Groups::GroupsFieldSet();

		$T=new PTable();
				$T->AddCell()->Insert(new PText("Group Name:"));
				$T->AddCell()->Insert(new PInput("text","","name"));
				$T->AddCell()->Insert(new PText("use [-@._a-z0-9 ]+ 63 chars max"));
			$T->AddRow();
				$T->AddCell();
				$T->AddCell()->Insert(new PInput("submit","Create!",""));
				$T->AddCell();

		return PFormSection::createForm()->Insert($T);
		}
	}

?>