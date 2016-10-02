	var idTimer = 0;
	var delay = 20;

function clockworking() {
	
	var now = new Date();
	var curr_date = String(now.getDate());
	var curr_month = String(now.getMonth() + 1);
	var curr_year = String(now.getFullYear());
	var curr_hour = String(now.getHours());
	var curr_sec = String(now.getSeconds());
	var curr_min = String(now.getMinutes());
	
	if (now.getHours() >= 12) {
		curr_hour = String(parseInt(now.getHours() - 12));
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
	
	if(curr_min.length == 2) {
		document.m1.src = "LAB11/dg" + curr_min.charAt(0) + ".gif"
		document.m2.src = "LAB11/dg" + curr_min.charAt(1) + ".gif"
	} else {
		document.m1.src = "LAB11/dg0.gif"
		document.m2.src = "LAB11/dg" + curr_min.charAt(0) + ".gif"
	}
	
	if(curr_sec.length == 2) {
		document.s1.src = "LAB11/dg" + curr_sec.charAt(0) + ".gif"
		document.s2.src = "LAB11/dg" + curr_sec.charAt(1) + ".gif"
	} else {
		document.s1.src = "LAB11/dg0.gif"
		document.s2.src = "LAB11/dg" + curr_sec.charAt(0) + ".gif"
	}
	
	if(curr_date.length == 2) {
		document.d1.src = "LAB11/dg" + curr_date.charAt(0) + ".gif"
		document.d2.src = "LAB11/dg" + curr_date.charAt(1) + ".gif"
	} else {
		document.d1.src = "LAB11/dg0.gif"
		document.d2.src = "LAB11/dg" + curr_date.charAt(0) + ".gif"
	}
	
	if(curr_month.length == 2) {
		document.mo1.src = "LAB11/dg" + curr_month.charAt(0) + ".gif"
		document.mo2.src = "LAB11/dg" + curr_month.charAt(1) + ".gif"
	} else {
		document.mo1.src = "LAB11/dg0.gif"
		document.mo2.src = "LAB11/dg" + curr_month.charAt(0) + ".gif"
	}
	
	document.y1.src = "LAB11/dg" + curr_year.charAt(0) + ".gif"
	document.y2.src = "LAB11/dg" + curr_year.charAt(1) + ".gif"
	document.y3.src = "LAB11/dg" + curr_year.charAt(2) + ".gif"
	document.y4.src = "LAB11/dg" + curr_year.charAt(3) + ".gif"
	
}