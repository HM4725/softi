# project 4: Multicolumn and Join 

## APIs

1. int init_db(int buf_num);
2. int open_table(const char * filename, int num_columns);
3. void close_table(int table_id);
4. int shutdown_db();
5. int insert(int table_id, int64_t key, int64_t * values);
6. int erase(int table_id, int64_t key);
6. int64_t * find(int table_id, int64_t key);
3. int64_t join (const char * query);


## Design

### project 3 (complement)

* The data type of key in record is changed.

uint64_t -> int64_t

* Some function names were changed.

delete -> erase

find_buf -> buf_search

insert_buf -> buf_insert

delete_buf -> buf_release

update_buf -> buf_sync_file

* Buffer mechanism is changed.

At project 3, when a page is buffered, its buf structure is newly allocated. And when the buf is discarded, its structure is deallocated. However, at project 4, open_table finishes the allocations of all buffer blocks. Then, they are free_buf linked list. When a page is buffered, file API brings a free_buf and uses it as a buffer block of the page. If the buffer pool runs out of free_buf, file API choices a buffer block by LRU policy and then overwrites on it. They are all for speed of DBMS.

* buf_search algorithm is changed.

```linear search: O(N) -> hash search: O(1)```

The hash table and its size are in Table data structure. Hash key (index) is pagenum and value is a address of Buf. The hash table is a dynamic table. Its size is same with num_pages of the table. When the num_pages becomes double, the table becomes double (re-hashing). Because of the doubling mechanism, there is no collision in the hash table. And by the amortized analysis of the dynamic table, its re-hashing cost is close to O(1). By no collision and O(1) re-hashing, it guarantees O(1) search time. But its space cost is num_pages * 8 (sizeof(Buf * )): O(N). Later, the hash table should be replaced with a hash table which can guarantee no collision and has space cost O(Buffer pool size).

### project 4 (new)

* Multiple columns

```record: key(8), val(120) -> key(8), val[0](8), ...```

1 <= #vals <= 15

2 <= #columns <= 16


* Join

