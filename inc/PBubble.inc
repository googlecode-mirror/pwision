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
/** 	The PBubble class is designed to model a text that is surround by a bubble. A bubble is formed from the left part(an image), the middle part(a drawable with a background) and the right part(an image). When the parts are drawn they form a bubble. See the example of PContentInContent.
	*	\latexonly \label{PWision:PBubble} \index{PBubble} \endlatexonly
	*	\brief a bubble.
	*	\version 1.2.1
	*	\par Example:
\code
include_once("inc/PBubble.inc");
$aL= Object(new PBubble())
	->Insert(new PText("text in leaf"));
print( $aL->Draw() );
\endcode
	*	\par Output:
\verbatim
<div class="Bubble">
	<div class="BubbleSideLeft">&nbsp;</div>
	<div class="BubbleInside"><div>text in leaf</div></div>
	<div class="BubbleSideRight">&nbsp;</div>
</div>
\endverbatim
	*/
class PBubble extends PContentInContent
	{
	function PBubble()
		{
		PContentInContent::PContentInContent(
			Object(new PElement("div"))
				->setAtr("class","Bubble")
			,
			new PContentWithFrame(
				Object(new PElement("div"))
						->setAtr("class","BubbleSideLeft")
					->Insert(new PText("&nbsp;"))
				,
				Object(new PElement("div"))
						->setAtr("class","BubbleSideRight")
					->Insert(new PText("&nbsp;"))
				,
				Object(new PElement("div"))
						->setAtr("class","BubbleInside")
				)
			);
		}
	}
?>