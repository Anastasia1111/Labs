#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>

using namespace std;

int IsNum(char* ProcString)
{
    while(*ProcString)
        if (*ProcString < '0' || *ProcString > '9')
            return 0;
        else ProcString++;
    return 1;
}

int main()
{
    struct dirent* ent = NULL ;
    int count = 0;
    DIR* dir = NULL ;
    dir = opendir("/proc/") ;
    if (dir == NULL)
    {
        perror("Couldn't open the directory") ;
        return -1;
    }
    while ((ent = readdir(dir)) != 0) {
        if (ent->d_type == DT_DIR) {
            if (IsNum(ent->d_name)) {
                string path = (string)"/proc/" + ent->d_name + "/stat";
                ifstream statFile(path.c_str());
                string statString;
                if (statFile) {
                    getline(statFile, statString);
                }
                int start = statString.find_first_of(" ");
                string name = statString.substr(start+1);
                int end = name.find_first_of(" ");


                cout << "pid: " << ent->d_name << " " << statString.substr(start,end+1) << endl;
                count++;
            }
        }
    }
    cout << count << " processes" << endl;
    closedir(dir);
    return 0;
}
