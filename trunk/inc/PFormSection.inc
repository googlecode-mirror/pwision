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
include_once("PSection.inc");
include_once("PForm.inc");
include_once("IMessage.inc");

/** 	The PFormSection  class is designed to model a section of a website that has only PSection::Chapter1() with a <b>form</b> element.
	*	\latexonly \label{PWision:PBasicFormSection} \index{PBasicFormSection} \endlatexonly
	*	\brief a section with a form.
	*	\version 3.0.0
	*/
abstract class PBasicFormSection extends PSection implements IMessage
	{
	/// The Message
	private $Message="";
		/**	Adds a new message.
			*	\brief Adds a new message.
			*	\param $text the message text
			*	\return reference to $this
			*/
		function AddMessage($text)
			{
			$this->Message.=($text."<br/>");
			return $this;
			}
		/**	Gets the Message, followed , if != "", by a horizontal line
			*	\brief gets all the messages
			*	\version 1.1.0
			*/
		function getMessages()
			{
			$ret=$this->Message;
			if($ret=="")return $ret;
				else return $ret."<hr/>";
			}
	function	Chapter0()
		{
		return PSection::Chapter0()->Insert(new PText($this->getMessages()));
		}
	/// the PForm that will be in the section
	protected $TheForm=null;
	/**	Constructs the section, setArguments() and creates the form.
		*	\brief contructor.
		*/
	function PBasicFormSection()
		{
		PSection::PSection();
		$this->
			TheForm=Object(new PForm())
				//->setAtr("name",get_class($this))
				->setAtr("action","index.php")
				->setAtr("method","get")
				->Insert(new PInput("hidden",$this->getName(),"section"))
				;
		}
	function Chapter1Title()
		{
		return PSection::Chapter1Title()
			->Insert( new PText( $this->getTitle() ) );
		}
	function Chapter1()
		{
		$ret=PSection::Chapter1()
			->Insert(
				Object(new PElement("p"))
						->setAtr("class","p1")
					->Insert($this->TheForm)
				);
		return $ret;
		}
	}

/** 	The PStepFormSection class is designed to be a model a PBasicFormSection with a step member.
	*	\latexonly \label{PStepFormSection:PStepFormSection} \index{PStepFormSection} \endlatexonly
	*	\brief a step form section.
	*	\version 1.0.0
	*/
class PStepFormSection extends PBasicFormSection
	{
	/**	This member indicates the current step string, that is used.
		*	\brief the step string.
		*/
	protected $Step;
	function getTitle()
		{
		return $this->getName().': '.$this->Step;
		}
	/**	Constructs
		*	\brief constructor
		*/
	function PStepFormSection()
		{
		$this->Step='';
		PBasicFormSection::PBasicFormSection();
		}
	}



/** 	The PFormSection  class is designed to model a section of a website that has only PSection::Chapter1() with a <b>form</b> element. The form is created if not all of the arguments are set or form processing ProcessOK() was not successful.
	*	\brief a section with a form.
	*	\version 1.1.1
	*	\par Example:
	*		see the login class
	*	\latexonly \label{PWision:PFormSection} \index{PFormSection} \endlatexonly
	*/
abstract class PFormSection extends PBasicFormSection
	{
	/**	Constructs the basic form section and creates the form. The form is created if not all of the arguments are set or form processing ProcessOK() was not successful.
		*	\brief constructor
		*/
	function PFormSection()
		{
		PBasicFormSection::PBasicFormSection();
		$this->Arguments=array();
		$this->setArguments();
		//if( !$this->ArgumentsAreSet() || $this->ProcessOK()==false )
				//$this->createForm();
		if($this->ArgumentsAreSet())
			{
			if($this->ProcessOK()==false)
				$this->createForm();
			}
			else
				$this->createForm();
		}
	/**	Processes the transmited form arguments and returns true on success.
		*	\brief form processing.
		*	\return true if form processing was successful
		*	\note called by constructor if all arguments are set. The form will be displayed if this method returns false.
		*	\note May use $Message.
		*/
	function ProcessOK()
		{
		return true;
		}
	/**	Creates the form into $TheForm.
		*	\brief creates the form.
		*	\return reference to $TheForm
		*/
	function & createForm()
		{
		return $this->TheForm;
		}
	/// array containing the arguments of the form
	protected $Arguments;
	/**	Inserts a new argument in $Arguments.
		*	\brief add a form argument.
		*	\param $arg_name argument name
		*	\return reference to $this
		*	\note called form setArguments() in derived classes
		*/
	protected function & addArgument($arg_name)
		{
		array_push($this->Arguments,$arg_name);
		return $this;
		}
	/**	This method is called by the constructor to set the arguments of the form, using addArgument(), for future extraction.
		*	\brief sets the arguments of the form.
		*	\note pure virtual method, to be implement in derived classes
		*/
	abstract function setArguments();//pure virtual

	/**	Checks in the _REQUEST array if all argument names from Arguments are transmited.
		*	\brief checks if all arguments are transmited.
		*	\return true if all arguments are transmited, false if exists one argument not transmited or no arguments are add to Arguments array
		*/
	function ArgumentsAreSet()
		{
		foreach($this->Arguments as $arg_name)
			if(!isset($_REQUEST[$arg_name]))
				return false;
		if(count($this->Arguments))return true;
		return false;
		}
	}
?>