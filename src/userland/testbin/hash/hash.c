/*
 * Copyright (c) 2000, 2001, 2002, 2003, 2004, 2005, 2008, 2009
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * hash: Takes a file and computes a "hash" value by adding together all
 * the values in the file mod some largish prime.
 *
 * Once the basic system calls are complete, this should work on any
 * file the system supports. However, it's probably of most use for
 * testing your file system code.
 *
 * This should really be replaced with a real hash, like MD5 or SHA-1.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

#ifdef HOST
#include "hostcompat.h"
#endif

#define HASHP 104729

int
main(int argc, char *argv[])
{
	int fd;
	char readbuf[1];
	int j = 0;

#ifdef HOST
	hostcompat_init(argc, argv);
#endif

	if (argc != 2) {
		errx(1, "Usage: hash filename");
	}

	fd = open(argv[1], O_RDONLY, 0664);

	if (fd<0) {
		err(1, "%s", argv[1]);
	}

	for (;;) {
		if (read(fd, readbuf, 1) <= 0) break;
		j = ((j*8) + (int) readbuf[0]) % HASHP;
	}

	close(fd);

	tprintf("Hash : %d\n", j);

	return 0;
}
//#include <unistd.h>
//#include <stdio.h>
//#include <test.h>
//
//int main() {
//    int oldfd = 1; // STDOUT
//    int newfd = 3; // Arbitrary number greater than 2 (STDERR)
//
//    char original_msg[] = "This should print to the console.\n";
//    char duplicate_msg[] = "This should also print to the console.\n";
//
//    // Write original message to STDOUT
//    int val = write(oldfd, original_msg, sizeof(original_msg));
//	printf("val1 \n");
//	printf("%d", val); //35
//    // Duplicate the file descriptor
//    int result = dup2(oldfd, newfd);
//    if (result < 0) {
//        printf("dup2 syscall failed!\n");
//		printf("%d", errno);
//        return -1;
//    }
//
//    // Write duplicate message to the new file descriptor
//    // Because newfd is a copy of oldfd, this should also print to STDOUT
//    val = write(newfd, duplicate_msg, sizeof(duplicate_msg));
//	printf("val2 \n");
//	printf("%d", val);
//    return 0;
//}