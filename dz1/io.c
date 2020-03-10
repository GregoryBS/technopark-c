#include "io.h"

int read_team_result(sport_result *team);

int read_team_name(char **name);

void write_team(const sport_result team);

int read_results(sport_result **arr, int *n)
{
	if (!arr || !n)
		return ERR_PARAM;
	
	int rc = OK;
	if (scanf("%d", n) != 1 || *n <= 0)
		rc = ERR_IO;
	if (rc == OK)
	{
		rc = alloc_mem(arr, *n);
		if (rc == OK)
		{
			int i = 0;
			while (i < *n && rc == OK)
			{
				rc = read_team_result(*arr + i);
				i++;
			}
		}
	}
	return rc;
}

void write_best(const sport_result *arr, const int *index)
{
	printf("Number Checkpoints Time Name\n");
	int i = 0;
	while (index[i] >= 0 && i < BEST_COUNT)
	{
		write_team(arr[index[i]]);
		i++;
	}
}

void write_team(const sport_result team)
{
	printf("%d %d %f %s\n", team.number, team.checkpoints, team.time, team.name);
}

int read_team_name(char **name)
{
	if (!name)
		return ERR_PARAM;
	
	int rc = OK, flag = OK;
	string n = { NULL, 0, 0, 10 };
	char c;
	while (rc == OK && flag == OK && (c = getc(stdin)) != EOF)
	{
		if (n.len == n.size)
		{
			char *tmp = (char*) realloc(n.data, (n.size + n.space) * sizeof(char));
			if (tmp)
			{
				n.data = tmp;
				n.size += n.space;
			}
			else
				rc = ERR_MEM;
		}
		if (rc == OK)
		{
			n.data[n.len] = c;
			n.len += 1;
		}
		if (c == '\n')
			flag = !flag;
	}
	if (rc == OK)
	{
		if (n.len > 0)
		{
			*name = n.data;
			(*name)[n.len - 1] = '\0';
		}
		else
			rc = ERR_IO;
	}
	return rc;
}

int read_team_result(sport_result *team)
{
	if (!team)
		return ERR_PARAM;
	
	int rc = OK;
	if (scanf("%d%d%f", &team->number, &team->checkpoints, &team->time) != 3 || team->checkpoints < 0 || team->time < EPS)
		rc = ERR_IO;
	if (rc == OK)
		rc = read_team_name(&team->name);
	return rc;
}