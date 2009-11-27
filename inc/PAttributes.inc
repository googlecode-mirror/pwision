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
/**	\brief interface to attributes
	*/
interface IAttributes
	{
	/** \brief sets the value of an attribute
		* \param $atr attribute name
		* \param $value the value of the attribute
		* \return reference to $this
		*/
	function & setAtr( $atr="", $value="" );
	/** \brief gets the value of an attribute
		* \param $atr attribute name
		* \return value of the attribute
		*/
	function getAtr( $atr="" );
	}
/** 	The PAttributes  class is designed to model a list of pair(key,value). It uses an associative array that by default will be drawn as [attribute1="value1" attribute2="value2" ... attributeN="valueN"].
	*	\latexonly \label{PWision:PAttributes} \index{PAttributes} \index{attributes} \endlatexonly
	*	\brief a list of attributes.
	*	\version 1.1.0
	*	\par Example:
\code
include_once("inc/PAttributes.inc");
$A=Object( new PAttributes() )
	->setAtr("name1","value1")
	->setAtr("name2","value2");
print( $A );
\endcode
	*	\par Output:
\verbatim
name1="value1" name2="value2"
\endverbatim
	*/
class PAttributes extends PDrawable implements IAttributes
	{
	/// the associative array
	protected $Associative;
		/**	If the value is != null, this functions sets it in the associative array.
			*	\brief sets the value of an attribute
			*	\version 1.1.0
			*	\param $atr attribute name
			*	\param $value the value of the attribute
			*	\return reference to $this
			*/
		function & setAtr( $atr="", $value="" )
			{
			if($value!=null)$this->Associative[$atr]=$value;
			return $this;
			}
		/** \brief gets the value of an attribute
			* \param $atr attribute name
			* \return value of the attribute
			*/
		function getAtr( $atr="" )
			{
			if($atr=="")return null;
			return $this->Associative[$atr];
			}

	/** \brief initialisation method.
		*
		* It constructs the PDrawable parent and then sets Associative.
		* \param $asoc the PDrawable::Associative member initial value
		*/
	function PAttributes( $asoc=array() )
		{
		PDrawable::PDrawable();
		$this->Associative=$asoc;
		}
	
	/**	\brief draws a pair(key,value)
		*	\param $key key name
		*	\param $value value
		*	\return key_name="value"
		*/
	function DrawPair($key="",$value="")
		{
		return $key."="."\"$value\"";
		}
	/**	\brief draws the separator
		*	\return space " "
		*/
	function DrawSeparator()
		{
		return " ";
		}
	/**	\brief draws the pairs
		*
		*	Draws the pairs using DrawPair() for each pair, separated by the separation string returned by DrawSeparator().
		* \note pairs with value == "" are not drawn
		*/
	function Draw()
		{
		$ret = "" ;
		foreach($this->Associative as $atr => $value)
			if($value!=null && $value != "")
				$ret=$ret.
					$this->DrawSeparator().
					$this->DrawPair( $atr, $value );
		return $ret;
		}
	}
/** 	The PURLAttributes is designed to make URL atributes.
	*	\latexonly \label{PWision:PURLAttributes} \index{PURLAttributes} \index{attributes} \endlatexonly
	*	\brief a list of URL attributes.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("inc/PAttributes.inc");
$A=Object( new PURLAttributes() )
	->setAtr("name1","value1")
	->setAtr("name2","value2");
print( $A );
\endcode
	*	\par Output:
\verbatim
name1=value1&name2=value2
\endverbatim
	*/
class PURLAttributes extends PAttributes
	{
	/**	\brief draws a pair(key,value)
		*	\param $key key name
		*	\param $value value
		*	\return key_name=value
		*/
	function DrawPair($key="",$value="")
		{
		return $key."="."$value";
		}
	/**	\brief draws the separator
		*	\return "&"
		*/
	function DrawSeparator()
		{
		return "&";
		}
	}
?>