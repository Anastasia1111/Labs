array1 = new Array(0,0,0,0,0,0,0,0,0);

RandomArray ();
PrintArray ();

function randomInteger (min, max) {
    var rand = min - 0.5 + Math.random() * (max - min + 1);
    rand = Math.round(rand);
    return rand;
}

function RandomArray () {
	var i;
	
	for(i = 0; i < 9; i++) {
		array1[i] = randomInteger (100, 999);
	}
}

function BinarySearch(t,A)
{
    var i = 0, j = 8, r = 4, k;   

	var td1 = document.getElementById('table1').getElementsByTagName('td');

    while (i <= j)
    {
		td1[r].innerHTML = i;
		r++;
		td1[r].innerHTML = j;
		r++;
		k = Math.floor((i+j)/2);
		td1[r].innerHTML = k;
		r++;
		td1[r].innerHTML = A[k];
		r++;
		if (t == A[k]) return (k + 1);
		else if (t < A[k]) j = k-1;
		else i = k+1;
    }

    return 0;
}


function PrintArray () {
	
	var index;

	for (index = 0; index < 9; index++) {
		document.getElementsByTagName('input')[index].value = array1[index];
	}

}

function Sort(a,b)
{
	return (a-b);
} 

function readingValue (arrnum) {
	
	var val = document.getElementsByTagName('input')[arrnum].value;

	array1[arrnum] = val;
	array1.sort(Sort);
	PrintArray();
	
}

