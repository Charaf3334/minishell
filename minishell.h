/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:23:12 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/02 12:04:55 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_H "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_quote_exp
{
	int					start;
	int					end;
	char				c;
	struct s_quote_exp	*next;
}						t_quote_exp;

typedef struct s_dollar_exp
{
	int					start;
	int					end;
	struct s_dollar_exp	*next;
}						t_dollar_exp;

typedef struct s_cd
{
	char				*path;
	char				*tmp;
	char				**parts;
	size_t				cap;
	char				**stk;
	int					top;
	size_t				total;
	char				*res;
	char				*p;
	size_t				len;
}						t_cd;

typedef struct s_free
{
	void				*adr;
	struct s_env		**my_env;
	struct s_free		*next;
}						t_free;

typedef struct s_quotes
{
	t_free				**free_nodes;
	char				quote_context;
	t_quote_exp			*quote_node;
	struct s_exec		*node;
}						t_quotes;

typedef struct s_split
{
	int					in_s;
	int					in_d;
	int					len;
	int					i;
	int					count;
	char				quote;
}						t_split;

typedef struct s_popword
{
	int					pos;
	int					end;
}						t_popword;

typedef struct s_files
{
	char				*file_name;
	int					type;
	int					ambiguous;
	int					append;
	struct s_files		*next;
}						t_files;

typedef struct s_exec
{
	char				**cmd;
	char				**cmd_before;
	char				**before_str;
	char				*before_str_joined;
	int					len_cmds;
	char				**infiles;
	char				**infiles_before;
	int					len_infiles;
	int					last_in;
	char				**here_doc;
	int					len_here_doc;
	char				**outfiles;
	char				**outfiles_before;
	int					len_outfiles;
	int					append;
	int					nodes_num;
	int					stdin_fd;
	int					stdout_fd;
	int					heredoc_fd;
	pid_t				pid;
	int					exit_flag;
	struct s_env		**my_env;
	struct s_files		*files;
	struct s_exec		*next;
}						t_exec;

typedef struct s_env_ll
{
	char				*key;
	char				*value;
	struct s_env_ll		*next;
}						t_env_ll;

typedef struct s_env
{
	char				**env_strs;
	t_env_ll			*env_ll;
	char				**default_path;
}						t_env;

typedef struct s_cmd_in
{
	int					j_cmd;
	int					j_in;
	int					j_here;
	int					index;
	int					flag;
	int					here_doc;
}						t_cmd_in;

typedef struct s_vals
{
	int					nodes_num;
	char				*fix_spaces;
	char				**before_str;
	char				**str;
	int					i;
	int					j;
	int					len_line;
	int					len_before;
	int					z;
	int					k;
	int					k2;
	int					k3;
	t_env				**my_env;
}						t_vals;

typedef struct s_exp
{
	int					count_d;
	int					start;
	char				*extracted;
}						t_exp;

typedef struct s_pls
{
	int					i;
	int					count_d;
	char				quote;
	char				*joined;
	int					in_d;
	int					in_s;
}						t_pls;

typedef struct s_access
{
	int					flags;
	int					inf_i;
	int					outf_i;
	char				*raw;
	char				*exp;
	int					fd;
}						t_access;

typedef struct s_exp_here
{
	char				*raw;
	char				*var_name;
	char				*value;
	char				*var_path;
	int					start;
	int					flag;
	char				*line;
}						t_exp_here;

typedef struct s_here_docc
{
	pid_t				pid;
	int					i;
}						t_here_docc;

typedef struct s_exp_dollar_var
{
	char				*var_name;
	char				*var_value;
	char				*var_path;
	int					st;
	char				*status;
}						t_exp_dollar_var;

typedef struct s_join_strs
{
	int					i;
	int					total_len;
	char				*result;
	char				*ptr;
	char				*s;
	int					count;
}						t_join_strs;

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
}						t_list;

typedef struct s_exp_in_out
{
	char				**files_array;
	char				*expanded;
	int					was_quoted;
	int					i;
	int					new_len;
	char				**source_array;
	t_quote_exp			*quote_node;
	t_dollar_exp		*dollar_node;
	t_list				*file_list;
}						t_exp_in_out;

typedef struct s_quotes_node
{
	t_quote_exp			*head;
	t_quote_exp			*curr;
	t_free				**free_nodes;
}						t_quotes_node;

typedef struct s_dollar_nodes
{
	t_dollar_exp		*head;
	t_dollar_exp		*curr;
	t_free				**free_nodes;
}						t_dollar_nodes;

typedef struct s_expand
{
	t_quote_exp			*quote_node;
	t_dollar_exp		*dollar_node;
	t_list				*cmd_list;
	char				**cmds;
	char				*expanded;
	int					was_quoted;
}						t_expand;

typedef struct s_atol
{
	unsigned long long	result;
	unsigned long long	max;
	unsigned int		limit;
	int					sign;
	int					i;
}						t_atol;

t_env_ll				*ft_lstlast(t_env_ll *lst);
char					*ft_strjoin(char *s1, char *s2, t_free **free_nodes);
char					*ft_strjoin3(char *s1, char *s2, char *s3,
							t_free **free_nodes);
char					*ft_strchr(const char *s, int c);
void					var_set(t_split *vars);
int						is_sep(char ch, char *c);
int						ft_strcmp(char *s1, char *s2);
size_t					ft_strlen(const char *s);
void					*ft_memcpy(void *dst, const void *src, size_t n);
char					*ft_join_strs(char **strs, t_free **free_nodes);
char					*ft_strdup(const char *s1, t_free **free_nodes);
char					*ft_substr(char *s, unsigned int start, size_t len,
							t_free **free_nodes);
void					ft_putstr_fd(char *str, int fd, int option);
char					*ft_strtrim(char *s1, char const *set,
							t_free **free_nodes);
char					**ft_split(char *str, char *c, t_free **free_nodes);
char					**ft_split_normal(char *str, char *c,
							t_free **free_nodes);
char					**ft_split_not_normal(char *str, char *c,
							t_free **free_nodes);
char					**ft_split_leaks(char *str, char *c);
char					**ft_split_quoted(char *str, char *c,
							t_free **free_nodes);
char					**ft_split_libft(char const *str, char *c);
int						utils_access_out(t_access *vars, t_files *files);
int						count_words2(char *str, char *c);
int						get_word_len2(char *str, char *c, int *j);
char					*ft_itoa(int n, t_free **free_nodes);
void					ft_lstadd_back(t_env **my_env, t_env_ll *new);
long					ft_atol(char *str);
char					*ft_strdup_normal(const char *s1);
char					*ft_strjoin3_normal(char *s1, char *s2, char *s3);
char					*ft_substr_normal(char *s, unsigned int start,
							size_t len);
char					*ft_strjoin_normal(char *s1, char *s2);
size_t					ft_doublen(char **str);
int						count_words(char *str, char *c);
int						get_word_len(char *str, char *c, int *j);
int						count_outfiles(char *before_str_joined);
int						count_cmds(char *s);
int						count_infiles(char *before_str_joined);
void					count_the_length(t_exec *exec, char *line, int *len,
							int *len_before);
char					*add_spaces(char *line, t_free **free_nodes);
t_exec					*create_new_node(t_free **free_nodes);
int						count_pipes(char *line);
void					close_all_fds(void);
void					env_and_1byte_alloc(t_env **my_env,
							t_free **free_nodes);
void					free_env(t_env **my_env);
int						process_line(char **line, t_free **free_nodes);
void					process_execution(char *line, t_free **free_nodes,
							t_env **my_env);
void					process_loop(t_vals *v, t_exec **head, t_exec **current,
							t_free **free_nodes);
void					handle_redirections(t_vals *v, t_exec *current,
							t_free **free_nodes);
void					init_process_loop(t_vals *v, t_exec **head,
							t_exec **current, t_free **free_nodes);
void					expand_if_possible(t_exec **current,
							t_free **free_nodes);
void					exec_init(t_exec **current, t_vals *v, t_free **fnds,
							t_env **my_env);
int						ft_exit_status(int status, int flag);
void					append_new_node(t_exec **head, t_exec **current,
							t_free **free_nodes);
void					vals_init(t_vals *vals, char *line, t_free **f_nds);
t_env					*env_generator(char **env, t_free **free_nodes);
void					*ft_malloc(size_t size, t_free **free_nodes);
void					*ft_malloc2(size_t size, t_env **my_env,
							t_free **free_nodes);
void					ft_lstclear(t_free **lst);
int						ft_exit_status(int status, int flag);
t_env					*env_generator(char **env, t_free **free_nodes);
void					free_env(t_env **my_env);
int						check_syntax(char *line);
int						print_quotes(int quotes);
int						print_redirection(int redirection);
int						print_pipe(void);
int						check_quotes(char *line);
int						quotes(char c, char *quote);
int						invalid_redirection(char *line);
int						invalid_pipe(char *line);
void					handle_cmds_ins(char **str, t_exec *exec,
							t_free **free_nodes, int *i);
void					handle_out(char **str, t_exec *exec,
							t_free **free_nodes, int *i);
void					handle_cmds_before(char **before_str, t_exec *exec,
							t_free **free_nodes, int *z);
void					handle_files(char **str, t_exec *exec,
							t_free **free_nodes, int *i);
void					handle_out_before(char **before_str, t_exec *exec,
							t_free **free_nodes, int *k2);
void					handle_in_before(char **before_str, t_exec *exec,
							t_free **free_nodes, int *k3);
void					expanding(t_exec *node, t_free **free_nodes);
void					expanding_in_out(t_exec *node, t_free **free_nodes,
							int mode);
int						is_alnum(char c);
char					*my_getenv(t_quotes *context, char *key);
int						is_di(char c);
int						is_al(char c);
int						count_dollar(t_exec *node);
int						check_dollar(char *str);
char					*ft_charjoin(char *str, char c, t_free **free_nodes);
void					*ft_new_quote_exp(int start, int end, char c,
							t_free **free_nodes);
void					ft_exp_quotes(t_quote_exp **head_quote, char *str,
							t_free **free_nodes);
void					*ft_new_dollar_exp(int start, int end,
							t_free **free_nodes);
void					ft_exp_dollars(t_dollar_exp **head_dollar, char *str,
							t_free **free_nodes);
int						index_last_quotes(int index, t_quote_exp *quote_node,
							char *type);
int						is_in_quotes(int index, t_quote_exp *quote_node,
							char *type);
int						check_exp(char **str, int len);
void					handle_regular_chars(char *before_str, int *i,
							char **result, t_quotes *context);
void					execution(t_exec *head, int nodes_num,
							t_free **free_nodes);
char					**extract_strs_env(char **env, t_free **free_nodes);
t_env_ll				*extract_ll_env(char **env_strs);
char					**gen_strs_env(t_env_ll *env_ll);
int						find_key(char *key, t_env_ll *env_ll);
void					append_node(t_env_ll **env_ll, char *key, char *value);
t_env_ll				*ft_new_env_ll_2(char *key, char *value, t_exec *head);
t_env_ll				*ft_new_env_ll(char *str, t_exec *node);
void					free_and_delete_node(t_env_ll **env_ll, char *key,
							t_exec *head);
int						check_valid_identifier(char *ident);
t_env_ll				*create_new_env(void);
int						check_access(t_exec *node, t_free **free_nodes);
void					open_infile(t_exec *node, t_free **free_nodes);
int						open_here_doc(t_exec *node, t_free **free_nodes);
int						open_outfile(t_exec *node, t_free **free_nodes);
void					ft_dup2(int old_fd, int new_fd, t_env **my_env,
							t_free **free_nodes);
char					*check_valid_path(char **paths, char **args,
							t_free **free_nodes);
char					*extract_path(char **env);
t_env_ll				*create_new_env(void);
void					print_error(char *str, int mode, t_free **free_nodes);
t_env_ll				*ft_new_env_ll_2(char *key, char *value, t_exec *head);
t_env_ll				*ft_new_env_ll(char *str, t_exec *node);
char					**format_env_vars(char **env, t_free **free_nodes);
int						check_access(t_exec *node, t_free **free_nodes);
void					sig_heredoc(int signo);
int						expand_here_doc_expand(char **new, int *i, char *line,
							t_quotes ctx);
char					*expand_here_doc(char *line, t_free **free_nodes,
							t_exec *node);
char					*here_doc_case(char *word, t_free **free_nodes);
void					here_doc_child(t_exec *head, int *p_fd, int i,
							t_free **free_nodes);
int						handle_builtins(t_exec *head, t_free **free_nodes);
char					*expand_variable(char *arg, t_env **env);
int						echo_option(t_exec *head);
void					execute_cmd(t_exec *node, t_free **free_nodes);
int						wait_for_childs(int *quit_printed, t_exec *head);
void					execute_nodes_helper(int p_fd[], int nodes_nums,
							t_exec *node, t_free **free_nodes);
int						handle_exit(t_exec *node, t_free **free_nodes);
void					cleanup_and_exit(t_env **env, t_free **free_nodes,
							int status);
int						handle_export_unset(t_exec *node, t_free **free_nodes,
							int *p_fd, int nodes_nums);
int						handle_export(t_exec *node, t_free **free_nodes,
							int *p_fd, int nodes_nums);
void					refresh_env_strs(t_exec *head);
void					print_export_env(char **env_quotes, int out_fd,
							t_free **free_nodes);
void					handle_export_no_args(t_exec *head, t_free **free_nodes,
							int *p_fd, int nodes_nums);
void					export_append_value(t_exec *head, t_free **free_nodes,
							char *cmd);
void					export_no_value(t_exec *head, char *cmd);
void					export_normal_assign(t_exec *head, t_free **free_nodes,
							char *cmd);
t_list					*ft_lstlast_exp(t_list *lst);
void					ft_lstadd_back_exp(t_list **my_lst, t_list *new);
int						ft_lstsize_exp(t_list *my_lst);
t_list					*ft_lstnew_exp(char *content, t_free **free_nodes);
int						is_quoted(char *str);
int						has_quote(char *str);
t_env_ll				*extract_ll_env(char **env_strs);
int						execute_nodes(t_exec *node, int nodes_nums,
							t_free **free_nodes);
int						cd_print_home_error(char *pwd, int flag,
							t_free **free_nodes);
void					cd_helper(t_exec *head, char *oldpwd_value, char *pwd,
							t_free **free_nodes);
int						cd_handle_file(char *path, t_free **free_nodes);
int						cd_no_args(t_quotes *c, t_exec *head, char *pwd,
							int flag);
void					cd_no_args_helper(char *home, t_quotes *c, int flag,
							char *pwd);
char					*formated_pwd(char *pwd, char *new_path,
							t_free **free_nodes);
void					helper_form_pwd(t_cd *vars, t_free **free_nodes);
void					init1(t_cd *vars, char *pwd, char *new_path,
							t_free **free_nodes);
int						check_dots_slash(const char *str, int mode);
int						handle_cd(t_exec *node, t_free **free_nodes);
void					exit_from_here_doc(char *line, int *p_fd, t_exec *head,
							t_free **free_nodes);
void					handle_fallback(t_exp_here *v, char **new, int *i,
							t_quotes ctx);
void					expand_dollar_variable(t_dollar_exp *dollar,
							char *before_str, char **result, t_quotes *context);
void					handle_dollar_init(char *quote_type, int *in_quotes,
							t_dollar_exp *dollar, t_quotes *context);
void					set_ambiguous(t_files *files, char *name);
void					init_exp(t_exp_dollar_var *vars, char *before_str,
							t_dollar_exp *dollar, t_quotes *context);
void					expand_dollar_variable2(t_dollar_exp *dollar,
							char *before_str, char **result, t_quotes *context);
void					init_exp2(char *quote_type, int *in_quotes,
							t_dollar_exp *dollar, t_quotes *context);
void					handle_dollar2(t_dollar_exp *dollar, char *before_str,
							char **result, t_quotes *context);
void					*ft_new_quote_exp(int start, int end, char c,
							t_free **free_nodes);
void					append_new_quotes_node(t_quotes_node *info, int start,
							int end, char c);
void					ft_exp_quotes(t_quote_exp **head_quote, char *str,
							t_free **free_nodes);
t_list					*ft_lstlast_exp(t_list *lst);
void					files_ll_init(t_files *file);
void					files_ll(t_exec *x, t_free **f_nds, int arr[],
							int *index);
void					init(t_cmd_in *vars, t_exec *x, int *i, t_free **f_nds);
void					in_doc(char **str, t_exec *exec, t_cmd_in *vars,
							t_free **f_nds);
void					checker(t_cmd_in *vars, int *i);
void					handle_cmds_ins(char **str, t_exec *exec,
							t_free **free_nodes, int *i);
void					handle_in_before(char **before_str, t_exec *exec,
							t_free **free_nodes, int *k3);
void					handle_out_before(char **before_str, t_exec *exec,
							t_free **free_nodes, int *k2);
void					handle_out(char **str, t_exec *exec,
							t_free **free_nodes, int *i);
void					init_before(t_cmd_in *vars, t_exec *x, int *z,
							t_free **f_nds);
void					handle_cmds_before(char **before_str, t_exec *exec,
							t_free **free_nodes, int *z);
void					handle_files(char **str, t_exec *exec,
							t_free **free_nodes, int *i);
void					handle_files_utils(t_exec *exec, char **str,
							t_free **free_nodes, t_cmd_in *vars);
int						count_operators(char *line);
int						count_infiles(char *before_str_joined);
int						count_outfiles(char *before_str_joined);
void					outfile_utils(char *line, int *i, int *count);
int						fd_return(t_files *files);
int						handle_unset(t_exec *head);
int						has_only_spaces(char *str);

#endif