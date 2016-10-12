<?xml version="1.0" encoding="WINDOWS-1251"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <table border="1">
            <tr align="center">
                <td>Название</td>
                <td>Расстояние от солнца</td>
                <td>Период обращения</td>
                <td>Период вращения вокруг своей оси</td>
                <td>Масса относительно Земли</td>
                <td>Диаметр</td>
                <td>Количество спутников</td>
            </tr>
            <xsl:for-each select="solar/planet">
                <xsl:sort order="ascending" select="satellite_number"/>
                <xsl:sort order="ascending" select="@caption"/>
                <tr align="center">
                    <td><xsl:value-of select="@caption"/></td>
                    <td><xsl:value-of select="satellite_number"/></td>
                    <td><xsl:value-of select="weight"/> <xsl:value-of select="weight/@unit"/></td>
                    <td><xsl:value-of select="diametr"/> <xsl:value-of select="diametr/@unit"/></td>
                    <td><xsl:value-of select="revolution_period"/> <xsl:value-of select="revolution_period/@unit"/></td>
                    <td><xsl:value-of select="circulation_period"/> <xsl:value-of select="circulation_period/@unit"/></td>
                    <td><xsl:value-of select="distance"/> <xsl:value-of select="distance/@unit"/></td>
                </tr>
            </xsl:for-each>
        </table>
    </xsl:template>
</xsl:stylesheet>