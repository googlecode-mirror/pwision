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

include_once("inc/PRedirectSection.inc");
include_once("inc/PTable.inc");
include_once("inc/Users.inc");

/** 	The MyUsers class is designed to be model a section that shows the users created by a user.
	*	\latexonly \label{PWision:Sections:MyUsers} \index{MyUsers} \index{user} \endlatexonly
	*	\brief MyUsers section.
	*	\version 1.0.0
	*/
class MyUsers extends PSection
	{
	/// the users created by this user
	protected $UsersTable;
	/**	Constructs the $Users table.
		*	\brief constructor
		*/
	function MyUsers()
		{
		PSection::PSection();
		$this->UsersTable=Object(new PTable())
				->setAtr("border",'1')
			->setCaptionText('Users');

			$this->UsersTable->addCell()->Insert(new PText("ID") );
			$this->UsersTable->addCell()->Insert(new PText("name") );
			$this->UsersTable->addCell()->Insert(new PText("password") );

		$Users=Main()->DB->fetch_all_query("SELECT * FROM Users WHERE CreatorUserID='".Main()->UserInfo['ID']."'");
		foreach($Users as $User)
			{
			$this->UsersTable->AddRow();
			$this->UsersTable->addCell()->Insert(new PText($User['ID']) );
			$this->UsersTable->addCell()->Insert(
				Sections::Link2(
					'EditUser',
					'',
					$User['Name'],
					Object(new PURLAttributes)
						->setAtr('ID',$User['ID'])
					)
				);
			$this->UsersTable->addCell()->Insert(new PText($User['Password']) );
			}
		}
	function	Chapter1()
		{
		return parent::Chapter1()
			->Insert($this->UsersTable)
			;
		}
	}
?>