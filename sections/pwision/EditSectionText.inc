<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2009--12 Becheru Petru-Ioan

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

include_once ('inc/PBBCodeInput.inc');
include_once('inc/BBCode.inc');
include_once("inc/PFormSection.inc");
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
include_once("inc/Groups.inc");



/** 	The EditSectionText class is designed to model the section that allows a user to edit a section's text.
	*	\latexonly \label{PWision:Sections:EditSectionText} \index{EditSectionText} \endlatexonly
	*	\brief a section editor.
	*	\version 2.0.0
	*/
class EditSectionText extends PFormSection
	{
	function Head()
		{
		return parent::Head()
			->Insert(
				El('script')
					->setAtr('type','text/javascript')
					->setAtr('src','http://ajax.googleapis.com/ajax/libs/jquery/1.3.2/jquery.min.js')
				)
			->Insert(
				El('script')
					->setAtr('type','text/javascript')
					->setAtr('src','http://pietschsoft.com/demo/jHtmlArea/scripts/jHtmlArea-0.6.0.min.js')
				)
			->Insert(
				El('link')
					->setAtr('rel','Stylesheet')
					->setAtr('type','text/css')
					->setAtr('href','http://pietschsoft.com/demo/jHtmlArea/style/jHtmlArea.css')
				)
// 			->Insert( PBBCodeInput::Head(Main()->getLanguage(),array('textContent', 'description')) )
			;
		}
	protected function preprocessParam($param_name)
		{
		$_REQUEST[$param_name]=charset_decode_utf_8($_REQUEST[$param_name]);
		}
	function setParams()
		{
		$fulltext='/^[ -~\xA\xD\t]*$/i';//match printable ASCII + LF and CR
		$URL='`(^(http|ftp|https):\/\/[\w\-_]+(\.[\w\-_]+)+([\w\-\.,@?^=%&amp;:/~\+#]*[\w\-\@?^=%&amp;/~\+#])?$)|(^$)`i';
		$this
			->addParam('sectionname','/^[a-z][_a-z0-9 ]{1,62}$/i','')
			->addParam('xhtml',$fulltext,'')
			;
		}
	function if_not_all_parameters_are_set()
		{
		$this->ConstructLocation();
		parent::if_not_all_parameters_are_set();
		}
	function getTitle()
		{
		return lang($this->getName()).' '.lang($this->getParam('sectionname'));
		}
	function ProcessOK()
		{
/*		print(
			'['.
				stripslashes(html_entity_decode($this->getParam('xhtml'), ENT_QUOTES, 'UTF-8'))
			."]");*/
// 		return true;
		$tidy = new tidy();
		Sections::setBBCode($this->getParam('sectionname'),
// 		print(
			BBCode::HTML2BBCode
				(
				html_entity_decode
					(
					$tidy->repairString
						(
						'<html xmlns="http://www.w3.org/1999/xhtml"><head/><body>'.
						str_replace(
							array('<?xml version="1.0"?>'),
							array(''),
							stripslashes($this->getParam('xhtml'))
							).
						'</body></html>'
						), ENT_QUOTES, 'UTF-8'
					)
				)
			);
// 		Sections::setHTML($this->getParam('sectionname'),stripslashes($this->getParam('xhtml')));
		return false;
		}
	function createForm()
		{
		$FormContent=new PContent();
		
		$Sections=Main()->DB->fetch_all_query("select * from Sections order by `Sort`");
		array_push($Sections,Sections::Section('Root'));
		if ($this->wasParamSet('sectionname'))
				{
				$section=Sections::Section($this->getParam('sectionname'));
				
				$FormContent
					->Insert(new PInput("hidden",$this->getParam('sectionname'),"sectionname"))
					->Insert(
						El('div')
								->setAtr('style','clear:both')
							->Insert(
								TextArea('xhtml',$section['HTML'])
									->setAtr('id','xhtml')
								)
						)
					->Insert(
						El('script')
								->setAtr('type','text/javascript')
							->Insert(new PText('$("#xhtml").htmlarea({
                // Override/Specify the Toolbar buttons to show
                toolbar: [
                    ["html"],
                    ["bold", "italic", "underline", "subscript", "superscript"],
                    ["orderedlist","unorderedlist"],
                    ["h4", "h5", "h6"],
                    ["link", "unlink", "|", "image"],
                    ["cut", "copy", "paste"]
                ],

                toolbarText: $.extend({}, jHtmlArea.defaultOptions.toolbarText, {
                        "h4": "subtitle",
                        "h5": "subsubtitle",
                        "h6": "subsubsubtitle",
                    })

                });'))
						)
					->Insert(new PInput("submit",lang("Save!"),""))
					;
				}
			else
				{
				$FormContent
					->Insert(PTextlang('Section:') )
					->Insert(SSelect('sectionname',$Sections, null, 'Name', 'Name'))
					->Insert(new PInput("submit",lang("Edit!"),""))
					;
				}

		return PFormSection::createForm()
				->setAtr("method",'post')

			->Insert($FormContent)
			;
		}
	}
?>