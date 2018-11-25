#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "menu.h"
#include "../catalog/catalog.h"

// void showMenu(MENU_ITEM *menuItems, int length)
int showMenu()
{
    int choice;
    while(choice = menu())
    {
        switch (choice)
        {
        case 1:
            // puts("\nUnder construction!\n");
            read_file("catalog.txt");
            break;
        default:
            puts("\n\nError!");
            break;
        }
    }

    getchar();
    return 0;
}

int menu()
{
    int choice;
    char str[50];
    MENU_ITEM T1 = {1, "Show Categories" };
    MENU_ITEM T2 = {0, "Exit" };

    do {
        printf("Main menu:\n%d. %s", T1.id, T1.name);
        printf("\n%d. %s\nChoose>>> ", T2.id, T2.name);
        scanf("%s", str);

        if(str[0] == '0')
        {
            return 0;
        }
        choice = atoi(str);
        if (choice == 0)
        {
            printf("\n\nERROR!!!\n\n");
            getchar();
        }
    }
    while (choice == 0);
    return choice;
}