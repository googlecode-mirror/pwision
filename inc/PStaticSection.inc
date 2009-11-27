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
include_once("PSection.inc");
/** 	The PStaticSection class is designed to model  a section of the website whose chapters are saved in 'sections/[sectionName]/chapter[no].html'. Each chapter has a title stored in 'sections/[sectionName]/chapter[no]Title.html'.
	*	\latexonly \label{PWision:PStaticSection} \index{PStaticSection} \index{chapter} \index{file} \endlatexonly
	*	\brief a HTML section of the website.
	*	\version 3.0.1
	*/
class PStaticSection extends PSection
	{
	/// section Name
	private $sectionName;
	/**
		*	\brief get section name
		*/
	function getName()
		{
		return $this->sectionName;
		}
	/**	Initialisates sectionName and loads the chapters.
		*	\brief  initialisation method.
		*	\param $sectionName section's name
		*/
	function PStaticSection($sectionName)
		{
		$this->sectionName=$sectionName;
		$this->Load();
		PSection::PSection();
		}


	private $Description="<br/><br/>";
	/**	the Description of the section.
			*	\brief section's description.
			*	\return the description text
			*	\note the description is loaded from DB by PSection::getDescription() or from a file by PStaticSection::Load().
			*/
	function getDescription()
		{
		return $this->Description;
		}

	/// chapters title
	private $chapterTitle=array(0=>null,1=>null,2=>null,3=>null,4=>null);
	/// chapters content
	private $chapter=array(0=>null,1=>null,2=>null,3=>null,4=>null);
	
	/**	Gets the content of a file.
		*	\brief load file content.
		*	\param $filename the name of the file
		*	\return the content of the file
		*/
	private static function LoadContent($filename)
		{
		$handle = fopen($filename, "r");
		$content = fread($handle, filesize($filename));
		fclose($handle);
		return $content;
		}
	
	/**	Loads the chapters from 'sections/[sectionName]/chapter[no].html'.
		*	\brief Loads the chapters.
		*	\version 1.2
		*	\return reference to $this
		*/
	protected function Load()
		{
		$sectionName=$this->getName();
		// chapters 0 to 4
		$found_a_chapter=false;
		for($i=5;$i--;)
			{
			$filename="sections/$sectionName/Chapter$i.html";
			if( file_exists($filename) )
				{
				$found_a_chapter=true;
				$this->chapter[$i]=new PText( PStaticSection::LoadContent($filename) );
				}
			$filename="sections/$sectionName/Chapter".$i."Title.html";
			if( file_exists($filename) )
				{
				$found_a_chapter=true;
				$this->chapterTitle[$i]=new PText( PStaticSection::LoadContent($filename) );
				}
			}
		if($found_a_chapter==false)
			$this->chapter[0]=new PText("no chapters for $sectionName found<br/>");
			
		// description
		$filename="sections/$sectionName.html";
		$this->Description=PStaticSection::LoadContent($filename);
		if($this->Description=="")
			$this->Description=PSection::getDescription();
		
		return $this;
		}

	function	Chapter0Title(){return $this->chapterTitle[0];}
	function	Chapter0(){return $this->chapter[0];}

	function	Chapter1Title(){return $this->chapterTitle[1];}
	function	Chapter1(){return $this->chapter[1];}

	function	Chapter2Title(){return $this->chapterTitle[2];}
	function	Chapter2(){return $this->chapter[2];}

	function	Chapter3Title(){return $this->chapterTitle[3];}
	function	Chapter3(){return $this->chapter[3];}

	function	Chapter4Title(){return $this->chapterTitle[4];}
	function	Chapter4(){return $this->chapter[4];}

	}
?>