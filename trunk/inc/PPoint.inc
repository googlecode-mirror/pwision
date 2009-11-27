<?
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
class PPoint
	{
	public $X;
	public $Y;
	function PPoint($x,$y)
		{
		$this->X=$x;$this->Y=$y;
		}
	function Normalize()
		{
		$len=sqrt($this->X*$this->X+$this->Y*$this->Y);
		if($len==0)$len=0.001;
		$this->X/=$len;
		$this->Y/=$len;
		return $this;
		}
	function Rotate($radians)
		{
		$x=$this->X;$y=$this->Y;
		$this->X = cos($radians) * $x - sin($radians) * $y;
		$this->Y = sin($radians) * $x + cos($radians) * $y;
		return $this;
		}
	}
?>