/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijoo <jijoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:32:54 by seonghyk          #+#    #+#             */
/*   Updated: 2022/12/06 14:46:36 by jijoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>

typedef struct s_shell_state {
	char	**envp;
	int		exit_status;
	int		orig_stdin;
}t_shell_state;

extern t_shell_state	g_shell_state;

/*
TOKEN LESS GREAT DLESS DGREAT PIPE
 str   '<'  '>'   '<<'  '>>'   '|'
*/
enum e_token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_NEWLINE,
	TOKEN_ASSIGNWORD
};

typedef struct s_token {
	enum e_token_type	type;
	char				*str;
	int					strlen;
	struct s_token		*next;
}	t_token;

void	pipe_redi2(char *line, int *idx_ptr, int *head_ptr, t_token **genesis);
void	pipe_redi(char *line, int *idx_ptr, int *head_ptr, t_token **genesis);

void	init_msh(int argc, char *argv[], char *envp[]);
int		get_type(char *str);
int		quote_open(char *str);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_token	*ft_lstnew(char *str);
t_token	*ft_lstlast(t_token *token);
void	ft_lstadd_back(t_token **token, t_token *new);
void	ft_showlst(t_token **genesis);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstfree(t_token **lst);

int		get_rl(char *str, char crt);
size_t	get_sl(char **dp, char crt);
void	split_strlcpy(char *dst, char *src, size_t size);
void	dobby(char **s, int i);
char	**ft_split(char const *s, char c);

void	quote_check(char *line, int *idx_ptr, char *str, char **envp);
void	quote_err(char *line);
void	delquote(char *str);
void	parse(char *line, t_token **genesis, char **envp);
void	tokenize(char *line, t_token **genesis, char **envp);
void	make_tstr(char *line, int *ptr_idx);
int		skip_space(char *line, int idx);
char	*ft_str(char *line, int idx, char **envp);
void	add_token(int head, t_token **genesis, char *str);
int		open_single_quote(char *str, int *idx_ptr);
int		open_double_quote(char *str, int *idx_ptr);
int		quote_open(char *str);
char	*ft_strdup(const char *src);
void	nop(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strcat(char *dest, const char *src);
void	ft_strcat_char(char *dest, char src);

size_t	len_envp(char *env);
void	ft_envp(char *line, int *ptr_idx, char *str, char **envp);
void	single_quote(char *line, int *ptr_idx, char *str);
void	double_quote(char *line, int *ptr_idx, char *str, char **envp);
void	no_quote(char *line, int *ptr_idx, char *str, char **envp);

void	control_C(void);
void	control_slash(void);
void	signaling(void);

void	ft_div(int num, int p, char *str, int i);
int		get_power(int *num, int *l);
char	*ft_itoa2(int n);
int		search_envp(char *line, int *ptr_idx, char **envp);
int		ft_ret_envplen(int exist, int *ptr_idx, char *var, char *env);
int		len_str_sq(char *line, int *idx_ptr);
int		len_str_dq(char *line, int *idx_ptr, char **envp);
void	ji_putstr_fd(char *s, int fd);

#endif
