#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

enum
{
    USER = 6,
    GROUP = 3
};

static int
uid_check(unsigned uid0, unsigned uid)
{
    return uid0 == uid;
}

static int
gid_check(unsigned gid0, int gid_count, unsigned *gids)
{
    for (int i = 0; i < gid_count; i++) {
        if (gid0 == gids[i]) {
            return 1;
        }
    }
    return 0;
}

int
myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (!task->uid) {
        return 1;
    }
    if (uid_check(stb->st_uid, task->uid)) {
        return ((stb->st_mode >> USER) & access) == access;
    }
    if (gid_check(stb->st_gid, task->gid_count, task->gids)) {
        return ((stb->st_mode >> GROUP) & access) == access;
    }
    return (stb->st_mode & access) == access;
}