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

include_once ('inc/PBBCodeInput.inc');
include_once('inc/BBCode.inc');
include_once("inc/PFormSection.inc");
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
include_once("inc/Groups.inc");



/** 	The EditSection class is designed to model the section that allows a user to edit the sections of the website. It provides an intuitive interface with textboxes (for section name and description) and checkboxes (that display the groups that the section will be member of).
	*	\latexonly \label{PWision:Sections:EditSection} \index{EditSection} \endlatexonly
	*	\brief a section editor.
	*	\version 2.0.0
	*/
class EditSection extends PFormSection
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
			->addParam('description','/^[-&#;a-z0-9,() ]{0,512}$/i','')
			->addParam('Owner','/^[a-z][_a-z0-9 ]{1,62}$/i','')
			->addParam('Sort','/^[a-z0-9]{1,16}$/i','')
// 			->addParam('groups','','')
// 			->addParam('attr','','')
			->addParam('text',$fulltext,'')
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
// 		return true;
		Sections::setDescription($this->getParam('sectionname'),$this->getParam('description'));
		
		Sections::setSort($this->getParam('sectionname'),$this->getParam('Sort'));
		
		Sections::setOwner($this->getParam('sectionname'),$this->getParam('Owner'));
		
		Sections::setBBCode($this->getParam('sectionname'),$this->getParam('text'));
		
		Sections::RemoveFromGroups($this->getParam('sectionname'));
		if(array_key_exists('groups',$_REQUEST))
			Sections::Add2Groups($this->getParam('sectionname'),$this->getParam('groups'));
		
		Sections::unHide($this->getParam('sectionname'));
		Sections::unBookmark($this->getParam('sectionname'));
		if(array_key_exists('attr',$_REQUEST))
			{
			$attr=$this->getParam('attr');
	// 		print_r($attr);
			if(array_key_exists('Hidden',$attr) && $attr['Hidden']=='Hidden')
				Sections::Hide($this->getParam('sectionname'));
			if(array_key_exists('Bookmarked',$attr) && $attr['Bookmarked']=='Bookmarked')
				Sections::Bookmark($this->getParam('sectionname'));
			}
		return false;
		}
	function createForm()
		{
		$FormContent=new PContent();
		
		$Sections=Main()->DB->fetch_all_query("select * from Sections order by `Sort`");
		array_push($Sections,Sections::Section('Root'));
		if ($this->wasParamSet('sectionname'))
				{
				$section=Sections::Section($this->getParam('sectionname'));
				
				$Description=Object(new PFieldSet(PTextlang('Description:')))
					->Insert(new PInput("text",$section['Description'],"description"));
				$FormContent->Insert($Description);
				
				$Owner=Object(new PFieldSet(PTextlang('Owner:')))
					->Insert(SSelect('Owner',$Sections, $section['Owner'], 'Name', 'Name'));
				$FormContent->Insert($Owner);
				
				$Sort=Object(new PFieldSet(PTextlang('Sort string:')))
					->Insert(new PInput("text",$section['Sort'],"Sort"));
				$FormContent->Insert($Sort);
				
				$Hidden=
					array(
						'text'=>'Hidden', 
						'value'=>'Hidden'
						);
				if(Sections::isHidden($this->getParam('sectionname')))
					$Hidden['checked']=true;
				$Bookmarked=
						array(
							'text'=>'Bookmarked', 
							'value'=>'Bookmarked'
						);
				if(Sections::isBookmarked($this->getParam('sectionname')))
					$Bookmarked['checked']=true;
				$FormContent
					->Insert(
						FieldSet('Attributes')
							->Insert(
								Array2Inputs(
									array($Hidden,$Bookmarked),
									'attr'
									)
							)
						);
						
				$Groups=FieldSet('Groups:');
				$Groups
					->Insert(
						Array2Inputs(
							Main()->DB->fetch_all_query(
								'select *, \'1\' as `checked` from Groups where ID in '.
'(select GroupID from GroupSections where SectionName=\''.$this->getParam('sectionname').'\')'
								)
								+
							Main()->DB->fetch_all_query(
								'select * from Groups where ID not in '.
'(select GroupID from GroupSections where SectionName=\''.$this->getParam('sectionname').'\')'
								)
							,
							'groups[]',
							"ID", "Name"
							)
						)
					;
				$FormContent->Insert($Groups);
					
				$FormContent
					->Insert(new PInput("hidden",$this->getParam('sectionname'),"sectionname"))
					->Insert(
						new PBBCodeInput(
							$this->wasParamSet('text')?$this->getParam('text'):$section['BBCode'],
							'text',
							'textContent'
							)
						)
					;
				}
			else
				{
				$FormContent
					->Insert(PTextlang('Section:') )
					->Insert(SSelect('sectionname',$Sections, null, 'Name', 'Name'))
					->Insert(new PInput("submit",lang("Edit!"),""))
					;
				}

		return PFormSection::createForm()
				->setAtr("method",'post')

			->Insert($FormContent)
			;
		}
	}
?>