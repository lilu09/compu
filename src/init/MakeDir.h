#ifndef MAKE_DIR
#define MAKE_DIR

#ifndef _WIN32

//#include <jlss.h>
//#include <emalloc.h>

#include <stdlib.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */

#include <string.h>
#include <sys/stat.h>
//#include <sysstat.h"    /* Fix up for Windows - inc mode_t */

typedef struct stat Stat;

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
const char jlss_id_mkpath_c[] = "@(#)$Id: mkpath.c,v 1.12 2008/05/19 00:43:33 jleffler Exp $";
#endif /* lint */

int do_mkdir(const char *path, mode_t mode)
{
    Stat            st;
    int             status = 0;

    if (stat(path, &st) != 0)
    {
        /* Directory does not exist */
        if (mkdir(path, mode) != 0)
            status = -1;
    }
    else if (!S_ISDIR(st.st_mode))
    {
        errno = ENOTDIR;
        status = -1;
    }

    return(status);
}

/**
** mkpath - ensure all directories in path exist
** Algorithm takes the pessimistic view and works top-down to ensure
** each directory in path exists, rather than optimistically creating
** the last element and working backwards.
*/
int mkpath(const char *path, mode_t mode)
{
    char           *pp;
    char           *sp;
    int             status;
    char           *copypath = strdup(path);

    status = 0;
    pp = copypath;
    while (status == 0 && (sp = strchr(pp, '/')) != 0)
    {
        if (sp != pp)
        {
            /* Neither root nor double slash in path */
            *sp = '\0';
            status = do_mkdir(copypath, mode);
            *sp = '/';
        }
        pp = sp + 1;
    }
    if (status == 0)
        status = do_mkdir(path, mode);
    free(copypath);
    return (status);
}

#endif

#endif

