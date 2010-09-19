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
include_once("PDrawable.inc");
include_once("PText.inc");
/// \brief object with a Last element
interface IhasLast
	{
	/**	get the last subelement
		*	\brief the last subelement
		*	\return the last subelement
		*/
	function & Last();
	}
/**
	*	\brief object with Insert
	*	\version 1.1.0
	*/
interface IInsertAble extends IhasLast
	{
	/**	Inserts $drawable in the subelements list
		*	\brief inserts a subelement.
		*	\param $drawable the PDrawable object that will be inserted as a subelement
		*	\return reference to $this pointer
		*/
	function & Insert(IDrawable &$drawable=null);
	/**	Inserts $drawable in the subelements list
		*	\brief inserts a subelement.
		*	\param $drawable the PDrawable object that will be inserted as a subelement
		*	\return reference to the inserted drawable
		*	\note future multithreaded PWision will introduce a mutex on this function
		*/
	function & LastInsert(IDrawable &$drawable=null);
	/**	Inserts $drawable as the first subelement.
		*	\brief inserts as the first subelement.
		*	\param $drawable the PDrawable object that will be inserted as the first subelement
		*	\return reference to $this pointer
		*/
	function & InsertFirst(IDrawable &$drawable=null);
	}
/// \brief object with Insert and Clone
interface IInsertAbleCloneAble extends IInsertAble, ICloneAble
	{}
/// \brief an object that is emptyable(Pop and Clear)
interface IEmptyAble
	{
	/**	removes the last subelement.
		*	\brief removes the last subelement.
		*	\return the poped object
		*/
	function Pop();
	/**	removes the first element.
		*	\brief removes the first subelement.
		*	\return the removed object
		*/
	function rmFirst();
	/** \brief clear the subelements array.
		* \return reference to $this pointer
		* \version 1.1
		*/
	function & Clear();
	}
/** \brief Content Interface
	*/
interface IContent extends IEmptyAble, IInsertAble
	{
	}
	
/// \brief drawable content
interface IDrawableContent extends IDrawable, IContent
	{
	}
	
/// \brief IDrawableCloneAbleContent
interface IDrawableCloneAbleContent extends IDrawableContent, IInsertAbleCloneAble
	{}

/** 	The PContent class is designed to model a drawable object that is formed of drawable objects(called subelements). A PContent object is drawn by drawn each subelement, in the insertion order.
	*	\latexonly \label{PWision:PContent} \index{PContent} \index{subelements} \index{insertion} \endlatexonly
	*	\brief a text made of subtexts.
	*	\version 2.3.0
	*	\par Example:
\code
include_once("inc/PText.inc");
include_once("inc/PContent.inc");
$Content = Object(new PContent())
	->Insert( new PText( "First string!" ) )
	->Insert( new PText( "Second string!" ) );
print( $Content->Draw() );
\endcode
	*	\par Output:
\verbatim
First string!Second string!
\endverbatim
	*/
class PContent extends PDrawable implements IDrawableCloneAbleContent
	{
		
	protected
		/**	array of drawable objects
			*	\brief the subelements.
			*/
		$SubElements=array();
	/**	Inserts $drawable in the subelements list
		*	\brief inserts a subelement.
		*	\param $drawable the PDrawable object that will be inserted as a subelement
		*	\return reference to $this pointer
		*/
	function & Insert(IDrawable &$drawable=null)
		{
		array_push($this->SubElements,$drawable);
		return $this;
		}
	/**	Inserts $drawable in the subelements list
		*	\brief inserts a subelement.
		*	\param $drawable the PDrawable object that will be inserted as a subelement
		*	\return reference to the inserted drawable
		*	\note future multithreaded PWision will introduce a mutex on this function
		*/
	function & LastInsert(IDrawable &$drawable=null)
		{
		$this->Insert($drawable);
		return $this->Last();
		}
	/**	Inserts $drawable as the first subelement.
		*	\brief inserts as the first subelement.
		*	\param $drawable the PDrawable object that will be inserted as the first subelement
		*	\return reference to $this pointer
		*/
	function & InsertFirst(IDrawable &$drawable=null)
		{
		array_unshift($this->SubElements,$drawable);
		return $this;
		}
	/**	removes the last inserted element.
		*	\brief removes the last subelement.
		*	\return the poped object
		*/
	function Pop()
		{
		return array_pop( $this->SubElements );
		}
	/**	removes the first element.
		*	\brief removes the first subelement.
		*	\return the removed object
		*/
	function rmFirst()
		{
		return array_shift( $this->SubElements );
		}
	/** \brief clear the subelements array.
		* \return reference to $this pointer
		* \version 1.1
		*/
	function & Clear()
		{
		$this->SubElements=array();
		return $this;
		}
	/**	get the last inserted subelement
		*	\brief the last subelement
		*	\return the last subelement
		*/
	function & Last()
		{
		end($this->SubElements);//move the index pointer to the last array item
		return $this->SubElements[key($this->SubElements)];
		}
	///It draws each non-null subelement and concatenates the results.
	function Draw()
		{
		///the content of the PContent
		$Content="";
		foreach ($this->SubElements as $elem)
			if($elem) $Content.=$elem->Draw();
		return $Content;
		}
	/** \brief initialisation method.
		* \param $arr the PContent::SubElements member initial value
		*/
	function PContent(array $arr=array())
		{
		//print("{PContent ");
		$this->SubElements=$arr;
		//print(" PContent}");
		}
	}

/** 	The PContentWithFrame class is designed to model a PContent that will be drawn between 2 PDrawable objects.
	*	\latexonly \label{PWision:PContentWithFrame} \index{PContentWithFrame} \index{frame} \endlatexonly
	*	\brief a framed PContent
	*	\version 2.1.0
	*	\par Example:
\code
include_once("inc/PTags.inc");
$CF=new PContentWithFrame(
		Object( new PContent() )
			->Insert(new PText("^"))
			->Insert(new PComplexTag("x"))
		,
		Object( new PContent() )
			->Insert(new PEndingTag("x"))
			->Insert(new PText("^"))
	);
$CF->getCenterFrame()->Insert(new PText("_"));
print( $CF->Draw() );
\endcode
	*	\par Output:
\verbatim
^<x>_</x>^
\endverbatim
	*/
class PContentWithFrame extends PDrawable implements IDrawableCloneAbleContent
	{
	/// left PDrawable
	protected $LeftFrame;
		/** \brief sets PContentWithFrame::LeftFrame
			* \param $left the left frame
			* \return reference to $this pointer
			*/
		protected function setLeftFrame(IDrawable $left){$this->LeftFrame=$left; return $this;}
		/** \brief gets PContentWithFrame::LeftFrame
			* \return the left frame
			*/
		protected function & getLeftFrame(){return $this->LeftFrame;}
	/// right PDrawable
	protected $RightFrame;
		/** \brief sets PContentWithFrame::RightFrame
			* \param $right the right frame
			* \return reference to $this pointer
			*/
		protected function setRightFrame(IDrawable $right){$this->RightFrame=$right; return $this;}
		/** \brief gets PContentWithFrame::RightFrame
			* \return the right frame
			*/
		protected function & getRightFrame(){return $this->RightFrame;}
	/// center PDrawable
	protected $CenterFrame;
		/** \brief sets PContentWithFrame::CenterFrame
			* \param $right the center frame
			* \return reference to $this pointer
			*/
		protected function setCenterFrame(IDrawableContent $right){$this->CenterFrame=$right; return $this;}
		/** \brief gets PContentWithFrame::CenterFrame
			* \return the center frame
			*/
		function & getCenterFrame(){return $this->CenterFrame;}


	/**	It constructs the PContent parent and then calls setFrames() to set the frames.
		*	\brief initialisation method.
		*	\param $leftFrame left frame
		*	\param $rightFrame right frame
		*	\param $centerFrame centerFrame
		*/
	function PContentWithFrame(
					IDrawable $leftFrame =NULL,
					IDrawable $rightFrame = NULL,
					IDrawableContent $centerFrame =null
					)
		{
		PDrawable::PDrawable();
		$this
			->setLeftFrame( ($leftFrame!=NULL)?($leftFrame):( new PDrawable() )  )
			->setRightFrame( ($rightFrame!=NULL)?($rightFrame):( new PDrawable() )  )
			->setCenterFrame( ($centerFrame!=NULL)?($centerFrame):( new PContent() )  )
			;
		}
	/**	Inserts $drawable in the subelements list
		*	\brief inserts a subelement.
		*	\param $drawable the PDrawable object that will be inserted as a subelement
		*	\return reference to $this pointer
		*/
	function & Insert(IDrawable &$drawable=null)
		{
		$this->getCenterFrame()->Insert($drawable);
		return $this;
		}
	/**	Inserts $drawable in the subelements list
		*	\brief inserts a subelement.
		*	\param $drawable the PDrawable object that will be inserted as a subelement
		*	\return reference to the inserted drawable
		*	\note future multithreaded PWision will introduce a mutex on this function
		*/
	function & LastInsert(IDrawable &$drawable=null)
		{
		$this->Insert($drawable);
		return $this->Last();
		}
	/**	Inserts $drawable as the first subelement.
		*	\brief inserts as the first subelement.
		*	\param $drawable the PDrawable object that will be inserted as the first subelement
		*	\return reference to $this pointer
		*/
	function & InsertFirst(IDrawable &$drawable=null)
		{
		$this->getCenterFrame()->InsertFirst($drawable);
		return $this;
		}
	/**	removes the last inserted element.
		*	\brief removes the last subelement.
		*	\return the poped object
		*/
	function Pop()
		{
		return $this->getCenterFrame()->Pop();
		}
	/**	removes the first element.
		*	\brief removes the first subelement.
		*	\return the removed object
		*/
	function rmFirst()
		{
		return $this->getCenterFrame()->rmFirst();
		}
	/** \brief clear the subelements array.
		* \return reference to $this pointer
		*/
	function & Clear()
		{
		$this->getCenterFrame()->Clear();
		return $this;
		}
	/**	get the last inserted subelement
		*	\brief the last subelement
		*	\return the last subelement
		*/
	function & Last()
		{
		return $this->getCenterFrame()->Last();
		}
	///draws $this between LeftFrame and RightFrame
	function Draw()
		{
		return
			$this->LeftFrame->Draw().
			$this->CenterFrame->Draw().
			$this->RightFrame->Draw();
		}
	}

/** 	The PContentInContent class is designed to model a content in content.
	*	\latexonly \label{PWision:PContentInContent} \index{PContentInContent} \endlatexonly
	*	\brief content in content.
	*	\version 1.2.0
	*	\par Example:
				Implemention of PBubble.
\code
include_once("inc/PElement.inc");
$T= new PContentInContent
		(
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
$T->Insert(new PText("xXx"));
print( $T );
\endcode
	*	\par Output:
\verbatim
<div class="Bubble">
	<div class="BubbleSideLeft">&nbsp;</div>
	<div class="BubbleInside">xXx</div>
	<div class="BubbleSideRight">&nbsp;</div>
</div>
\endverbatim
	*/
class PContentInContent extends PDrawable implements IDrawableCloneAbleContent
	{
	/// the Content
	private $Content;
	/**	Gets the inner content of $this->Content.
		*	\brief inner content
		*	\return the last element of $this->Content
		*/
	function & InnerContent()
		{
		return $this->Content->Last();
		}
	/**	Inserts $drawable in the subelements list
		*	\brief inserts a subelement.
		*	\param $drawable the PDrawable object that will be inserted as a subelement
		*	\return reference to $this pointer
		*/
	function & Insert(IDrawable &$drawable=null)
		{
		$this->InnerContent()->Insert($drawable);
		return $this;
		}
	/**	Inserts $drawable in the subelements list
		*	\brief inserts a subelement.
		*	\param $drawable the PDrawable object that will be inserted as a subelement
		*	\return reference to the inserted drawable
		*	\note future multithreaded PWision will introduce a mutex on this function
		*/
	function & LastInsert(IDrawable &$drawable=null)
		{
		$this->InnerContent()->Insert($drawable);
		return $this->Last();
		}
	/**	Inserts $drawable as the first subelement.
		*	\brief inserts as the first subelement.
		*	\param $drawable the PDrawable object that will be inserted as the first subelement
		*	\return reference to $this pointer
		*/
	function & InsertFirst(IDrawable &$drawable=null)
		{
		$this->InnerContent()->Insert($drawable);
		return $this;
		}
	/**	removes the last inserted element.
		*	\brief removes the last subelement.
		*	\return the poped object
		*/
	function Pop()
		{
		return $this->InnerContent()->Pop();
		}
	/**	removes the first element.
		*	\brief removes the first subelement.
		*	\return the removed object
		*/
	function rmFirst()
		{
		return $this->InnerContent()->rmFirst();
		}
	/** \brief clear the subelements array.
		* \return reference to $this pointer
		*/
	function & Clear()
		{
		$this->InnerContent()->Clear();
		return $this;
		}
	/**	get the last inserted subelement
		*	\brief the last subelement
		*	\return the last subelement
		*/
	function & Last()
		{
		return $this->InnerContent()->Last();
		}
	/**	Constructs
		*	\brief constructor
		*	\param $Content the Content
		*	\param $InnerContent the inner content for $Content
		*/
	function PContentInContent(IDrawableContent $Content,IDrawableContent $InnerContent)
		{
		$this->Content=$Content;
		$this->Content->Insert($InnerContent);
		}
	///It draws each non-null subelement and concatenates the results.
	function Draw()
		{
		return $this->Content->Draw();
		}
	}


/** 	The PContentWithTextFrame class is designed to model a PContent that will be drawn between 2 text strings.
	*	\latexonly \label{PWision:PContentWithTextFrame} \index{PContentWithTextFrame} \index{text} \index{string} \index{frame} \endlatexonly
	*	\brief a text framed PContent.
	*	\version 1.1.0
	*	\par Example:
\code
include_once("inc/PContent.inc");
$Content=Object(new PContentWithTextFrame("[left_frame::.. "," ..::right_frame]"))
   ->Insert(new PText("Inner Content"));
print( $Content->Draw() );
\endcode
	*	\par Output:
\verbatim
[left_frame::.. Inner Content ..::right_frame]
\endverbatim
	*/
class PContentWithTextFrame extends PContentWithFrame
	{
	/**	constructs a PContent that will be drawn between 2 text strings.
		*	\brief constructor
		*	\param $leftText the left frame text
		*	\param $rightText the right frame text
		*/
	function PContentWithTextFrame(	$leftText = "",	$rightText = "")
		{
		PContentWithFrame::PContentWithFrame( new PText($leftText), new PText($rightText));
		}
	}
?>