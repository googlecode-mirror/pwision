<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2010 Becheru Petru-Ioan

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


include_once('PElement.inc');
include_once('PText.inc');

/** 	The PVirtualKeyboard class is designed to functions to implement a virtual keyboard on the website.
	*	\latexonly \label{PWision:PVirtualKeyboard} \index{PVirtualKeyboard} \index{keyboard} \index{virtual keyboard} \index{google} \endlatexonly
	*	\brief a virtual keyboard class.
	*	\version 1.0.0
	*	\par Example:
\code
\endcode
	*	\par Output:
\verbatim
\endverbatim
	*/
class PVirtualKeyboard
	{
	/**	Constructs the two scripts needed to implement google virtual keyboard.
		*	\brief head script
		*	\param $lang language code
		*	\param $ids ids of the inputs where the keyboard will be active
		*	\return a PContent object containg the script
		*/
	static function Head($lang='en',$ids=array('textContent'))
		{
		return Object(new PContent)
			->Insert(
				El('script')
						->setAtr('type','text/javascript')
						->setAtr('src','http://www.google.com/jsapi')
				)
			->Insert(
				El('script')
						->setAtr('type','text/javascript')
					->Insert(new PText('
// Load the Google Onscreen Keyboard API
google.load("elements", "1", {packages: "keyboard"});

var kbd;  // A Keyboard object.

// Draw a list of keyboard layouts in their native languages.
// User can click any of them to switch to that keyboard layout.
function drawMenu() {
	html = ["<select onchange=\'kbd.setLayout(this.options[this.selectedIndex].value)\' >"];
	html.push("<option value=\"en\" >", "'.lang('Select a layout for the virtual keyboard').'", "</option>");
	for (var i in google.elements.keyboard.LayoutCode) {
		var code = google.elements.keyboard.LayoutCode[i];
		var name = google.elements.keyboard.getLayoutName(code);
		html.push("<option value=\"", code, "\" >", name, "</option>");
	}
			html.push("</select>");
	document.getElementById("kbSelect").innerHTML += html.join("");
}


function onLoad() {
	// Create an instance on Keyboard.
	kbd = new google.elements.keyboard.Keyboard([
		google.elements.keyboard.LayoutCode.ENGLISH],
		["'.implode('", "',$ids).'"]);
	drawMenu();
	kbd.setLayout("'.$lang.'");
}

google.setOnLoadCallback(onLoad);
					'))
				)
			;
		}
	/**	Constructs a div PElement and sets the id to kbSelect.
		*	\brief keyboard layer selector.
		*	\return a div PElement
		*/
	static function kbSelect()
		{
		return
				El('div')
					->setAtr('id','kbSelect')
				;
		}
	}


?>