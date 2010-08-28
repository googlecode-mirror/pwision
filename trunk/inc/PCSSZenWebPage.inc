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
include_once("PBasicWebPage.inc");

/** 	The PCSSZenWebPage class is designed to model the <a href="http://www.csszengarden.com">www.csszengarden.com</a> website layout so we can use the themes provided by this website.
	*	\latexonly \label{PWision:PCSSZenWebPage} \index{PCSSZenWebPage} \index{webpage} \index{layout} \index{theme} \index{css zen garden} \endlatexonly
	*	\brief a themed webpage.
	*	\version 3.1.0
	*	\par Example:
\code
include_once("PCSSZenWebPage.inc");
print( );
\endcode
	*	\par Output:
\verbatim
\endverbatim
	*/
abstract class PCSSZenWebPage extends PBasicWebPage
	{
	/**	gets the current location.
		*	\brief Current location
		*	\return a PContent object contaning the location
		*/
	protected function Location()
		{
		return Object(new PContent)
// 				->Insert(new PText(""))
				->Insert(Sections::PathLinks($this->getSectionName()))
// 				->Insert(new PText(""))
			;
		}
	/**	Constructs
		*	\brief constructor
		*/
	function PCSSZenWebPage()
		{
		PBasicWebPage::PBasicWebPage();
		}
		protected function pwision_css()
			{
			// get theme number from UserInfo
			$no=$this->UserInfo["Theme"];
			//$no="138";
			/*
			my favourite numbers:
			001 069 020 025 097 063 195 091 092 138
			*/
			return new PText(" @import \"http://www.csszengarden.com/$no/$no.css\"; ");
			}
	/**	the body.
		*	\brief builds the body
		*	\version 1.0.0
		*	\return the <b>body</b> element
		*/
	protected function Body()
		{
		$ret=Object(new PElement("body"))
				->setAtr("id","css-zen-garden")
			->Insert($this->idContainer())
			->Insert($this->Body_ExtraDivs())
			;
		return $ret;
		}
	/// \brief container div
	protected function idContainer()
		{
		return Object(new PElement("div"))
				->setAtr("id","container")
			->Insert($this->idIntro())
			->Insert($this->idSupportingText())
			->Insert($this->idLinkList())
			;
		}
	/// \brief intro div
	protected function idIntro()
		{
		return Object(new PElement("div"))
				->setAtr("id","intro")
			->Insert($this->idPageHeader())
			->Insert($this->idQuickSummary())
			->Insert($this->idPreamble())
			;
		}
	/**
		*	\brief pageHeader div
		*	\version 1.1.1
		*/
	protected function idPageHeader()
		{
		return Object(new PElement("div"))
				->setAtr("id","pageHeader")
				->setAtr("title",$this->getTitle()." : ".$this->getMotto())
			->Insert(
				Object(new PElement("h1"))
						->setAtr("onclick","window.location='index.php?section=Root'")
					->Insert(
						El("span")
								->setAtr('class','notranslate')
							->Insert( $this->getFormatedTitle() )
						)
				)
			->Insert(
				Object(new PElement("h2"))
					->Insert(
						Object(new PElement("span"))
							->Insert(new PText($this->getMotto()))
						)
				)
			;
		}
	/// \brief quickSummary div
	protected function idQuickSummary()
		{
		return Object(new PElement("div"))
				->setAtr("id","quickSummary")
			->Insert(
				Object(new PElement("p"))
						->setAtr("class","p2")
					->Insert(
						Object(new PElement("span"))
							->Insert($UB)
						)
				)
			->Insert(
				Object(new PElement("p"))
						->setAtr("class","p1")
					->Insert(
						Object(new PElement("span"))
							->Insert(
								new PText(
									$this->getMessages().
									$this->getSection()->getDescription()
									)
								)
						)
				)
			;
		}
	/// \brief preamble div
	protected function idPreamble()
		{
		return Object(new PElement("div"))
				->setAtr("id","preamble")
			//->Insert($this->SearchForm())
			->Insert(
				El("h3")->Insert(
						El("span")->Insert( $this->getSection()->Chapter0Title() )
						)
				)
			->Insert( $this->getSection()->Chapter0() )
			;
		}
	/// \brief supportingText div
	protected function idSupportingText()
		{
		return Object(new PElement("div"))
				->setAtr("id","supportingText")
			->Insert(
				Object(new PElement("div"))
						->setAtr("id","explanation")
					->Insert(
						El("h3")->Insert(
								El("span")->Insert( $this->getSection()->Chapter1Title() )
								)
						)
					->Insert($this->getSection()->Chapter1())
				)
			->Insert(
				Object(new PElement("div"))
						->setAtr("id","participation")
					->Insert(
						El("h3")->Insert(
								El("span")->Insert( $this->getSection()->Chapter2Title() )
								)
						)
					->Insert($this->getSection()->Chapter2())
				)
			->Insert(
				Object(new PElement("div"))
						->setAtr("id","benefits")
					->Insert(
						El("h3")->Insert(
								El("span")->Insert( $this->getSection()->Chapter3Title() )
								)
						)
					->Insert($this->getSection()->Chapter3())
				)
			->Insert(
				Object(new PElement("div"))
						->setAtr("id","requirements")
					->Insert(
						El("h3")->Insert(
								El("span")->Insert( $this->getSection()->Chapter4Title() )
								)
						)
					->Insert($this->getSection()->Chapter4())
					->Insert($this->LongAdd())
				)
			->Insert($this->idFooter())
			;
		}
	/// \brief footer div
	protected function idFooter()
		{
		$ret=Object(new PElement("div"))
				->setAtr("id","footer");
		if($this->UserInfo['ID']!=0)
		$ret->Insert( new PText("User:&nbsp;" . $this->UserInfo['Name'].' ') );
		$ret->Insert($this->Location());
		return $ret;
		}
	/**	\brief linkList div
		*	\version 1.1.1
		*/
	protected function idLinkList()
		{
		return Object(new PElement("div"))
				->setAtr("id","linkList")
			->Insert( $this->idLinkList2() )
			->Insert( $this->SkyAdd() )
			;
		}
	/**	\brief linkList2 div
		*/
	protected function idLinkList2()
		{
		return Object(new PElement("div"))
						->setAtr("id","linkList2")
					->Insert($this->idLselect())
					->Insert($this->idLarchives())
					->Insert($this->idLresources())
			;
		}
	/**	Constructs a list structure.
		*	\brief a list structure.
		*	\return an  PStructure
		*/
	protected function ListStructure()
		{
		return new PStructure(new PElement("li"), new PElement("ul"));
		}
			/**	Constructs the list with and the bookmarked sections.
				*	\brief bookmarks list.
				*	\return an \<ul\> PStructure with the bookmarks
				*/
			protected function BookmarksList()
				{
				$ul=$this->ListStructure();
				$ul->newKid()
						->setAtr('class','selected')
					->Insert($this->Location())
					;

				$SectsArray=Sections::AccesibleBookmarkedSections ($_SESSION['userID']);
				foreach($SectsArray as $section)
					$ul->newKid()->Insert(
						Sections::Link2SQLSection($section)
							//->setAtr("class","c")
						);

				return $ul;
				}
			/**	an \<ul\> element with the <b>T</b>ranslateElement(),<b>S</b>earchForm() and the bookmarked sections.
				*	\brief bookmarks list with Translate and Search.
				*	\return an \<ul\> PStructure with the bookmarks
				*/
			protected function BookmarksListWithTS()
				{
				$ul=$this->BookmarksList();

				// search form insertion
				if( $searchF=$this->SearchForm() )
					$ul->newFirstKid()->Insert($searchF);

				if($trE=$this->TranslateElementWithCheck() )
					$ul->newFirstKid()->Insert($trE);

				return $ul;
				}
	/**	The accesible user's bookmarks. The translate element appears only if the current section is member of Guest or Public group.
		*	\brief user's bookmarks:lselect div
		*	\version 1.1.0
		*/
	protected function idLselect()
		{
		return Object(new PElement("div"))
				->setAtr("id","lselect")
				->setAtr("title",lang('Bookmarks'))
			->Insert(
				Object(new PElement("h3"))
						->setAtr("class","select")
					->Insert(
						Object(new PElement("span"))
							->Insert(PTextlang('Bookmarks'))
						)
				)
			->Insert( $this->BookmarksListWithTS() )
			;
		}
	/**	The accesible subsections of the current section.
		*	\brief the sections:larchives div
		*	\version 1.0.2
		*	\note null is returned if no subsections found
		*/
	protected function idLarchives()
		{
		$ret=Object(new PElement("div"))
				->setAtr("id","lresources")
				->setAtr("title",lang('Subsections of')." ".$this->getSectionName())
				;
		//if current section is Root the subsections are displayed by idLarchives()
		if($this->getSectionName()!="Root")
			{
			$ul=$this->ListStructure();
			//the name of the section for which we will get the subsections
			$section_name=$this->getSectionName();
			$SectsArray=Sections::AccesibleNotHiddenSubSections($section_name,$_SESSION['userID']);
			if(count($SectsArray)==0)
				{
				$owner=Sections::Owner($section_name);
				if($owner!='Root')
					{
					$section_name=$owner;
					$SectsArray=Sections::AccesibleNotHiddenSubSections($section_name,$_SESSION['userID']);
					if(count($SectsArray)==0) return $ret;
					}
					else return $ret;
				}
			foreach($SectsArray as $section)
				{
				$ul->newKid()->Insert(Sections::Link2SQLSection($section));
				}
			$ret
				->Insert(
					Object(new PElement("h3"))
							->setAtr("class","resources")
						->Insert(
							Object(new PElement("span"))
								->Insert(
									new PText(
										//lang('Subsections of')." ".
										lang($section_name))
									)
							)
					)
				->Insert($ul);
			}
		return $ret;
		}
	/**	The sections of the website.
		*	\brief the sections:larchives div
		*	\version 1.0.1
		*/
	protected function idLresources()
		{
		$ul=$this->ListStructure() ;
		$path_arr=Sections::PathArray($this->getSectionName());
		$SectsArray=Sections::AccesibleNotHiddenSubSections("Root",$_SESSION['userID']);
		if(count($SectsArray)==0)return null;
		foreach($SectsArray as $section)
			{
			$li=$ul->newKid();
			if(count($path_arr)>1 && $section['Name'] == $path_arr[1]['Name'])//we are in a sub..subsection of $section
					{
					$li->setAtr('class','selected');
					}
				$li->Insert(Sections::Link2SQLSection($section));
			}
		return Object(new PElement("div"))
				->setAtr("id","larchives")
				->setAtr("title",lang('Website\'s sections'))
			->Insert(
				Object(new PElement("h3"))
						->setAtr("class","archives")
					->Insert(
						Object(new PElement("span"))
							->Insert(new PText(lang('Website\'s sections')))
						)
				)
			->Insert($ul)
			;
		}
	/**	These extra divs/spans may be used as catch-alls to add extra imagery.
		*	\brief Zen's Garden extra Divs.
		*	\version 1.0.0
		*	\return the extra divs
		*/
	protected function Body_ExtraDivs()
		{
		return new PText('<div id="extraDiv1"><span></span></div><div id="extraDiv2"><span></span></div><div id="extraDiv3"><span></span></div><div id="extraDiv4"><span></span></div><div id="extraDiv5"><span></span></div><div id="extraDiv6"><span></span></div>');
		}
	}

/** 	The PWebPageDefault class is designed to be the default themed webpage of PWision. The layout described by this theme is derived from PCSSZenWebPage layout.
	*	\latexonly \label{PWision:PWebPageDefault} \index{PWebPageDefault} \endlatexonly
	*	\brief PWision's default themed webpage.
	*	\version 1.4.0
	*/
abstract class PWebPageDefault extends PCSSZenWebPage
	{
		protected function pwision_css()
			{
			return new PText(" @import \"css/pwision_kde.css\"; ");
			}
	protected function UserBookmarks()
		{
		return null;
		$UB=Object(new PContent)
			;
		return $UB
// 				->Insert(new PText(" | ["))
				->Insert(Sections::PathLinks($this->getSectionName()))
// 				->Insert(new PText("] | "))

			;
		}
	/// \brief container div
	protected function idContainer()
		{
		return Object(new PElement("div"))
				->setAtr("id","container")
			->Insert($this->idPageHeader())
			->Insert( $this->idIntro() )
			->Insert( $this->idSupportingText() )
			;
		}
	/// \brief intro div
	protected function idIntro()
		{
		return Object(new PElement("div"))
				->setAtr("id","intro")
			->Insert($this->idLinkList())
			;
		}
	/**	Constructs a list structure.
		*	\brief a list structure.
		*	\return an  PStructure
		*/
	protected function ListStructure()
		{
		return new PStructure(new PElement("div"), new PElement("div"));
		}
			/**	an \<ul\> element with and the bookmarked sections.
				*	\brief bookmarks list.
				*	\return an \<ul\> PStructure with the bookmarks
				*/
			protected function BookmarksListWithTS()
				{
				return $this->BookmarksList();
				}
	/**
		*	\brief pageHeader div
		*/
	protected function idPageHeader()
		{
		return El("div")
					->setAtr("id","pageHeader")
				->Insert( $this->idLTools() )
				->Insert(
					PCSSZenWebPage::idPageHeader()
						->setAtr('id','pageTitle')
					)
				->Insert($this->idLselect())
			;
		}
	/// \brief quickSummary div
	protected function idQuickSummary()
		{
		return Object(new PElement("div"))
				->setAtr("id","quickSummary")
			->Insert(
				new PText(
					$this->getMessages().
					$this->getSection()->getDescription()
					)
				)
			;
		}
	/// \brief supportingText div
	protected function idSupportingText()
		{
		return PCSSZenWebPage::idSupportingText()
			->InsertFirst( $this->idPreamble() )
			->InsertFirst( $this->idQuickSummary() )
			;
		}
	/**	\brief linkList2 div
		*/
	protected function idLinkList2()
		{
		return Object(new PElement("div"))
						->setAtr("id","linkList2")
					//->Insert($this->idLselect())
					->Insert($this->idLarchives())
					->Insert($this->idLresources())
			;
		return PCSSZenWebPage::idLinkList2()
			;
		}
			/**	an \<ul\> element with and the tools.
				*	\brief tools list.
				*	\return an \<ul\> PStructure with the tools
				*/
			protected function ToolsList()
				{
				$ul=$this->ListStructure();

				$ul->newKid()->Insert(
					$this->TranslateElementWithCheck()
					);
				$ul->newKid()->Insert(
					$this->SearchForm()
					);

				return $ul;
				}
	/// text "Tools" in local language
	public $ToolsTitle="Tools";
	protected function idLtools()
		{
		return Object(new PElement("div"))
				->setAtr("id","ltools")
				->setAtr("title",$this->ToolsTitle)
			->Insert(
				Object(new PElement("h3"))
						->setAtr("class","select")
					->Insert(
						Object(new PElement("span"))
							->Insert(PTextlang($this->ToolsTitle))
						)
				)
			->Insert( $this->ToolsList() )
			;
		}
	function PWebPageDefault()
		{
		PCSSZenWebPage::PCSSZenWebPage();
		}
	}

?>