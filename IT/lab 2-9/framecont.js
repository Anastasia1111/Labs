function opening (elem, source){

var nframeDoc = window.parent.frames[0].document;
if (iframeDoc.readyState == 'complete') {
	var nframeneeded = nframeDoc.getElementsByName(source).contentWindow.document;
}
if (nframeneeded.readyState == 'complete') {
	nframeneeded.getElementsByTagName('img')[0].src = elem; 
}
}