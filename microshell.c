#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <printf.h>

typedef struct	s_cmd
{
	char			**args;
	int				pipe;
	int				fd[2];
	struct s_cmd	*next;
}				t_cmd;

void ft_quit()
{
	write(2, "error: fatal\n", 13); 
	exit(1);
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char 	*ft_strdup(char *str)
{
	int i = 0;
	char *ret;

	if (!(ret = malloc(ft_strlen(str) + 1)))
		ft_quit();
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

t_cmd *new_node(char **av, int *n)
{
	int i = 0;
	t_cmd *ret = malloc(sizeof(t_cmd));

	ret->args = malloc(sizeof(char *) * 200);  //yolo
	ret->pipe = 0;
	ret->next = 0;

	while (av[*n] && strcmp(av[*n], ";") && strcmp(av[*n], "|"))
	{
		
		ret->args[i++] = ft_strdup(av[(*n)++]);
		//printf("%d %s\n", *n, ret->args[i - 1]);
	}
	if (strcmp(*av, "|"))
		ret->pipe = 1;
	return (ret);
}



int main(int ac, char **av, char **env)
{
	int n = 0;
	t_cmd *list = 0;
	t_cmd *tmp;

	while (++n < ac)
	{
		if (!list)
		{
			list = new_node(av, &n);
			tmp = list;
		}
		else
		{
			tmp->next = new_node(av, &n);
			tmp = tmp->next;
		}
	}
	
}