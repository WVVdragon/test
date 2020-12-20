#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int opterr = 0;
char path[1024] = "";
char targetname[100] = "";
int modifiedtime = -1;
int changetime = -1;

char match(char *first, char *second) 
{
    if (*first == '\0' && *second == '\0') 
        return 1; 
    if (*first == '*' && *(first+1) != '\0' && *second == '\0') 
        return 0; 
    if (*first == '?' || *first == *second) 
        return match(first+1, second+1); 
    if (*first == '*') 
        return match(first+1, second) || match(first, second+1); 
    return 0; 
}

char isFileOk(char *name, time_t mt, time_t ct){
    time_t now = time(0);
    int spd = 24*3600;
    int mtd = (now - mt)/spd;
    int ctd = (now - ct)/spd;

    //printf("filename: %s target: %s\n", name, targetname);
    if(match(targetname, name) == 1){
        if(modifiedtime != -1 && mtd > modifiedtime) return 0;
        if(changetime != -1 && ctd > changetime) return 0;
        return 1;
    }
    return 0;
}

void findInDir(char *path) {
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            char newpath[1024];
            snprintf(newpath, sizeof(newpath), "%s/%s", path, dir->d_name);
            if (dir->d_type == DT_DIR) {
                if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
                findInDir(newpath);
            } else {
                struct stat buf;
                if(stat(newpath, &buf)==0){
                    if(isFileOk(dir->d_name, buf.st_mtime, buf.st_ctime)){
                        printf("%s/%s\n", path, dir->d_name);
                    }
                }
            }
        }
        closedir(d);
    }
}

int main(int argc, char *argv[]){
    char *optstr = "p:n:m:c:";
    struct option opts[] = {
        {"path", 1, NULL, 'p'},
        {"name", 1, NULL, 'n'},
        {"mtime", 1, NULL, 'm'},
        {"ctime", 1, NULL, 'c'},
        {0, 0, 0, 0},
    };
    int opt;
    while((opt = getopt_long(argc, argv, optstr, opts, NULL)) != -1){
        switch(opt) {
            case 'p':
                strcpy(path, optarg);
                break;
            case 'n':
                strcpy(targetname, optarg);
                break;
            case 'm':
                modifiedtime = atoi(optarg);
                break;
            case 'c':
                changetime = atoi(optarg);
                break;
            case '?':
                if(strchr(optstr, optopt) == NULL){
                    fprintf(stderr, "unknown option '-%c'\n", optopt);
                }else{
                    fprintf(stderr, "option requires an argument '-%c'\n", optopt);
                }
                return 1;
        }
    }
    findInDir(path);
    return 0;
}
