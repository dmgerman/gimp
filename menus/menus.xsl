<?xml version="1.0" encoding="utf-8"?>

<!-- This is an XSL transformation that we use to generate XML menu
     files. So far it contains a template to generate a menubar and a
     popup with identical content.
  -->

<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:param name="unstable-menus" />

  <xsl:output method="xml"
              version="1.0"
              encoding="utf-8"
              indent="yes"
              doctype-system="gtkuimanager.dtd" />

  <xsl:template match="/">
    <xsl:comment> This file is automatically generated. Do not edit! </xsl:comment>
    <xsl:apply-templates />
  </xsl:template>

  <xsl:template match="menubar-and-popup">
    <menubar>
      <xsl:attribute name="action"><xsl:value-of select="@action-name"/>-menubar</xsl:attribute>
      <xsl:apply-templates />
    </menubar>
    <menubar name="dummy-menubar">
      <menu>
        <xsl:attribute name="action"><xsl:value-of select="@action-name"/>-popup</xsl:attribute>
        <xsl:apply-templates />
      </menu>
    </menubar>
  </xsl:template>

  <xsl:template match="menuitems">
    <xsl:apply-templates />
  </xsl:template>

  <xsl:template match="menu[@action='debug-menu']">
    <xsl:if test="$unstable-menus='yes'">
      <xsl:call-template name="identity" />
    </xsl:if>
  </xsl:template>

  <xsl:template match="menu[@action='view-use-gegl']">
    <xsl:if test="$unstable-menus='yes'">
      <xsl:call-template name="identity" />
    </xsl:if>
  </xsl:template>

  <!-- need to strip the XInclude namespace declaration from the ui element -->
  <xsl:template match="ui">
    <ui>
      <xsl:apply-templates />
    </ui>
  </xsl:template>

  <xsl:template match="@*|node()" name="identity">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()" />
    </xsl:copy>
  </xsl:template>

</xsl:stylesheet>
