<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2009--11 Becheru Petru-Ioan

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
include_once("PMainComponent.inc");
/**	A namespace for user relation functions.
	*	\brief user's namespace.
	*	\version 1.7.0
	*/
final class Users
	{
	/**	Creates a new user for the website and makes it member to some groups.
		*	\brief create an user.
		*	\version 1.1.0
		*	\param $UserName name of the user
		*	\param $Password password of the user
		*	\param $CreatorID user id of the creator of the user
		*	\param $grp_arr array of group IDs
		*	\return the new user's id on succes, 0 is $UserName allready exists
		*/
	static function Create( $UserName, $Password, $CreatorID, $grp_arr )
		{
		//user exists?
		$row=Main()->DB->fetch_array_query("SELECT * FROM Users WHERE Name='$UserName'");
		if($row==false)
			{
			Main()->DB->query("INSERT INTO `Users` (`Name`, `Password`,`CreatorUserID`) VALUES ('$UserName', '$Password', $CreatorID)");
			$uid=mysql_insert_id();
			Users::Add2Groups($uid,$grp_arr);
			return $uid;
			}
		return 0;
		}
	/**	Delete a user from the Users database table after removing it from the groups.
		*	\brief removes an user from the database.
		*	\version 1.1.0
		*	\param $UserID the identification number of the user to be deleted
		*/
	static function Remove( $UserID )
		{
		Users::RemoveBookmarks($UserID);
		Users::RemoveFromGroups( $UserID );
		Main()->DB->query("DELETE FROM `Users` WHERE `ID` = '$UserID'");
		return 1;
		}
	/**	Change the username of user with $UserID.
		*	\brief rename a user.
		*	\version 1.0.0
		*	\param $UserID the identification number of the user to be renamed
		*	\param $UserName the new username
		*/
	static function ReName( $UserID, $UserName)
		{
		Main()->DB->query("UPDATE `Users` SET  `Name` =  '$UserName' WHERE  `ID` = $UserID");
		return 1;
		}
	/**	Change the password of user with $UserID.
		*	\brief change the password.
		*	\version 1.0.0
		*	\param $UserID the identification number of the user
		*	\param $Password the new password
		*/
	static function SetPassword( $UserID, $Password)
		{
		Main()->DB->query("UPDATE `Users` SET  `Password` =  '$Password' WHERE  `ID` = $UserID");
		return 1;
		}
	/**	Deletes from <b>UserBookmarkedSections</b> sections of the user.
		*	\brief removes user's bookmarks.
		*	\param $UserID the identification number of the user
		*/
	static function RemoveBookmarks( $UserID )
		{
		Main()->DB->query("DELETE FROM `UserBookmarkedSections` WHERE UserID='$UserID'");
		}
	/**	For every group ID from $grp_arr this function creates a pair (<i>user id</i>, <i>group ID</i>) and inserts it in GroupUsers database table, making the user with $uid ID member of the group with that ID.
		*	\note see the <i>access rule</i> in Users::hasAccess()
		*	\note a regular expresion check is done to see if the array items are numbers. Needed because CreateUser and EditUser can't check each item of group array param.
		*	\brief adds an user to some groups.
		*	\version 1.0.1
		*	\param $uid user id of the user
		*	\param $grp_arr array of group IDs
		*/
	static function Add2Groups( $uid, $grp_arr )
		{
		$Values="";
		$values_found=false;
		foreach($grp_arr as $grp)
			if(preg_match('/^[0-9]{1,10}$/',$grp))//grp is a number
				{
				$values_found=true;
				$Values=$Values.",('$uid','$grp')";
				}
		if($values_found==false) return;
		$Values[0]=' ';
		Main()->DB->query("INSERT INTO `GroupUsers` (`UserID`, `GroupID`) VALUES $Values;");
		}
	/**	Deletes from GroupUsers all the pairs containing the user id.
		*	\brief removes an user from all groups.
		*	\param $id the identification number of the user to be deleted
		*/
	static function RemoveFromGroups( $id )
		{
		Main()->DB->query("DELETE FROM `GroupUsers` WHERE `UserID` = '$id'");
		}
	/**	Checks if the user $UserName has the password $Password.
		*	\brief check if a (user, password) pair.
		*	\version 1.0.1
		*	\param $UserName the name of the user
		*	\param $Password the password for the user
		*	\return the user's ID on succes, 0 insucces, -1 regexp missmatch
		*/
	static function CheckUserPass( $UserName, $Password )
		{
		if(preg_match("`^[-@._a-z0-9 ]{1,64}$`i",$UserName)==false) return -1;
		if(preg_match("`^[a-z0-9 ]{1,64}$`i",$Password)==false) return -1;
		$row=Main()->DB->fetch_array_query
			("SELECT * FROM Users WHERE Name='$UserName'");
		if($row && $row['Password']==$Password)
			return $row['ID'];
		return 0;
		}
	/**	Checks if a user is active by searching for its ID in Inactive database table.
		*	\brief check if a user is active.
		*	\param $Id the user id
		*	\return true if it is active, else false
		*/
	static function IsActive( $Id )
		{
		$row=Main()->DB->fetch_array_query
			("SELECT * FROM Inactive WHERE UserID='$Id'");
		return $row['UserID'] != $Id ;
		}
	/**	Gets the user's row from the Users database table.
		*	\brief get the user information.
		*	\version 1.0.2
		*	\param $id the ID of the user
		*	\return an array containing the row
		*/
	static function UserInfo( $id )
		{
		$ret=Main()->DB->fetch_array_query
			("SELECT * FROM Users WHERE ID='$id'");
		if($ret)
			{
			$ret['Groups']=Main()->DB->fetch_all_query
				('SELECT Groups.ID, Name
					FROM Groups, GroupUsers
					WHERE
					Groups.ID=GroupUsers.GroupID and
					UserID='.$id );
			return $ret;
			}
		return null;
		}
	/**	Gets the user's row from the Users database table.
		*	\brief get the user information.
		*	\version 1.0.0
		*	\param $Name name of the user
		*	\return an array containing the row
		*/
	static function UserInfoByName( $Name )
		{
		$ret=Main()->DB->fetch_array_query
			("SELECT * FROM Users WHERE Name='$Name'");
		if($ret)
			{
			$ret['Groups']=Main()->DB->fetch_all_query
				('SELECT Groups.ID, Name
					FROM Groups, GroupUsers
					WHERE
					Groups.ID=GroupUsers.GroupID and
					UserID='.$ret['ID'] );
			return $ret;
			}
		return null;
		}
	/**	Checks if a user has access to a section.
		*	\par Access Rule
		*		<i>A user has access to a section if it is member of a group that the section is also member of</i>!
		*	\brief Check if a user has access to a section.
		*	\param $UserID user's id
		*	\param $SectionName Sec name
		*	\return true if it has
		*/
	static function hasAccess( $UserID, $SectionName )
		{
		$row= Main()->DB->fetch_array_query
// 			(
// 			"select GroupID from GroupSections where SectionName='$SectionName' ".
// 				" and GroupID in ".
// 			"(select GroupID from GroupUsers where UserID='$UserID')"
// 			);
						("
			SELECT UserID, SectionName
FROM GroupUsers
JOIN  `GroupSections` ON GroupUsers.`GroupID` = GroupSections.GroupID
WHERE GroupSections.SectionName =  '$SectionName'
AND GroupUsers.UserID ='$UserID'
			");

		return $row['UserID']!=null;
		}
	/**	Checks if a user is member of a group.
		*	\brief Check if a user is in a group.
		*	\param $UserID user's id
		*	\param $GroupName Sec name
		*	\return true if it has
		*/
	static function inGroup( $UserID, $GroupName )
		{
		$row= Main()->DB->fetch_array_query
			(
			"SELECT GroupID from Groups, GroupUsers Where UserID='$UserID' AND Groups.Name='$GroupName' AND GroupUsers.GroupID=Groups.ID
			"
			);
		return $row['GroupID']!=null;
		}
	/**	The login process: if Users::CheckUserPass() returns an ID of an user(a number > 0), the session variable <b>userID</b> is assigned that ID.
		*	\brief try to login a user.
		*	\param $UserName the name of the user
		*	\param $Password the password of the user
		*	\return true on succes, else false
		*/
	static function LogIn( $UserName, $Password )
		{
		$Chk=Users::CheckUserPass($UserName,$Password);
		if($Chk>0)
				{
				$_SESSION['userID']=$Chk;
				return true;
				}
		sleep(1);
		return false;
		}
	/**	The logout process: the session variable <b>userID</b> is assigned 0 (the ID of the Guest user).
		*	\brief log out a user.
		*/
	static function LogOut()
		{
		$_SESSION['userID']=0;
		//$_SESSION['message']="Logged out(now u are a guest)";
		}
	}
?>