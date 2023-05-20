/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:08:50 by mrichard          #+#    #+#             */
/*   Updated: 2023/05/20 16:36:30 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//CTRL C no meio de um processo
static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printf("\nERROR STATUS SIGINT MIDDLE OF PROCESS: %d\n", g_exit_status);
		printf("\n");
		//move o cursor para a próxima linha e att o buffer interno do readline
		rl_on_new_line();
		//atualiza o conteúdo da linha atual
		rl_replace_line("", 0);
	}
}

//outros momentos de CTRL C
static void	handle_global_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printf("\nERROR STATUS SIGINT: %d\n", g_exit_status);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		//mostra o prompt novamente
		rl_redisplay();
	}
}

void	handle_cmd_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_cmd_signal);
}

void	handle_global_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_global_signal);
}