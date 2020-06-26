#include "lex.h"

/*
** Save or set lexer state after signal
*/

void	fuck_norme_lexer_state(int need_update, char **u_in,\
		int *n_nl, int *ind)
{
	static char	**user_in;
	static int	*need_new_line;
	static int	*index;

	if (need_update)
	{
		ft_memdel((void **)user_in);
		*need_new_line = 1;
		*index = 0;
	}
	else
	{
		user_in = u_in;
		need_new_line = n_nl;
		index = ind;
	}
}
