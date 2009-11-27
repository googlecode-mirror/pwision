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
/** 	The ICloneAble interface is designed to model an object that can be cloned. It is the base interface for all cloneable classes.
	*	\latexonly \label{PWision:ICloneAble} \index{ICloneAble} \index{cloning} \endlatexonly
	*	\brief a cloneable object interface
	*	\version 2.0.0
	*/
interface ICloneAble
	{
	/** \brief clone the object
		* \return the clone
		*/
	function CloneMe();
	}
/** 	The IDrawable interface is designed to model an object that can be transformed into a text. It is the base interface for all drawable classes.
	*	\latexonly \label{PWision:IDrawable} \index{IDrawable} \index{text} \endlatexonly
	*	\brief a drawable object interface.
	*	\version 1.0.0
	*	\par Example:
	*		See PContent::Insert()
	*/
interface IDrawable
	{
	/**	\brief textual representation of the object
		*	\return a string
		*/
	function Draw();
	/**	\brief textual representation of the object
		*	\return a string
		*	\note called from echo or print functions
		*/
	function __toString();
	}
/** 	The IDrawableCloneAble interface is designed to model an object that can be cloned and drawn. It is the base interface for all cloneable and drawable classes.
	*	\latexonly \label{PWision:IDrawableCloneAble} \index{IDrawableCloneAble} \index{cloning} \endlatexonly
	*	\brief a drawable and cloneable object interface.
	*	\version 1.0.0
	*/
interface IDrawableCloneAble extends IDrawable, ICloneAble
	{}
/** 	The PDrawable class is designed to model an object that can be transformed into a text. It is the base class for all drawable classes.
	*	\latexonly \label{PWision:PDrawable} \index{PDrawable} \index{text} \index{base class} \endlatexonly
	*	\brief a drawable object
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PDrawable.inc");
$Obj=new PDrawable();
print( $Obj->Draw() );
\endcode
	*	\par Output:
\verbatim
\endverbatim
	*/
class PDrawable implements IDrawableCloneAble
	{
	/**	Nothing.
		*	\brief initialisation method
		*/
	function PDrawable()
		{}
	/** \brief clone the object
		* \return the clone
		*/
	function CloneMe()
		{
		return unserialize(serialize($this));
		}
	/** \brief textual representation of the object
		* \return a string
		*/
	function Draw()
		{
		return "";
		}
	/**	\brief textual representation of the object
		*	\return a string
		*	\note called from echo or print functions
		*/
	function __toString()
		{
		return $this->Draw();
		}
	/** 	\brief conversion to array
		*	\return an array with one element: $this.
		*/
	function toArray()
		{
		return array($this);
		}
	}
	
	
/**	Reference to the object given as parammeter.
	*	\latexonly \label{PWision:Object} \index{Object function} \endlatexonly
	*	\brief reference to an object
	*	\version 1.0.0
	*	\param $obj reference to an object
	*	\return reference to parammeter
	*	\par Example:
	*		See example at PContent class.
	*/
function & Object(&$obj)
	{
	return $obj;
	}

function & newObject($class_name)
	{
	return new $class_name();
	}
/*

*/
?>