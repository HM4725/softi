# Project3 Buffer_management_layer

## A. Table

*  Data Structure
![table_structure](/uploads/a78b02166d48c6697c8177ec6ef56ad3/table_structure.PNG)

Table Directory는 Table을 관리하는 자료구조이다. 특정 Table이 open 되면, 그 Table file은 Table Directory의 table 배열 중 하나에 저장되고 그 index 값이 table_id가 된다. Table 배열 중 index가 0인 첫번째 원소는 table_id가 0이므로 사용되지 않는다. Table 구조체에는 file descriptor와 header page, 그리고 table의 이름이 저장된다.

*  init_table_directory
![table_init_table_directory](/uploads/70acbe02349b74ce18ea27cf2d95f2f9/table_init_table_directory.PNG)

db가 시작되면, Table Directory를 초기화해주어야 한다. init_table_directory가 초기화를 담당한다. table 배열의 크기는 capacity에 저장되고, open된 table의 수는 num_alloc_tables에 저장된다. init_table_directory가 호출된 직 후엔 num_alloc_tables는 0이고, capacity는 MAX_TID (10)이다.

*  open_table
![table_open_table](/uploads/f3459ca8e29eace7af07fe15afb5e705/table_open_table.PNG)

table을 open하는 함수이다. 먼저 1번 table_id 부터 TableDirectory의 table 배열 중 비어있는 위치를 찾는다. 빈 원소를 찾으면 특정 table file을 열고, table에 대한 정보를 저장한다.

*  close_table
![table_close_table](/uploads/2c069aa3621098e822901bb116029295/table_close_table.PNG)

table을 close하는 함수이다. buffer에 올라와 있는 특정 table에 대한 block을 모두 delete한다. 그 다음 Table Directory에서 이 table에 대한 정보를 지운다.

## B. Buffer Manager

*  Data Structure
![buffer_structure](/uploads/28c0074caf034ebc6c8e4cdb4f078778/buffer_structure.PNG)

각 Buffer block은 Buf 구조체로 나타내고 BufMgr 구조체가 buffer block을 관리한다. Buf 구조체는 linked list로 구현하였고, Least Recently Used (이하, LRU) Policy에 따라 num_pages == capacity일 때 주로 마지막 Buf가 delete된다. 먼저 delete될 첫번째 Buf는 마지막 Buf이고 접근속도를 빠르게 하기 위해 first_buf의 prev에 마지막 Buf의 주소를 저장하였다. 만약 마지막 Buf가 pin이 꽂힌 상태이면 prev Buf를 확인한다. 계속 prev 방향으로 진행하며 pin 여부를 확인하고 pin이 없는 경우 해당 Buf를 delete한다. 새로 추가되는 Buf는 first_buf로 추가되며, cache hit되는 Buf도 read 또는 write 후 first_buf로 옮겨진다. LRU policy를 바탕으로 한 file_write_page와 file_read_page의 logic은 다음과 같다.

*  Page read, write on the buffer

file_write_page와 file_read_page는 logic이 거의 비슷하며 case도 동일하게 나누어진다. 그렇기 때문에 write와 read를 동시에 설명한다. 

`cache hit`

첫번째 case는 cache hit 일 때이다. 여기서 cache hit이란, 버퍼에 해당 페이지가 이미 올라와 있는 상황에서 그 페이지를 read 또는 write하는 것을 뜻한다. 그림으로 보면 다음과 같다.

![buffer_cache_hit_1](/uploads/c46068ad21fcdb8cbafe8fa64b290937/buffer_cache_hit_1.PNG)

먼저 linked_list의 처음부터 해당 (table_id, pagenum)을 갖고 있는 buf를 찾는다. bufmgr의 num_pages가 n일 때, O(n)의 search time이 소요될 수 있다. 그래서 이 search time을 줄이고자 search time이 O(1)에 가까운 hash table을 이용해 보았다. 하지만 insert를 10만번 반복한 결과 단순 linked_list가 2배 이상 빨랐다. cache 특성상 hit되는 buf는 앞쪽에 주로 위치하기 때문에 linked_list에서 그렇게 큰 search time이 소요되지 않았고, hash table의 경우엔 insert Buf함과 동시에 hash insert도 해야하기 때문에 linked_list의 insert보다 더욱 많은 시간이 소요된 것으로 보인다.

![buffer_cache_hit_2](/uploads/becceec95d2e0e5e93e818b29aad34a6/buffer_cache_hit_2.PNG)

linked_list를 이용해 해당 buf를 찾은 후, buf에 pin을 꽂은 다음 memcpy를 통해 곧바로 dest 구조체에 page의 내용을 저장한다. write의 경우엔 src 구조체의 내용을 memcpy를 통해 buf에 저장하고 buf의 dirty bit을 켠다.

![buffer_cache_hit_3](/uploads/88b1c5a4af5e42ac72fc9ab924480206/buffer_cache_hit_3.PNG)

마지막으로 해당 buf를 linked_list의 맨 앞으로 옮겨주고 pin을 뺀다. 이전 과정에서 해당 buf와 정보가 교환되는 이웃 buf들도 pin을 꽂고 빼 주어야 한다.


`cache miss`

다음은 cache miss일 때이다. cache hit과 반대로 buffer에서 해당 페이지를 찾지 못했을 때를 뜻한다. 
cache miss일 땐, buffer가 꽉 찼다면 해당 페이지를 buffer에 올리기 위해 한 block을 delete해야 한다. 만약 buffer가 아직 다 찬 상태가 아니라면, 단순히 해당 페이지를 buffer에 올리면 된다.

![buffer_cache_miss_1](/uploads/dc341d209774f2523db01465cb9700db/buffer_cache_miss_1.PNG)

![buffer_cache_miss_2](/uploads/a15df5b5b40bb85228e69ae48a47454d/buffer_cache_miss_2.PNG)

![buffer_cache_miss_3](/uploads/c53169c680e01b4483d504570fabba27/buffer_cache_miss_3.PNG)

![buffer_cache_miss_4](/uploads/b35af9528b4d4d586caa1c23985c1792/buffer_cache_miss_4.PNG)

만약 buffer가 꽉 찬 상태라면, LRU policy에 따라 가장 오래 사용되지 않았기 때문에 first_buf로 부터 가장 멀리 있는 last buf를 delete해야 한다. 하지만 pin이 꽂혀있는 상황에선 delete할 수 없다. 그렇기 때문에 차선책으로 prev를 delete한다. 만약 prev도 pin이 꽂혀있다면, prev->prev를 확인한다. 만약 이 때의 prev가 pin이 없다면 이 해당 buf를 delete한다. 

![buffer_cache_miss_5](/uploads/ed51558063c500331d7ce3dc85062dd9/buffer_cache_miss_5.PNG)

![buffer_cache_miss_6](/uploads/1a7b740dcc8a65c084c7eca14b6aaebe/buffer_cache_miss_6.PNG)

![buffer_cache_miss_7](/uploads/f6ce8def42bea4c6ec61abe8483953b5/buffer_cache_miss_7.PNG)

다음으로 해당 page를 buffer에 올린 후 write 또는 read를 하는 단계이다. 만약 buffer가 꽉 차지 않았었더라면 이 단계만 수행하면 된다. 먼저 pin을 꽂은 상태로 해당 page를 linked_list의 가장 앞에 위치시킨다. 이후 memcpy를 통해 buffer write, read를 수행한다. 만약 write를 수행했다면 dirty bit을 켜주어야 한다. buffer write, read 가 끝나면, pin을 빼준다.


## C. database, B+tree APIs

* database APIs

DB를 키고 끄는 API인 init_db와 shutdown_db를 구현하였다. init_db는 위에서 설명한 두가지 자료구조를 초기화 하는 api이다. 즉, init_db는 init_bufmgr와 init_table_directory를 호출한다. shutdown_db는 모든 버퍼를 delete하는 함수이다. 핵심은 buf에 올라와 있는 dirty page를 모두 update해주는 것이다. 이후 tranxaction과 recovery 코드를 짤 때 다시 자세히 살펴보아야 할 것 같다.

* B*tree APIs

project 2에서 b+tree file management 코드를 구현하였다. 이때 insert, delete, find API를 구현하였는데, project 3에선 세 API의 logic은 동일하고 각각에 table_id와 table_directory가 추가만 되었다. 


## D. 차후에 해결해야할 부분

1. close_table: 특정 table_id를 갖는 buf를 pin에 상관없이 shutdown db처럼 delete해야할지 아니면 pin이 있다면 table을 못닫게 설정해야 할지. 현재는 후자의 경우로 코드가 짜여있다.

2. find_buf: search time이 적은 진짜 이유를 조사해보기.
