#ifndef _XSVFEXEC_H_
#define _XSVFEXEC_H_

/*
 * $Log$
 */

/*!
 * \file xsvfexec.h
 * \brief Executor header file.
 */
unsigned char test1[10];
unsigned char test2[10];
unsigned char test3[10];
extern void XsvfInit(void);
extern void XsvfClose(void);
extern int XsvfExec(char *buf, int size);


#endif
