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
/// \brief object with messages
interface IMessage
	{
		/**	Adds a new message.
			*	\brief Adds a new message.
			*	\param $text the message text
			*	\return reference to $this
			*/
		function AddMessage($text);
		/**	Gets the Message, followed , if != "", by a horizontal line
			*	\brief gets all the messages
			*	\version 1.1.0
			*/
		function getMessages();
	}
?>