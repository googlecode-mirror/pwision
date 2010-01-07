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
include_once("PMainComponent.inc");
include_once("PBubble.inc");

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
	*	\version 3.1.0
	*	\note it will be derived in files X.inc from sections/ as X class
	*/
class PSection
	{
	/// section information from DB
	protected $Info;

			/// parameters of the section
			protected $Params=array();
			/**
				*	\brief adds a parameter for the section.
				*	\version 1.1.0
				*	\param $param_name the name of the parameter
				*	\param $reg_exp the regular expresion that must be matched
				*	\param $error_message the message if the parameter doesn't check
				*	\return reference to $this
				*/
			protected function & addParam( $param_name, $reg_exp='', $error_message=null )
				{
				if($error_message==null)$error_message="Parammeter '$param_name' has an illegal value!";
				array_push( $this->Params, array($param_name, $reg_exp, $error_message ) );
				return $this;
				}
	/**	This method is called by the constructor to set the arguments of the form, using addParam(), for future extraction.
		*	\brief sets the arguments of the form.
		*/
	function setParams(){}
	/**	Checks all the params that are set if they match the asociate regular expresion. If a param doesn't check, exception PSection_ParamNCheck with the apropiate message is thrown.
		*	\brief checks the arguments of the sections.
		*	\version 1.2.1
		*	\return true if all parameters are set and match their regular expresion
		*/
	protected function CheckParams()
		{
		$parameters_are_set=true;
		foreach($this->Params as $param)
			if( isset($_REQUEST[$param[0]]) )
				{
				if( $param[1]!='' )
					{
					$check=preg_match( $param[1], $_REQUEST[$param[0]] );
					if($check==0 || $check==FALSE)
						throw new PSection_ParamNCheck($param[2]);
					}
				}
				else
					{
					$this->AddMessage('Parammeter '.$param[0].' is not set!');
					$parameters_are_set=false;
					}
		return $parameters_are_set;
		}
	/**	This method is called by the constructor if all par of the section are set <i>and matched</i>.
		*	\brief if parameters are set.
		*/
	function if_parameters_are_set(){}
	/**	This method is called by the constructor if not all par of the section are set, <i>but all that are set are also matched with their regular expresion</i>.
		*	\brief if not all parameters are set.
		*/
	function if_not_all_parameters_are_set(){}
	/**	This method is called by the constructor if PSection_ParamNCheck is thrown.
		*	\brief PSection_ParamNCheck thrown.
		*/
	function param_NCheck(PSection_ParamNCheck &$e)
		{
		throw $e;
		}
	/**
		*	\brief  initialisation method.
		*	\version 2.0.0
		*/
	function PSection()
		{
		$this->Info = Sections::Section( $this->getName() );
		$this->setParams();
		try
			{
			$parameters_are_set=$this->CheckParams();
			if($parameters_are_set)
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
		return $this->getName();
		}
	/**	Get the content of a param if set.
		*	\brief get the content of a section parameter.
		*	\return parameter value or '' if the parameter is not set
		*/
	function getParam($param_name)
		{
		return isset($_REQUEST[$param_name])?$_REQUEST[$param_name]:'';
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
				DivEText("$subsect_no subsection".( ($subsect_no!=1)?"s":"" )." found")
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
		$ret=$this->Info['Description'];
		if($ret == null || $ret== "") $ret="<br/><br/>";
		return $ret;
		}

	/**
		*	\brief title of preamble of the section
		*	\version 1.2.0
		*/
	function	Chapter0Title(){
		$ret=new PContent();
		if(get_class($this)=="PSection")
			{
			$ret->Insert(new PText(Main()->SubsectionsTitle.' '.$this->getName() ) );
			}
		return $ret;
		}
	/**
		*	\brief preamble of the section
		*	\version 1.1.1
		*/
	function	Chapter0(){
		$ret=new PContent();
		if(get_class($this)=="PSection")
			{
			$ul=new PStructure(new PElement("li"), new PElement("ul"));
			$SectsArray=Sections::AccesibleNotHiddenSubSections($this->getName(),$_SESSION['userID']);
			if(count($SectsArray)==0)return $ret;
			foreach($SectsArray as $section)
				{
				$ul->newKid()->Insert(Sections::Link2SQLSection($section));
				}
			$ret->Insert($ul);
			}
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
	*	\version 3.0.0
	*/
final class Sections
	{
	/**	Check if $section_name is formed only of maximum 63 letters and space.
		*	\brief section name check
		*	\param $section_name the name of the section
		*	\return true if ok, else false
		*/
	static function CheckName( $section_name="Root" )
		{
		if(preg_match('/^[a-z][_a-z ]{1,62}$/i',$section_name) == false || $section_name=="")
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
		*	\version 2.0.0
		*	\param name name of the new section(must not exist, e.g. a new name)
		*	\param owner owner section of the new section(must exist)
		*	\param descr description text "^[a-z ]{0,127}$"
		*	\param grp_arr array of group numbers
		*	\param $attr attributes(bookmarked,hidden)
		*	\return true if success
		*/
	static function Create( $name, $owner, $descr="", $grp_arr=null,$attr=null )
		{
		if($grp_arr==null)$grp_arr=array();
		if($attr==null)$attr=array();
		if(
			!Sections::CheckName($name) ||
			!Sections::CheckName($owner) ||
			//(eregi("^[a-z ]{0,127}$",$descr)==false) ||
			(count($grp_arr)==0) ||
			Sections::Exists($name) ||
			!Sections::Exists($owner) /*||
			(eregi("^[01]{1}$",$hidden)==false)*/
			)
				return false;
		Main()->DB->query("INSERT INTO `Sections` (`Name`, `Owner`, `Type`, `Description`) VALUES ('$name', '$owner', 'section', '$descr');");
		Sections::Add2Groups($name,$grp_arr);
		if(array_key_exists('Hidden',$attr) && $attr['Hidden']=='Hidden')Sections::Hide($name);
		if(array_key_exists('Bookmarked',$attr) && $attr['Bookmarked']=='Bookmarked')Sections::Bookmark($name);
		return true;
		}
	/**	Gets the row of the section from the Sections database table.
		*	\brief information about a section.
		*	\param $section_name the name of the section
		*	\return an array containing the row, false if the $section_name does not check as a section name
		*/
	static function Section( $section_name="Root" )
		{
		if(!Sections::CheckName($section_name))return false;
		if($section_name!='Root')
			return Main()->DB->fetch_array_query("SELECT * FROM Sections WHERE Name='$section_name'");
			else return array('Name'=>'Root','Owner'=>'Root','Type'=>'section','Description'=>Main()->getRootName());
		}
	/**	For every group ID from $grp_arr this function creates a pair (<i>section name</i>, <i>group ID</i>) and inserts it in GroupSections database table, making section $section_name member of the group with that ID.
		*	\latexonly \label{PWision:Sections:Add2Groups} \endlatexonly
		*	\brief adds a section to groups.
		*	\param $section_name the name of the section
		*	\param $grp_arr an array containing the group IDs
		*/
	static function Add2Groups( $section_name, $grp_arr )
		{
		$Values="";
		foreach($grp_arr as $grp)
			if(eregi("^[1-9][0-9]{0,10}$",$grp))//grp is a number
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
	/**	Hide a section by inserting it in the HiddenSections table.
		*	\brief hide a section.
		*	\param $section_name the name of the section to be hidden
		*/
	static function Hide( $section_name )
		{
		Main()->DB->query("INSERT INTO `HiddenSections`(`SectionName`) VALUES ('$section_name')");
		}
	/**	Checks if a section is in HiddenSections table.
		*	\brief checks if a section is hidden.
		*	\param $section_name name of the section
		*	\return true or false
		*/
	static function isHidden( $section_name="Root" )
		{
		if(!Sections::CheckName($section_name))return false;
		$row=Main()->DB->fetch_array_query( "SELECT SectionName FROM HiddenSections WHERE SectionName='$section_name'");
		if($row) return true;
		return false;
		}
	/**	Deletes from HiddenSections table the section $section_name.
		*	\brief unhide a section.
		*	\param $section_name the name of the section to be unhidden
		*/
	static function unHide( $section_name )
		{
		Main()->DB->query("DELETE FROM `HiddenSections` WHERE `SectionName` = '$section_name'");
		}
//---------BOOKMARKS
	/**	Hide a section by inserting it in the HiddenSections table.
		*	\brief hide a section.
		*	\param $section_name the name of the section to be hidden
		*	\param $UserID the user's id
		*/
	static function Bookmark( $section_name, $UserID=0 )
		{
		Main()->DB->query("INSERT INTO `UserBookmarkedSections`(`SectionName`,`UserID`) VALUES ('$section_name',$UserID)");
		}
	/**	Checks if a section is in UserBookmarkedSections table.
		*	\brief checks if a section is bookmarked.
		*	\version 1.0.1
		*	\param $section_name name of the section
		*	\param $UserID the user's id
		*	\return true or false
		*/
	static function isBookmarked( $section_name="Root", $UserID =0)
		{
		if(!Sections::CheckName($section_name))return false;
		if(!eregi("^[0-9]{1,10}$",$UserID))return false;
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
		if($UserID=='*')
				Main()->DB->query("DELETE FROM `UserBookmarkedSections` WHERE `SectionName` = '$section_name'");
			elseif($UserID>0)
				Main()->DB->query("DELETE FROM `UserBookmarkedSections` WHERE `SectionName` = '$section_name' AND UserID='$UserID'");
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
		*	\param $section_name the name of the section
		*	\return an array containing the subsections with full information
		*/
 	static function SubSections( $section_name="Root" )
		{
		if(!Sections::CheckName($section_name)) return false;
		return Main()->DB->fetch_all_query( "SELECT * FROM Sections WHERE Owner='$section_name'");
		}

	/**	Gets the sections that have as Owner $section_name and are accesible by the user with $UserID.
		*	\note see the <i>access rule</i> in Users::hasAccess()
		*	\brief the subsections of a section that are accesible by an user.
		*	\param $section_name the name of the section
		*	\param $UserID the user's id
		*	\return an array containing the accesible subsections with full information
		*/
	static function AccesibleSubSections( $section_name="Root", $UserID=0 )
		{
		if(!Sections::CheckName($section_name)) return false;
		return Main()->DB->fetch_all_query(
			"SELECT * FROM Sections WHERE Owner='$section_name' and ".
					"(".
					"select Count(*) from GroupSections where SectionName=Sections.Name ".
						" and GroupID in ".
							"(select GroupID from GroupUsers where UserID='$UserID')".
					")>0"
			);
		}
	/**	Gets the sections that have as Owner $section_name, are accesible by the user with $UserID and are not hidden.
		*	\brief the subsections of a section that are accesible by an user and not hidden.
		*	\param $section_name the name of the section
		*	\param $UserID the user's id
		*	\return an array containing the accesible not hidden subsections with full information
		*/
	static function AccesibleNotHiddenSubSections( $section_name="Root", $UserID=0 )
		{
		if(!Sections::CheckName($section_name)) return false;
		return Main()->DB->fetch_all_query(
			"SELECT * FROM Sections WHERE Owner='$section_name' and ".
					"( Sections.Name NOT IN " .
						"(select SectionName from HiddenSections ) ".
					")".
				" and ".
					"(".
					"select Count(*) from GroupSections where SectionName=Sections.Name ".
						" and GroupID in ".
							"(select GroupID from GroupUsers where UserID='$UserID')".
					")>0"
			);
		}

	/**	the bookmarked sections of a user combined with those of used 0(guest).
		*	\brief the accesible bookmarked sections.
		*	\param $UserID the user's id
		*	\return an array containing the accesible bookmarked sections with full information
		*/
	static function AccesibleBookmarkedSections( $UserID=0 )
		{
		return Main()->DB->fetch_all_query(
			"SELECT * FROM Sections WHERE ".
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
					")>0"
			);
		}

	/**	Constructs an hyperlink to a section from a SQL section information.
		*	\brief hyperlink to a SQL section information.
		*	\param $section array containing section information, that may have been return by Section() function.
		*	\return an <b>a</b> element with a hyper reference to the section.
		*/
	static function Link2SQLSection( $section)
		{
		if($section['Type']=='section')
				return Sections::Link2($section['Name'],$section['Description']);
			else
				return
					El("a")
							->setAtr("href","index.php?section=". $section['Owner']. "#". $section['Name'])
							->setAtr("title",$section['Description'])
						->Insert(new PText($section['Name']));
		}
	/**	Constructs an hyperlink to a section.
		*	\brief hyperlink to a section.
		*	\param $section_name the name of the section
		*	\param $title title of the link
		*	\param text text of the link(by default $section_name used)
		*	\param attr attributes to link, besides <b>section=<i>section_name</i></b>
		*	\return an <b>a</b> element with a hyper reference to the section.
		*	\version 1.1.0
	 */
	static function Link2( $section_name="Root", $title="", $text="" , PURLAttributes $attr=null)
		{
		if($title=="")
			{
			$section=Sections::Section($section_name);
			$title=$section['Description'];
			}
		if($attr==null)$attr=new PURLAttributes();
		$lnk=El("a")
				->setAtr( "href", "index.php?section=$section_name".$attr->Draw() )
				->setAtr( "title", $title ) ;
		if($text=="")
			if($section_name!="Root")
					$text=$section_name;
				else//$section_name == "Root"
					$text=Main()->getRootName();
		return $lnk->Insert(new PText($text));
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
		*	\return a PContent object containing the hyperlinks
		*/
	static function PathArray2Links( $path_arr=array(), $separator="&rsaquo; " )
		{
		$links=new PContent();
		$the_path=$path_arr;
		foreach($the_path as $section)
			$links
				->Insert(Sections::Link2SQLSection($section))
				->Insert(new PText($separator))
				;
		$links->Pop();
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
		*	\version 1.0.1
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
		$Sections=Main()->DB->fetch_all_query("select * from Sections");
		return $SectionBox
			->Insert( Array2Inputs($Sections, $name, "Name", "Name", $input_type, sEl("br")) );
		}
	}
?>