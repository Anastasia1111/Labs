document.onmousemove = moveTip;
	
function moveTip(e) {
	floatTipStyle = document.getElementById("floatTip").style;
	w = 250; // Ширина подсказки

		// Для браузера IE6-8
	if (document.all)  { 
		x = event.clientX + document.body.scrollLeft; 
		y = event.clientY + document.body.scrollTop; 

		// Для остальных браузеров
	} else   { 
		x = e.pageX;
		y = e.pageY;
	}

	if ((x + w + 10) < document.body.clientWidth) { 
		floatTipStyle.left = x + 'px';

	} else { 
		floatTipStyle.left = x - w + 'px';
	}

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