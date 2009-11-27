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
include_once("PPoint.php");
class PImage
	{
	private $Handler;
	public $Dimension;
	
	private $Color;
	function SetColor($r=0,$g=0,$b=0,$a=0)
		{
		$this->Color=imagecolorallocatealpha($this->Handler,$r,$g,$b,$a);
		return $this;
		}
		
	private $Brush;
	function copyimg(&$img)
		{
		imagedestroy($this->Handler);
		$this->Dimension=$img->Dimension;
		$this->Handler=imagecreatetruecolor($dim->X,$height->Y);
		imagesavealpha($this->Handler, true);
		imagecopy($this->Handler,$img->Handler,0,0,0,0,$img->Dimension->X,$img->Dimension-Y);
		}
	function SetBrush(&$img)
		{
		$this->Brush=new PImage(new PPoint(1,1));
		$this->Brush->copyimg($img);
		imagesetbrush($this->Handler,$this->Brush->Handler);
		$Color=IMG_COLOR_BRUSHED;
		return $this;
		}
		
		
	function TextAt($text,$At)
		{
		imagestring($this->Handler,2,$At->X,$At->Y,$text,$this->Color); 
		return $this;
		}
	function Line(PPoint $A, PPoint $B)
		{
		imageline($this->Handler,$A->X,$A->Y,$B->X,$B->Y,$this->Color);
		return $this;
		}
	function Ellipse($A,$B)
		{
		imagefilledellipse($this->Handler,$A->X,$A->Y,$B->X,$B->Y,$this->Color);
		return $this;
		}
	function Rectangle($A,$B)
		{
		imagefilledrectangle($this->Handler,$A->X,$A->Y,$B->X,$B->Y,$this->Color);
		return $this;
		}
	function Fill()
		{
		imagefill($this->Handler, 0, 0, $this->Color);
		return $this;
		}
	
	function PImage($dim)
		{
		$this->Dimension=$dim;
		
		$this->Handler=imagecreatetruecolor($dim->X,$dim->Y);
		imagesavealpha($this->Handler, true);
		
		$this->SetColor(0, 0, 0, 127)->Fill();
		$this->SetColor(0,0,0,0);
		
		}
	function Display($type="JPEG")
		{
		switch(strtoupper($type))
			{
			case "PNG":
				header("Content-type: image/png");
				imagepng($this->Handler);
				break;
			case "JPEG": 
				header("Content-type: image/jpeg");
				imagejpeg($this->Handler);
				break;
			}
		return $this;
		}
	function __destruct()
		{
		imagedestroy($this->Handler);
		}
	}
?>