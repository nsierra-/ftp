int			tokens_are_enough(const char **tokens, int qty)
{
	int		i;

	i = 0;
	while (i < qty)
	{
		if (!tokens[i++])
			return (0);
	}
	return (1);
}

int			tokens_are_too_much(const char **tokens, int qty)
{
	int		i;

	i = 0;
	while (tokens[i])
		++i;
	return (i > qty);
}
