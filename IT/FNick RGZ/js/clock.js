var idTimer = 0;
var delay = 500;
	
function clockworking() {
	
	var default_now = new Date();
	var now = new Date(default_now.getTime() + (rand_tz-7)*3600000);
	
	var curr_year = String(now.getFullYear());
	var curr_hour = String(now.getHours());
	
	if (rand_tz >= 0) {
		if (rand_tz > 0) {
			document.getElementById("timezone").innerHTML = "Текущий часовой пояс: GMT+"+rand_tz;
		} else {
			document.getElementById("timezone").innerHTML = "Текущий часовой пояс: GMT";
		}
	} else {
		document.getElementById("timezone").innerHTML = "Текущий часовой пояс: GMT"+rand_tz;
	}
	
	if (now.getHours() >= 12) {
		curr_hour = String((now.getHours() - 12));
		document.apm.src = "../digits/dgpm.gif"
	} else {
		document.apm.src = "../digits/dgam.gif"
	}
	
	if(curr_hour.length == 2) {
		document.h1.src = "../digits/dg" + curr_hour.charAt(0) + ".gif"
		document.h2.src = "../digits/dg" + curr_hour.charAt(1) + ".gif"
	} else {
		document.h1.src = "../digits/dg0.gif"
		document.h2.src = "../digits/dg" + curr_hour.charAt(0) + ".gif"
	}
	
	document.m1.src = "../digits/dg" + Math.floor(now.getMinutes()/10) + ".gif"
	document.m2.src = "../digits/dg" + Math.floor(now.getMinutes()%10) + ".gif"

	document.s1.src = "../digits/dg" + Math.floor(now.getSeconds()/10) + ".gif"
	document.s2.src = "../digits/dg" + Math.floor(now.getSeconds()%10) + ".gif"

	document.d1.src = "../digits/dg" + Math.floor(now.getDate()/10) + ".gif"
	document.d2.src = "../digits/dg" + Math.floor(now.getDate()%10) + ".gif"

	document.mo1.src = "../digits/dg" + Math.floor((now.getMonth()+1)/10) + ".gif"
	document.mo2.src = "../digits/dg" + Math.floor((now.getMonth()+1)%10) + ".gif"
	
	document.y1.src = "../digits/dg" + curr_year.charAt(0) + ".gif"
	document.y2.src = "../digits/dg" + curr_year.charAt(1) + ".gif"
	document.y3.src = "../digits/dg" + curr_year.charAt(2) + ".gif"
	document.y4.src = "../digits/dg" + curr_year.charAt(3) + ".gif"
	
	delete now;
}
