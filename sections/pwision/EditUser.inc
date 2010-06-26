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
/** 	The EditUser class is designed to model the section that allows a user to edit an appointer.
	*	\latexonly \label{PWision:Sections:EditUser} \index{EditUser} \index{user} \endlatexonly
	*	\brief Edit an appointer .
	*	\version 1.1.3
	*	\todo implement user edit
	*/
class EditUser extends PStepFormSection
	{
	function setParams()
		{
		$this
			->addParam('ID','/^[0-9]{1,10}$/','')
			->addParam('action','/^[a-z]{1,64}$/i','')
			->addParam('confirm','/^[a-z]{1,64}$/i','')
			->addParam("username",'/^[-@._a-z0-9 ]{1,64}$/i','')
			->addParam("Password",'/^[a-z0-9 ]{1,64}$/i','')
			->addParam('groups','','')//this param is checked in Users::Add2groups()
			;
		}
	/// constructor
	function EditUser()
		{
		PStepFormSection::PStepFormSection();
		$userinfo=array();
		if( $this->wasParamSet('ID') && ($userinfo=Users::UserInfo($this->getParam('ID')) ) )
				{
				$table=Object(new PTable())
						->setAtr("border",'1')
					->setCaptionText('User data');

					$table->addCell()->Insert(new PText("ID") );
					$table->addCell()->Insert(new PText("name") );
					$table->addCell()->Insert(new PText("password") );
					$table->addCell()->Insert(new PText("Member of ") );

				$table->addRow();
					$table->addCell()->Insert(new PText($userinfo['ID']) );
					$table->addCell()->Insert(new PText($userinfo['Name']) );
					$table->addCell()->Insert(new PText($userinfo['Password']) );
						{$gr="";
						foreach($userinfo['Groups'] as $a_gr)
							$gr.=$a_gr['Name'].", ";
					$table->addCell()->Insert(new PText($gr) );}

				if( $this->wasParamSet('action') )
						if( $this->getParam('action')=='remove' )
								{
								$this->Step='Step 3 - Removing user';
								if( Users::Remove( $this->getParam('ID') ) > 0 )
									{
									$this->Step='Step 3 - Remove done';
									$this->AddMessage('Remove of user ['. $this->getParam('ID') .'] successfull!');
									}
								}
							else// $_REQUEST['action'] != 'remove'
								if( $this->wasParamSet('confirm') && $this->getParam('confirm')=='yes' )
										{
										$this->Step='Step 4 - Editing user data';
										Users::RemoveFromGroups( $this->getParam('ID') );
										Users::Add2Groups( $this->getParam('ID'), $this->getParam('groups') );
										Users::ReName( $this->getParam('ID'), $this->getParam('username') );
										Users::SetPassword( $this->getParam('ID'), $this->getParam('Password') );
										$this->TheForm->Insert(
											JSRedirect2Section(
												'EditUser',
												Object(new PURLAttributes)
													->setAtr( 'ID', $this->getParam('ID') )
													->setAtr( 'action', 'edit' )
												)
											);
										}
									else
										{
										$this->Step='Step 3 - Edit user data';
										$table->addRow();
											$table->addCell();
											$table->addCell()->Insert(new PInput('text',$userinfo['Name'],'username'));
											$table->addCell()->Insert(new PInput('text',$userinfo['Password'],'Password'));
											$table->addCell()->Insert(
												Object(new PFieldSet(new PText('Select Groups')))
													->Insert( Array2Inputs(Main()->UserInfo['Groups'], "groups[]", "ID", "Name", 'checkbox', new PSimpleTag("br")) )
												);
										$this->TheForm
											->Insert( $table )
											->Insert( new PInput('hidden',$userinfo['ID'],'ID') )
											->Insert( new PInput('hidden','edit','action') )
											->Insert( new PInput('hidden','yes','confirm') )
											->Insert( new PInput('submit','Go to Step 4!','') )
											;
										}
					else// $_REQUEST['action'] not set
						{
						$this->Step='Step 2 - Select the action';

						$this->TheForm
							->Insert( $table )
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
							->Insert(new PInput('hidden',$userinfo['ID'],'ID'))
							->Insert( new PInput("submit","Action Selected!","") )
							;
						}
				}
			else// $_REQUEST['ID'] not set or user not found
				{
				$this->Step='Step 1 - Enter the ID number of the user';
				if($this->wasParamSet('ID')) $this->AddMessage('user ['. $this->getParam('ID') .'] does not exist!');
				$this->TheForm
					->Insert( new PInput('text','','ID') )
					->Insert( new PInput("submit","Go to Step 2!","") )
					;
				}
		}
	}
?>