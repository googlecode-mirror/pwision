<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	>
<!--
BBCodeXML to HTML
version 1.2.0
Copyright (C) 2010,2011 Becheru Petru-Ioan

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

<!-- remove the xBBCode tag, but the content remains -->
<xsl:template match="xBBCode"><xsl:apply-templates/></xsl:template>

<!-- we don't care about the script element and its content -->
<xsl:template match="script"><!-- eat this --></xsl:template>


<!-- 0 structure -->

<!-- 0.1 subtitle -->
<xsl:template match="subtitle">
<h4><xsl:apply-templates/></h4>
</xsl:template>

<!-- 0.2 subsubtitle -->
<xsl:template match="subsubtitle">
<h5><xsl:apply-templates/></h5>
</xsl:template>

<!-- 0.3 subsubsubtitle -->
<xsl:template match="subsubsubtitle">
<h6><xsl:apply-templates/></h6>
</xsl:template>

<!-- 0.4 paragraph -->
<xsl:template match="p">
<p><xsl:apply-templates/></p>
</xsl:template>

<!-- 0.5 no translate tag -->
<xsl:template match="notranslate">
<span class="notranslate"><xsl:apply-templates/></span>
</xsl:template>

<!-- 0.5.1 language tag -->
<xsl:template match="lang">
&lt;span <xsl:if test="@language">lang="<xsl:value-of select="attribute::language" />"</xsl:if>&gt;<xsl:apply-templates/>&lt;/span&gt;
</xsl:template>


<!-- 0.6 line break -->
<xsl:template match="br">
<br/>
</xsl:template>

<!-- 0.7 lambda tag -->
<xsl:template match="lambda">
<span class="simple"><xsl:apply-templates/></span>
</xsl:template>

<!-- 0.8 left and right brackets [] -->
<xsl:template match="lb">[</xsl:template>
<xsl:template match="rb">]</xsl:template>


<!-- 1 lists -->

<!-- 1.1 list -->
<xsl:template match="list">
<xsl:choose>
	<xsl:when test="@type">&lt;ol type="<xsl:value-of select="attribute::type" />"&gt;<xsl:apply-templates/>&lt;/ol&gt;</xsl:when>
	<xsl:otherwise><ul><xsl:apply-templates/></ul></xsl:otherwise>
</xsl:choose>
</xsl:template>

<!-- 1.2 list item -->
<xsl:template match="li">
<li><xsl:apply-templates/></li>
</xsl:template>


<!-- 2 links -->

<!-- 2.1 url -->
<xsl:template match="url">
&lt;a<xsl:if test="@href"> href="<xsl:value-of select="attribute::href" />"</xsl:if><xsl:if test="@name"> name="<xsl:value-of select="attribute::name" />"</xsl:if><xsl:if test="@target"> target="<xsl:value-of select="attribute::target" />"</xsl:if><xsl:if test="@title"> title="<xsl:value-of select="attribute::title" />"</xsl:if>&gt;<xsl:apply-templates/>&lt;/a&gt;
</xsl:template>

<!-- 2.2 redirection -->
<xsl:template match="redirect">
<xsl:if test="@href">
&lt;a href="<xsl:value-of select="attribute::href" />"&gt;<xsl:apply-templates/>&lt;/a&gt;&lt;script type="text/javascript"&gt;setTimeout("redir()",1000);function redir(){window.location="<xsl:value-of select="attribute::href" />";}&lt;/script&gt;</xsl:if>
</xsl:template>


<!-- 3 visual -->

<!-- 3.1 simple images -->
<xsl:template match="image_simple"><xsl:if test="@src">&lt;img src="<xsl:value-of select="attribute::src" />"/&gt;</xsl:if></xsl:template>

<!-- 3.2 images with caption -->
<xsl:template match="image_with_caption">
<xsl:if test="@src">
<table><caption><xsl:apply-templates/></caption><tr><td>&lt;img src="<xsl:value-of select="attribute::src" />"/&gt;</td></tr></table></xsl:if>
</xsl:template>

<!-- 3.3 bold -->
<xsl:template match="b">
<span style="font-weight: bold;"><xsl:apply-templates/></span>
</xsl:template>

<!-- 3.4 italic -->
<xsl:template match="i">
<span style="font-style: italic;"><xsl:apply-templates/></span>
</xsl:template>

<!-- 3.5 underline -->
<xsl:template match="u">
<span style="text-decoration: underline;"><xsl:apply-templates/></span>
</xsl:template>

<!-- 3.6 overline -->
<xsl:template match="o">
<span style="text-decoration: overline;"><xsl:apply-templates/></span>
</xsl:template>

<!-- 3.7 subscript -->
<xsl:template match="sub">
<sub><xsl:apply-templates/></sub>
</xsl:template>

<!-- 3.8 superscript -->
<xsl:template match="sup">
<sup><xsl:apply-templates/></sup>
</xsl:template>


<!-- 4 tables -->

<!-- 4.1 table -->
<xsl:template match="table">
&lt;table<xsl:if test="@border"> border="<xsl:value-of select="attribute::border" />"</xsl:if>&gt;<xsl:apply-templates/>&lt;/table&gt;
</xsl:template>

<!-- 4.2 table row -->
<xsl:template match="tr">
<tr><xsl:apply-templates/></tr>
</xsl:template>

<!-- 4.3 table cell -->
<xsl:template match="td">&lt;td<xsl:if test="attribute::colspan &gt; 0"> colspan="<xsl:value-of select="attribute::colspan" />"</xsl:if><xsl:if test="attribute::rowspan &gt; 0"> rowspan="<xsl:value-of select="attribute::rowspan" />"</xsl:if>&gt;<xsl:apply-templates/>&lt;/td&gt;</xsl:template>

<!-- 4.4 caption -->
<xsl:template match="caption">
<caption><xsl:apply-templates/></caption>
</xsl:template>



<!-- 0  -->

<!-- 0.1 tag -->
<xsl:template match="tag">
<tag><xsl:apply-templates/></tag>
</xsl:template>

</xsl:stylesheet>