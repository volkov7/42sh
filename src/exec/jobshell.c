#include "jobshell.h"

/*
** top-level shell is the only one who does job control
** if g_top_level_shell==0, we are in job shell
** all our children must stay in same group
*/
int g_top_level_shell = 1;

/*
** Not used now. Probably, will be helpful for scripts
*/
int g_job_control_enabled;

/*
** If nonzero, do the asynchronious notification when BG job changes state
** See set -o notify
*/
int g_async_notify_bg;

void set_jobshell_signal(void)
{
	if (g_interactive_shell)
	{
		signal(SIGINT, SIG_IGN); /* In case of come child handles */
		signal(SIGTERM, SIG_IGN); /* In case of come child handles */
	}
	/* If SIG_IGN process will be silently destroyed and not turned to zombie*/
	signal(SIGCHLD, SIG_DFL); /* We wait, parent does job control */
	signal(SIGTSTP, SIG_DFL); /*
								 Jobshell is stopped and top-level shell
								 recieves SIGCHLD and sends SIGCONT
								*/
}

void create_jobshell(t_complete_cmd *cmd)
{
	pid_t			job;
	int				status;

	job = fork();
	if (job) /* top-level shell */
	{
		if (g_interactive_shell)
			setpgid(job, job);
		add_job(job, 1, andor_to_str(cmd->and_or));
	}
	else	 /* job shell */
	{
		if (g_interactive_shell)
			setpgid(getpid(), getpid());
		set_jobshell_signal();
		g_top_level_shell = 0;
		exec_andor_list(cmd->and_or, &status);
		exit(g_last_cmd_status);
	}
}
