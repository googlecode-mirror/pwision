<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:html="http://www.w3.org/1999/xhtml"
	>
<!--
xHTML to BBCode
version 1.5.0
Copyright (C) 2010-12 Becheru Petru-Ioan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
-->

<!-- remove the html tag, but the content remains -->
<xsl:template match="html:html"><xsl:apply-templates/></xsl:template>

<!-- we don't care about the head element and its content -->
<xsl:template match="html:head"><!-- eat this --></xsl:template>
<!-- we don't care about the script element and its content -->
<xsl:template match="html:script"><!-- eat this --></xsl:template>


<!-- remove the body tag, but the content remains -->
<xsl:template match="html:body"><xsl:apply-templates/></xsl:template>

<!-- remove the font tag, but the content remains with a space after it -->
<xsl:template match="html:font">[null]<xsl:apply-templates/> [/null]</xsl:template>


<!-- 0. titles -->

<!-- 0.1 subtitles -->
<xsl:template match="html:h1">
[subtitle]<xsl:apply-templates/>[/subtitle]
</xsl:template>
<xsl:template match="html:h4">
[subtitle]<xsl:apply-templates/>[/subtitle]
</xsl:template>

<!-- 0.2 subsubtitle -->
<xsl:template match="html:h2">
[subsubtitle]<xsl:apply-templates/>[/subsubtitle]
</xsl:template>
<xsl:template match="html:h5">
[subsubtitle]<xsl:apply-templates/>[/subsubtitle]
</xsl:template>

<!-- 0.3 subsubsubtitle -->
<xsl:template match="html:h3">
[subsubsubtitle]<xsl:apply-templates/>[/subsubsubtitle]
</xsl:template>
<xsl:template match="html:h6">
[subsubsubtitle]<xsl:apply-templates/>[/subsubsubtitle]
</xsl:template>


<!-- 1. lists -->

<!-- 1.0 list item -->
<xsl:template match="html:li">
 [li]<xsl:apply-templates/>[/li]</xsl:template>
<!-- 1.0.1 remove paragraphs tags from list items, but the content remains -->
<xsl:template match="html:li/html:p"><xsl:apply-templates/></xsl:template>

<!-- 1.1 unordered list -->
<xsl:template match="html:ul">
[list]<xsl:apply-templates/>
[/list]
</xsl:template>

<!-- 1.2 ordered list -->
<xsl:template match="html:ol">
[list type=1]<xsl:apply-templates/>
[/list]
</xsl:template>


<!-- 2. paragraph -->
<xsl:template match="html:p|html:div">
[p]<xsl:apply-templates/>[/p]
</xsl:template>


<!-- 3.Table -->

<!-- 3.1 table element with/without border -->
<xsl:template match="html:table">
[table<xsl:if test="attribute::border &gt; 0"> border=<xsl:value-of select="attribute::border" /></xsl:if>]<xsl:apply-templates />
[/table]
</xsl:template>

<!-- 3.2 table row -->
<xsl:template match="html:tr">
 [tr]<xsl:apply-templates/>
 [/tr]</xsl:template>

<!-- 3.3 captions -->
<xsl:template match="html:caption">
 [caption]<xsl:apply-templates/>
 [/caption]</xsl:template>


<!-- 3.4 table cell -->
<xsl:template match="html:td">
  [td<xsl:if test="attribute::colspan &gt; 0"> colspan=<xsl:value-of select="attribute::colspan" /></xsl:if><xsl:if test="attribute::rowspan &gt; 0"> rowspan=<xsl:value-of select="attribute::rowspan" /></xsl:if>]<xsl:apply-templates/>[/td]</xsl:template>
<!-- 3.4.0 remove paragraphs tags from table cells , but the content remains -->
<xsl:template match="html:td/html:p"><xsl:apply-templates/></xsl:template>


<!-- 4. Visual -->

<!-- 4.0 Images -->
<xsl:template match="html:img">[img=<xsl:value-of select="attribute::src" />]<xsl:apply-templates />[/img]</xsl:template>

<!-- 4.1 italic -->
<xsl:template match="html:i">[i]<xsl:apply-templates/>[/i]</xsl:template>

<!-- 4.2 Bold -->
<xsl:template match="html:b">[b]<xsl:apply-templates/>[/b]</xsl:template>

<!-- 4.3 Underline -->
<xsl:template match="html:u">[u]<xsl:apply-templates/>[/u]</xsl:template>

<!-- 4.4 Superscript -->
<xsl:template match="html:sup">[sup]<xsl:apply-templates/>[/sup]</xsl:template>

<!-- 4.5 Subscript -->
<xsl:template match="html:sub">[sub]<xsl:apply-templates/>[/sub]</xsl:template>


<!-- 5 Link -->
<xsl:template match="html:a">[url=<xsl:value-of select="attribute::href" /><xsl:if test="@name"> name=<xsl:value-of select="attribute::name" /></xsl:if>]<xsl:apply-templates />[/url]</xsl:template>

<!-- 0.6 line break -->
<xsl:template match="html:br">[br]</xsl:template>

</xsl:stylesheet>