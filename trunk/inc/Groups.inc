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


/**	A namespace for groups relation functions.
	*	\brief groups's namespace.
	*	\version 1.2.0
	*/
final class Groups
	{
	/**	Adds a new item into Groups table.
		*	\brief Create a new group.
		*	\param $name the name of the group
		*	\param $description text
		*	\return the ID of the new group
		*/
	static function Create( $name, $description='')
		{
		Main()->DB->query("INSERT INTO `Groups` (`Name`,`Description`) VALUES ('$name','$description')");
		return mysql_insert_id();
		}
	/**
		*	\brief edit a user.
		*	\param $ID id of the group
		*	\param $name the new name of the group
		*	\param $description the new description of the group
		*/
	static function Edit($ID, $name, $description='')
		{
		Main()->DB->query("UPDATE `Groups` SET  `Name` =  '$name', `Description` = '$description' WHERE  `ID` = $ID");
		}
	/**	Removes all the users from this group, then removes all the sections from this group and finally removes the group the Groups table.
		*	\brief Removes a group.
		*	\param $ID id of the group
		*/
	static function Remove($ID)
		{
		//remove all the users from this group
		Main()->DB->query("DELETE FROM `GroupUsers` WHERE `ID` = '$ID'");
		//remove all the sections from this group
		Main()->DB->query("DELETE FROM `GroupSections` WHERE `GroupID` = '$ID'");
		//remove the group the Groups table
		Main()->DB->query("DELETE FROM `Groups` WHERE `ID` = '$ID'");
		}
	/**
		*	\brief get the group information
		*	\param $ID id of the group
		*	\return array('ID','Description','Users','Sections')
		*/
	static function Info($ID)
		{
		$ret=Main()->DB->fetch_array_query("SELECT * FROM Groups WHERE ID='$ID'");
		if($ret)
			{
			$ret['Users']=Main()->DB->fetch_all_query
				('SELECT Users.Name `Name`
					FROM GroupUsers, Users
					WHERE
					GroupUsers.GroupID='.$ID.' and
					GroupUsers.UserID=Users.ID' );
			$ret['Sections']=Main()->DB->fetch_all_query
				('SELECT SectionName `Name`
					FROM GroupSections
					WHERE
					GroupSections.GroupID='.$ID );
			return $ret;
			}
		return null;
		}
	/**
		*	\brief get the group information
		*	\param $Name name of the group
		*	\return array('ID','Description','Users','Sections')
		*/
	static function InfoByName($Name)
		{
		$ret=Main()->DB->fetch_array_query("SELECT * FROM Groups WHERE Name='$Name'");
		if($ret)
			return Groups::Info($ret['ID']);
		return null;
		}
	/**	Gets a fieldset with inputs for all the groups of the website.
		*	\brief a fieldset with all the groups.
		*	\version 1.0.2
		*	\param $name name of the input
		*	\param $legend the text of the <b>legend</b> element
		*	\param $input_type the <b>input</b> elements type
		*	\return a PFieldSet object containing a PInput object for every group of the website
		*/
	static function GroupsFieldSet( $name="groups[]", $legend="Select Groups", $input_type="checkbox" )
		{
		$GroupBox=new PFieldSet(new PText($legend));
		$Groups=Main()->DB->fetch_all_query("select * from Groups");
		return $GroupBox->Insert( Array2Inputs($Groups, $name, "ID", "Name", $input_type, new PSimpleTag("br")) );
		}
	}
?>