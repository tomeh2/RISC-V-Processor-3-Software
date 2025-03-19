#ifndef __SYSCALL_H_
#define __SYSCALL_H_

void sys_write(const char* buf, unsigned int len);
void sys_read(char* buf, unsigned int len);

#endif