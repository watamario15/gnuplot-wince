#ifndef _ERRNO_H_
#define _ERRNO_H_

#define	EDOM 33
#define	ERANGE 34

int* _errno(void);
#define	errno (*_errno())

#endif

