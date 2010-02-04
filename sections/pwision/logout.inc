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
include_once("inc/PRedirectSection.inc");
include_once("inc/Users.inc");
/** 	The logout class is designed to model the section where a user logs out(becoming guest).
	*	\latexonly \label{PWision:Sections:logout} \index{logout} \index{guest} \index{user} \endlatexonly
	*	\brief a logout section.
	*	\version 2.1.0
	*/
class logout extends PRedirect2Section
	{
	function logout()
		{
		PRedirect2Section::PRedirect2Section("Root");
		Users::LogOut();
		}
	function Chapter1Title()
		{
		return PRedirect2Section::Chapter1Title()
			->Insert( new PText(lang("You are now logged out.")) );
		}
	}
?>