#ifndef __BPT_H__
#define __BPT_H__

// Uncomment the line below if you are compiling on Windows.
// #define WINDOWS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#define LEAF_ORDER 32
#define INTERNAL_ORDER 249
#define PAGESZ 4096
#define SUCCESS 0
#define FAIL -1
#define NO_FREE_PAGE 0
#define NO_NODE_PAGE 0
#define DISUSED 0
#define DEFAULT_NUMBER_OF_PAGES 301

typedef uint64_t pagenum_t;
typedef struct record record;
typedef struct node node;
typedef struct header_page_t header_page_t;
typedef struct free_page_t free_page_t;
typedef struct page_t page_t;

enum db_page_type {
	UNDETERMINED, HEADER, FREE, LEAF, INTERNAL
};

struct record {
	char value[120];	// (on-disk)
};

// Used for internal and leaf pages.
struct node {
	int type;			// (in-memory)
	pagenum_t pagenum;	// (in-memory)
    void ** pointers;	// (in-memory)
	uint64_t* coffset;	// child page offset: used for internal (on-disk)
	uint64_t rsoffset;	// right sibling page offset: used for leaf (on-disk)
    int64_t * keys;		// (on-disk)
    node * parent;		// (in-memory)
	uint64_t poffset;	// parent page offset (on-disk)
    int is_leaf;		// (on-disk)
    int num_keys;		// (on-disk)
};

// Used for the header page.
struct header_page_t {
	int type;			// (in-memory)
	pagenum_t pagenum;	// (in-memory)
	uint64_t foffset;	// Free page offset (on-disk)
	free_page_t * free;	// (in-memory)
	uint64_t roffset;	// root page offset (on-disk)
	node * root;		// (in-memory)
	uint64_t num_pages;	// Number of pages (on-disk)
	/* reserved */
};

// Used for the free pages.
struct free_page_t {
	int type;			// (in-memory)
	pagenum_t pagenum;	// (in-memory)
	uint64_t nfoffset;	// Next free page offset (on-disk)
	free_page_t * next;	// Next free page address (in-memory)
};

// Used for managing pages.
struct page_t{
	int type;			// (in-memory)
	pagenum_t pagenum;	// (on-disk->in-memory)
};



// GLOBALS.

extern FILE * db;

extern header_page_t * headpg;	// header page

// FUNCTION PROTOTYPES.

// Output and utility.

node * find_leaf(int64_t key);
record * find_record(int64_t key);
char * find(int64_t key);
int cut( int length );

// Insertion.

record * make_record(char* value);
node * make_node(free_page_t* free);
node * make_leaf(free_page_t* free);
free_page_t* mem_use_free_page();
int get_left_index(node * parent, node * left);
node * insert_into_leaf( node * leaf, int64_t key, record * pointer );
node * insert_into_leaf_after_splitting(node * root, node * leaf, int64_t key,
                                        record * pointer);
node * insert_into_node(node * root, node * parent, 
        int left_index, int64_t key, node * right);
node * insert_into_node_after_splitting(node * root, node * parent,
                                        int left_index,
        int64_t key, node * right);
node * insert_into_parent(node * root, node * left, int64_t key, node * right);
node * insert_into_new_root(node * left, int64_t key, node * right);
node * start_new_tree(int64_t key, record * pointer);
int insert(int64_t key, char * value);

// Deletion.

int get_neighbor_index( node * n );
node * adjust_root(node * root);
node * coalesce_nodes(node * root, node * n, node * neighbor,
                      int neighbor_index, int k_prime);
node * delete_entry( node * root, node * n, int64_t key, void * pointer );
int delete( int64_t key );

/* Utilities */
int pathname_check(char* pathname);
free_page_t* select_free_page();
free_page_t* free_page();
uint64_t get_file_size();
char* mem_make_write_buf(const page_t* pg);
char* mem_make_read_buf();
void mem_dealloc_buf(char* buf);
header_page_t* mem_make_header_page();
void mem_dealloc_header_page();	// not used yet
pagenum_t file_alloc_header_page();
free_page_t* mem_make_free_page(pagenum_t pagenum);
void mem_dealloc_free_page(free_page_t* free_page);	// not used yet
pagenum_t file_alloc_free_page(pagenum_t new_pagenum);
int mem_read_page(char* buf, page_t* dest);


/* file managing APIs */
pagenum_t file_alloc_page();
void file_free_page(pagenum_t pagenum);
void file_read_page(pagenum_t pagenum, page_t* dest);
void file_write_page(pagenum_t pagenum, const page_t* src);

/* open db */
void create_db();
int open_header_page();
int open_free_pages();
node* open_node();
node* open_root();
node* build_nodes(node* root, node* sibling[2]);
int open_db_entry();
int open_db(char* pathname);



#endif /* __BPT_H__*/
