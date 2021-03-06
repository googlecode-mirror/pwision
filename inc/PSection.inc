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
include_once("PMainComponent.inc");
include_once('BBCode.inc');


/**	The PSection_ParamNCheck class is thrown by PSection::CheckParams() function if a parameter of a section doesn't check the associated regular expresion.
	*	\latexonly \label{PWision:PSection_ParamNCheck} \index{PSection} \index{section} \index{website} \index{webpage} \index{parameters} \endlatexonly
	*	\brief parameter doesn't check.
	*/
class PSection_ParamNCheck extends Exception
	{
	}

/** 	The PSection class is designed to model a section of the website. A section has a name, a description and is splitted in 5 chapters (numbered 0 to 4).
	*	\latexonly \label{PWision:PSection} \index{PSection} \index{section} \index{website} \endlatexonly
	*	\brief a section of the website.
	*	\version 4.3.2
	*	\note it will be derived in files X.inc from sections/ as X class
	*/
class PSection
	{
	/// section information from DB
	protected $Info;

	/// The Message
	private $Message="";
		/**	Adds a new message.
			*	\brief Adds a new message.
			*	\version 1.0.1
			*	\param $text the message text
			*	\return reference to $this
			*/
		function AddMessage($text)
			{
			if($text && $text!='')$this->Message.=($text."<br/>");
			return $this;
			}
		/**	Gets the Message, followed , if != "", by a horizontal line
			*	\brief gets all the messages
			*	\version 1.1.0
			*/
		function getMessages()
			{
			$ret=$this->Message;
			if($ret=="")return $ret;
				else return $ret."<hr/>";
			}

			/**	This is an arrays of arrays(matrix). For each parameter(identified by a string for example $name) we have the array $this->Params[$name] (see addParam() ):
			<ul>
				<li>$this->Params[$name][0] - parameter name</li>
				<li>$this->Params[$name][1] - regular expresion</li>
				<li>$this->Params[$name][2] - error message text</li>
				<li>$this->Params[$name][3] - true if this param was set at last CheckParams()</li>
				<li>$this->Params[$name][4] - true if this param checked the reg_exp at last CheckParams()</li>
				<li>$this->Params[$name][5] - not set message</li>
			</ul>
				*	\brief parameters of the section
				*/
			protected $Params=array();
			/**
				*	\brief adds a parameter for the section.
				*	\version 2.0.1
				*	\param $param_name the name of the parameter
				*	\param $reg_exp the regular expresion that must be matched
				*	\param $not_set_message the message if the parameter is not set(defined)
				*	\param $error_message the message if the parameter doesn't check
				*	\return reference to $this
				*	\note if the reg_exp if '' it will be not checked
				*/
			protected function & addParam( $param_name, $reg_exp='', $not_set_message=null, $error_message=null )
				{
				if($error_message===null)$error_message=lang("Parammeter")." '$param_name' ".lang("has an illegal value!");
				if($not_set_message===null)$not_set_message=lang("Parammeter")." '$param_name' ".lang("is not set!");
				$this->Params[$param_name]=array(
					$param_name, // parameter name
					$reg_exp,  // regular expresion
					$error_message, // error message text
					false , // true if this param was set at last CheckParams()
					false ,// true if this param checked the reg_exp at last CheckParams()
					$not_set_message // not set message
					);
				return $this;
				}
	/**	This method is called by the constructor to set the arguments of the form, using addParam(), for future extraction.
		*	\brief sets the arguments of the form.
		*/
	function setParams(){}
	/**	This method is called by the CheckParams() before checking the regexp.
		*	\note params should be accessed by $_REQUEST[]
		*	\brief preprocess a param.
		*	\param $param_name a parameter that is set
		*	\return nothing
		*/
	protected function preprocessParam($param_name)
		{}
	/**	Checks all the params that are set if they match the asociate regular expresion. If a param doesn't check, exception PSection_ParamNCheck with the apropiate message is thrown.
		*	\brief checks the arguments of the sections.
		*	\version 1.2.3
		*	\return true if all parameters are set and match their regular expresion
		*/
	protected function CheckParams()
		{
		$parameters_are_set=true;
		foreach($this->Params as $param_name => &$param)
			if( isset($_REQUEST[$param[0]]) )
				{
				$param[3]=true; // $param[0] set
				$this->preprocessParam($param_name);
				if( $param[1]!='' )
					{
					$param[4]=false;
					$check=preg_match( $param[1], $_REQUEST[$param[0]] );
					if($check==0 || $check==FALSE)
						throw new PSection_ParamNCheck($param[2]);
					$param[4]=true;
					}
				}
				else
					{
					$param[3]=false;// $param[0] not set
					//$param[4]=false;// if a param is not set then it does not check the reg_exp
					$this->AddMessage($param[5]);
					$parameters_are_set=false;
					}
		return $parameters_are_set;
		}
		/// contains the URL path to the article
		protected $URLPath='';
		/// a PContent object that contains the Path as html anchors
		protected $theLocation=null;
		/**	This function constructs the $URLPath and $theLocation members.
			*	\brief construct the location members.
			*	\return nothing
			*/
		protected function ConstructLocation()
			{
// 			$this->theLocation=Sections::PathLinks($this->getName(),'&rsaquo;');
			$ret=Sections::PathArray2LinksURL(Sections::PathArray($this->getName()));
			$this->theLocation=$ret[0];
			$this->URLPath=$ret[1];
			}
	/**	This method is called by the constructor if all par of the section are set <i>and matched</i>.
		*	\brief if parameters are set.
		*/
	function if_parameters_are_set()
		{
		$this->ConstructLocation();
		}
	/**	This method is called by the constructor if not all par of the section are set, <i>but all that are set are also matched with their regular expresion</i>.
		*	\brief if not all parameters are set.
		*/
	function if_not_all_parameters_are_set(){}
	/**	This method is called by the constructor if PSection_ParamNCheck is thrown. By default it retrows the exception so it will be catched in PBasicWebPage::setSection().
		*	\brief PSection_ParamNCheck thrown.
		*/
	function param_NCheck(PSection_ParamNCheck &$e)
		{
		throw $e;
		}
	/**
		*	\brief  initialisation method.
		*	\version 2.0.1
		*/
	function PSection()
		{
		$this->Info = Sections::Section( $this->getName() );
		$this->setParams();
		try
			{
			if($this->CheckParams())
					$this->if_parameters_are_set();
				else
					$this->if_not_all_parameters_are_set();
			}
		catch(PSection_ParamNCheck $e) { $this->param_NCheck($e);}
		}
	/**	The section name is the name of the class.
		*	\brief get section name.
		*	\version 1.1.0
		*	\note not using get_class($this) because PStaticSection class is used to load static sections!
		*/
	function getName()
		{
		return Main()->getSectionName();
		}
	/**	The section name is the title of the class.
		*	\brief get the title section.
		*	\return the title of the section
		*/
	function getTitle()
		{
		return lang($this->getName());
		}
	/**	
		*	\brief get the location of the section
		*	\return a Sections::PathLinks() structure
		*/
	function getLocation($separator="&rsaquo; " )
		{
		return $this->theLocation;
		}
	/**	Get the content of a param if set.
		*	\brief get the content of a section parameter.
		*	\param $param_name the name of the parameter
		*	\return parameter value or '' if the parameter is not set
		*/
	function getParam($param_name)
		{
		return isset($_REQUEST[$param_name])?$_REQUEST[$param_name]:'';
		}
	/**	Get the value of $Params[$param_name][3].
		*	\brief was a parameter set?
		*	\param $param_name the name of the parameter
		*	\return true or false
		*/
	function wasParamSet($param_name)
		{
		return $this->Params[$param_name][3];
		}
	/**	Get the value of $Params[$param_name][4].
		*	\brief did a parameter checked its regular expresion?
		*	\param $param_name the name of the parameter
		*	\return true or false
		*/
	function didParamCheckedRegExp($param_name)
		{
		return $this->Params[$param_name][4];
		}
	/**	Get the content of a param if checked.
		*	\brief get the content of a section parameter.
		*	\param $param_name the name of the parameter
		*	\return parameter value or null if the parameter is not set
		*/
	function getCheckedParam($param_name)
		{
		return didParamCheckedRegExp($param_name)?$_REQUEST[$param_name]:null;
		}
	/**	Gets the subsections of current section.
		*	\brief the subsections
		*	\param $mother the container element for the subsections(by default it is an <b>ul</b> element)
		*	\param $kid the container element for each subsection(by default it is a <b>li</b> element)
		*	\return an element containing the subsections
		*/
	function AccesibleSubSections(IContent $mother=null, IInsertAbleCloneAble $kid=null)
		{ if($mother==null)$mother=new PElement("ul"); if($kid==null)$kid=new PElement("li");

		$ret= new PFieldSet(Sections::PathLinks($this->getName()));
		$SubSects=new PStructure($kid,$mother);
		$SubSectsArray=Sections::AccesibleNotHiddenSubSections($this->getName(),$_SESSION['userID']);
		foreach($SubSectsArray as $section)
			{
			$SubSects->newKid()->Insert(Sections::Link2SQLSection($section));
			}
		$subsect_no=count($SubSectsArray);
		if($subsect_no==0)return null;
		$SubSects->newKid()->Insert(
				DivEText("$subsect_no ".lang("subsection".( ($subsect_no!=1)?"s":"" )." found") )
					->setAtr("class","subsections_number")
			);
		return $ret->Insert($SubSects);
		}

	/**	The returned object will be inserted into the head element of the webpage. This function can be used to add an additional CSS or JavaScript that is needed for the section to display/work.
		*	\brief head content.
		*	\return a PDrawable object
		*/
	function Head()
		{
		return new PContent;
		}

	/**	the Description of the section .
			*	\brief section's description.
			*	\return the description text
			*/
	function getDescription()
		{
		return lang($this->Info['Description']);
		}

	/**
		*	\brief title of preamble of the section
		*	\version 1.2.2
		*/
	function	Chapter0Title(){
		$ret=new PContent();
		return $ret;
		}
	/**
		*	\brief preamble of the section
		*	\version 1.1.5
		*/
	function	Chapter0(){
		$ret=new PContent();
			$ret->Insert(new PText($this->getMessages()));
		$html=new PText($this->Info['HTML']);
			if(get_class($this)=='PSection')
					{
					if($_SERVER['REQUEST_URI']!=$this->URLPath)
						{
						header('HTTP/1.1 301 Moved Permanently');
						header('Location: http://'.$_SERVER['SERVER_NAME'].$this->URLPath
							); /* Redirect browser */
						exit;
						}
					if( ($html==null || $html=='') )
						{
						$html= El('div')
							->setAtr('class','subsections')
							;
						$ul=new PStructure(new PElement("li"), new PElement("ul"));
						$SectsArray=Sections::AccesibleNotHiddenSubSections($this->getName(),$_SESSION['userID']);
						if(count($SectsArray)!=0)
							{
							$html
								->Insert(
									El('h4')
										->Insert(new PText( lang('Subsections of').' '.lang($this->getName()) ) )
									)
								;
							foreach($SectsArray as $section)
								$ul->newKid()->Insert(Sections::Link2SQLSection($section));
							}
						$html->Insert($ul);
						}
					}
		$ret->Insert( $html );
		return $ret;
		}

	/// \brief title of chapter 1 of the section
	function	Chapter1Title(){return new PContent;}
	/// \brief chapter 1 of the section
	function	Chapter1(){return new PContent;}

	/// \brief title of chapter 2 of the section
	function	Chapter2Title(){return new PContent;}
	/// \brief chapter 2 of the section
	function	Chapter2(){return new PContent;}

	/// \brief title of chapter 3 of the section
	function	Chapter3Title(){return new PContent;}
	/// \brief chapter 3 of the section
	function	Chapter3(){return new PContent;}

	/// \brief title of chapter 4 of the section
	function	Chapter4Title(){return new PContent;}
	/// \brief chapter 4 of the section
	function	Chapter4(){return new PContent;}

	}



/**	A namespace for section relation functions.
	*	\latexonly \label{PWision:Sections} \endlatexonly
	*	\brief section's namespace.
	*	\version 4.4.0
	*/
final class Sections
	{
	/**	Check if $section_name is formed only of maximum 63 letters and space.
		*	\brief section name check
		*	\version 1.0.1
		*	\param $section_name the name of the section
		*	\return true if ok, else false
		*/
	static function CheckName( $section_name="Root" )
		{
		if(preg_match('/^[a-z][_a-z0-9 ]{1,62}$/i',$section_name) == false || $section_name=="")
				{
				//print("checking of $section_name failed");
				return false;
				}
			else
				return true;
		}
	/**	Creates a new section of the website by adding it to Sections table and to its groups.
		*	\latexonly \label{PWision:Sections:Create} \endlatexonly
		*	\brief create a section
		*	\version 2.1.0
		*	\param name name of the new section(must not exist, e.g. a new name)
		*	\param owner owner section of the new section(must exist)
		*	\param descr description text "^[a-z ]{0,127}$"
		*	\param grp_arr array of group numbers
		*	\param $attr attributes(bookmarked,hidden)
		*	\param $type type of the section: ['section'], 'xml'
		*	\return true if success
		*/
	static function Create( $name, $owner, $descr="", $grp_arr=null,$attr=null, $Type='section' )
		{
		if($grp_arr==null)$grp_arr=array();
		if($attr==null)$attr=array();
		if(
			!Sections::CheckName($name) ||
			!Sections::CheckName($owner) ||
			//(eregi("^[a-z ]{0,127}$",$descr)==false) ||
			//(count($grp_arr)==0) ||
			Sections::Exists($name) ||
			!Sections::Exists($owner) /*||
			(eregi("^[01]{1}$",$hidden)==false)*/
			)
				return false;
		Main()->DB->query("INSERT INTO `Sections` (`Name`, `Owner`, `Type`, `Description`, `BBCode`, `HTML`) VALUES ('$name', '$owner', '$Type', '$descr', '', '')");
		Sections::Add2Groups($name,$grp_arr);
		if(array_key_exists('Hidden',$attr) && $attr['Hidden']=='Hidden')Sections::Hide($name);
		if(array_key_exists('Bookmarked',$attr) && $attr['Bookmarked']=='Bookmarked')Sections::Bookmark($name);
		return true;
		}
	/**	Gets the row of the section from the Sections database table.
		*	\brief information about a section.
		*	\version 1.1.1
		*	\param $section_name the name of the section
		*	\return an array containing the row, false if the $section_name does not check as a section name
		*/
	static function Section( $section_name="Root" )
		{
		if(!Sections::CheckName($section_name))return false;
		if($section_name!='Root')
			return Main()->DB->fetch_array_query("SELECT * FROM Sections WHERE Name='$section_name'");
			else return array('Name'=>'Root','Owner'=>'Root','Type'=>'section','Description'=>lang('Root'), 'BBCode'=>'', 'HTML'=>'');
		}
	/** Set the description field of a section.
		*	\brief set the description of a section.
		*	\param $section_name the name of the section
		*	\param $Description the description text of the section
		*/
	static function setDescription($section_name,$Description)
		{
		Main()->DB->query(
			"UPDATE `Sections` SET `Description` = '$Description' WHERE `Name` ='$section_name'"
			);
		}
	/** Set the owner field of a section.
		*	\brief set the Owner section of a section.
		*	\param $section_name the name of the section
		*	\param $Owner the Owner section
		*/
	static function setOwner($section_name,$Owner)
		{
		if(!$Owner)$Owner='Root';
		Main()->DB->query(
			"UPDATE `Sections` SET `Owner` = '$Owner' WHERE `Name` ='$section_name'"
			);
		}
	/** Set the Sort field of a section.
		*	\brief set the sort of a section.
		*	\param $section_name the name of the section
		*	\param $Sort the sort string of the section
		*/
	static function setSort($section_name,$Sort)
		{
		Main()->DB->query(
			"UPDATE `Sections` SET `Sort` = '$Sort' WHERE `Name` ='$section_name'"
			);
		}
	/** Set the BBCode field of a section.
		*	\brief set the BBCode of a section.
		*	\param $section_name the name of the section
		*	\param $BBCode the BBCode string of the section
		*/
	static function setBBCode($section_name,$BBCode)
		{
		Main()->DB->query(
			"UPDATE `Sections` SET `BBCode` = '$BBCode', `HTML` = '".BBCode::BBCode2HTML($BBCode)."' WHERE `Name` ='$section_name'"
			);
		}
	/** Set the HTML field of a section.
		*	\brief set the HTML of a section.
		*	\param $section_name the name of the section
		*	\param $HTML the HTML string of the section
		*/
	static function setHTML($section_name,$HTML)
		{
		Main()->DB->query
// 		print
			(
			"UPDATE `Sections` SET `HTML` = '".mysql_real_escape_string ($HTML)."' WHERE `Name` ='$section_name'"
			);
		}
	/**	For every group ID from $grp_arr this function creates a pair (<i>section name</i>, <i>group ID</i>) and inserts it in GroupSections database table, making section $section_name member of the group with that ID.
		*	\latexonly \label{PWision:Sections:Add2Groups} \endlatexonly
		*	\brief adds a section to groups.
		*	\version 1.0.1
		*	\param $section_name the name of the section
		*	\param $grp_arr an array containing the group IDs
		*/
	static function Add2Groups( $section_name, $grp_arr )
		{
		$Values="";
		foreach($grp_arr as $grp)
			if(preg_match("`^[1-9][0-9]{0,10}$`",$grp))//grp is a number
				$Values=$Values.",('$section_name','$grp')";
		$Values[0]=' ';
		Main()->DB->query("INSERT INTO `GroupSections` (`SectionName`, `GroupID`) VALUES $Values;");
		}
	/**	Deletes from GroupSections all the pairs containing the section $section_name.
		*	\brief removes a section from all groups.
		*	\param $section_name the name of the section to be removed
		*/
	static function RemoveFromGroups( $section_name )
		{
		Main()->DB->query("DELETE FROM `GroupSections` WHERE `SectionName` = '$section_name'");
		}
	/**	Hide a section.
		*	\brief hide a section.
		*	\param $section_name the name of the section to be hidden
		*/
	static function Hide( $section_name )
		{
		Main()->DB->query("UPDATE `Sections` SET Hidden=1 WHERE `Name` = '$section_name'");
		}
	/**	Checks if a section is in HiddenSections table.
		*	\brief checks if a section is hidden.
		*	\param $section_name name of the section
		*	\return true or false
		*/
	static function isHidden( $section_name="Root" )
		{
		if(!Sections::CheckName($section_name))return false;
		$row=Main()->DB->fetch_array_query( "SELECT Hidden, Type FROM Sections WHERE Name='$section_name'");
		if($row['Hidden']=='1' || $row['Type']=='xml') return true;
		return false;
		}
	/**	Deletes from HiddenSections table the section $section_name.
		*	\brief unhide a section.
		*	\param $section_name the name of the section to be unhidden
		*/
	static function unHide( $section_name )
		{
		Main()->DB->query("UPDATE `Sections` SET Hidden=0  WHERE `Name` = '$section_name'");
		}

//---------BOOKMARKS
	/**	Bookmark a section by inserting it in the UserBookmarkedSections table.
		*	\brief bookmark a section.
		*	\param $section_name the name of the section to be bookmarked
		*	\param $UserID the user's id
		*/
	static function Bookmark( $section_name, $UserID=0 )
		{
		Main()->DB->query("INSERT INTO `UserBookmarkedSections`(`SectionName`,`UserID`) VALUES ('$section_name',$UserID)");
		}
	/**	Checks if a section is in UserBookmarkedSections table.
		*	\brief checks if a section is bookmarked.
		*	\version 1.0.2
		*	\param $section_name name of the section
		*	\param $UserID the user's id
		*	\return true or false
		*/
	static function isBookmarked( $section_name="Root", $UserID =0)
		{
		if(!Sections::CheckName($section_name))return false;
		if(!preg_match("`^[0-9]{1,10}$`",$UserID))return false;
		$row=Main()->DB->fetch_array_query(
			"select SectionName from UserBookmarkedSections where `SectionName` = '$section_name' and (UserID='$UserID' or UserID='0')"
			);
		if($row) return true;
		return false;
		}
	/**	Deletes from UserBookmarkedSections table the section $section_name.
		*	\brief unBookmark a section.
		*	\param $section_name the name of the section to be unhidden
		*	\param $UserID the user's id
		*/
	static function unBookmark( $section_name, $UserID=0  )
		{
// 		if($UserID=='*')
				Main()->DB->query("DELETE FROM `UserBookmarkedSections` WHERE `SectionName` = '$section_name'");
// 			elseif($UserID>0)
// 				Main()->DB->query("DELETE FROM `UserBookmarkedSections` WHERE `SectionName` = '$section_name' AND UserID='$UserID'");
		}
//--------------------

/**	First the section is removed fromm all groups, then it is unhidden, then it is deleted from the Sections database table.
		*	\brief removes a section from the database.
		*	\version 1.1.0
		*	\param $section_name the name of the section to be removed
		*/
	static function Remove( $section_name )
		{
		Sections::RemoveFromGroups($section_name);
		Sections::unHide($section_name);
		Sections::unBookmark($section_name,'*');
		Main()->DB->query("DELETE FROM `Sections` WHERE `Name` = '$section_name'");
		}
	/**	Gets the Owner field from the section information row.
		*	\brief gets the owner of a section.
		*	\param $section_name name of the section
		*	\return the section name of its owner
		*	\note The owner of Root is Root!
		*/
	static function Owner( $section_name="Root" )
		{
		if(!Sections::CheckName($section_name))return false;
		if($section_name=="Root")return "Root";
		$row=Main()->DB->fetch_array_query( "SELECT * FROM Sections WHERE Name='$section_name'");
		if($row) return $row["Owner"];
		return false;
		}
	/**	A section exists if it has an owner.
		*	\brief checks if a section exists.
		*	\param $section_name the name of the section
		*	\return true if the section exists, else false
		*/
	static function Exists ($section_name="Root" )
		{
		return Sections::Owner($section_name) != false;
		//return true;
		}

	/**	Gets the sections that have as Owner $section_name.
		*	\brief the subsections of a section.
		*	\version 1.0.1
		*	\param $section_name the name of the section
		*	\return an array containing the subsections with full information
		*/
 	static function SubSections( $section_name="Root" )
		{
		if(!Sections::CheckName($section_name)) return false;
		return Main()->DB->fetch_all_query( "SELECT * FROM Sections WHERE Owner='$section_name' order by `Sort`");
		}

	/**	Gets the sections that have as Owner $section_name and are accesible by the user with $UserID.
		*	\note see the <i>access rule</i> in Users::hasAccess()
		*	\brief the subsections of a section that are accesible by an user.
		*	\version 1.0.2
		*	\param $section_name the name of the section
		*	\param $UserID the user's id
		*	\return an array containing the accesible subsections with full information
		*/
	static function AccesibleSubSections( $section_name="Root", $UserID=0 )
		{
		if(!Sections::CheckName($section_name)) return false;
		return Main()->DB->fetch_all_query(
/*			"SELECT * FROM Sections WHERE Owner='$section_name' and ".
					"(".
					"select Count(*) from GroupSections where SectionName=Sections.Name ".
						" and GroupID in ".
							"(select GroupID from GroupUsers where UserID='$UserID')".
					")>0".
				' order by `Sort`'*/
"SELECT * FROM Sections 
JOIN GroupSections ON GroupSections.SectionName=Sections.Name
JOIN GroupUsers ON GroupUsers.GroupID = GroupSections.GroupID
WHERE  
Sections.Owner ='$section_name' AND Sections.Type <>'xml'
GroupUsers.UserID ='$UserID' 
order by Sort, SectionName"
			);
		}
	/**	Gets the sections that have as Owner $section_name, are accesible by the user with $UserID and are not hidden.
		*	\brief the subsections of a section that are accesible by an user and not hidden.
		*	\version 1.0.3
		*	\param $section_name the name of the section
		*	\param $UserID the user's id
		*	\return an array containing the accesible not hidden subsections with full information
		*/
	static function AccesibleNotHiddenSubSections( $section_name="Root", $UserID=0 )
		{
		if(!Sections::CheckName($section_name)) return false;
		return Main()->DB->fetch_all_query(
/*			"SELECT * FROM Sections WHERE Owner='$section_name' and ".
					"( Sections.Name NOT IN " .
						"(select SectionName from HiddenSections ) ".
					")".
				" and ".
					"(".
					"select Count(*) from GroupSections where SectionName=Sections.Name ".
						" and GroupID in ".
							"(select GroupID from GroupUsers where UserID='$UserID')".
					")>0".
				' order by `Sort`'*/
"SELECT * FROM Sections 
JOIN GroupSections ON GroupSections.SectionName=Sections.Name
JOIN GroupUsers ON GroupUsers.GroupID = GroupSections.GroupID
WHERE  
Sections.Owner ='$section_name' AND Sections.Hidden=0 AND Sections.Type <>'xml' AND 
GroupUsers.UserID ='$UserID' 
GROUP BY SectionName
order by Sort, SectionName
"

			);
		}

	/**	the bookmarked sections of a user combined with those of used 0(guest).
		*	\brief the accesible bookmarked sections.
		*	\version 1.0.2
		*	\param $UserID the user's id
		*	\return an array containing the accesible bookmarked sections with full information
		*/
	static function AccesibleBookmarkedSections( $UserID=0 )
		{
		return Main()->DB->fetch_all_query(
			/*"SELECT * FROM Sections WHERE ".
					"( Sections.Name IN " .
						"(select SectionName from UserBookmarkedSections ".
							"where UserBookmarkedSections.UserID='$UserID' or UserBookmarkedSections.UserID='0'".
						") ".
					")".
				" and ".
					"(".
					"select Count(*) from GroupSections where GroupSections.SectionName=Sections.Name ".
						" and GroupSections.GroupID in ".
							"(select GroupID from GroupUsers where GroupUsers.UserID='$UserID')".
					")>0".
				' order by `Sort`'*/
"SELECT * FROM Sections 
JOIN UserBookmarkedSections ON Sections.Name=UserBookmarkedSections.SectionName
JOIN GroupSections ON GroupSections.SectionName=Sections.Name
JOIN GroupUsers ON GroupUsers.GroupID = GroupSections.GroupID
WHERE  
Sections.Type <>'xml' AND 
(UserBookmarkedSections.UserID='0' OR UserBookmarkedSections.UserID='0') AND 
GroupUsers.UserID ='0' 
order by Sort, Sections.Name"
			);
		}

	/**	Constructs an hyperlink to a section from a SQL section information.
		*	\brief hyperlink to a SQL section information.
		*	\version 1.0.4
		*	\param $section array containing section information, that may have been return by Section() function.
		*	\return an <b>a</b> element with a hyper reference to the section.
		*/
	static function Link2SQLSection( $section)
		{
		$ret;
		switch($section['Type'])
			{
			case 'section':
				return Sections::Link2($section['Name'],lang($section['Description']));
				break;
			case 'xml':
					$ret=El('span');
				break;
			default:
					$ret=El("a")->setAtr("href","index.php?section=". $section['Owner']. "#". $section['Name']);
				break;
			}
		$ret
				->setAtr("title",lang($section['Description']))
			->Insert(
				El('span')
					->Insert(
						PTextlang($section['Name'])
						)
				);
		return $ret;
		}
	/**	Constructs an hyperlink to a section.
		*	\brief hyperlink to a section.
		*	\param $section_name the name of the section
		*	\param $title title of the link
		*	\param text text of the link(by default $section_name used). If null, no content is inserted.
		*	\param attr attributes to link, besides <b>section=<i>section_name</i></b>
		*	\return an <b>a</b> element with a hyper reference to the section.
		*	\version 1.1.6
	 */
	static function Link2( $section_name="Root", $title="", $text="" , PURLAttributes $attr=null)
		{
		$section=Sections::Section($section_name);
		if($title=="")
			{
//			$section=Sections::Section($section_name);
			$title=lang($section['Description']);
			}
		if($attr==null)$attr=new PURLAttributes();
		
		$lnk;
		switch($section['Type'])
			{
			case 'section':
				$lnk=El('a')
						->setAtr( 'href', "/$section_name".$attr->Draw() );
				break;
			case 'xml':
					$lnk=El('span');
				break;
			default:
					$lnk=El("a")->setAtr("href","index.php?section=". $section['Owner']. "#". $section['Name']);
				break;
			}
				
		$lnk
				->setAtr( 'title', $title )
				->setAtr( 'class', "section $section_name")
				;
		
		if($text==="")
				$text=lang($section_name);
		if($text!=null)
			{
			$lnk
				->Insert(
					El('span')
						->Insert(new PText($text))
					)
				;
			}
		return $lnk;
		}
	/**	Gets the path to a section, starting with the Root section. Each section in the path is the owner of the next section in the path.
		*	\brief the path to a section from Root.
		*	\version 2.0
		*	\param $section_name the name of the section
		*	\return array of SQL section information arrays
		*/
	static function PathArray( $section_name="Root" )
		{
		$the_path=array();
		$sec=Sections::Section($section_name);
		$owner=Sections::Owner($section_name);
		$i=0;$max_depth=20;
		while($sec['Name']!="Root" && $sec['Name']!=$owner && $i<$max_depth)
			{
			array_push($the_path,$sec);
			$sec=Sections::Section($owner);
			$owner=$sec['Owner'];
			++$i;
			}
		array_push($the_path,
			Sections::Section('Root')
			);
		return array_reverse($the_path);
		}
	/**	Transforms a path array to hyperlinks separated by a separator string.
		*	\brief transform a path array to hyperlinks.
		*	\param $path_arr array of SQL section information arrays
		*	\param $separator a separator string that will be between hyperlinks
		*	\return an array 0:PContent object containing the hyperlinks, 1: URL
		*/
	static function PathArray2LinksURL( $path_arr=array(), $separator="&rsaquo; " )
		{
		$links=new PContent();
		$URL='';
		$the_path=$path_arr;
		foreach($the_path as $section)
			{
			$links
				->Insert(Sections::Link2SQLSection($section))
				->Insert(new PText($separator))
				;
			if($section['Name']!='Root')
				$URL=$URL.'/'.$section['Name'];
			}
		$links->Pop();
		return array($links,$URL);
		}
	/**	Transforms a path array to hyperlinks separated by a separator string.
		*	\brief transform a path array to hyperlinks.
		*	\version 1.0.1
		*	\param $path_arr array of SQL section information arrays
		*	\param $separator a separator string that will be between hyperlinks
		*	\return a PContent object containing the hyperlinks
		*/
	static function PathArray2Links( $path_arr=array(), $separator="&rsaquo; " )
		{
		$ret=Sections::PathArray2LinksURL($path_arr,$separator);
		$links=$ret[0];
		return $links;
		}
	/**	Gets the path to a section and then transforms it into hyperlinks separated by a separator string.
		*	\brief the path of hyperlinks to a section from Root.
		*	\param $section_name the name of the section
		*	\param $separator a separator string that will be between hyperlinks
		*	\return a PContent object containing the hyperlinks
		*/
	static function PathLinks( $section_name, $separator="&rsaquo; " )
		{
		return Sections::PathArray2Links(
			Sections::PathArray($section_name),
			$separator
			);
		}
	/**	Gets a fieldset with inputs for all the sections of the website.
		*	\brief a fieldset with all the sections.
		*	\version 1.0.2
		*	\param $name name of the input
		*	\param $legend the text of the <b>legend</b> element
		*	\param $input_type the <b>input</b> elements type
		*	\return a PFieldSet object containing a PInput object for every section of the website
		*	\todo make this show the sections tree with indentation
		*/
	static function SectionsFieldSet( $name="sectionname", $legend="Select a Section", $input_type="radio" )
		{
		$SectionBox=Object(new PFieldSet(new PText($legend)))
			->Insert(new PInput($input_type,"Root",$name))
			->Insert(Sections::Link2("Root"))
			->Insert( sEl("br") )
			;
		$Sections=Main()->DB->fetch_all_query("select * from Sections order by `Sort`");
		return $SectionBox
			->Insert( Array2Inputs($Sections, $name, "Name", "Name", $input_type, sEl("br")) );
		}
	}
?>