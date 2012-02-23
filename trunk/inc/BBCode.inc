<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2010--12 Becheru Petru-Ioan

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

include_once('PProcessor.inc');
include_once('PDrawable.inc');

/** 	The PBBCode2HTML class is designed to be a BBCode to HTML convert class.
	*	\latexonly \label{PWision:PBBCode2HTML} \index{PBBCode2HTML} \endlatexonly
	*	\brief BBCode to HTML class.
	*	\version 1.1.0
	*	\par Example:
\code
include_once("PBBCode2HTML.inc");
$processor=new PBBCode2HTML('[b]bold text[/b]');
print( $processor->Run() );
\endcode
	*	\par Output:
\verbatim
<span style="font-weight: bold;">bold text</span>
\endverbatim
	*/
class PBBCode2HTML extends PProcessor
	{
	/// the BBCode text
	protected $BBCode;
	/**	Constructs
		*	\brief constructor
		*	\param $BBCode the BBCode text
		*/
	function PBBCode2HTML($BBCode)
		{
		$this->BBCode=$BBCode;
		PProcessor::PProcessor();
		}
	/// BBCodeXML
	protected $BBCodeXML;
	function PreProcess()
		{
		$this->RegulateBBCode();
		$this->xBBCode2XML();
		return parent::PreProcess();
		}
	protected $xBBCode;
	protected function RegulateBBCode()
		{
		//regulate the code
		$bbcode2xBBCode=array(
			//XML tag markers
			'`<`' => '_lt;'
			,'`>`' => '_gt;'
			//XML entity char
			,'`&`' => '_and_'

			,'`\[br\]`is'=>"[br/]"//new line(break)
			,'`\[lb\]`is'=>"[lb/]"//left bracket  [
			,'`\[rb\]`is'=>"[rb/]"//right bracket ]

			,'`\[url=([#-=%&_?\/.a-z0-9]+)\]`is'=>'[url href="$1"]'
				,'`\[url=([#-=%&_?\/.a-z0-9]+)[[:space:]]+title=[\\\\]*[\'"]?([&#;a-z0-9 ]+)[\\\\]*[\'"]?\]`is'=>'[url href="$1" title="$2"]'//url with title
			,"/\[url=([#-=%&_?\/.a-z0-9]+)[[:space:]]+name=([a-z0-9_]*)\]/is" => '[url href="$1" name="$2"]' //url with name
			,"/\[[*]url=([#-=%&_?\/.a-z0-9]+)\]/is" => '[url href="$1" target="_blank" ]' //href in new window
			,"/\[redirect=([#-=%&_?\/.a-z0-9]+)\]/is" => '[redirect href="$1"]' //redirection to an href, starting tag

			,"/\[([\/]?)\]/is" => '[$1lambda]' // lambda tag

			,'`\[lang=([-a-z0-9]{2,5})\]`is'=>'[lang language="$1"]'//language tag

			,"/\[img]([#-=%&_?\/.a-z0-9]*)\[\/img\]/is" => '[image_simple src="$1"/]' // simple image (without caption)
			,"/\[img=([#-=%&_?\/.a-z0-9]*)\][[:space:]]*\[\/img\]/is" => '[image_simple src="$1"/]' // simple image (without caption)
			,"/\[img=([#-=%&_?\/.a-z0-9]*)\]/is" => '[image_with_caption src="$1"]'//image with caption, starting tag
			,"/\[\/img\]/is" => '[/image_with_caption]'//image with caption, ending tag

			,"/\[list[[:space:]]+(type=['\"]?)?([1AaIi])['\"]?\]/is" => '[list type="$2"]' //unordered list

			,"/\[table[[:space:]]+(border=)?([0-9]+)\]/is" => '[table border="$2"]' //table with border
			,"/\[td[[:space:]]+colspan=[\\\\]*['\"]?([0-9]+)[\\\\]*['\"]?\]/is" => '[td colspan="$1"]' //table cell with colspan
			,"/\[td[[:space:]]+rowspan=[\\\\]*['\"]?([0-9]+)[\\\\]*['\"]?\]/is" => '[td rowspan="$1"]' //table cell with rowspan
			,"/\[td[[:space:]]+((((col)|(row))span)=[\\\\]*['\"]?([0-9]+)[\\\\]*['\"]?)[[:space:]]+((((col)|(row))span)=[\\\\]*['\"]?([0-9]+)[\\\\]*['\"]?)\]/is" => '[td $2="$6" $8="$12"]' //table cell

			);
		$this->xBBCode=BBCode::repeat_replace($bbcode2xBBCode,$this->BBCode,1);
 		return $this;
		}
	protected function & xBBCode2XML()
		{
		$xBBCode2XML=array(
			//XML tag markers
			'`\[`' => '<'
			,'`\]`' => '>'
			);
		$this->BBCodeXML=BBCode::repeat_replace($xBBCode2XML,'[xBBCode]'.$this->xBBCode.'[/xBBCode]',1);
		return $this;
		}
	/// the BBCodeXML translated
	protected $translated;
	function Process()
		{
		$this->translated=
			Object( new PXSLTFileXMLProcessor('inc/BBCodeXML2HTML.xslt',$this->BBCodeXML) )
				->Run()
			;
		return parent::Process();
		}
	function & PostProcess()
		{
		$XMLtagMarkers=array(
			'`_and_`' => '&'
			,'`&lt;`' => '<'
			,'`&gt;`' => '>'
			,'`_lt;`' => '&lt;'
			,'`_gt;`' => '&gt;'
			);
		$this->result=BBCode::repeat_replace($XMLtagMarkers,$this->translated,1);
		return $this;
		}
	}


/**	A namespace for BBCode related functions.
	*	\latexonly \label{PWision:BBCode} \index{BBCode} \endlatexonly
	*	\brief BBCode's namespace.
	*	\version 1.1.0
	*/
final class BBCode
	{
	/**	Compile a BBCoded text to HTML.
		*	\brief translate BBCode to HTML.
		*	\latexonly \label{PWision:Sections:BBCode2HTML} \index{BBCode!to HTML}\endlatexonly
		*	\version 1.0.0
		*	\param $text BBCoded input text string
		*	\return HTML encoded text string
		*/
	function BBCode2HTML($text)
		{
		return
			Object(new PBBCode2HTML($text))
				->Run()
			;
		}
	/**	Translate HTML to BBCode.
		*	\brief translate HTML to BBCode.
		*	\latexonly \label{PWision:Sections:HTML2BBCode} \index{BBCode!from HTML}\endlatexonly
		*	\version 1.0.0
		*	\param $text xHTML input text string
		*	\return BBCode encoded text string
		*/
	function HTML2BBCode($text)
		{
		$tag2ent=array(
			//CDATA
			'`<!\[CDATA\[`' => '__CDATA_START__'
			,'`\]\]>`' => '__CDATA_END__'
			//BBCode tag markers
			,'`\[`' => '&amp;#91;'
			,'`\]`' => '&amp;#93;'
			,'`[&]amp[;][#]91[;]`' => '[lb]'
			,'`[&]amp[;][#]93[;]`' => '[rb]'
			//CDATA restore
			,'`__CDATA_START__`' =>'<![CDATA['
			,'`__CDATA_END__`' =>']]>'
			);
		$text=BBCode::repeat_replace($tag2ent,$text,1);
		// xHTML2BBCode
		$translated=
			Object( new PXSLTFileXMLProcessor('inc/HTML2BBCode.xslt', $text ) )
				->Run()
			;
		//remove useless tags
		$bbcode_empty=array(
			'/<\?xml version="1.0"\?>/is' =>'' //XML version removed
 			,'`\[li\][[:space:]]*\[p\](.*?)\[\/p\][[:space:]]*\[\/li\]`is' => '[li]$1[/li]'
 			,'`\[td([a-z0-9"\'=[:space:]]*?)\][[:space:]]*\[p\](.*?)\[\/p\][[:space:]]*\[\/td\]`is' => '[td$1]$2[/td]'
 			,'`\[p\](\[img[=\/.a-z0-9_]*\]\[\/img\])\[\/p\]`is' =>'$1'

			,'`[[:space:]][[:space:]]+`is' => ' ' // multiple space is replaced by one space
			,'`[\xA\xD]+`is' => " "
			,'`\[\/b\][[:space:]]+\[b\]`is' => ' '
			,'`\[\/b\]\[b\]`is' => ''
			,'`\[\/i\]\[i\]`is' => ''
// 			,'/\[br\]/is'=>" "
			,'`\[sup\][[:space:]]*\[\/sup\]`' => ''
			,'`\[sub\][[:space:]]*\[\/sub\]`' => ''
			,'`\[p\][[:space:]]*\[\/p\]`' => ''
			);
		$translated=BBCode::repeat_replace($bbcode_empty,$translated);
		//beautifie the code
		$bbcode_beauty=array(
			'`\[\/p\]`is'=>"[/p]\n\n"
			,'`\[\/((sub)+title)\]`is'=>"[/$1]\n\n"
			,'`\[li\]`is'=>"\n [li]"
			,'`\[td([a-z0-9"\'=[:space:]]*?)\]`is'=>"\n  [td$1]"
			,'`\[tr\]`is'=>"\n [tr]"
			,'`\[\/tr\]`is'=>"\n [/tr]"
			,'`\[\/list\]`is'=>"\n[/list]\n\n"
			,'`\[\/table([a-z0-9"\'=[:space:]]*?)\]`is'=>"\n[/table$1]\n"
			// now clear the spaces before some tags
			,'`[ ]*\[p\]`is'=>"[p]"
			,'`[ ]*\[list\]`is'=>"[list]"
			,'`[ ]*\[table([a-z0-9"\'=[:space:]]*?)\]`is'=>"[table$1]"
			);
		$translated=BBCode::repeat_replace($bbcode_beauty,$translated,1);
		return $translated;
		}
	/**	Repeats a preg_replace until no more replacements are done.
		*	\brief repeated replace.
		*	\param $arr array of pairs([reg exp]=>[replacement])
		*	\param $it input text
		*	\param $max_repeats maximum number of repeats
		*	\return text string with the matched replacements done.
		*/
	static function repeat_replace($arr,$it,$max_repeats=128)
		{
		$ret=$it;
		for($count=1;$count!=0 && $max_repeats--;)//repeat until no replacements are done
			{
			$temp=preg_replace(
						array_keys($arr),
						array_values($arr),
						$ret,
						-1,
						$count
						);
			$ret=$temp;
			}
		return $ret;
		}
	}
?>