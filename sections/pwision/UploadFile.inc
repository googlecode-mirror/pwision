<?php
/*
part of PWision toolkit: http://pwision.googlecode.com/
Copyright (C) 2010--11 Becheru Petru-Ioan

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
include_once("inc/PFormSection.inc");
include_once("inc/PRedirectSection.inc");
include_once("inc/PTable.inc");
include_once("inc/Users.inc");
include_once("inc/PMainComponent.inc");
include_once("externalAPI/recaptchalib.php");
/** 	The UploadFile class is designed to model a file upload section.
	*	\latexonly \label{PWision:UploadFile} \index{UploadFile}  \index{upload} \index{file}\endlatexonly
	*	\brief the UploadFile section.
	*	\version 1.3.0
	*	\note This section allows uploading of some sorts of files. See ProcessOK().
	*/
class UploadFile extends PFormSection
	{
	/**	Selects a random char from the sourse string until it creates a $length string, that is returned.
		*	\brief create a random string.
		*	\param $length the length of the returned string
		*	\param $source the sourse string
		*	\return a string of random chars
		*/
	private static function randStr(
			$length=8,
			$source='ABCDEFGHIJKLMNOPQRSTUWXYZabcdefghijklmnopqrstuwxyz0123456789'
			)
		{
		$length_of_sourse=strlen($source)-1;
		$ret='';
		while($length--)
			$ret.=$source[rand(0,$length_of_sourse)];
		return $ret;
		}
	/**
		*	\brief get a new name for a file.
		*	\param $file a file array(name,tmp_name,error)
		*	\param $keepOriginalName true for try to keep original filename
		*	\return the name of file
		*/
	protected function newName($path, $filename, $keepOriginalName)
		{
		$ext = '.'.strtolower( substr($filename, strrpos($filename, '.') + 1) );
		$name=substr($filename, 0, strrpos($filename, '.') - 1);
		if(
			$ext != '.jpeg' &&
			$ext != '.jpg' &&
			$ext != '.png' &&
			$ext != '.pdf' &&
			$ext != '.odt' &&
			$ext != '.txt' &&
			$ext != '.doc' &&
			$ext != '.ppt' &&
			$ext != '.zip' &&
			$ext != '.'
			)
				$ext='.txt';
		if($keepOriginalName)
			{
			while(file_exists($path . $filename))
					$filename=$name.'_'. UploadFile::randStr(8) . $ext;
			return $filename;
			}
		do
			$newname=UploadFile::randStr(16) . $ext;
		while(file_exists( $path . $newname));
		return $newname;
		}
	/**	Checks if an error ocured during uploading, checks if extension needs to be changed, creates a new random name for the file and moves it to /uploads/ dir.
		*	\brief move an uploaded file to /uploads/ dir.
		*	\param $file a file array(name,tmp_name,error)
		*	\param $keepOriginalName true for try to keep original filename
		*	\return the name of file
		*/
	protected function moveUploadedFile($file, $keepOriginalName=true)
		{
		$path=dirname(__FILE__).'/../../uploads/';
		$error_types = array(
			1=>'The uploaded file exceeds the upload_max_filesize directive in php.ini.',
			'The uploaded file exceeds the MAX_FILE_SIZE directive that was specified in the HTML form.',
			'The uploaded file was only partially uploaded.',
			'No file was uploaded.',
			6=>'Missing a temporary folder.',
			'Failed to write file to disk.',
			'A PHP extension stopped the file upload.'
			);
		if( $file['error'] > 0 ) throw new Exception($error_types[$file['error']]);
		$newname=$this->newName($path, preg_replace('`[^-_.a-z0-9]`i','_',basename($file['name'])), $keepOriginalName );
		if (move_uploaded_file($file['tmp_name'],$path . $newname))
				return $newname;
			else
				return false;
		}
	/**	
		*	\brief post process a file
		*	\param $newName the new name of the file
		*/
	function postProcessFile($newname,&$content)
		{
		$content
			->Insert(
				new PText("  [li][*url=/uploads/$newname]")
				)
				->Insert(
					El('a')
						->setAtr('href',"/uploads/$newname")
						->setAtr('target','_blank')
						->Insert(new PText($newname))
					)
			->Insert(
				new PText("[/url][/li]<br/>")
				)
			;
		}
	/// 	*	\todo add error messages when return false in ProcessOK()
	function ProcessOK()
		{
		$files=array();
		if( !isset($_FILES['file']) ) return false;
			else
				{
				$fdata=$_FILES['file'];
				if(is_array($fdata['name']))
						{
						for($i=0;$i<count($fdata['name']);++$i)
							{
							$files[]=array(
								'name'    	=>$fdata['name'][$i],
								'tmp_name'	=>$fdata['tmp_name'][$i],
								'error'		=>$fdata['error'][$i]
								);
							}
						}
					else
						$files[]=$fdata;
				}
		/*$resp = recaptcha_check_answer (Main()->reCAPTCHAprivatekey(),
												$_SERVER["REMOTE_ADDR"],
												$_POST["recaptcha_challenge_field"],
												$_POST["recaptcha_response_field"]);
		if (!$resp->is_valid)
			{
			$this->AddMessage("Captcha not ok! Try again");
			return false;
			}*/
		$content=El('div');
		foreach($files as $file)
			{
			$newname=false;
			try
				{
				$newname=$this->moveUploadedFile($file, isset($_REQUEST['keepOriginalName']));
				}
				catch(Exception $e)
					{
					$this->TheForm->Insert( new PText( $e->getMessage() ) );
					}
			if ($newname)
					{
					$this->postProcessFile($newname,$content);
					}
				else
					return false;
			}
		$content
			->InsertFirst(new PText('[list]<br/>'))
			->Insert(new PText('[/list]<br/>'));
		$this->TheForm->Insert($content);
		return true;
		}
	function & createForm()
		{
		return PFormSection::createForm()
				->setAtr("method","post")
				->setAtr('enctype','multipart/form-data')
			->Insert(
				Object(new PFieldSet(PTextlang("Choose the files")))
					->Insert(
						Object(new PInput("file","","file[]"))
							->setAtr('multiple','multiple')
						)
					//->Insert(PTextlang("select the file"))->Insert(new PSimpleTag("br"))
					//->Insert(new PText(recaptcha_get_html(Main()->reCAPTCHApublickey()) ) )
					->Insert(new PInput('checkbox','keepOriginalName','keepOriginalName'))
					->Insert(
						El('label')
							->setAtr('for','keepOriginalName')
							->Insert(PTextlang('Keep Original Filename'))
						)
					->Insert(sEl('br'))
					->Insert(new PInput("submit",lang("Upload!"),""))
				)
			;
		}
	}
?>