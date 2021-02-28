#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "avl_tree.h"

#define PAGE_SIZE 4096

union U128 {
    char str[16];
    __int128 int128;
};

struct lex_node {
    union U128 u128;
	struct avl_tree_node node;
};

static struct avl_tree_node *root = NULL;
struct lex_node *i;
uint64_t i_index = 0;

#define PAGE_SIZE 4096

__attribute__((constructor))
void init_first_node()
{
    i = malloc(PAGE_SIZE);
}

#define LEX_NODE(__node) avl_tree_entry(__node, struct lex_node, node)
#define STR_VALUE(node) LEX_NODE(node)->u128.int128
#define HEIGHT(node) ((node) ? LEX_NODE(node)->height : 0)
#define max(a, b) ((a) > (b) ? (a) : (b))

static int cmp_str(const struct avl_tree_node *node1,
                   const struct avl_tree_node *node2)
{
	if (STR_VALUE(node1) > STR_VALUE(node2))
        return 1;
    if (STR_VALUE(node1) < STR_VALUE(node2))
        return -1;
    return 0;
}

inline static void insert(const char* yytext, const int yyleng)
{
    memset(i[i_index].u128.str, 0, 16);
    memcpy(i[i_index].u128.str, yytext, yyleng);

    if (! avl_tree_insert(&root, &i[i_index].node, cmp_str)) {
        if ((PAGE_SIZE / sizeof(struct lex_node)) == ++i_index) {
            i_index = 0;
            i = malloc(PAGE_SIZE);
        }
        printf("%s", yytext);
    }
}

int main()
{
    char *line = NULL;
    ssize_t nread;
    size_t len = 0;

    while ((nread = getline(&line, &len, stdin)) != -1)
        insert(line, nread-1);
}
