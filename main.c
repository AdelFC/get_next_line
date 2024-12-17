#include "get_next_line.h"
#include <fcntl.h> // Pour open
#include <stdlib.h> // Pour atoi
#include <stdio.h> // Pour printf, perror

int	main(int argc, char **argv)
{
	int		fd;
	int		n;
	int		i;
	char	*line;

	if (argc != 3) // Vérifier le nombre d'arguments
	{
		printf("Usage: %s <file> <number_of_lines>\n", argv[0]);
		return (1);
	}

	// Ouvrir le fichier
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}

	// Vérification de la valeur numérique
	n = atoi(argv[2]);
	if (n <= 0)
	{
		printf("Error: <number_of_lines> must be a positive integer\n");
		close(fd);
		return (1);
	}

	// Lire et afficher les lignes
	i = 0;
	while (i < n)
	{
		line = get_next_line(fd);
		if (!line) // Gérer l'arrêt à la fin du fichier
		{
			printf("End of file reached or error.\n");
			break;
		}
		printf("LINE %d: %s", i + 1, line);
		free(line);
		i++;
	}

	// Fermer le fichier et terminer proprement
	close(fd);
	return (0);
}
