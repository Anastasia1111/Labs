array1 = new Array(0,0,0,0,0,0,0,0,0,0);
array2 = new Array(0,0,0,0,0,0,0,0,0,0);
PrintArray ();

function randomInteger (min, max) {
    var rand = min - 0.5 + Math.random() * (max - min + 1);
    rand = Math.round(rand);
    return rand;
}

function PrintArray () {
	
	var index;

	for (index = 0; index < 10; index++) {
		document.getElementsByTagName('input')[index].value = array1[index];
	}
	
	for (index = 12; index < 22;index++) {
		document.getElementsByTagName('input')[index].value = array2[index - 12];
	}
}

function RandomArray () {
	var i;
	
	for(i = 0; i < 10; i++) {
		array1[i] = randomInteger (100, 999);
	}
	PrintArray();
}


function readingValue (arrnum) {
	
	var val = document.getElementsByTagName('input')[arrnum].value;
	
	array1[arrnum] = val;

	PrintArray();
}

function Sort(a,b)
{
	return (a-b);
} 

function sorting() {
	
	for(var i = 0; i < 10; i++) {
		array2[i] = array1[i];
	}
	
	array2.sort(Sort);
	PrintArray();
}
