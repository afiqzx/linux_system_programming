#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    struct passwd *user;
    struct group *grp;
    char *username = NULL;
    char *groupname = NULL;
    unsigned int uid;
    unsigned int gid;
    
    /* Check that the user supplied two arguments 
     * (filename and user or user:group) */

    if(argc != 3) {
        fprintf(stderr, "Usage: %s [user][:group] path\n", argv[0]);
        return 1;
    }


    /* Extract username and groupname */
    username = strtok(argv[1], ":");
    groupname = strtok(NULL, ":");

    if((user = getpwnam(username)) == NULL) {
        fprintf(stderr, "Invalid username \n");
        return 1;
    }

    uid = user->pw_uid;

    if(groupname != NULL) {
        if((grp = getgrnam(groupname)) == NULL) {
            fprintf(stderr, "Invalid groupname\n");
            return 1;
        }
        gid = grp->gr_gid;
    }
    else {
        gid = -1;
    }

    /* Update user/group */
    if(chown(argv[2], uid, gid) == -1) {
        perror("Cannot change owner/group");
        return 1;
    }

    return 0;
}
