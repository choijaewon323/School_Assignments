#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LENGTH 512
static short octarray[9] = { 0400, 0200, 0100,
                            0040, 0020, 0010,
                            0004, 0002, 0001 };
static char perms[10] = "rwxrwxrwx";

int file_handler(char* new_file_name, char* path);
int cmd_handler(int line_num, DIR* dir, char* path);

int main(int argc, char* argv[]) {
    int entry_num = 0;
    int line_num = 0;
    char* cmd, * file_name;
    char path[MAX_LENGTH];
    char new_file_name[MAX_LENGTH];
    char original_path[MAX_LENGTH];
    DIR* dir;
    struct dirent* entry;

    while (1) {
        /* 1. Get the current working directory into 'char path[MAX_LENGTH]'. */
        /* your code */
        if ((getcwd(path, MAX_LENGTH)) == NULL) {
            printf("fail to get current working directory\n");
            return -1;
        }

        /* 2. Open the current working directory into 'DIR *dir'. */
        /* your code */
        if ((dir = opendir(path)) == NULL) {
            printf("fail to open current working directory\n");
            return -1;
        }

        /* 3. Print out all entries in the current working directory. */
	    entry_num = 0;
	    while ((entry = readdir(dir)) != NULL) {
            printf("%d %s\n", entry_num, entry->d_name);
	    entry_num++;
	    }
    	rewinddir(dir);
	    printf("-------------------------------------------\n");        

        if (strcpy(original_path, path) < 0) {
            printf("strcpy failed!\n");
            return -1;
        }

        /* 4. Receive the next command. */
        fgets(path, 512, stdin);
        cmd = strtok(path, "\n");

        /* 5. Parse the received command. */
        if (strcmp(cmd, "c") == 0) {
            if (fgets(new_file_name, 512, stdin) < 0) {
                printf("fgets failed\n");
                return -1;
            }
            file_name = strtok(new_file_name, "\n");
            if (file_handler(file_name, original_path) < 0) {
                printf("file_handler failed!\n");
                return -1;
            }
        }
        else {
            line_num = atoi(path);
            if (line_num >= 0 && line_num < entry_num) {
                if (cmd_handler(line_num, dir, original_path) < 0) {
                    printf("cmd_hanlder failed...\n");
                    return -1;
                }
            }
            else {
                printf("Invalid command...\n");
            }
        }
    }
    return 0;
}

int file_handler(char* new_file_name, char* path) {
    int fd;
    char fullpath[MAX_LENGTH * 2];
    int flag = 0;

    if (new_file_name == NULL || path == NULL) {
        printf("Invalid input arguments in cmd_handler()!\n");
        return -1;
    }

    /* 1. Try to open the file first. */
    sprintf(fullpath, "%s/%s", path, new_file_name);
    /* your code */
    if ((fd = open(fullpath, O_RDWR | O_EXCL | O_CREAT, 0644)) == -1) {
        flag = 1;
    }

    /* 2. If the file exists, delete it. */
    /* your code */
    if (flag) {
        remove(fullpath);
        printf("\n");
	return 0;
    }
    printf("\n");

    close(fd);

    return 0;
}

int cmd_handler(int line_num, DIR* dir, char* path) {
    int pointer = 0;
    char descript[10];
    char newpath[MAX_LENGTH];
    struct dirent* entry;
    struct stat info;
    int i;

    if (dir == NULL || path == NULL) {
        printf("Invalid input arguments in cmd_handler()!\n");
        return -1;
    }

    /* 1. Get the requested entry into 'struct dirent *entry'. */
    /* your code */
    for (i = 0; i <= line_num; i++) {
        entry = readdir(dir);
    }
    rewinddir(dir);
    
    sprintf(newpath, "%s/%s", path, entry->d_name);

    /* 2. Handle the request for directories and files correspondingly. */
    /* your code */
    stat(newpath, &info);
    pointer = info.st_mode & S_IFMT;
    
    switch (pointer) {
        case S_IFREG:
	    printf((info.st_mode & S_IRUSR) ? "r" : "-");
	    printf((info.st_mode & S_IWUSR) ? "w" : "-");
	    printf((info.st_mode & S_IXUSR) ? "x" : "-");
	    printf((info.st_mode & S_IRGRP) ? "r" : "-");
	    printf((info.st_mode & S_IWGRP) ? "w" : "-");
	    printf((info.st_mode & S_IXGRP) ? "x" : "-");
	    printf((info.st_mode & S_IROTH) ? "r" : "-");
	    printf((info.st_mode & S_IWOTH) ? "w" : "-");
	    printf((info.st_mode & S_IXOTH) ? "x" : "-");
	    printf("\t");
	    printf("%ld\t", info.st_size);
	    printf("%s\n\n", entry->d_name);
	    break;
	case S_IFDIR:
	    chdir(newpath);
	    break;
    }

    return 0;
}
