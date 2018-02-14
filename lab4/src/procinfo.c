#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PATH_LEN 100
#define MAX_SPACE_LEN 100
#define MAX_NAME_LEN 1000
#define MAX_VALUE_LEN 1000

#define FULL_NAME_LEN 10

const char* short_info[] = {"Pid", "Name"};
const int field_len[] = {6, 20};
const char* short_info_default[] = {"?", "?"};


const char* full_info[] = {"Pid", "PPid", "Name", "State", "VmSize", "Threads"};
const char* full_info_default[] = {"?", "?", "?", "?", "?", "?"};


void printProcList(){

    int info_len = sizeof(short_info)/sizeof(char*);

    for (int i=0; i<info_len; i++){
        char format[100];
        sprintf(format, "%%%ds ", field_len[i]);
        printf(format, short_info[i]);
    }
    printf("\n");

    char* values[info_len];
    for (int i=0; i<info_len; i++){
        values[i] = (char*) malloc(sizeof(char) * MAX_VALUE_LEN);
        strcpy(values[i], short_info_default[i]);
    }

    DIR* dir = opendir("/proc");
    if (dir){
        struct dirent* ent;
        while ((ent=readdir(dir)) != NULL){
            char temp;
            int pid;
            int res = sscanf(ent->d_name, "%d%1[^\n]", &pid, &temp);
            if (res==1){
                char status_path[MAX_PATH_LEN] = {0};
                sprintf(status_path, "/proc/%d/status", pid);

                FILE *pStatusFile = fopen(status_path, "r");
                if (pStatusFile){
                    char name[MAX_VALUE_LEN], spaces[MAX_SPACE_LEN], value[MAX_VALUE_LEN];
                    while (!feof(pStatusFile)){
                        fscanf(pStatusFile, "%[^:]:%[ \t]%[^\n]\n", name, spaces, value);
                        for (int i=0; i<info_len; i++)
                            if (!strcmp(name, short_info[i]))
                                strcpy(values[i], value);
                    }
                    fclose(pStatusFile);

                    for (int i=0; i<info_len; i++){
                        char format[100];
                        sprintf(format, "%%%ds ", field_len[i]);
                        printf(format, values[i]);
                    }
                    printf("\n");
                }
            }
        }
        closedir(dir);
    }
    else
        fprintf(stderr, "Can't open directory");
}



void printProcInfo(int _pid){

    int info_len = sizeof(full_info)/sizeof(char*);

    char* values[info_len];
    for (int i=0; i<info_len; i++){
        values[i] = (char*) malloc(sizeof(char) * MAX_VALUE_LEN);
        strcpy(values[i], full_info_default[i]);
    }

    DIR* dir = opendir("/proc");
    if (dir){
        struct dirent* ent;
        while ((ent=readdir(dir)) != NULL){
            char temp;
            int pid;
            int res = sscanf(ent->d_name, "%d%1[^\n]", &pid, &temp);
            if (res==1){
                if (pid!=_pid)
                    continue;
                char status_path[MAX_PATH_LEN] = {0};
                sprintf(status_path, "/proc/%d/status", pid);

                FILE *pStatusFile = fopen(status_path, "r");
                if (pStatusFile){
                    char name[MAX_VALUE_LEN], spaces[MAX_SPACE_LEN], value[MAX_VALUE_LEN];
                    while (!feof(pStatusFile)){
                        fscanf(pStatusFile, "%[^:]:%[ \t]%[^\n]\n", name, spaces, value);
                        for (int i=0; i<info_len; i++)
                            if (!strcmp(name, full_info[i]))
                                strcpy(values[i], value);
                    }
                    fclose(pStatusFile);

                    for (int i=0; i<info_len; i++){
                        char format[100];
                        sprintf(format, "%%%ds: %%s\n", FULL_NAME_LEN);
                        printf(format, full_info[i], values[i]);
                    }
                }
            }
        }
        closedir(dir);
    }
    else
        fprintf(stderr, "Can't open directory");
}
