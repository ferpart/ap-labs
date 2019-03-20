#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include "logger.h"
#include <unistd.h>
#include <sys/inotify.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

static int displayInotifyEvent(struct inotify_event *i);
static int display_info(const char *fpath, const struct stat *sb, int tflag, 
			struct FTW *ftwbuf);
int inotifFd;

int main (int argc, char *argv[])
{
	
	int flags = 0;
	char buf[BUF_LEN] __attribute__ ((aligned(8)));
	ssize_t numRead;
	char *p;
	struct inotify_event *event;

	inotifFd = inotify_init();
	
	if (inotifFd== -1) {
		errorf("inotify file descriptor couldn't be initiated");
		exit(1);
	}

	flags = FTW_PHYS;
	if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags) == -1) {
		panicf("nftw");
		exit(1);
	}

	for (;;) {                                  /* Read events forever */
		numRead = read(inotifFd, buf, BUF_LEN);
		if (numRead == 0) {
			panicf("read() from inotify fd returned 0!");
			exit(1);
		}
		if (numRead == -1) {
			errorf("read");
			exit(1);
		}
		for (p = buf; p < buf + numRead;) {
			event = (struct inotify_event *)p;
			displayInotifyEvent(event);
			
			p += sizeof(struct inotify_event) + event->len;
		}
		inotifFd = inotify_init();
		if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags) ==
		    -1) {
			panicf("Transversion of nftw impossible");
			exit(1);
		}
	}
	exit(0);
}

static int displayInotifyEvent(struct inotify_event *i)
{
	if (i->mask & IN_CREATE)	infof("IN_CREATE ");
	if (i->mask & IN_DELETE)	infof("IN_DELETE ");
	if (i->mask & IN_MOVED_FROM)	infof("IN_MOVED_FROM ");
	if (i->mask & IN_MOVED_TO)	infof("IN_MOVED_TO ");
	printf("\n");

	if (i->len > 0)
		printf("        name = %s\n", i->name);

	return 0;
}

static int display_info(const char *fpath, const struct stat *sb, int tflag, 
	       		struct FTW *ftwbuf)
{
	int notiWatch = inotify_add_watch(inotifFd, fpath, IN_CREATE | IN_CREATE|
					IN_MOVED_TO | IN_MOVED_FROM);

	if (notiWatch == -1) {
		errorf("Watch for inotify not added");
		exit(1);
	}

	return 0;
}
