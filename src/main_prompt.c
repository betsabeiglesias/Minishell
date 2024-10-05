

int main()
{
	char *line;

	while(1)
	{	
		line = prompt( );
		free(line);
		if (line == NULL) // Detecta EOF (Ctrl+D)
    		break;

	}
	
	return(0);
}