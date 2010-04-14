/* A program for exploring ideas */
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "parser.h"
#include "to_newick.h"

void get_params(int argc, char *argv[])
{
	if (2 == argc) {
		if (0 != strcmp("-", argv[1])) {
			FILE *fin = fopen(argv[1], "r");
			extern FILE *nwsin;
			if (NULL == fin) {
				perror(NULL);
				exit(EXIT_FAILURE);
			}
			nwsin = fin;
		}
	} else {
		fprintf(stderr, "Usage: %s <filename|->\n",
				argv[0]);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	struct rooted_tree *tree;

	get_params(argc, argv);

	while (NULL != (tree = parse_tree())) {
		dump_newick(tree->root);
		destroy_tree(tree, FREE_NODE_DATA);
	}
	
	return 0;
}
