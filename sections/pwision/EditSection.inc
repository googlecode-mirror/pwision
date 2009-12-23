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
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
/** 	The EditSection class is designed to model the section that allows a user to edit the sections of the website.
	*	\latexonly \label{PWision:Sections:EditSection} \index{EditSection} \endlatexonly
	*	\brief a section editor.
	*	\version 1.2.0
	*/
class EditSection extends PStepFormSection
	{
	function setParams()
		{
		$this
			->addParam('sectionname','/^[a-z][_a-z ]{1,62}$/i')
			->addParam('owner','/^[a-z][_a-z ]{1,62}$/i')
			->addParam('description','/^[a-z0-9 ]{0,127}$/i')
			->addParam('groups')
			->addParam('attr')

			->addParam('action','/^[a-z]{1,64}$/i')
			->addParam('confirm','/^[a-z]{1,3}$/i')
			;
		}
	function EditSection()
		{
		PBasicFormSection::PBasicFormSection();

		if(
			!isset($_REQUEST['sectionname']) ||
			!Sections::Exists($_REQUEST['sectionname']) ||
			!($_REQUEST['action']=="edit" ||$_REQUEST['action']=="remove")
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
			else//$_REQUEST['sectionname'] != "" si $_REQUEST['action'] == edit sau remove
				{
				$this->TheForm
					->Insert(new PInput("hidden","yes","confirm"))
					->Insert(new PInput("hidden",$_REQUEST['sectionname'],"sectionname"))
					;
				if($_REQUEST['action']=="edit")
						if( !(isset($_REQUEST['confirm']) && $_REQUEST['confirm']=="yes") )
								{
								$this->Step='Step 2 - edit section "'.$_REQUEST['sectionname'].'"';
								$this->TheForm
									->Insert(new PInput("hidden","edit","action"))
									;
								$section=Sections::Section($_REQUEST['sectionname']);
								$description=$section["Description"];
								$grps=Main()->DB->fetch_all_query
									(
									"select Name from Groups ".
									"where ID in ".
									"(select GroupID from GroupSections where SectionName='".$_REQUEST['sectionname']."')"
									);
								$gr="";
								foreach($grps as $a_gr);
									$gr.=$a_gr['Name'].", ";
								$T=new PTable();
										$T->addCell()->Insert(new PText("Section Name:"));
										$T->addCell()->Insert(new PText($_REQUEST['sectionname']));
										$T->addCell();
									$T->AddRow();
										$T->addCell()->Insert(new PText("Description:"));
										$T->addCell()->Insert(new PInput("text",$description,"description"));
										$T->addCell()->Insert(new PText("use ' a-z' 127 chars max"));
									$T->AddRow();
										$T->addCell()->Insert(new PText("Current configuration:"));
									$T->AddRow();
										$T->addCell()
											->Insert(
												Object(new PFieldSet(new PText('Attributes')))
													->Insert(
														new PText(
															(Sections::isHidden($_REQUEST['sectionname'])?'':'not ').'hidden, '
															)
														)
													->Insert(
														new PText(
															(Sections::isBookmarked($_REQUEST['sectionname'],0)?'':'not ').'bookmarked, '
															)
														)
												)
											;
										$T->addCell()->Insert(
												FieldSet('Owner:')
													->Insert( new PText(Sections::Owner($_REQUEST['sectionname'])) )
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
									$T->AddRow();
										$T->addCell();
										$T->addCell()->Insert(new PInput("submit","Save!",""));
								$this->TheForm->Insert($T);
								}
							else
								{//$_REQUEST['confirm']=="yes"
								if(!Sections::Exists($_REQUEST['owner']))
									{
									$this->TheForm->Insert(new PText("Owner Section '".$_REQUEST['owner']."' does not exits."));
									return;
									}
								if(eregi("^[a-z ]{0,127}$",$_REQUEST['description'])==false)
									{
									$this->TheForm->Insert(new PText("'".$_REQUEST['description']."' does not follow '^[a-z ]{0,127}$'"));
									return;
									}
								Sections::RemoveFromGroups($_REQUEST['sectionname']);
								Sections::Add2Groups($_REQUEST['sectionname'],$_REQUEST['groups']);
								Main()->DB->query(
									"UPDATE `Sections` SET `Owner` = '".$_REQUEST['owner']."',
`Description` = '".$_REQUEST['description']."' WHERE `Name` ='".$_REQUEST['sectionname']."'"
									);
								Sections::unHide($_REQUEST['sectionname']);
								Sections::unBookmark($_REQUEST['sectionname']);
								if(array_key_exists('attr',$_REQUEST) )
									{
									$attr=$_REQUEST['attr'];
									if(array_key_exists('Hidden',$attr) && $attr['Hidden']=='Hidden')
										Sections::Hide($_REQUEST['sectionname']);
									if(array_key_exists('Bookmarked',$attr) && $attr['Bookmarked']=='Bookmarked')
										Sections::Bookmark($_REQUEST['sectionname']);
									$this->TheForm->Insert(new PText("Section '".$_REQUEST['sectionname']."' modified."));
									}
								$this->Step='Step 3 - Editing done!';
								return;
								}
					else//$_REQUEST['action']=="remove"
						if( !(isset($_REQUEST['confirm']) && $_REQUEST['confirm']=="yes") )
								{
								$this->Step='Step 2 - Really want to delete?';
								$this->TheForm
									->Insert(new PInput("hidden","remove","action"))
									;
								$this->TheForm
									->Insert(new PText("Do you really want to remove section '".$_REQUEST['sectionname']."' ?<br/>"))
									->Insert(
										Sections::Link2("EditSection","I don't want to remove","NO")
										)
									->Insert(new PText(" | "))
									->Insert(new PInput("submit","YES",""))
									;
								}
							else//$_REQUEST['confirm']=="yes"
								{
								Sections::Remove($_REQUEST['sectionname']);
								$this->TheForm
									->Insert(new PText("Section '".$_REQUEST['sectionname']."' removed! "))
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