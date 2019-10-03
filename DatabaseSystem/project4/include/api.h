#ifndef __API_H__
#define __API_H__

int init_db(int buf_num);
int open_table(char* filename, int num_columns);
void close_table(int table_id);
int shutdown_db();
int insert(int table_id, int64_t key, int64_t* values);
int erase(int table_id, int64_t key);
int64_t* find(int table_id, int64_t key);
int64_t join(const char* query);

void print_tree(int table_id);
void find_and_print(int table_id, int64_t key); 
void analysis(int table_id);

void license_notice( void );
void usage_1( void );
void usage_2( void );
#endif // __API_H__
