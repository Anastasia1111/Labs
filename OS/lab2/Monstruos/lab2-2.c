#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
	DIR *dir = opendir("/tmp");
	struct dirent *ent;
	struct stat st;
	int count = 0;
	int size = 0;
	while( (ent = readdir(dir)) != NULL )
	{
		stat(ent->d_name, &st);
		++count;
		size += st.st_size;
		printf("%s - %d bytes\n", ent->d_name, st.st_size);
	}
	printf("--------------------------\nTotal:%d files, %d bytes totally", count, size);
	closedir(dir);
	return 0;
}