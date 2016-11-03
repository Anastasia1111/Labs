document.onmousemove = moveTip;
	
function moveTip(e) {
	floatTipStyle = document.getElementById("floatTip").style;


	if (document.all)  { 
		x = event.clientX; 
		y = event.clientY; 

	} else   { 
		x = e.pageX;
		y = e.pageY;
	}

		floatTipStyle.left = x + 'px';
	floatTipStyle.top = y + 20 + 'px';
}

function toolTip(msg) {
	floatTipStyle = document.getElementById("floatTip").style;
	if (msg) {
		document.getElementById("floatTip").innerHTML = msg;
		floatTipStyle.display = "block";
	} else { 
		floatTipStyle.display = "none";
	} 
}