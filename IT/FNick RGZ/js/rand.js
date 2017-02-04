function getRandomInt(min, max)
{
	if (isNaN(min) || isNaN(max))
	{
		alert('ֲגוהטעו צטפנû');
	} else {
		return Math.floor(Math.random() * (max - min + 1)) + min;
	}
}