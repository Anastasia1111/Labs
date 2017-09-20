#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	char buf[70];
	char msg[80] = "Hello, ";
	write(1, "Say your name: ", 15);
	int n = read(0, buf, 69);
	strncat(msg, buf, n-1);
	strcat(msg, "!\n\n");
	write(1, msg, strlen(msg));
	
	DIR* dir1 = opendir("/tmp");
	struct dirent* ent1 = readdir(dir1);
	long int count1 = 0, size = 0;
	struct stat st1;
	while (ent1 != NULL)
	{
		stat(ent1->d_name, &st1);
		size += st1.st_size;
		++count1;
		ent1 = readdir(dir1);
	}
	printf("Size of \"\\tmp\": %ld bytes (%ld files)\n\n", size, count1);
	closedir(dir1);
	
	DIR* dir2 = opendir("/proc");
	struct dirent* ent2 = readdir(dir2);
	long int count2 = 0;
	while (ent2 != NULL)
	{
		if (ent2->d_type == DT_DIR && isdigit(ent2->d_name[0]))
		{
			char path[PATH_MAX+1] = "/proc/";
			strcat(path, ent2->d_name);
			strcat(path, "/stat");
			ifstream file(path);
			string content;
			if (file) {
				getline(file, content);
			}
			int start = content.find_first_of(" ");
			string name = content.substr(start+1);
			int end = name.find_first_of(" ");
			printf("pid: %s process name: %s\n", ent2->d_name, name.substr(0, end+1).c_str());
			++count2;
		}
		ent2 = readdir(dir2);
	}
	printf("Totally %ld processes\n", count2);
	closedir(dir2);
	
	return 0;
}
