<?xml version="1.0" encoding="UTF-8"?>

<!--  simple XSL transformation to create a header file from authors.xml  -->

<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:output method="text" />
  <xsl:template match="/gimp-authors">
<xsl:text>
/* NOTE: This file is autogenerated from authors.xml, do not edit it. */

/*
 * The main authors are Spencer Kimball and Peter Mattis.
 */

static const gchar *authors[] =
{
</xsl:text><xsl:apply-templates select="contributor" /><xsl:text>  NULL
};
</xsl:text>
  </xsl:template>

  <xsl:template match="contributor">  "<xsl:apply-templates />",
</xsl:template>

</xsl:stylesheet>
