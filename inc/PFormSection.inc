<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2009,2011 Becheru Petru-Ioan

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
	*	\version 3.0.2
	*/
abstract class PBasicFormSection extends PSection implements IMessage
	{
	/// the PForm that will be in the section
	protected $TheForm=null;
	/**	Constructs the section, setArguments() and creates the form.
		*	\brief contructor.
		*/
	function PBasicFormSection()
		{
		$this->
			TheForm=Object(new PForm())
				//->setAtr("name",get_class($this))
// 				->setAtr("action","index.php")
				->setAtr("action","/")
				->setAtr("method","post")
				->Insert(new PInput("hidden",$this->getName(),"section"))
				;
		PSection::PSection();
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
	*	\version 1.0.1
	*/
class PStepFormSection extends PBasicFormSection
	{
	/**	This member indicates the current step string, that is used.
		*	\brief the step string.
		*/
	protected $Step;
	function getTitle()
		{
		return parent::getTitle().': '.$this->Step;
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
	*	\version 2.0.1
	*	\par Example:
	*		see the login class
	*	\latexonly \label{PWision:PFormSection} \index{PFormSection} \endlatexonly
	*/
abstract class PFormSection extends PBasicFormSection
	{
	function if_parameters_are_set()
		{
		parent::if_parameters_are_set();
		if($this->ProcessOK()==false)
			$this->createForm();
		}
	/**	This method is called by the constructor if not all par of the section are set, <i>but all that are set are also matched with their regular expresion</i>.
		*	\brief if not all parameters are set.
		*/
	function if_not_all_parameters_are_set()
		{
		$this->createForm();
		}
	/**	This method is called by the constructor if PSection_ParamNCheck is thrown.
		*	\brief PSection_ParamNCheck thrown.
		*/
	function param_NCheck(PSection_ParamNCheck &$e)
		{
		$this->AddMessage($e->getMessage());
		$this->createForm();
		}
	/**	Constructs the basic form section and creates the form. The form is created if not all of the arguments are set or form processing ProcessOK() was not successful.
		*	\brief constructor
		*/
	function PFormSection()
		{
		PBasicFormSection::PBasicFormSection();
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
	}

/**	Replace multibyte chars with the &#<i>number</i>; corespondent.
	*	\brief decode a UTF string
	*	\param $string the UTF string
	*	\return the decoded string
	*/
function charset_decode_utf_8 ($string) 
	{ 

	// decode three byte unicode characters 
	$string = preg_replace("/([\340-\357])([\200-\277])([\200-\277])/e",
	"'&#'.((ord('\\1')-224)*4096 + (ord('\\2')-128)*64 + (ord('\\3')-128)).';'",
	$string); 

	// decode two byte unicode characters 
	$string = preg_replace("/([\300-\337])([\200-\277])/e",
	"'&#'.((ord('\\1')-192)*64+(ord('\\2')-128)).';'",
	$string);

	//decode ASCII extended
	$string = preg_replace("/([\x7F-\277])/e", "'&#'.(ord('\\1')).';'", $string);

	return $string; 
	} 


?>