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
include_once("inc/Groups.inc");
include_once('inc/PRedirectSection.inc');
/** 	The EditGroup class is designed to model the section that allows a user to edit an group.
	*	\latexonly \label{PWision:Sections:EditGroup} \index{EditGroup} \index{group} \endlatexonly
	*	\brief Edit an group .
	*	\version 1.0.0
	*/
class EditGroup extends PStepFormSection
	{
	function setParams()
		{
		$this
			->addParam('ID','/^[0-9]{1,10}$/','')//number
			->addParam('action','/^[a-z]{1,64}$/i','')
			->addParam('confirm','/^[a-z]{1,64}$/i','')
			->addParam('Name','/^[a-z][_a-z ]{1,62}$/i','')
			->addParam('Description','/^[&#;a-z0-9 ]{0,127}$/i','')
			;
		}
	/// constructor
	function EditGroup()
		{
		PStepFormSection::PStepFormSection();
		if( $this->wasParamSet('ID') && $this->wasParamSet('action') )
				if( $this->getParam('action') == 'remove' )
						{
						$this->Step='Step 2 - Group '. $this->getParam('ID') .' Removed';
						Groups::Remove( $this->getParam('ID') );
						}
					else
						if( $this->wasParamSet('confirm') && $this->getParam('confirm')=='yes' )
								{
								$this->Step='Step 3 - Saving group data';
								Groups::Edit($this->getParam('ID'), $this->getParam('Name'), $this->getParam('Description'));
								$this->AddMessage(
										JSRedirect2Section(
											'EditGroup',
											Object(new PURLAttributes)
												->setAtr( 'ID', $this->getParam('ID') )
												->setAtr( 'action', 'edit' )
											)
									);
								}
							else
								{
								$this->Step='Step 2 - Edit group data';
								$info=Groups::Info( $this->getParam('ID') );
								$table=Object(new PTable())
									->setCaptionText('Group data');
									$table->addCell()->Insert(new PText('Group Name'));
									$table->addCell()->Insert( new PInput('text',$info['Name'],'Name') );
								$table->addRow();
									$table->addCell()->Insert(new PText('Description'));
									$table->addCell()->Insert( new PInput('text',$info['Description'],'Description') );
								$table->addRow();
									$table->addCell()->Insert(new PText('Users'));
									$table->addCell()->Insert(
										new PText( implode(', ',array_column($info['Users'],'Name')) )
										);
								$table->addRow();
									$table->addCell()->Insert(new PText('Sections'));
									$table->addCell()->Insert(
										new PText( implode(', ',array_column($info['Sections'],'Name')) )
										);
								$this->TheForm
									->Insert( new PInput('hidden',$this->getParam('ID'),'ID') )
									->Insert( new PInput('hidden','edit','action') )
									->Insert( new PInput('hidden','yes','confirm') )
									->Insert($table)
									->Insert( new PInput("submit","Save!","") )
									;
								}
			else
				{
				$this->Step='Step 1 - Select the group and the action';
				$this->TheForm
					->Insert(Groups::GroupsFieldSet('ID','Select Groups','radio'))
					->Insert(
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
					->Insert( new PInput("submit","Go to Step 2!","") )
					;
				}
		}
	}
?>