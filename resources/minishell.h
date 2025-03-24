/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:16:45 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/03/24 12:26:08 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/header/ft_printf.h"
# include "libft/header/get_next_line.h"
# include "libft/header/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_tokens
{
	WORD,
	PIPE,
	REDIREC_IN,  // <
	REDIREC_OUT, // >
	APPEND,      // >>
	HEREDOC,     // <<
}					t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token_type;
	struct s_lexer	*next;
}					t_lexer;

void				minishell_loop(t_lexer *token);
t_lexer				*tokenizer(char *str, t_lexer *token);
t_lexer				*lexer(char *str, t_lexer *token);
int					check_quotes(char *str);
#endif