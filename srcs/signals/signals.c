///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   signals.c                                          :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
///*   Updated: 2023/06/03 20:13:06 by caalbert         ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "../../includes/minishell.h"
//
//void	signal_handler_ctrlc(int signal)
//{
//	strsignal(signal);
//	printf("\nctrlc\n");
//}
//
//void	signal_handler_ctrlslash(int signal)
//{
//	strsignal(signal);
//	printf("\nslash\n");
//}
//
//void	signal_handler_ctrld(int signal, siginfo_t *siginfo, void *context)
//{
//	t_cmds	*cmds;
//	printf("\nctrld\n");
//
//	cmds = ((
//				struct s_signal_handler_data *)
//			siginfo->si_value.sival_ptr)->cmds;
//	printf("signal_handler_ctrld: %d\n", signal);
//	printf("signal_handler_ctrld: %p\n", cmds);
//	printf("context: %p\n", context);
//}
//
//void	signals_handlers(t_cmds *cmds)
//{
//	struct sigaction				sa_ctrlc;
//	struct sigaction				sa_ctrlslash;
//	struct sigaction				sa_ctrld;
//	struct s_signal_handler_data	data;
//
//	data.cmds = cmds;
//	data.cmds->exit_code.code = 0;
//
//	sigemptyset(&sa_ctrlc.sa_mask);
//	sa_ctrlc.sa_flags = SA_SIGINFO;
//	sa_ctrld.sa_sigaction  = signal_handler_ctrld;
//	sigaction(SIGINT, &sa_ctrlc, NULL);
//
//	sa_ctrlslash.sa_handler = NULL;
//	sigemptyset(&sa_ctrlslash.sa_mask);
//	sa_ctrlslash.sa_flags = 0;
//	sigaction(SIGQUIT, &sa_ctrlslash, NULL);
//
//	sigemptyset(&sa_ctrld.sa_mask);
//	sa_ctrld.sa_flags = SA_SIGINFO;
//	sa_ctrld.sa_sigaction = signal_handler_ctrld;
//	sigaction(SIGTERM, &sa_ctrld, NULL);
//}
