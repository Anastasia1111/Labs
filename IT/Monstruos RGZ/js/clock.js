	var idTimer = 0;
	var delay = 2000;

function clockworking() {
	
	var now = new Date();
	var curr_year = String(now.getFullYear());
	var curr_hour = String(now.getHours());
	var mars_year = String(((now.getFullYear() * 365) + (now.getFullYear()/4)) / 687);
	
	if (now.getHours() >= 12) {
		curr_hour = String((now.getHours() - 12));
		document.apm.src = "../clock/dgpm.gif"
	} else {
		document.apm.src = "../clock/dgam.gif"
	}
	
	if(curr_hour.length == 2) {
		document.h1.src = "../clock/dg" + curr_hour.charAt(0) + ".gif"
		document.h2.src = "../clock/dg" + curr_hour.charAt(1) + ".gif"
	} else {
		document.h1.src = "../clock/dg0.gif"
		document.h2.src = "../clock/dg" + curr_hour.charAt(0) + ".gif"
	}
	
		document.m1.src = "../clock/dg" + Math.floor(now.getMinutes()/10) + ".gif"
		document.m2.src = "../clock/dg" + Math.floor(now.getMinutes()%10) + ".gif"


		document.d1.src = "../clock/dg" + Math.floor(now.getDate()/10) + ".gif"
		document.d2.src = "../clock/dg" + Math.floor(now.getDate()%10) + ".gif"


		document.mo1.src = "../clock/dg" + Math.floor((now.getMonth()+1)/10) + ".gif"
		document.mo2.src = "../clock/dg" + Math.floor((now.getMonth()+1)%10) + ".gif"

	document.y1.src = "../clock/dg" + curr_year.charAt(0) + ".gif"
	document.y2.src = "../clock/dg" + curr_year.charAt(1) + ".gif"
	document.y3.src = "../clock/dg" + curr_year.charAt(2) + ".gif"
	document.y4.src = "../clock/dg" + curr_year.charAt(3) + ".gif"
	
	document.ym1.src =  "../clock/dg" + mars_year.charAt(0) + ".gif"
	document.ym2.src =  "../clock/dg" + mars_year.charAt(1) + ".gif"
	document.ym3.src =  "../clock/dg" + mars_year.charAt(2) + ".gif"
	document.ym4.src =  "../clock/dg" + mars_year.charAt(3) + ".gif"
	
	delete now;
}
