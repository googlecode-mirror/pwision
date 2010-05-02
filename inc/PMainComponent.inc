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
/** 	The PMainComponent is a final class that holds the static variable PMainComponent::$Main.
	*	\latexonly \label{PWision:PMainComponent} \index{PMainComponent} \endlatexonly
	*	\brief the holder of the Main variable .
	*	\version 1.1.0
	*/
final class PMainComponent
	{
	/** 	The $Main variable is a reference to webpage object.
		*	\brief reference to the webpage object.
		*/
	static public $Main;
	/**	Used by lang() function.
		*	\brief language array
		*/
	static public $Lang=array();
	}
/** 	
	*	\brief reference to the webpage object.
	*	\return PMainComponent::$Main
	*/
function & Main()
	{
	return PMainComponent::$Main;
	}

/**
	*	\brief translate a text.
	*	\param $text the text
	*	\return the translated text, if translation is defined; else the original text
	*/
function lang($text)
	{
	return isset(PMainComponent::$Lang[$text])
		?PMainComponent::$Lang[$text]
		:$text;
	}
/**
	*	\brief translated text in PText.
	*	\param $text the text
	*	\return a new PText object with a translated text
	*/
function PTextlang($text)
	{
	return new PText(lang($text));
	}
?>