function opening (elem, source){
var nframe = window.getElementsByName('thwin');

var nframeDoc = nframe.contentWindow.document;

var nframeneeded = nframeDoc.getElementsByName(source).contentWindow.document;

nframeneeded.getElementsByTagName('img')[0].src = elem; 

}