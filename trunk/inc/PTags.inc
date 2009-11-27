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
include_once("PContent.inc");
include_once("PAttributes.inc");
include_once("PText.inc");
/**	$leftText != ("<","</") sau $rightText != (">","/>") in PComplexTag::PComplexTag
	*	\brief Starting or Ending strings of a tag not correct
	*/
class StartingEndingCharsValue extends Exception { }

/** 	The PComplexTag class is designed to model a complex tag 
	*	\latexonly \label{PWision:PComplexTag} \index{PComplexTag} \index{tag} \index{complex tag} \endlatexonly
		\brief a complex tag.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PTags.inc");
$Div=Object( new PComplexTag("div") )
	->setAtr( "class", "h4X0r" );
print( $Div->Draw() );
\endcode
	*	\par Output:
\verbatim
<div class="h4X0r">
\endverbatim
	*/
class PComplexTag extends PContentWithTextFrame implements IAttributes
	{
	/// the name of the tag
	protected $tagName="";
		/**	\brief sets PComplexTag::tagName.
			*	\param $name the name of the tag
			*	\return reference to $this
			*/
		protected function settagName($name){$this->tagName=$name; return $this;}
		/**	\brief gets PComplexTag::tagName.
			*	\return the name of the tag
			*/
		protected function & gettagName(){return $this->tagName;}
		
	/// the attributes of the tag
	protected $Attributes;
		/**	\brief sets an attribute of the tag.
			*	\param $atr_name attribute name
			*	\param $value the value of the attribute
			*	\return reference to $this
			*/
		function & setAtr($atr_name="",$value="")
			{
			$this->Attributes->setAtr($atr_name,$value);
			return $this;
			}
		/**	\brief gets an attribute of the tag.
			*	\param $atr_name attribute name
			*	\return value of the attribute
			*/
		function getAtr($atr_name="")
			{
			return $this->Attributes->getAtr($atr_name);
			}

	/**	\brief initialisation method.
		*
		* It constructs the PContentWithFrame parent and then the tag name to $name..
		*	\param $name the tag's name
		*	\param $arr the PContent::SubElements member initial value
		*	\param $leftText the starting characters of the tag
		*	\param $rightText the ending characters
		*	\note if $name is ""(lambda tag) nothing will be drawn. See Draw()
		*	\note if $leftText != ("<","</") sau $rightText != (">","/>") StartingEndingCharsValue exception is thrown
		*/
	function PComplexTag( $name="div", $arr = array(), $leftText="<", $rightText=">" )
		{
		PContentWithTextFrame::PContentWithTextFrame($leftText, $rightText, $arr);
		$this->settagName( $name );
		$this->Attributes = new PAttributes();
		if( $leftText!="<" && $leftText!="</" && $rightText!=">" && $rightText!="/>" )
			throw new StartingEndingCharsValue("\$leftText != (\"<\",\"</\") or \$rightText != (\">\",\"/>\")");
		}
	/**	\brief draws the tag.
		*
		*	\note if tagName == "" this function returns PDrawable::Draw() (e.g. empty string). This 'lambda' tags will be used to model the fact that a PSimpleTag can be PElement(LeftFrame and RightFrame of a PElement will be a lambda tag).
		*	\return the tag
		*/
	function Draw()
		{
		if($this->tagName != "")
				{
				PComplexTag :: getCenterFrame()-> Insert( new PText($this->tagName) );
				PComplexTag :: getCenterFrame()-> Insert( $this->Attributes );
				$ret = PContentWithFrame::Draw();
				//removing Attributes and tagName so a second draw would not reinsert them again
				$this -> getCenterFrame()-> Pop();
				$this -> getCenterFrame()-> Pop();
				return $ret;
				}
		//lambda tag
		return PDrawable::Draw();//nothing
		}
	}
	
/** 	The PEndingTag class is designed to model an ending tag.
	*	\latexonly \label{PWision:PEndingTag} \index{PEndingTag} \index{tag} \index{ending tag} \endlatexonly
	*	\brief an ending tag.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PTags.inc");
$EDiv= new PEndingTag( "div" );
print( $EDiv->Draw() );
\endcode
	*	\par Output:
\verbatim
</div>
\endverbatim
	*/
class PEndingTag extends PComplexTag
	{
	/**	It constructs an ending tag as a PComplexTag where left and right frames are "</" and ">".
		*	\brief initialisation method.
		*	\param $name the tag's name
		*	\param $arr the PContent::SubElements member initial value
		*/
	function PEndingTag($name="div", $arr = array() )
		{
		PComplexTag::PComplexTag($name,$arr,"</",">");
		}
	}
	
/** 	The PSimpleTag class is designed to model a simple tag.
	*	\latexonly \label{PWision:PSimpleTag} \index{PSimpleTag} \index{tag} \index{simple tag} \endlatexonly
	*	\brief a simple tag.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PTags.inc");
$SDiv= new PSimpleTag( "br" );
print( $SDiv->Draw() );
\endcode
	*	\par Output:
\verbatim
<br/>
\endverbatim
	*/
class PSimpleTag extends PComplexTag
	{
	/**	It constructs a simple tag as a PComplexTag where left and right frames are "<" and "/>".
		*	\brief initialisation method.
		*	\param $name the tag's name
		*	\param $arr the PContent::SubElements member initial value
		*/
	function PSimpleTag($name="br", $arr = array() )
		{
		PComplexTag::PComplexTag($name,$arr,"<","/>");
		}
	/**	Transforms a PSimpleTag into an element by inserting the simple tag into a lambda PElement.
		*	\brief simple tag as a PElement
		*	\return a "lambda" PElement containing $this
		*	\note Calling member functions like setAtr() will reference the lambda PElement, NOT the PSimpleTag! . See also the notes at PComplexTag::Draw(), PElement::PElement()
		*/
	function toPElement()
		{
		//lambda element creation($tag_name ctor parammeter is "")
		$LambdaElement=new PElement("");
		//insert $this simple tag and return the lambda element containing it
		return $LambdaElement->Insert( $this ) ;
		}
	}

?>