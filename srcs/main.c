
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
	//
	// // ------- Test 1 -----------
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
	//
	// // // ------- Test free -----------
	// // // char *str;
	// //
	// printf("--- START ---\n");
	// str = (char *)malloc(8);
	// free(str);
	// str = (char *)malloc(8);
	// free(str);
	// printf("1\n");
	// str = (char *)malloc(16);
	// free(str);
	// printf("2\n");
	// str = (char *)malloc(32);
	// free(str);
	// printf("3\n");
	// str = (char *)malloc(16);
	// free(str);
	// //
	// // // -------- Test realloc ---------
	// // char *str;
	// char *tmp;
	//
	// str = (char *)malloc(200);
	// tmp = (char *)malloc(200);
	// free(tmp);
	// str = (char *)realloc(str, 400);
	// show_alloc_mem();

	char *str;
	char *str2;
	char *str3;
	char *str4;

	str4 = (char *)malloc(50);
	str = (char *)malloc(40);
	str3 = (char *)malloc(30);
	str2 = (char *)malloc(20);
	free(str);
	// free(str2);
	free(str3);
	// free(str4);
	t_block	*free_block_list;

	free_block_list = g_main_struct->free_block;
	while (free_block_list)
	{
		printf("free block size: %ld\n", free_block_list->size);
		free_block_list = free_block_list->free_next;
	}
	show_alloc_mem();
	return (0);
}
