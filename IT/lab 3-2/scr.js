
function getCookie(Name) {   
	var search = Name + "="
		//Создается строка для поиска в document.cookie
	if (document.cookie.length > 0) {
		offset = document.cookie.indexOf(search)
			//Поиск cookie по ее имени
		if (offset != -1) {
			offset += search.length
			end = document.cookie.indexOf(";", offset)
				//Определили положение нужной cookie, и по индексам вырежем ее
			if (end == -1)
				end = document.cookie.length
			return unescape(document.cookie.substring(offset, end))
				//Вернули подстроку, содержащюю нужное значение cookie
		}
	}
}

function setCookie(name, value, expire) {  
	document.cookie = name + "=" + escape(value) + cookie;
	((expire == null) ? "" : ("; expires=" + expire.toGMTString()))
}

function setCookie1(name, value, options) {
  options = options || {};

  var expires = options.expires;

  if (typeof expires == "number" && expires) {
    var d = new Date();
    d.setTime(d.getTime() + expires * 1000);
    expires = options.expires = d;
  }
  if (expires && expires.toUTCString) {
    options.expires = expires.toUTCString();
  }

  value = encodeURIComponent(value);

  var updatedCookie = name + "=" + value;

  for (var propName in options) {
    updatedCookie += "; " + propName;
    var propValue = options[propName];
    if (propValue !== true) {
      updatedCookie += "=" + propValue;
    }
  }

  document.cookie = updatedCookie;
}