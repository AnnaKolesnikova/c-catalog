typedef struct CatItem CatItem;

struct CatItem {
    char *name;
    CatItem **children;
    int children_count; 
    CatItem *parent;
};

typedef struct Catalog {
    CatItem *root;
} Catalog;


CatItem* create(char *name);

void print_children(CatItem *item);

CatItem* append_child(CatItem *item, CatItem *child);

void read_file(char *filename);

int count_dashes(char *str);

char *get_name(char *str);

void print_catalog(Catalog *cat);
