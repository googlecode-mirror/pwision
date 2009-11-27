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
/** 	The IStructure interface is designed to model an object(<i>mother</i>) that is composed of substructures that share some characteristics with the other substructures(<i>kids</i>), that are constructed by the mother structure. The only way to insert kids into a mother is by using the newKid() function. In other words a structure is an object where you can insert only special objects, that have the same type and initial values.
	*	\latexonly \label{PWision:IStructure} \index{IStructure} \endlatexonly
	*	\brief a structure.
	*	\version 1.0.0
	*	\par Example:
	*	A table is a structure with the <b>table</b> element as mother and as kids the structure with the <b>tr</b> element as mother and <b>td</b> as kids. See the example at PStructure class.
	*/
interface IStructure extends IEmptyAble, IhasLast, ICloneAble
	{
	/**	gets the container
		*	\return the container
		*/
	function & getContainer();
	/**	Creates a new kid, that shares some characteristics with the other kids.
		*	\brief a new kid
		*	\return the new inserted kid
		*	\note called from the newKid() function.
		*	\note recommend to be 'protected' where languages accept protected methods in interfaces
		*/
	function makeNewKid();
	/**	Creates a new kid using makeNewKid(), that shares some characteristics with the other kids, inserts it into the structure.
		*	\brief insert a new kid
		*	\return reference to the new inserted kid
		*/
	function & newKid();
	/**	Creates a new kid using makeNewKid(), that shares some characteristics with the other kids, inserts it first into the structure.
		*	\brief insert as first a new kid
		*	\return reference to the new inserted kid
		*/
	function & newFirstKid();
	}
/// \brief a drawable structure
interface IDrawAbleStructure extends IStructure, IDrawable
	{
	}
	
/** 	The PStructure class is designed to model a drawable structure.
	*	\latexonly \label{PWision:PStructure} \index{PStructure} \index{structure} \endlatexonly
	*	\brief a drawable structure.
	*	\version 1.0.0
	*	\par Example:
			A table is a structure with the <b>table</b> element as mother and as kids the structure with the <b>tr</b> element as mother and <b>td</b> as kids.
\code
include_once("inc/PStructure.inc");
include_once("inc/PElement.inc");
$Table=new PStructure(
		//** kids of table: the rows**
		new PStructure(
			// ** kids of row: cells <td> **
			new PElement("td"),
			// ** mother row: <tr> element **
			new PElement("tr")),
		// ** mother table: <table> element **
		new PElement("table"));
$Row=$Table->newKid();// ** new row **
	// ** new cell with text **
	$Row->newKid()->Insert(new PText("Row1Cell1"));
	$Row->newKid()->Insert(new PText("Row1Cell2"));
$Row=$Table->newKid();// ** second row **
	$Row->newKid()->Insert(new PText("Row2Cell1"));
	$Row->newKid()->Insert(new PText("Row2Cell2"));
print( $Table->Draw() );
\endcode
	*	\par Output:
\verbatim
<table><tr><td>c1</td><td>c2</td><td>c3</td></tr></table>
\endverbatim
	*/
class PStructure implements IDrawAbleStructure
	{
	private $Container;
	/**	gets the container
		*	\return the container
		*/
	function & getContainer()
		{
		return $this->Container;
		}
	/** \brief clone the object
		* \return the clone
		*/
	function CloneMe()
		{
		return unserialize(serialize($this));
		}
	/**	removes the last inserted element.
		*	\brief removes the last subelement.
		*	\return the poped object
		*/
	function Pop()
		{
		return $this->Container->Pop();
		}
	/**	removes the first element.
		*	\brief removes the first subelement.
		*	\return the removed object
		*/
	function rmFirst()
		{
		return $this->Container->rmFirst();
		}
	/** \brief clear the subelements array.
		* \return reference to $this pointer
		* \version 1.1
		*/
	function & Clear()
		{
		$this->Container->Clear();
		return $this;
		}
	/**	get the last inserted kid
		*	\brief the last kid
		*	\return the last kid
		*/
	function & Last()
		{
		return $this->Container->Last();
		}
	/// the cloneable kid
	private $givenKid;
	/**	Creates a new kid, that shares some characteristics with the other kids.
		*	\brief a new kid
		*	\return the new inserted kid
		*	\note called from the newKid() function.
		*	\note recommend to be 'protected' where languages accept protected methods in interfaces
		*/
	function makeNewKid()
		{
		return $this->givenKid->CloneMe();
		}
	/**	Creates a new kid using makeNewKid(), that shares some characteristics with the other kids, inserts it into the structure.
		*	\brief insert a new kid
		*	\return reference to the new inserted kid
		*/
	function & newKid()
		{
		return $this->Container->LastInsert($this->makeNewKid());
		}
	/**	Creates a new kid using makeNewKid(), that shares some characteristics with the other kids, inserts it first into the structure.
		*	\brief insert as first a new kid
		*	\return reference to the new inserted kid
		*/
	function & newFirstKid()
		{
		$kid=$this->makeNewKid();
		$this->Container->InsertFirst($kid);
		return $kid;
		}
	/** \brief textual representation of the container
		* \return a string
		*/
	function Draw()
		{
		return $this->Container->Draw();
		}
	/**	\brief textual representation of the object
		*	\return a string
		*	\note called from echo or print functions
		*/
	function __toString()
		{
		return $this->Draw();
		}
	/**	Constructs a drawable structure
		*	\brief constructor
		*	\param $kid the ICloneAble kid
		*	\param $Container IContent object that will be the container
		*/
	function PStructure( ICloneAble $kid=null, IContent $Container=null)
		{
		if($kid)
				$this->givenKid=$kid;
			else
				$this->givenKid=new PDrawable();
		if($Container)
				$this->Container=$Container;
			else
				$this->Container=new PContent();
		}
	}
?>