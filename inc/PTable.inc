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
include_once("PElement.inc");
include_once("PStructure.inc");

/// \brief drawable with cells
interface ICellable extends IDrawable
	{
	/**	Inserts a new cell.
		*	\brief add a cell.
		*	\return reference to the new cell
		*/
	function & AddCell();
	}
	
/// \brief drawable with rows
interface IRowable extends IDrawable
	{
	/**	Inserts a new row.
		*	\brief add a row.
		*	\return reference to the new row
		*/
	function & AddRow();
	/**	Inserts a new row.
		*	\brief add a row.
		*	\return reference to $this
		*/
	function & InsertRow();
	}
	
/// \brief object that is rowable and cellable
interface ITable extends IRowable,ICellable
	{
	}

/** 	The PTableRow class is designed to model a row from a table. It is a structure wiht the <b>tr</b> element as mother and <b>td</b> as kids. See the example at PStructure class.
	*	\latexonly \label{PWision:PTableRow} \index{PTableRow} \index{table} \index{row} \endlatexonly
	*	\brief a table row.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("inc/PTable.inc");
$R=new PTableRow();
$R->AddCell()->Insert(new PText("RowCell1"));
$R->AddCell()->Insert(new PText("RowCell2"));
print( $R->Draw() );
\endcode
	*	\par Output:
\verbatim
<tr>
	<td>RowCell1</td>
	<td>RowCell2</td>
</tr>
\endverbatim
	*/
class PTableRow extends PStructure implements ICellable
	{
	/**	It constructs the <b>tr</b> PElement.
		*	\brief initialisation method.
		*	\param $arr the PContent::SubElements member initial value
		*/
	function PTableRow($arr=array())
		{
		PStructure::PStructure(new PElement("td"),new PElement("tr",$arr));
		}
	/**	Inserts a new cell as a <b>td</b> PElement.
		*	\brief add a cell.
		*	\return reference to the new cell
		*/
	function & AddCell()
		{
		return $this->newKid();
		}
	}


/** 	The PTable class is designed to model a table( with rows and cells). It that is a structure with the <b>table</b> element as mother and as kids the structure PTableRow, that has the <b>tr</b> element as mother and <b>td</b> as kids. See the example at PStructure class.
	*	\latexonly \label{PWision:PTable} \index{PTable} \index{table} \index{cell} \index{row} \endlatexonly
	*	\brief a table.
	*	\version 2.1.0
	*	\par Example:
\code
include_once("inc/PTable.inc");
$T=new PTable();
$T->AddCell()->Insert(new PText("Row1Cell1"));
$T->AddCell()->Insert(new PText("Row1Cell2"));
$T->AddRow();
$T->AddCell()->Insert(new PText("Row2Cell1"));
$T->AddCell()->Insert(new PText("Row2Cell2"));
print( $T->Draw() );
\endcode
	*	\par Output:
\verbatim
<table>
	<tr>
		<td>Row1Cell1</td>
		<td>Row1Cell2</td>
	</tr>
	<tr>
		<td>Row2Cell1</td>
		<td>Row2Cell2</td>
	</tr>
</table>
\endverbatim
	*/
class PTable extends PDrawable implements ITable, IAttributes
	{
	private $Structure;
	/**	It constructs the table as a <b>table</b> PElement with one row.
		*	\brief initialisation method.
		*	\version 1.1.0
		*	\param $with_a_first_row true if you want a table that allready has a first row added
		*/
	function PTable($with_a_first_row=true)
		{
		//print("{PTableTag");
		$this->Structure=new PStructure(new PTableRow(),new PElement("table"));
		if($with_a_first_row)$this->AddRow();
		//print("PTableTag}");
		}
		
	/** \brief textual representation of the object
		* \return a string
		*/
	function Draw()
		{
		return $this->Structure->Draw();
		}
	/**	Inserts a new row.
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
		return $this->Structure->Last()->AddCell();
		}
	/**	\brief sets an attribute of the tag.
		*	\param $atr_name attribute name
		*	\param $value the value of the attribute
		*	\return reference to $this
		*/
	function & setAtr($atr_name="",$value="")
		{
		$this->Structure->getContainer()->setAtr($atr_name,$value);
		return $this;
		}
	/**	\brief gets an attribute of the tag.
		*	\param $atr_name attribute name
		*	\return value of the attribute
		*/
	function getAtr($atr_name="")
		{
		return $this->Structure->getContainer->getAtr($atr_name);
		}
	/**	creates a new cell as a <b>td</b> PElement.
		*	\brief creates a cell.
		*	\param $arr the PContent::SubElements member initial value
		*	\return the new cell
		*/
	static function Cell($arr=array())
		{
		return new PElement("td",$arr);
		}
	}
?>