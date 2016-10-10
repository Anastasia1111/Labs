	var idTimer = 0;
	var delay = 500;

function clockworking() {
	
	var now = new Date();
	var curr_year = String(now.getFullYear());
	var curr_hour = String(now.getHours());
	
	if (now.getHours() >= 12) {
		curr_hour = String((now.getHours() - 12));
		document.apm.src = "LAB11/dgpm.gif"
	} else {
		document.apm.src = "LAB11/dgam.gif"
	}
	
	if(curr_hour.length == 2) {
		document.h1.src = "LAB11/dg" + curr_hour.charAt(0) + ".gif"
		document.h2.src = "LAB11/dg" + curr_hour.charAt(1) + ".gif"
	} else {
		document.h1.src = "LAB11/dg0.gif"
		document.h2.src = "LAB11/dg" + curr_hour.charAt(0) + ".gif"
	}
	
		document.m1.src = "LAB11/dg" + Math.floor(now.getMinutes()/10) + ".gif"
		document.m2.src = "LAB11/dg" + Math.floor(now.getMinutes()%10) + ".gif"

	
		document.s1.src = "LAB11/dg" + Math.floor(now.getSeconds()/10) + ".gif"
		document.s2.src = "LAB11/dg" + Math.floor(now.getSeconds()%10) + ".gif"


		document.d1.src = "LAB11/dg" + Math.floor(now.getDate()/10) + ".gif"
		document.d2.src = "LAB11/dg" + Math.floor(now.getDate()%10) + ".gif"


		document.mo1.src = "LAB11/dg" + Math.floor((now.getMonth()+1)/10) + ".gif"
		document.mo2.src = "LAB11/dg" + Math.floor((now.getMonth()+1)%10) + ".gif"

	
	document.y1.src = "LAB11/dg" + curr_year.charAt(0) + ".gif"
	document.y2.src = "LAB11/dg" + curr_year.charAt(1) + ".gif"
	document.y3.src = "LAB11/dg" + curr_year.charAt(2) + ".gif"
	document.y4.src = "LAB11/dg" + curr_year.charAt(3) + ".gif"
	
	delete now;
}
