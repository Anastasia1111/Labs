

function setCookie(name, value, expire) {  
	document.cookie = name + "=" + escape(value);
	((expire == null) ? "; path=/" : ("; expires=" + expire.toGMTString() + "; path=/"))
}

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