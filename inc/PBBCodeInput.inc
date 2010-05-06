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


include_once('PForm.inc');

/** 	The PBBCodeInput class is designed to be a BBCode input textarea with button for BBCode tags.
	*	\latexonly \label{PBBCodeInput:PBBCodeInput} \index{PBBCodeInput} \index{BBCode} \index{textarea} \endlatexonly
	*	\brief BBCode input textarea.
	*	\version 1.1.0
	*	\par Example:
\code
include_once("PBBCodeInput.inc");
print( new PBBCodeInput('the text', 'text','textContent') );
\endcode
	*	\par Output:
\verbatim
<input type="button" value="Clear Text!" onclick="clearText()"/><input type="button" value="Scroll down!" onclick="scrolltoEnd()"/><input type="submit" value="Submit Changes!"/><br></br><textarea name="text" rows="20" id="textContent">the text</textarea><br></br>Insert:<br></br><div class="BBCodes" onclick="insertAtCursor('','&#258;')">&#258;</div><div class="BBCodes" onclick="insertAtCursor('','&#259;')">&#259;</div><div class="BBCodes" onclick="insertAtCursor('','&#194;')">&#194;</div><div class="BBCodes" onclick="insertAtCursor('','&#226;')">&#226;</div><div class="BBCodes" onclick="insertAtCursor('','&#206;')">&#206;</div><div class="BBCodes" onclick="insertAtCursor('','&#238;')">&#238;</div><div class="BBCodes" onclick="insertAtCursor('','&#x218;')">&#x218;</div><div class="BBCodes" onclick="insertAtCursor('','&#x219;')">&#x219;</div><div class="BBCodes" onclick="insertAtCursor('','&#x21A;')">&#x21A;</div><div class="BBCodes" onclick="insertAtCursor('','&#x21B;')">&#x21B;</div><hr/><div class="BBCodes" onclick="insertAtCursor('[subtitle]','[/subtitle]')">[subtitle][/subtitle]</div><div class="BBCodes" onclick="insertAtCursor('[subsubtitle]','[/subsubtitle]')">[subsubtitle][/subsubtitle]</div><div class="BBCodes" onclick="insertAtCursor('[subsubsubtitle]','[/subsubsubtitle]')">[subsubsubtitle][/subsubsubtitle]</div><div class="BBCodes" onclick="insertAtCursor('[p]','[/p]')">[p][/p]</div><div class="BBCodes" onclick="insertAtCursor('[kw]','[/kw]')">[kw][/kw]</div><div class="BBCodes" onclick="insertAtCursor('[notranslate]','[/notranslate]')">[notranslate][/notranslate]</div><div class="BBCodes" onclick="insertAtCursor('[img=]','[/img]')">[img=][/img]</div><div class="BBCodes" onclick="insertAtCursor('','[br]')">[br]</div><hr/><div class="BBCodes" onclick="insertAtCursor('[i]','[/i]')">[i][/i]</div><div class="BBCodes" onclick="insertAtCursor('[b]','[/b]')">[b][/b]</div><div class="BBCodes" onclick="insertAtCursor('[sub]','[/sub]')">[sub][/sub]</div><div class="BBCodes" onclick="insertAtCursor('[sup]','[/sup]')">[sup][/sup]</div><hr/><div class="BBCodes" onclick="insertAtCursor('[list type=1AaIi]','[/list]')">[list type=1AaIi][/list]</div><div class="BBCodes" onclick="insertAtCursor(' [li]','[/li]')"> [li][/li]</div><hr/><div class="BBCodes" onclick="insertAtCursor('[table border=1][caption]','[/caption][/table]')">[table border=1][caption][/caption][/table]</div><div class="BBCodes" onclick="insertAtCursor(' [tr]','[/tr]')"> [tr][/tr]</div><div class="BBCodes" onclick="insertAtCursor('   [td]','[/td]')">   [td][/td]</div><div class="BBCodes" onclick="insertAtCursor('[td colrowspan=1]','[/td]')">[td colrowspan=1][/td]</div><div class="BBCodes" onclick="insertAtCursor('[]','[/]')">[][/]</div><hr/><script type="text/javascript">function scrolltoEnd(){el=document.getElementById("textContent");el.scrollTop=el.scrollHeight;}function insertText(txt){el=document.getElementById("textContent");el.value=el.value+(txt);}function clearText(){el=document.getElementById("textContent");if(confirm("Are you sure you want to clear the text content?"))el.value="";el.focus();}
function insertAtCursor( before, after)
	{
	myField=document.getElementById("textContent");
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
										</script>
\endverbatim
	*/
class PBBCodeInput extends PContent
	{
	/**	Creates an input button that insert a text when clicked.
		*	\brief create a button that inserts text.
		*	\version 2.0.0
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
				Object(new PInput("button","Clear Text!",""))
					->setAtr('onclick', 'clearText()')
				)
			->Insert(
				Object(new PInput("button","Scroll down!",""))
					->setAtr('onclick', 'scrolltoEnd()')
				)
			->Insert(new PInput("submit","Submit Changes!",""))
			->Insert(El('br'))
			->Insert(
				TextArea($name,$text)
					->setAtr('id',$id)
				)
							->Insert(El('br'))
						->Insert(new PText('Insert:') )->Insert(El('br'))
							->Insert(PBBCodeInput::insertTextButton('','&#258;'))
							->Insert(PBBCodeInput::insertTextButton('','&#259;'))
							->Insert(PBBCodeInput::insertTextButton('','&#194;'))
							->Insert(PBBCodeInput::insertTextButton('','&#226;'))
							->Insert(PBBCodeInput::insertTextButton('','&#206;'))
							->Insert(PBBCodeInput::insertTextButton('','&#238;'))
							->Insert(PBBCodeInput::insertTextButton('','&#x218;'))
							->Insert(PBBCodeInput::insertTextButton('','&#x219;'))
							->Insert(PBBCodeInput::insertTextButton('','&#x21A;'))
							->Insert(PBBCodeInput::insertTextButton('','&#x21B;'))
						->Insert(sEl('hr'))
							->Insert(PBBCodeInput::insertTextButton('[subtitle]','[/subtitle]'))
							->Insert(PBBCodeInput::insertTextButton('[subsubtitle]','[/subsubtitle]'))
							->Insert(PBBCodeInput::insertTextButton('[subsubsubtitle]','[/subsubsubtitle]'))
							->Insert(PBBCodeInput::insertTextButton('[p]','[/p]'))
							->Insert(PBBCodeInput::insertTextButton('[kw]','[/kw]'))
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