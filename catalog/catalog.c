#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "catalog.h"

struct CatItem* create(char *name)
{
    struct CatItem *p = (struct CatItem *)malloc(sizeof(CatItem));
    p->name = name;
    if(p == NULL) {
        printf("Error.");
        exit(0);
    }
    return p;
}

void print_children(CatItem *item)
{
    if (item->children == NULL) {
        printf("None\n");
        return;
    }
    int n = item->children_count;
    for (int i = 0; i < n; i++) {
        CatItem *child = item->children[i];
        printf("%s\n", child->name);
    }
}

CatItem* append_child(CatItem *item, CatItem *child)
{
    int n = item->children_count;
    if (item->children_count == 0) {
        item->children = (CatItem**) malloc(sizeof(CatItem*));
    } else {
        item->children = (CatItem**) realloc(item->children, (n + 1) * sizeof(CatItem*));
    }
    item->children_count = n + 1;
    item->children[n] = child;
    child->parent = item;
    return item;
}

void read_file(char *filename)
{
    int prev_dashes_counter = 0;
    char line[100 + 1] = "";  /* initialize all to 0 ('\0') */
    FILE *fp = fopen(filename, "r");

    CatItem *item = create("root");
	Catalog cat = {item};

    if(fp == NULL) 
    {
        printf("\nNo file\n");
        return;
    }
    while(fgets(line, sizeof(line), fp) != NULL) {
        int dashes_count = count_dashes(line);
        if(dashes_count > prev_dashes_counter)
        {
            item = item->children[item->children_count - 1];          
        }
        else if(dashes_count < prev_dashes_counter)
        {
            int diff = prev_dashes_counter - dashes_count;
            for(int i = 0; i < diff; i++)
            {
                item = item->parent;
            }
        }
        char *name = get_name(line);
        CatItem *child = create(name);
        append_child(item, child);
        prev_dashes_counter = dashes_count;
    }
    print_catalog(&cat);
}

int count_dashes(char *str)
{
    int i = 0;
    while(str[i] == '-')
    {
        i++;
    }
    return i;
}

char *get_name(char *str)
{
    int i = 0;
    while(str[i] == '-')
    {
        i++;
    }
    int n = strlen(str);
    int to = str[n - 1] == '\n' ? n - 1 : n;
    int len = to - i;
    char *name = (char*) malloc(len + 1);
    strncpy(name, str + i, len);
    name[len] = '\0';
    return name;
}

void traverse(CatItem *item, int level)
{
    for(int j = 0; j < level; j++ )
    {
        printf("-");
    }
    printf("%s\n", item->name);
    if(item->children == NULL)
    {
        return;
    }
    for(int i = 0; i < item->children_count; i++)
    {
        traverse(item->children[i], level + 1);
    }
}

void print_catalog(Catalog *cat)
{
    traverse(cat->root, -1);
}