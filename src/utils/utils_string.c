int	is_quote(const char c)
{
	return (c == '\'' || c == '"');
}

int	is_blank(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
