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
include_once("PDrawable.inc");
/** 	The PText class is designed to model text strings as PDrawable objects.
	*	\latexonly \label{PWision:PText} \index{PText} \index{text} \index{string} \endlatexonly
	*	\brief a text.
	*	\version 1.2.0
	*	\par Example:
\code
include_once("inc/PText.inc");
$Text= new PText( "Hello PWision!" );
print( $Text->Draw() );
\endcode
	*	\par Output:
\verbatim
Hello PWision!
\endverbatim
	*/
class PText extends PDrawable
	{
	/** \brief text string.
		* contains the text string
		*/
	private $text="";
		/** \brief sets PText::text
			* \param $the_text the string
			* \return reference to $this pointer
			* \version 1.1
			*/
		function setText($the_text){$this->text=$the_text; return $this;}
		/**
			*	\brief gets the text
			*	\return PText::text
			*/
		function getText(){return $this->text;}
	/** \brief constructs a PText
		* \param $the_text the string
		*/
	function PText($the_text="")
		{
		//print("{PText ");
		$this->setText($the_text);
		//print(" PText}");
		}

	function Draw()
		{
		return $this->getText();
		}
	}

/**	Constructs a div PElement containing a PText.
	*	\brief a div element with text.
	*	\version 1.0.0
	*	\param $text the text string
	*	\return the div element
	*/
function DivEText($text="")
	{
	return
		Object(new PElement("div"))
			->Insert(new PText($text))
		;
	}

/** an array containing a text.
 * \param $text the text string
 * \return array of a single PText
 */
function Text2Array($text)
	{
	return array(new PText($text));
	}
?>