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
include_once("PElement.inc");
include_once("PTable.inc");
/** 	The PTabs class is designed to model tabs.
	*	\latexonly \label{PWision:PTabs} \index{PTabs} \index{tab} \endlatexonly
	*	\brief a tab area.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PTabs.inc");
$Tabs=Object( new PTabs() )
	->InsertAsNewTab(new PText("tab 1"),PTabs::$notactive)
	->InsertAsNewTab(new PText("tab 1"),PTabs::$notactive)
	->InsertAsNewTab(new PText("tab 3"),PTabs::$active)
	->InsertAsNewTab(new PText("tab 1"),PTabs::$notactive)
	;
print($Tabs->Draw());
\endcode
	*	\par Output(indented):
\verbatim
<div class="Tabs">
	<div class="Line">
		<div class="left">&nbsp;</div>
		<div class="center">
			<div class="theTabs">
				<div class="notactive">tab 1</div>
				<div class="notactive">tab 1</div>
				<div class="active">tab 3</div>
				<div class="notactive">tab 1</div>
			</div>
		</div>
		<div class="right">&nbsp;</div>
	</div>
</div>
\endverbatim
	* \todo functiile InsertInLeft si InsertInRight
	*/
class PTabs extends PDrawable implements ITable
	{
	private $Structure;
	static $notactive="notactive";
	static $active="active";
	function PTabs()
		{
		$this->Structure= new PStructure(
			new PContentInContent(
				Object(new PElement("div"))
						->setAtr("class","Line"),
				new PContentWithFrame(
					Object(new PElement("div"))
							->setAtr("class","left")
						->Insert(new PText("&nbsp;")),
					Object(new PElement("div"))
							->setAtr("class","right")
						->Insert(new PText("&nbsp;")),
					new PStructure(
						Object(new PElement("div"))->setAtr("class",PTabs::$notactive),
						Object(new PElement("div"))->setAtr("class","theTabs")
						)
					)
				),
			Object(new PElement("div"))->setAtr("class","Tabs")
			);
		$this->AddRow();
		}
	function InsertAsNewTab(IDrawable &$dr,$class="notactive")
		{
		$this->AddCell()->setAtr("class",$class)->Insert($dr);
		return $this;
		}
	/** \brief textual representation of the object
		* \return a string
		*/
	function Draw()
		{
		return $this->Structure->Draw();
		}
	/**	Inserts a new row of tabs.
		*	\brief add a row.
		*	\return reference to the new row
		*/
	function & AddRow()
		{
		return $this->Structure->newKid();
		}
	/**	Inserts a new row.
		*	\brief add a row.
		*	\return reference to $this
		*/
	function & InsertRow()
		{
		$this->AddRow();
		return $this;
		}
		
	/**	Inserts a new cell.
		*	\brief add a cell.
		*	\return reference to the new cell
		*/
	function & AddCell()
		{
		// beat this !
		return 
			$this
				->Structure
					->Last()
						->InnerContent()
							->getCenterFrame()
								->newKid();
		}
	}
?>