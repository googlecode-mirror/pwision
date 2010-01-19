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
include_once('inc/PRedirectSection.inc');
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
/** 	The CreateSection class is designed to model a section that allows a user to create sections of the website. It provides an intuitive interface with textboxes (for section name and description) and checkboxes (that display the groups that the section will be member of).
	*	\latexonly \label{PWision:Sections:CreateSection} \index{CreateSection} \index{section} \endlatexonly
	*	\brief a section creator.
	*	\version 2.0.0
	*/
class CreateSection extends PFormSection
	{
	function setParams()
		{
		$this
			->addParam('sectionname','/^[a-z][_a-z ]{1,62}$/i')
			;
		}
	function ProcessOK()
		{
		if( Sections::Create( $_REQUEST['sectionname'], 'Root') )
				{
				$this->AddMessage("Section '".$_REQUEST['sectionname']."' created ! ".
					JSRedirect2Section('EditSection',
						Object(new PURLAttributes)
							->setAtr('sectionname',$_REQUEST['sectionname'])
							->setAtr('action','edit')
						) 
					);
				return true;
				}
		$this->AddMessage("Section '".$_REQUEST['sectionname']."' NOT created!");
		return false;
		}
	function createForm()
		{
		$SectionBox=Sections::SectionsFieldSet("owner","Select Owner Section:");

		$GroupBox=Groups::GroupsFieldSet();

		$T=new PTable();
				$T->AddCell()->Insert(new PText("Section Name:"));
				$T->AddCell()->Insert(new PInput("text","","sectionname"));
				$T->AddCell()->Insert(new PText("use ' a-z' 63 chars max"));
			$T->AddRow();
				$T->AddCell();
				$T->AddCell()->Insert(new PInput("submit","Create!",""));

		return PFormSection::createForm()->Insert($T);
		}
	}

?>