#ifndef __API_H__
#define __API_H__

int init_db(int buf_num);
int open_table(const char* filename);
void close_table(int table_id);
int shutdown_db();
int insert(int table_id, uint64_t key, const char* value);
int delete(int table_id, uint64_t key);
char* find(int table_id, uint64_t key);

void print_tree(int table_id);
void find_and_print(int table_id, uint64_t key); 

void license_notice( void );
void usage_1( void );
void usage_2( void );
#endif // __API_H__
