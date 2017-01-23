
#include "malloc.h"
// ****************************** TEST MAIN ********************************* //
void print_page(void)
{
	int j = 0;
	t_page *tmp = g_main_struct->page;

	printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	while (tmp)
	{
		j++;
		printf("Page: %d, size: %d, free mem: %ld\n-----------------------\n", j, tmp->type, tmp->free_mem);
		tmp = tmp->next;
	}
	printf("Nombre de page: %d\n", j);

}

int main(void)
{
	// char **tab;
	//
	// printf("%ld\n", ROUNDUP(8192 + sizeof(t_page)));
	// tab = (char **)malloc(sizeof(char *) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();
	// *tab = (char *)malloc(sizeof(char) * 1024);
	// print_page();

	// ------- Test 1 -----------
	// char *str;
	// int i = 0;
	// while (i < 1024)
	// {
	// 	printf("%d\n", i);
	// 	str = malloc(1024);
	// 	// print_page();
	// 	// if (!(i % 2))
	// 	// 	free(str);
	// 	i++;
	// }
	// print_page();

	// // ------- Test free -----------
	// // char *str;
	//
	// printf("--- START ---\n");
	// str = (char *)malloc(8);
	// // free(str);
	// str = (char *)malloc(8);
	// // free(str);
	// printf("1\n");
	// str = (char *)malloc(16);
	// // free(str);
	// printf("2\n");
	// str = (char *)malloc(32);
	// // free(str);
	// printf("3\n");
	// str = (char *)malloc(16);
	// // free(str);
	//
	// // -------- Test realloc ---------
	char *str;
	char *tmp;

	str = (char *)malloc(200);
	tmp = (char *)malloc(200);
	free(tmp);
	str = (char *)realloc(str, 400);
	return (0);
}
