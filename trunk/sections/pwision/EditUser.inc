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
include_once('inc/PRedirectSection.inc');
/** 	The EditUser class is designed to model the section that allows a user to edit an appointer.
	*	\latexonly \label{PWision:Sections:EditUser} \index{EditUser} \index{office} \endlatexonly
	*	\brief Edit an appointer .
	*	\version 1.0.0
	*	\todo user edit
	*/
class EditUser extends PStepFormSection
	{
	/// constructor
	function EditUser()
		{
		PBasicFormSection::PBasicFormSection();
		if( isset($_REQUEST['ID']) && preg_match('/^[0-9]{1,10}$/',$_REQUEST['ID'])==1 && ($userinfo=Users::UserInfo($_REQUEST['ID'])) )
				if( isset($_REQUEST['action']) )
						if($_REQUEST['action']=='remove')
								{
								$this->Step='Step 3 - Removed tried';
								if(Users::Remove($_REQUEST['ID'])>0)
									{
									$this->Step='Step 3 - Remove done';
									$this->AddMessage('Remove of user ['.$_REQUEST['ID'].'] successfull!');
									}
								}
							else// $_REQUEST['action'] != 'remove'
								{
	/*							if(
									(
									$edit=Users::EditUser(
										$_REQUEST['ID'],....
											)
									)>0)
									{
									$this->AddMessage('Edit successfull!');
									}*/
								$this->AddMessage('Edit user not implemented yet!');
								}
					else// $_REQUEST['action'] not set
						{
						$this->Step='Step 2 - Select the action';
						
						//show user info
						$table=Object(new PTable())
							->setAtr("border",'1');
						
						$table->addCell()->Insert(new PText("ID") );
						$table->addCell()->Insert(new PText($userinfo['ID']) );
						
						$table->addRow();
						$table->addCell()->Insert(new PText("name") );
						$table->addCell()->Insert(new PText($userinfo['Name']) );

						$table->addRow();
						$table->addCell()->Insert(new PText("Member of ") );
							$grps=Main()->DB->fetch_all_query
								("	SELECT DISTINCT Name 
									FROM Groups, GroupUsers
									WHERE
									Groups.ID=GroupUsers.GroupID and
									UserID=".$userinfo['ID'] );
							$gr="";
							foreach($grps as $a_gr)
								$gr.=$a_gr['Name'].", ";
						$table->addCell()->Insert(new PText($gr) );
						
						$this->TheForm
							->Insert( 
								El('p')
									->Insert( El('span')->Insert(
										new PText(' Here is some info about the user you want to edit or remove:') ) )
									->Insert( $table )
								)
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
			else// $_REQUEST['ID'] not set
				{
				$this->Step='Step 1 - Enter the ID number of the user';
				$this->TheForm
					->Insert( new PInput('text','','ID') )
					->Insert( new PInput("submit","Go to Step 2!","") )
					;
				}
		}
	}
?>