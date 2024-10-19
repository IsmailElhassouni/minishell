/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielhasso <ielhasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:04 by nbenasso          #+#    #+#             */
/*   Updated: 2024/05/20 19:02:18 by ielhasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

void					rl_replace_line(const char *cont, int type);

typedef struct s_var	t_var;
struct					s_var
{
	int					i;
	char				*result;
};

typedef struct s_prs	t_prs;
struct					s_prs
{
	int					arg_num;
	int					i;
	int					ambigous;
	int					ret_value;
	char				**extra_args;
	int					outside_quote;
	t_var				var;
};

typedef struct s_env	t_env;
struct					s_env
{
	char				*key;
	char				*value;
};
typedef struct s_redir	t_redir;
struct					s_redir
{
	char				type;
	char				*file;
};
typedef struct s_cmd	t_cmd;
struct					s_cmd
{
	char				*cmd;
	char				**args;
	t_list				*redir;
};

int						g_exit_status;
void					free_cmds(t_list *cmd);
char					**list_to_arr(t_list *lst);
int						ft_echo(char **argv);
void					free_env_list(t_list *env_lst);
t_list					*env_copy(t_list *env_lst, char **env, char *s);
void					init_env_node(t_env *new);
int						check_syntax_errors(char *input);
char					*env_var_checker(char *s, t_list *env_lst, t_prs *prs);
int						check_quote(char c, int quote);
void					fill_arg(char *temp, t_cmd *new, t_list *env_lst,
							t_prs *prs);
int						check_redir_errors(char *str);
t_list					*split_pipe(t_list *head, char *input, t_list *env_lst);
t_cmd					*new_node(char *s, t_list *env_lst);
void					initialize_prs_node(t_prs *prs);
void					initialize_cmd_node(t_cmd *new, char *s,
							t_list *env_lst);
void					allocate_args(char *s, t_cmd *cmd, t_list *env_lst);
int						count_extra_args(char *s, int i, int j,
							t_list *env_lst);
char					*variable_expander(char *key, t_list *env_lst);
int						check_ambigous_redirect(char *s, t_list *env_lst,
							t_prs *prs, t_redir *redir);
char					*double_quotes(char *s, t_list *env_lst, t_prs *prs);
char					*single_quotes(char *s, t_prs *prs);
void					add_extra_args(t_cmd *new, t_prs *prs);
void					initialize_redir_node(t_redir *new);
t_list					*redirections(t_list *redir, char *s, t_list *env_lst,
							t_prs *prs);
void					get_filepath(t_redir *redir, char *s, t_list *env_lst,
							t_prs *prs);
t_list					*defautl(t_env *tmp, t_list *env_lst, t_list *lst,
							char *s);
char					*remove_spaces(char *s);
int						get_size(char *s);
int						ft_put_error(char *error);
void					signals(void);
void					tab_to_space(char *str);
int						my_exec(t_list *cmds, t_list **envp, t_cmd *cmd);
int						ft_heredoc(t_list *cmds, t_list *envp);
int						is_cmd(t_cmd *cmd);
int						ft_cmd(t_list *cmds, t_cmd *cmd, t_list **envp,
							int status);
int						my_redirect(t_list *redir);
void					ft_dup2(int fd1, int fd2);
int						ft_pwd(char *gpwd);
int						ft_chdir(t_cmd *cmd, t_list *envp, char **path);
int						ft_env(t_list *envp);
void					ft_exit(char **args, int i, t_list **cmds,
							t_list **envp);
int						ft_valid_env_name(char *value);
int						ft_valid_env_name_tow(char *value);
int						ft_unset(t_list **envp, char *value);
char					*get_key(char *env);
int						ft_display_envp(t_list *envp, int i, int j);
char					*get_value(char *env);
t_env					*env_in_node(char *key, char *value);
int						ft_export(t_list **envp, char *key, char *arg,
							t_list *tmp);
int						chek_for_append(char *value, t_list **envp);
void					close_pfds(int *pfds, int nbr);
int						exec_cmdd(t_list *cmds, t_cmd *cmd, t_list **envp,
							int status);
// execv
char					**get_paths(t_list *envp);
char					*get_cmd_path(char *cmd, char **paths);
void					ft_execve(char *path, char **args, char **tab);
void					wait_cmds(int nbr_cmds);
void					disable_echo(void);
void					set_(char **args, t_list **envp, int nbr_cmds);
void					if_is_unset(char *args, t_list **envp, t_env *env);
int						spac(char *s);
void					frees(char **path);
char					*expand_variables(char *line, t_list *envp);
char					*no_file_error(char **paths, char *cmd, char *str2);

#endif