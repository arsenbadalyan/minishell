#ifndef BUILT_IN__H
#define BUILT_IN__H

// echo
char	*_echo(char *line, int here_doc_mode);
char	*modify_line(char *line, int here_doc_mode, int sg_quote, int db_quote);
int		quote_check(int *sg_quote, int *db_quote, char c);
int		_pwd(void);

#endif