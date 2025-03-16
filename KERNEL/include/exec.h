#ifndef __EXEC_H_
#define __EXEC_H_

void temp_exec_init();
void temp_register_subroutine(const char* name, void (*subroutine)(void));
int exec(const char* name, const char** argv, unsigned int argc);

#endif