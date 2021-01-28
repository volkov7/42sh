#ifndef EXEC_H
# define EXEC_H

#define IGNORE_STREAM -2

#include "lexer.h"

extern int top_level_shell;
extern int async_notify_bg;

void set_jobshell_signal(void);
void sigchld_handler(int n);

int exec_pipeline(t_pipeline *pipeline);
int exec_complete_cmd(t_complete_cmd *cmd);

#endif
