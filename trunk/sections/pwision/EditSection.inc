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

include_once ('inc/PBBCodeInput.inc');
include_once("inc/PFormSection.inc");
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
include_once("inc/Groups.inc");
/** 	The EditSection class is designed to model the section that allows a user to edit the sections of the website. It provides an intuitive interface with textboxes (for section name and description) and checkboxes (that display the groups that the section will be member of).
	*	\latexonly \label{PWision:Sections:EditSection} \index{EditSection} \endlatexonly
	*	\brief a section editor.
	*	\version 1.5.0
	*/
class EditSection extends PStepFormSection
	{
	protected function preprocessParam($param_name)
		{
		$_REQUEST[$param_name]=charset_decode_utf_8($_REQUEST[$param_name]);
		}
	function setParams()
		{
		$fulltext='/^[ -~\xA\xD]*$/i';//match printable ASCII + LF and CR
		$this
			->addParam('sectionname','/^[a-z][_a-z0-9 ]{1,62}$/i')
			->addParam('owner','/^[a-z][_a-z ]{1,62}$/i')
			->addParam('description','/^[&#;a-z0-9 ]{0,127}$/i')
			->addParam('Sort','/^[a-z0-9]{1,16}$/i')
			->addParam('groups','','')
			->addParam('attr','','')
			->addParam('text',$fulltext,'')

			->addParam('action','/^[a-z]{1,64}$/i','')
			->addParam('confirm','/^[a-z]{1,3}$/i','')
			;
		}
	function EditSection()
		{
		PStepFormSection::PStepFormSection();

		if(
			!$this->wasParamSet('sectionname') ||
			!Sections::Exists($this->getParam('sectionname')) ||
			!($this->getParam('action')=="edit" ||$this->getParam('action')=="remove")
			)
				{//f1
				$this->Step='Step 1 - Select section and action';
				$this->TheForm->Insert( Sections::SectionsFieldSet() );
				$this->TheForm->Insert(
					FieldSet('Select Action')
						->Insert(
							Array2Inputs(
								array(
									array('text'=>'Edit', 'value'=>'edit', 'checked'=>'checked'),
									array('text'=>'Remove', 'value'=>'remove')
									),
								'action',
								'value','text',
								'radio'
								)
						)
					)
					;
				$this->TheForm->Insert(new PInput("submit","Go",""));
				}
			else//$this->getParam('sectionname') != "" and ( $this->getParam('action') == edit or remove )
				{
				$this->TheForm
					->Insert(new PInput("hidden","yes","confirm"))
					->Insert(new PInput("hidden",$this->getParam('sectionname'),"sectionname"))
					;
				if($this->getParam('action')=="edit")
						if( !(  $this->wasParamSet('confirm') && $this->getParam('confirm')=="yes"  ) )
								{
								$this->Step='Step 2 - edit section "'.$this->getParam('sectionname').'"';
								$this->TheForm
									->Insert(new PInput("hidden","edit","action"))
									;
								$section=Sections::Section($this->getParam('sectionname'));
								$description=$section["Description"];
								$grps=Main()->DB->fetch_all_query
									(
									"select Name from Groups ".
									"where ID in ".
									"(select GroupID from GroupSections where SectionName='".$this->getParam('sectionname')."')"
									);
								$gr="";
								foreach($grps as $a_gr)
									$gr.=$a_gr['Name'].", ";
								$T=new PTable();
										$T->addCell()->Insert(new PText("Section Name:"));
										$T->addCell()->Insert(new PText($this->getParam('sectionname')));
										$T->addCell();
									$T->AddRow();
										$T->addCell()->Insert(new PText("Description:"));
										$T->addCell()->Insert(new PInput("text",$description,"description"));
										$T->addCell()->Insert(new PText("use ' a-z' 127 chars max"));
									$T->AddRow();
										$T->addCell()->Insert(new PText("Sorting string:"));
										$T->addCell()->Insert(new PInput("text",$section['Sort'],"Sort"));
										$T->addCell()->Insert(new PText("use 'a-z0-9' 16 chars max"));
									$T->AddRow();
										$T->addCell()->Insert(new PText("Current configuration:"));
									$T->AddRow();
										$T->addCell()
											->Insert(
												Object(new PFieldSet(new PText('Attributes')))
													->Insert(
														new PText(
															(Sections::isHidden($this->getParam('sectionname'))?'':'not ').'hidden, '
															)
														)
													->Insert(
														new PText(
															(Sections::isBookmarked($this->getParam('sectionname'),0)?'':'not ').'bookmarked, '
															)
														)
												)
											;
										$T->addCell()->Insert(
												FieldSet('Owner:')
													->Insert( new PText(Sections::Owner($this->getParam('sectionname'))) )
												);
										$T->addCell()->Insert(
											FieldSet("Groups:")
												->Insert( new PText($gr) )
											);
									$T->AddRow();
										$T->addCell()->Insert(new PText("New configuration:"));
									$T->AddRow();
										$T->addCell()
											->Insert(
												FieldSet('Attributes')
													->Insert(
														Array2Inputs(
															array(
																array('text'=>'Hidden', 'value'=>'Hidden'),
																array('text'=>'Bookmarked', 'value'=>'Bookmarked', 'checked'=>'checked')
																),
															'attr'
															)
													)
												)
											;
										$T->addCell()->Insert( Sections::SectionsFieldSet("owner","Select Owner Section:") );
										$T->addCell()->Insert( Groups::GroupsFieldSet() );
								$this->TheForm
									->Insert($T)
									->Insert(
										new PBBCodeInput(
											$this->Params['text'][3]?$this->getParam('text'):$section['BBCode'],
											'text',
											'textContent'
											)
										)
									;
								}
							else
								{//$this->getParam('confirm')=="yes"
								if(!Sections::Exists($this->getParam('owner')))
									{
									$this->TheForm->Insert(new PText("Owner Section '".$this->getParam('owner')."' does not exits."));
									return;
									}
								if(eregi("^[&#259;a-z0-9 ]{0,127}$",$this->getParam('description'))==false)
									{
									$this->TheForm->Insert(new PText("'".$this->getParam('description')."' does not follow '^[&#259;a-z0-9 ]{0,127}$'"));
									return;
									}
								Sections::RemoveFromGroups($this->getParam('sectionname'));
								Sections::Add2Groups($this->getParam('sectionname'),$this->getParam('groups'));
								Main()->DB->query(
									"UPDATE `Sections` SET ".
											"`Owner` = '".$this->getParam('owner').
											"', `Description` = '".$this->getParam('description').
											"', `Sort` = '".$this->getParam('Sort').
										"' WHERE `Name` ='".$this->getParam('sectionname')."'"
									);
								Sections::unHide($this->getParam('sectionname'));
								Sections::unBookmark($this->getParam('sectionname'));
								if(array_key_exists('attr',$_REQUEST) )
									{
									$attr=$this->getParam('attr');
									if(array_key_exists('Hidden',$attr) && $attr['Hidden']=='Hidden')
										Sections::Hide($this->getParam('sectionname'));
									if(array_key_exists('Bookmarked',$attr) && $attr['Bookmarked']=='Bookmarked')
										Sections::Bookmark($this->getParam('sectionname'));
									$this->TheForm->Insert(new PText("Section '".$this->getParam('sectionname')."' modified."));
									}
								Main()->DB->query(
									"UPDATE `Sections` SET `BBCode` = '".$this->getParam('text')."',
`HTML` = '".Sections::BBCode2HTML($this->getParam('text'))."' WHERE `Name` ='".$this->getParam('sectionname')."'"
									);
								$this->Step='Step 3 - Editing done!';
								return;
								}
					else//$this->getParam('action'=="remove"
						if(   !( $this->wasParamSet('confirm') && $this->getParam('confirm')=="yes" )   )
								{
								$this->Step='Step 2 - Really want to delete?';
								$this->TheForm
									->Insert(new PInput("hidden","remove","action"))
									;
								$this->TheForm
									->Insert(new PText("Do you really want to remove section '".$this->getParam('sectionname')."' ?<br/>"))
									->Insert(
										Sections::Link2("EditSection","I don't want to remove","NO")
										)
									->Insert(new PText(" | "))
									->Insert(new PInput("submit","YES",""))
									;
								}
							else//$this->getParam('confirm')=="yes"
								{
								Sections::Remove($this->getParam('sectionname'));
								$this->TheForm
									->Insert(new PText("Section '".$this->getParam('sectionname')."' removed! "))
									->Insert(
										Sections::Link2("EditSection","Edit another section","Click here to edit another section.")
										)
									;
								$this->Step='Step 3 - Removing done!';
								return;
								}
				}
		}
	}
?>