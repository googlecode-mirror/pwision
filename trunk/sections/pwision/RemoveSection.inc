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



/** 	The RemoveSection class is designed to model the section that deletes other sections.
	*	\latexonly \label{PWision:Sections:RemoveSection} \index{RemoveSection} \endlatexonly
	*	\brief a section remover.
	*	\version 1.0.0
	*/
class RemoveSection extends PFormSection
	{
	function Head()
		{
		return parent::Head()
			->Insert( PBBCodeInput::Head(Main()->getLanguage(),array('textContent', 'description')) )
			;
		}
	protected function preprocessParam($param_name)
		{
		$_REQUEST[$param_name]=charset_decode_utf_8($_REQUEST[$param_name]);
		}
	function setParams()
		{
		$fulltext='/^[ -~\xA\xD\t]*$/i';//match printable ASCII + LF and CR
		$URL='`(^(http|ftp|https):\/\/[\w\-_]+(\.[\w\-_]+)+([\w\-\.,@?^=%&amp;:/~\+#]*[\w\-\@?^=%&amp;/~\+#])?$)|(^$)`i';
		$this
			->addParam('sectionname','/^[a-z][_a-z0-9 ]{1,62}$/i','')
			;
		}
	function if_not_all_parameters_are_set()
		{
		$this->ConstructLocation();
		parent::if_not_all_parameters_are_set();
		}
	function getTitle()
		{
		return lang($this->getName()).' '.lang($this->getParam('sectionname'));
		}
	function ProcessOK()
		{
		Sections::Remove($this->getParam('sectionname'));
		return true;
		}
	function createForm()
		{
		$FormContent=new PContent();
		
		$Sections=Main()->DB->fetch_all_query("select * from Sections order by `Sort`");
		array_push($Sections,Sections::Section('Root'));
		$FormContent
			->Insert(PTextlang('Section:') )
			->Insert(SSelect('sectionname',$Sections, null, 'Name', 'Name'))
			->Insert(new PInput("submit",lang("Remove!"),""))
			;

		return PFormSection::createForm()
				->setAtr("method",'post')

			->Insert($FormContent)
			;
		}
	}
?>