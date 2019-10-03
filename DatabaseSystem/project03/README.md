# Project3 Buffer_management_layer

## A. Table

*  Data Structure
![table_structure](/uploads/a78b02166d48c6697c8177ec6ef56ad3/table_structure.PNG)

Table Directory�� Table�� �����ϴ� �ڷᱸ���̴�. Ư�� Table�� open �Ǹ�, �� Table file�� Table Directory�� table �迭 �� �ϳ��� ����ǰ� �� index ���� table_id�� �ȴ�. Table �迭 �� index�� 0�� ù��° ���Ҵ� table_id�� 0�̹Ƿ� ������ �ʴ´�. Table ����ü���� file descriptor�� header page, �׸��� table�� �̸��� ����ȴ�.

*  init_table_directory
![table_init_table_directory](/uploads/70acbe02349b74ce18ea27cf2d95f2f9/table_init_table_directory.PNG)

db�� ���۵Ǹ�, Table Directory�� �ʱ�ȭ���־�� �Ѵ�. init_table_directory�� �ʱ�ȭ�� ����Ѵ�. table �迭�� ũ��� capacity�� ����ǰ�, open�� table�� ���� num_alloc_tables�� ����ȴ�. init_table_directory�� ȣ��� �� �Ŀ� num_alloc_tables�� 0�̰�, capacity�� MAX_TID (10)�̴�.

*  open_table
![table_open_table](/uploads/f3459ca8e29eace7af07fe15afb5e705/table_open_table.PNG)

table�� open�ϴ� �Լ��̴�. ���� 1�� table_id ���� TableDirectory�� table �迭 �� ����ִ� ��ġ�� ã�´�. �� ���Ҹ� ã���� Ư�� table file�� ����, table�� ���� ������ �����Ѵ�.

*  close_table
![table_close_table](/uploads/2c069aa3621098e822901bb116029295/table_close_table.PNG)

table�� close�ϴ� �Լ��̴�. buffer�� �ö�� �ִ� Ư�� table�� ���� block�� ��� delete�Ѵ�. �� ���� Table Directory���� �� table�� ���� ������ �����.

## B. Buffer Manager

*  Data Structure
![buffer_structure](/uploads/28c0074caf034ebc6c8e4cdb4f078778/buffer_structure.PNG)

�� Buffer block�� Buf ����ü�� ��Ÿ���� BufMgr ����ü�� buffer block�� �����Ѵ�. Buf ����ü�� linked list�� �����Ͽ���, Least Recently Used (����, LRU) Policy�� ���� num_pages == capacity�� �� �ַ� ������ Buf�� delete�ȴ�. ���� delete�� ù��° Buf�� ������ Buf�̰� ���ټӵ��� ������ �ϱ� ���� first_buf�� prev�� ������ Buf�� �ּҸ� �����Ͽ���. ���� ������ Buf�� pin�� ���� �����̸� prev Buf�� Ȯ���Ѵ�. ��� prev �������� �����ϸ� pin ���θ� Ȯ���ϰ� pin�� ���� ��� �ش� Buf�� delete�Ѵ�. ���� �߰��Ǵ� Buf�� first_buf�� �߰��Ǹ�, cache hit�Ǵ� Buf�� read �Ǵ� write �� first_buf�� �Ű�����. LRU policy�� �������� �� file_write_page�� file_read_page�� logic�� ������ ����.

*  Page read, write on the buffer

file_write_page�� file_read_page�� logic�� ���� ����ϸ� case�� �����ϰ� ����������. �׷��� ������ write�� read�� ���ÿ� �����Ѵ�. 

`cache hit`

ù��° case�� cache hit �� ���̴�. ���⼭ cache hit�̶�, ���ۿ� �ش� �������� �̹� �ö�� �ִ� ��Ȳ���� �� �������� read �Ǵ� write�ϴ� ���� ���Ѵ�. �׸����� ���� ������ ����.

![buffer_cache_hit_1](/uploads/c46068ad21fcdb8cbafe8fa64b290937/buffer_cache_hit_1.PNG)

���� linked_list�� ó������ �ش� (table_id, pagenum)�� ���� �ִ� buf�� ã�´�. bufmgr�� num_pages�� n�� ��, O(n)�� search time�� �ҿ�� �� �ִ�. �׷��� �� search time�� ���̰��� search time�� O(1)�� ����� hash table�� �̿��� ���Ҵ�. ������ insert�� 10���� �ݺ��� ��� �ܼ� linked_list�� 2�� �̻� ������. cache Ư���� hit�Ǵ� buf�� ���ʿ� �ַ� ��ġ�ϱ� ������ linked_list���� �׷��� ū search time�� �ҿ���� �ʾҰ�, hash table�� ��쿣 insert Buf�԰� ���ÿ� hash insert�� �ؾ��ϱ� ������ linked_list�� insert���� ���� ���� �ð��� �ҿ�� ������ ���δ�.

![buffer_cache_hit_2](/uploads/becceec95d2e0e5e93e818b29aad34a6/buffer_cache_hit_2.PNG)

linked_list�� �̿��� �ش� buf�� ã�� ��, buf�� pin�� ���� ���� memcpy�� ���� ��ٷ� dest ����ü�� page�� ������ �����Ѵ�. write�� ��쿣 src ����ü�� ������ memcpy�� ���� buf�� �����ϰ� buf�� dirty bit�� �Ҵ�.

![buffer_cache_hit_3](/uploads/88b1c5a4af5e42ac72fc9ab924480206/buffer_cache_hit_3.PNG)

���������� �ش� buf�� linked_list�� �� ������ �Ű��ְ� pin�� ����. ���� �������� �ش� buf�� ������ ��ȯ�Ǵ� �̿� buf�鵵 pin�� �Ȱ� �� �־�� �Ѵ�.


`cache miss`

������ cache miss�� ���̴�. cache hit�� �ݴ�� buffer���� �ش� �������� ã�� ������ ���� ���Ѵ�. 
cache miss�� ��, buffer�� �� á�ٸ� �ش� �������� buffer�� �ø��� ���� �� block�� delete�ؾ� �Ѵ�. ���� buffer�� ���� �� �� ���°� �ƴ϶��, �ܼ��� �ش� �������� buffer�� �ø��� �ȴ�.

![buffer_cache_miss_1](/uploads/dc341d209774f2523db01465cb9700db/buffer_cache_miss_1.PNG)

![buffer_cache_miss_2](/uploads/a15df5b5b40bb85228e69ae48a47454d/buffer_cache_miss_2.PNG)

![buffer_cache_miss_3](/uploads/c53169c680e01b4483d504570fabba27/buffer_cache_miss_3.PNG)

![buffer_cache_miss_4](/uploads/b35af9528b4d4d586caa1c23985c1792/buffer_cache_miss_4.PNG)

���� buffer�� �� �� ���¶��, LRU policy�� ���� ���� ���� ������ �ʾұ� ������ first_buf�� ���� ���� �ָ� �ִ� last buf�� delete�ؾ� �Ѵ�. ������ pin�� �����ִ� ��Ȳ���� delete�� �� ����. �׷��� ������ ����å���� prev�� delete�Ѵ�. ���� prev�� pin�� �����ִٸ�, prev->prev�� Ȯ���Ѵ�. ���� �� ���� prev�� pin�� ���ٸ� �� �ش� buf�� delete�Ѵ�. 

![buffer_cache_miss_5](/uploads/ed51558063c500331d7ce3dc85062dd9/buffer_cache_miss_5.PNG)

![buffer_cache_miss_6](/uploads/1a7b740dcc8a65c084c7eca14b6aaebe/buffer_cache_miss_6.PNG)

![buffer_cache_miss_7](/uploads/f6ce8def42bea4c6ec61abe8483953b5/buffer_cache_miss_7.PNG)

�������� �ش� page�� buffer�� �ø� �� write �Ǵ� read�� �ϴ� �ܰ��̴�. ���� buffer�� �� ���� �ʾҾ������ �� �ܰ踸 �����ϸ� �ȴ�. ���� pin�� ���� ���·� �ش� page�� linked_list�� ���� �տ� ��ġ��Ų��. ���� memcpy�� ���� buffer write, read�� �����Ѵ�. ���� write�� �����ߴٸ� dirty bit�� ���־�� �Ѵ�. buffer write, read �� ������, pin�� ���ش�.


## C. database, B+tree APIs

* database APIs

DB�� Ű�� ���� API�� init_db�� shutdown_db�� �����Ͽ���. init_db�� ������ ������ �ΰ��� �ڷᱸ���� �ʱ�ȭ �ϴ� api�̴�. ��, init_db�� init_bufmgr�� init_table_directory�� ȣ���Ѵ�. shutdown_db�� ��� ���۸� delete�ϴ� �Լ��̴�. �ٽ��� buf�� �ö�� �ִ� dirty page�� ��� update���ִ� ���̴�. ���� tranxaction�� recovery �ڵ带 © �� �ٽ� �ڼ��� ���캸�ƾ� �� �� ����.

* B*tree APIs

project 2���� b+tree file management �ڵ带 �����Ͽ���. �̶� insert, delete, find API�� �����Ͽ��µ�, project 3���� �� API�� logic�� �����ϰ� ������ table_id�� table_directory�� �߰��� �Ǿ���. 


## D. ���Ŀ� �ذ��ؾ��� �κ�

1. close_table: Ư�� table_id�� ���� buf�� pin�� ������� shutdown dbó�� delete�ؾ����� �ƴϸ� pin�� �ִٸ� table�� ���ݰ� �����ؾ� ����. ����� ������ ���� �ڵ尡 ¥���ִ�.

2. find_buf: search time�� ���� ��¥ ������ �����غ���.
