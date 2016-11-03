function change(elem, planet, sw)
{
	if(sw == 1) {
		elem.src = "../images/" + planet + "neg.jpg";
	} else {
		elem.src = "../images/" + planet + ".jpg";
	}	
}