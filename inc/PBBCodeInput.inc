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


include_once('PForm.inc');
include_once('PVirtualKeyboard.inc');

/** 	The PBBCodeInput class is designed to be a BBCode input textarea with button for BBCode tags.
	*	\latexonly \label{PBBCodeInput:PBBCodeInput} \index{PBBCodeInput} \index{BBCode} \index{textarea} \endlatexonly
	*	\brief BBCode input textarea.
	*	\version 1.2.1
	*	\par Example:
\code
include_once("PBBCodeInput.inc");
print( new PBBCodeInput('the text', 'text','textContent') );
\endcode
	*	\par Output:
\verbatim
\endverbatim
	*/
class PBBCodeInput extends PContent
	{
	/**
		*	\brief head script
		*	\param $lang language code
		*	\param $ids ids of the inputs where the keyboard will be active
		*	\return PVirtualKeyboard::Head($lang, $ids)
		*/
	static function Head($lang='en',$ids=array('textContent'))
		{
		return PVirtualKeyboard::Head($lang, $ids);
		}
	/**	Creates an input button that insert a text when clicked.
		*	\brief create a button that inserts text.
		*	\version 2.0.1
		*	\param $before before the cursor text string
		*	\param $after after the cursor text string
		*	\return a PInput element
		*/
	private static function insertTextButton($before,$after)
		{
				return
					El('div')
							->setAtr('class','BBCodes')
							->setAtr('onclick', "insertAtCursor('$before','$after')")
						->Insert(new PText($before.$after))
						;
		}
	/**	Constructs
		*	\brief constructor
		*	\version 1.0.3
		*	\param $text initial text content of textarea
		*	\param $name name of the textarea
		*	\param $id id attribute of the textarea
		*/
	function PBBCodeInput($text='',$name='text',$id='textContent')
		{
		PContent::PContent();
		$this
			->Insert(sEl('hr'))
			->Insert(
				PVirtualKeyboard::kbSelect()
				)
			->Insert(
				Object(new PInput("button",lang("Clear Text!"),""))
					->setAtr('onclick', 'clearText()')
				)
			->Insert(
				Object(new PInput("button",lang("Scroll down!"),""))
					->setAtr('onclick', 'scrolltoEnd()')
				)
			->Insert(new PInput("submit",lang("Submit Changes!"),""))
			->Insert(El('br'))
			->Insert(
				TextArea($name,$text)
					->setAtr('id',$id)
				)
							->Insert(El('br'))
						->Insert(PTextlang('Insert:') )->Insert(El('br'))
						->Insert(sEl('hr'))
							->Insert(PBBCodeInput::insertTextButton('[subtitle]','[/subtitle]'))
							->Insert(PBBCodeInput::insertTextButton('[subsubtitle]','[/subsubtitle]'))
							->Insert(PBBCodeInput::insertTextButton('[subsubsubtitle]','[/subsubsubtitle]'))
							->Insert(PBBCodeInput::insertTextButton('[p]','[/p]'))
							->Insert(PBBCodeInput::insertTextButton('[kw]','[/kw]'))
							->Insert(PBBCodeInput::insertTextButton('[url=]','[/url]'))
							->Insert(PBBCodeInput::insertTextButton('[notranslate]','[/notranslate]'))
							->Insert(PBBCodeInput::insertTextButton('[img=]','[/img]'))
							->Insert(PBBCodeInput::insertTextButton('','[br]'))
						->Insert(sEl('hr'))
							->Insert(PBBCodeInput::insertTextButton('[i]','[/i]'))
							->Insert(PBBCodeInput::insertTextButton('[b]','[/b]'))
							->Insert(PBBCodeInput::insertTextButton('[sub]','[/sub]'))
							->Insert(PBBCodeInput::insertTextButton('[sup]','[/sup]'))
						->Insert(sEl('hr'))
							->Insert(PBBCodeInput::insertTextButton('[list type=1AaIi]','[/list]'))
							->Insert(PBBCodeInput::insertTextButton(' [li]','[/li]'))
						->Insert(sEl('hr'))
							->Insert(PBBCodeInput::insertTextButton("[table border=1][caption]","[/caption][/table]"))
							->Insert(PBBCodeInput::insertTextButton(' [tr]','[/tr]'))
							->Insert(PBBCodeInput::insertTextButton('   [td]','[/td]'))
							->Insert(PBBCodeInput::insertTextButton('[td colrowspan=1]','[/td]'))
							->Insert(PBBCodeInput::insertTextButton('[]','[/]'))
						->Insert(sEl('hr'))
							->Insert(
								El('script')
										->setAtr('type','text/javascript')
									->Insert(new PText('function scrolltoEnd(){el=document.getElementById("'.$id.'");el.scrollTop=el.scrollHeight;}'))
									->Insert(new PText('function insertText(txt){el=document.getElementById("'.$id.'");el.value=el.value+(txt);}'))
									->Insert(new PText('function clearText(){el=document.getElementById("'.$id.'");if(confirm("Are you sure you want to clear the text content?"))el.value="";el.focus();}'))
									->Insert(new PText("
function insertAtCursor( before, after)
	{
	myField=document.getElementById(\"$id\");
	//IE support
	if (document.selection)
			{
			myField.focus();
			sel = document.selection.createRange();
			sel.text = myValue;
			}
		//MOZILLA/NETSCAPE support
		else
			if (myField.selectionStart || myField.selectionStart == '0')
					{
					var startPos = myField.selectionStart;
					var endPos = myField.selectionEnd;
					myField.value =
						myField.value.substring(0, startPos)
						+ before
						+ myField.value.substring(startPos,endPos)
						+ after
						+ myField.value.substring(endPos, myField.value.length);
					}
				else
					{
					myField.value += before+after;
					}
	myField.focus();
	}
										"))
								)
			;
		}
	}


?>