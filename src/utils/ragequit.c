#include "utils.h"

int	ragequit(char *message, int	exit_status)
{
	ft_printf("%s", message);
	return (exit_status);
}