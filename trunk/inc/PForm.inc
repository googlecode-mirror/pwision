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
/** 	The PForm class is designed to model the HTML form element.
	*	\latexonly \label{PWision:PForm} \index{PForm} \index{form} \endlatexonly
	*	\brief a form.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PForm.inc");
$aForm= new PForm("aform","handler.php");
print( $aForm->Draw() );
\endcode
	*	\par Output:
\verbatim
<form action="handler.php" method="post"></form>
\endverbatim
	*/
class PForm extends PElement
	{
	/**	\brief  initialisation method.
		*	\latexonly \index{action} \index{method} \index{POST} \index{GET} \endlatexonly
		*	\param $name name of the form
		*	\param $action action URL or the form
		*	\param $method the methods for sending the parameters(can be "post"(default) or "get")
		*	\param $arr the PContent::SubElements member initial value
		*/
	function PForm($name="",$action="",$method="post",$arr=array())
		{
		//print("{PForm ");
		PElement::PElement("form",$arr);
		$this
			//->setAtr("name",$name)
			->setAtr("action",$action)
			->setAtr("method",$method)
			;
		//print(" PForm}");
		}
	}

/** 	The PInput class is designed to model the HTML input element. A PInput is inserted in a PForm object.
	*	\latexonly \label{PWision:PInput} \index{PInput} \index{input} \index{form} \endlatexonly
	*	\brief an input element.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PForm.inc");
$anInp= new PInput("text","insert text here","description");
print( $anInp->Draw() );
\endcode
	*	\par Output:
\verbatim
<input type="text" value="insert text here" name="description"/>
\endverbatim
	*/
class PInput extends PSimpleTag
	{
		function getTheType(){return $this->getAtr("type");}
		function & setTheType($Type='text'){return $this->setAtr("type",$Type);}
		function getValue(){return $this->getAtr("value");}
		function & setValue($Value=""){return $this->setAtr("value",$Value);}
		function getName(){return $this->getAtr("name");}
		function & setName($name=""){return $this->IName=$name;}

	/**	\brief initialisation method.
		*	\param $type input type(button, checkbox, file, hidden, image, password, radio, reset, submit, text)
		*	\param $value value
		*	\param $name nameid of the element
		*/
	function PInput($type="text",$value,$name)
		{
		PSimpleTag::PSimpleTag("input");
		$this
			->setAtr("type",$type)
			->setAtr("value",$value)
			->setAtr("name",$name)
			;
		}
	}
/**	Constructs a collection of inputs from an array whose items are arrays with a key for the value of the input and a key for the text that follows the input.
	*	\brief array to inputs.
	*	\version 1.1.0
	*	\par Example:
	*		See Groups::GroupsFieldSet() .
	*	\param $arr the array of array items
	*	\param $name name of the inputs
	*	\param $key4Value the key for the value of the input
	*	\param $key4Text the key for the text that follows the input
	*	\param $type the type of the input. By default checkbox
	*	\param $separator the IDrawAble that sepates the generated inputs
	*	\param $sEl_name the name of the simple element(by default <b>input</b>).
	*	\return a PContent object that contains the inputs
	*/
function Array2Inputs($arr=null,$name='',$key4Value='value',$key4Text='text',$type="checkbox",IDrawAble $separator=null, $sEl_name="input")
	{if($separator==null)$separator=new PSimpleTag("br");
	
	if($arr==null)return null;
	$Content=new PContent();
	$key_in_name=($type=='checkbox') && !eregi('^[a-z0-9_.]*\[\]$',$name);
	foreach($arr as $item)
		{
		$Content
			->Insert(
				Object(new PSimpleTag($sEl_name))
					->setAtr("type",$type)
					->setAtr("value",
						array_key_exists($key4Value,$item)?$item[$key4Value]:'1'
						)
					->setAtr("name",
						$key_in_name?$name.'['. (array_key_exists($key4Value,$item)?$item[$key4Value]:'') .']':$name
						)
					->setAtr('checked',
						array_key_exists('checked',$item)?$item['checked']:null
						)
				)
			->Insert(new PText($item[$key4Text]))
			->Insert($separator);
		}
	return $Content;
	}
/**	This function constructs a PStructure that has a select PElement as mother and option PElement as kids.
	*	\brief the select structure.
	*	\version 1.1
	*	\param $name name attribute of the select
	*	\param $arr pairs ('0'=>text) for the option
	*	\param $selected selected value
	*	\param $click_and_select if this is true the first kid will contain the text 'Click and Select' with the value '_'
	*	\return the structure
	*/
function SSelect($name,$arr=null,$selected=null,$click_and_select=false)
	{
	$SS=new PStructure(
		new PElement("option"),
		Object(new PElement("select"))
			->setAtr("name",$name)
		);
	if($arr)
		{
		if($click_and_select)
			$SS->newKid()
				->setAtr("value","_")
				->Insert(
					new PText('Click and Select')
					);
		foreach($arr as $item)
			{
			$kid=$SS->newKid()->setAtr("value",$item[0]);
			if(isset($item[1]))
					$kid->Insert(
							new PText($item[1])
							);
				else
					$kid->Insert(
							new PText($item[0])
							);
			if($item[0]==$selected)
				$kid->setAtr("selected","selected");
			}
		}
	return $SS;
	}

/** 	The PFieldSet class is designed to model the HTML fieldset element.
	*	\latexonly \label{PWision:PFieldSet} \index{PFieldSet} \index{fieldset} \endlatexonly
	*	\brief fieldset element.
	*	\version 1.0.1
	*	\par Example:
\code
include_once("PForm.inc");
$aFS= new PFieldSet("Owners");
$aFS
	->Insert(new PText("a text"))
	->Insert(new PInput("text","insert text here","description"))
	;
print( $aFS->Draw() );
\endcode
	*	\par Output(indented):
\verbatim
<fieldset>
   <legend>
      Owners
   </legend>
   a text
      <input
         type="text"
         value="insert text here"
         name="description"
         />
</fieldset>
\endverbatim
	*/
class PFieldSet extends PElement
	{
	/// legend content
	protected $Legend;
		/**	\brief gets an legend of the fieldset
			*	\return value of the Legend
			*/
		function getLegend(){return $this->Legend;}
		/**	\brief sets the legend of the fieldset.
			*	\param $legend the legend PText
			*	\return reference to $this
			*/
		function & setLegend($legend){$this->Legend=$legend;return $this;}
	/**	It constructs a fieldset element with a legend.
		*	\brief initialisation method.
		*	\param $legend the legend PText
		*/
	function PFieldSet($legend)
		{
		$this->Legend=$legend;
		PElement::PElement("fieldset");
		}
	/**	Insert the legend element, draws the fieldset then removes the legend element.
		*	\brief draws the tag.
		*	\version 1.0.1
		*	\return the fieldset
		*/
	function Draw()
		{
		$this->InsertFirst(
			Object(new PElement("legend"))
			->Insert($this->Legend)
			);
		$ret=PElement::Draw();
		$this->rmFirst();
		return $ret;
		}
	}
/**	Constructs a PFieldSet with a text legend.
	*	\brief a PFieldSet
	*	\param $legend_text legend string text
	*	\return a PFieldSet
	*/
function FieldSet($legend_text='')
	{
	return new PFieldSet( new PText($legend_text) );
	}

/**	Constructs a textarea input element.
	*	\brief a textarea.
	*	\param $name name of the textarea
	*	\param $text initial text content of textarea
	*	\param $rows number of visible rows of the textarea
	*	\return an textarea PElement
	*/
function TextArea($name,$text='',$rows=20)
	{
	return
		El('textarea')
				->setAtr('name',$name)
				->setAtr('rows',$rows)
			->Insert(new PText($text) )
		;
	}
?>