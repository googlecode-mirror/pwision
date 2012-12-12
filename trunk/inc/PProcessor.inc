<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2010,2012 Becheru Petru-Ioan

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

/** 	The PProcessor class is designed to be the base class for processing classes.
	*	\latexonly \label{PWision:PProcessor} \index{PProcessor} \endlatexonly
	*	\brief abstract processor class.
	*	\version 1.0.0
	*	\par Example:
\code
include_once("PProcessor.inc");
$P=new PProcessor();
print( $P->Run() );
\endcode
	*	\par Output:
\verbatim
\endverbatim
	*/
class PProcessor
	{
	/// the result
	protected $result;
	/**	Gets the processed result.
		*	\brief gets the result.
		*	\return the $result field.
		*/
	function getResult(){return $this->result;}
	/**	Sets the initial value of $result. Calls the PreProcess() method.
		*	\brief constructor
		*/
	function PProcessor()
		{
		$this->result=null;
		$this->PreProcess();
		}
	/**	This method preprocesses.
		*	\brief the preprocess method.
		*	\return reference to $this
		*/
	function & PreProcess()
		{
		return $this;
		}
	/**	This method processes.
		*	\brief the processing method.
		*	\return reference to $this
		*/
	function & Process()
		{
		return $this;
		}
	/**	This method postprecesses.
		*	\brief the postprocessing method.
		*	\return reference to $this
		*/
	function & PostProcess()
		{
		return $this;
		}
	/**	Calls Process() and PostProcess() methods.
		*	\brief Runs the processor.
		*	\return the result
		*/
	function Run()
		{
		$this->Process();
		$this->PostProcess();
		return $this->result;
		}
	}

/** 	The PXSLTFileProcessor class is designed to be XSTL file loader.
	*	\latexonly \label{PWision:PXSLTFileProcessor} \index{PXSLTFileProcessor} \endlatexonly
	*	\brief a XSTL file loader class.
	*	\version 1.0.0
	*/
class PXSLTFileProcessor extends PProcessor
	{
	/// the name of the XSTL file
	protected $filename;
	/**	Constructs
		*	\brief constructor
		*	\param $filename  the name of the XSTL file
		*/
	function PXSLTFileProcessor($filename)
		{
		$this->filename=$filename;
		PProcessor::PProcessor();
		}
	/// the XSLTProcessor object
	protected $xslt;
	/**	Loads the xslt as a DOMDocument and imports it as a XSLTProcessor in $xslt.
		*	\brief loads and imports the xslt.
		*	\return reference to $this
		*/
	function & PreProcess()
		{
		$xsl=new DOMDocument();
		$xsl->load($this->filename);
		$this->xslt=new XSLTProcessor();
		$this->xslt->importStylesheet( $xsl );
		return parent::PreProcess();
		}
	}

/** 	The PXSLTFileXMLProcessor class is designed to be a XSTL file processor of XML text.
	*	\latexonly \label{PWision:PXSLTFileXMLProcessor} \index{PXSLTFileXMLProcessor} \endlatexonly
	*	\brief XSTL File XML Processor class.
	*	\version 1.0.1
	*	\par Example:
\code
include_once("PXSLTFileXMLProcessor.inc");
print( );
\endcode
	*	\par Output:
\verbatim
\endverbatim
	*/
class PXSLTFileXMLProcessor extends PXSLTFileProcessor
	{
	/// the xml text that will be processed
	protected $xml_text;
	/**	Constructs
		*	\brief constructor
		*	\param $xml  the xml text that will be processed
		*/
	function PXSLTFileXMLProcessor($filename,$xml_text)
		{
		$this->xml_text=$xml_text;
		PXSLTFileProcessor::PXSLTFileProcessor($filename);
		}
	/// the XSLTProcessor object
	protected $xml;
	/**	Loads the $xml_text as a DOMDocument.
		*	\brief loads the xml.
		*	\return reference to $this
		*/
	function & PreProcess()
		{
		$this->xml= new DOMDocument();
		$this->xml->loadXML( $this->xml_text );
		return parent::PreProcess();
		}
	function & Process()
		{
		$this->result=$this->xslt->transformToXML( $this->xml );
		return parent::Process();
		}
	}


?>