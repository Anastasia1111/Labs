document.onkeypress = function(e) {
	//getElementsByTagName("input")
  e = e || event;

  if (e.ctrlKey || e.altKey || e.metaKey) return;

  var chr = getChar(e);

  //if (chr == null) return;

  if (chr < '0' || chr > '9') {
    return false;
  }
}

function getChar(event) {
      if (event.which == null) {
        if (event.keyCode < 32) return null;
        return String.fromCharCode(event.keyCode) // IE
      }

      if (event.which != 0 && event.charCode != 0) {
        if (event.which < 32) return null;
        return String.fromCharCode(event.which) // остальные
      }

      return null; // специальная клавиша
    }

function parse(num, val) {
	
	var nvalue = parseInt(val,num) || 0;
	nvalue = nvalue.toString().length < val.toString().length ? 0 : nvalue; 
	var avalue = nvalue.toString(2)
	var bvalue = nvalue.toString(8)
	var cvalue = nvalue.toString(16)
	var dvalue = nvalue.toString(10)
	
	document.getElementById("i1").value = avalue;
	document.getElementById("i2").value = bvalue;
	document.getElementById("i3").value = dvalue;
	document.getElementById("i4").value = cvalue;
	
}