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
include_once("PTags.inc");
/** 	The PElement class is designed to model HTML elements. A HTML element is either a PSimpleTag, either a PContentWithFrame, where frames are a PComplexTag and a PEndingTag.
	*	\latexonly \label{PWision:PElement} \index{PElement} \index{element} \index{tag} \index{simple tag} \index{frame} \index{complex tag} \index{ending tag} \endlatexonly
*	\brief an HTML element.
	*	\version 1.1.3
	*	\par Example:
\code
include_once("PElement.inc");
$anEl=Object(new PElement("div"))
	->setAtr("title","first tag")
	->setAtr("class","menu")
	->Insert(
		Object(new PElement("p"))
			->setAtr("class","main")
			->Insert(new PText("A paragraph inside a div"))
		);
print( $anEl->Draw() );
\endcode
	*	\par Output:
\verbatim
<div title="first tag" class="menu"><p class="main">A paragraph inside a div</p></div>
\endverbatim
	*/
class PElement extends PContentWithFrame implements IAttributes
	{
	/// tag name
	protected $tagName;
	/**	\brief the starting tag
		*
		*	Gets the starting tag of the element, e.g. the left frame
		*	\return the starting tag of the element
		*/
	function & getTag()
		{
		return PElement::getLeftFrame();
		}
	/**	\brief sets an attribute of the tag.
		*	\param $atr_name attribute name
		*	\param $value the value of the attribute
		*	\return reference to $this
		*/
	function & setAtr($atr_name="",$value="")
		{
		$this->getTag()->setAtr($atr_name,$value);
		return $this;
		}
	/**	\brief gets an attribute of the tag.
		*	\param $atr_name attribute name
		*	\return value of the attribute
		*/
	function getAtr($atr_name="")
		{
		return $this->getTag()->getAtr($atr_name);
		}

	/**	\brief  initialisation method.
		*	\param $tag_name tag name (by default "div")
		*	\note if $tag_name="" the left and right frames inherited from PContentWithFrame will be lambda tags so nothing will be drawn as frames(see PComplexTag::PComplexTag() ). This allows us to create lambda elements that will be drawn without frames( only the inner content is actually drawn). Used to transform a PSimpleTag into an element by inserting the simple tag into a lambda PElement. See PSimpleTag::toPElement().
		*/
	function PElement($tag_name="div")
		{
		$this->tagName=$tag_name;
		PContentWithFrame::PContentWithFrame(
			new PComplexTag($this->tagName),
			new PEndingTag($this->tagName)
			);
		}
	}
/**	Creates a new PElement
	*	\brief an element
	*	\version 1.0.0
	*	\param $tag_name tag name
	*	\return the element
	*/
function El($tag_name="div")
	{
	return new PElement($tag_name);
	}
/**	Creates a new PSimpleTag transformed into a PElement
	*	\brief a PSimpleTag as a PElement
	*	\version 1.0.0
	*	\param $tag_name tag name
	*	\return the element
	*/
function sEl($tag_name="br")
	{
	return Object(new PSimpleTag($tag_name))->toPElement();
	}
?>