function dump_props(t, obj_name) 
{
	obj_name.value = "";
	with(t){
		for (var i in t) 
		{
			obj_name.value += i + " = " + t[i] + "\n";
		}
	}
}