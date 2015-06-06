#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct obyvatel {
	char meno[30], priezvisko[30];
	int cislo, datum_prihlasenia;
	struct obyvatel *next;
} OBYVATEL;

OBYVATEL *pridaj(OBYVATEL *head, OBYVATEL *new)
{
	OBYVATEL *curr = head, *prev = NULL;

	if (head == NULL)
		head = new;

	while (curr) {
		if (strcmp(new->priezvisko, curr->priezvisko) < 0) {
			if (prev == NULL) {
				new->next = head;
				head = new;
			}
			else {
				prev->next = new;
				new->next = curr;
			}
			break;
		}
		prev = curr;
		curr = curr->next;
	}

	if (prev && curr == NULL)
		prev->next = new;

	return head;
}

OBYVATEL *vymaz(OBYVATEL *head, int datum)
{
	OBYVATEL *prev = NULL, *curr = head, *delete;

	while (curr) {
		if (curr->datum_prihlasenia > datum)
		{
			delete = curr;
			if (prev == NULL)
			{
				head = curr->next;
				curr = head;
			}
			else {
				prev->next = curr->next;
				curr = prev->next;
			}
			free(delete);
		} 
		else {
			prev = curr;
			curr = curr->next;
		}
	}

	return head;
}

void vypis(OBYVATEL *head)
{
	int i = 1;
	while(head) {
		printf("%d.\n%s\n%d\n", i++, head->priezvisko, head->datum_prihlasenia);
		head = head->next;
	}
}


void freedom(OBYVATEL *head)
{
	OBYVATEL *curr;
	while (head)
	{
		curr = head;
		head = head->next;
		free(curr);
	}
}

int main()
{
	OBYVATEL *head = NULL, *new;
	int datum;
	char opt;

	while ((opt = getchar()) != 'k')
	{
		if (opt == 'p') {
			new = (OBYVATEL *) malloc(sizeof(OBYVATEL));
			fscanf(stdin, "%[^\r\n] %d \n", new->priezvisko, &new->datum_prihlasenia);
			new->next = NULL;
			head = pridaj(head, new);
		}
		else if (opt == 'z') {
			scanf("%d", &datum);
			head = vymaz(head, datum);
		}
		else if (opt == 'v') {
			vypis(head);
		}
	}

	freedom(head);

	return 0;
}
