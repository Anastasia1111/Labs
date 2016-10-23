<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">

    </xsl:template>
    <xsl:template match="/">
        <html>
            <body>
                <table border="1">
                    <tr align="center">
	   <td>#</td>
                        <td>Название</td>
                        <td>Расстояние от солнца</td>
                        <td>Период обращения</td>
                        <td>Период вращения вокруг своей оси</td>
                        <td>Масса относительно Земли</td>
                        <td>Диаметр</td>
                        <td>Количество спутников</td>
                    </tr>
                    <xsl:for-each select="solar/planet">
                        <xsl:sort order="descending" data-type = "number" select="satellite_number"/>
                        <xsl:choose>
                        <xsl:when test="satellite_number &gt; 0 and position() mod 2 = 0">
                        <tr align="center" bgcolor="#823456">
                            <td><xsl:value-of select="position()" /></td>
                            <td><xsl:value-of select="@caption"/></td>
	                        <td><xsl:value-of select="distance"/> <xsl:value-of select="distance/@unit"/></td>
							<td><xsl:value-of select="circulation_period"/> <xsl:value-of select="circulation_period/@unit"/></td>
							<td><xsl:value-of select="revolution_period"/> <xsl:value-of select="revolution_period/@unit"/></td>
							<td><xsl:value-of select="weight"/> <xsl:value-of select="weight/@unit"/></td>
                            <td><xsl:value-of select="diametr"/> <xsl:value-of select="diametr/@unit"/></td>
                            <td><xsl:value-of select="satellite_number"/></td>
                        </tr>
						</xsl:when>
						<xsl:when test="satellite_number &gt; 0 and position() mod 2 = 1">
                        <tr align="center" bgcolor="#A7F8D8">
                            <td><xsl:value-of select="position()" /></td>
                            <td><xsl:value-of select="@caption"/></td>
	                        <td><xsl:value-of select="distance"/> <xsl:value-of select="distance/@unit"/></td>
							<td><xsl:value-of select="circulation_period"/> <xsl:value-of select="circulation_period/@unit"/></td>
							<td><xsl:value-of select="revolution_period"/> <xsl:value-of select="revolution_period/@unit"/></td>
							<td><xsl:value-of select="weight"/> <xsl:value-of select="weight/@unit"/></td>
                            <td><xsl:value-of select="diametr"/> <xsl:value-of select="diametr/@unit"/></td>
                            <td><xsl:value-of select="satellite_number"/></td>
                        </tr>
						</xsl:when>
                        </xsl:choose>
                    </xsl:for-each>
                </table>
				Без спутников:
				<xsl:for-each select="solar/planet">
					<xsl:if test="satellite_number = 0">
					<p>
					<xsl:value-of select="position()" />. 
					<xsl:value-of select="@caption"/> - 
					<xsl:value-of select="distance"/> <xsl:value-of select="distance/@unit"/> - 
					<xsl:value-of select="circulation_period"/> <xsl:value-of select="circulation_period/@unit"/> - 
					<xsl:value-of select="revolution_period"/> <xsl:value-of select="revolution_period/@unit"/> - 
					<xsl:value-of select="weight"/> <xsl:value-of select="weight/@unit"/> - 
					<xsl:value-of select="diametr"/> <xsl:value-of select="diametr/@unit"/>
					</p>
					</xsl:if>
				</xsl:for-each>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>