#include "join.h"
#include "panic.h"
#include <cmath>
#include <algorithm>
#include <string.h>

void Join::make_operators() {
	JoinOperator* oper = NULL;
	JoinColumn* left = NULL;
	JoinColumn* right = NULL;
	char* token = NULL;
	int ltid;
	int lcol;
	int rtid;
	int rcol;

	token = strtok(query, "&");
	while(token != NULL) {
		sscanf(token, "%d.%d=%d.%d", &ltid, &lcol, &rtid, &rcol);
		left = (JoinColumn*)malloc(sizeof(JoinColumn));
		if(left == NULL) {
			PANIC("failed to allocate left JoinColumn");
		}
		left->table_id = ltid;
		left->col_num = lcol;
		right = (JoinColumn*)malloc(sizeof(JoinColumn));
		if(right == NULL) {
			PANIC("failed to allocate right JoinColumn");
		}
		right->table_id = rtid;
		right->col_num = rcol;
		oper = (JoinOperator*)malloc(sizeof(JoinOperator));
		if(oper == NULL) {
			PANIC("failed to allocate JoinOpertor");
		}
		oper->left = left;
		oper->right = right;

		opers.push_back(oper);

		token = strtok(NULL, "&");
	}
}

void Join::destroy_operators() {
	vector<JoinOperator*>::iterator itr;

	for(itr = opers.begin() ; itr != opers.end() ;) {
		free((*itr)->left);
		free((*itr)->right);
		free(*itr);
		itr = opers.erase(itr);
	}
}

void Join::check_operators() {
	JoinColumn* col;
	vector<JoinOperator*>::iterator itr;
	Table* table;

	try {
		if(opers.size() == 0 || opers.size() > 10) {
			throw false;
		}

		for(itr = opers.begin() ; itr != opers.end() ; itr++) {

			col = (*itr)->left;
			table = &td.tables[col->table_id];
			if(col->table_id < 1 || col->table_id > 10) {
				throw false;
			}
			if(col->col_num < 1 || col->col_num > 16) {
				throw false;
			}
			if(table->fd == NOTOPEN) {
				throw false;
			}
			if(col->col_num > table->header->num_columns) {
				throw false;
			}

			col = (*itr)->right;
			table = &td.tables[col->table_id];
			if(col->table_id < 1 || col->table_id > 10) {
				throw false;
			}
			if(col->col_num < 1 || col->col_num > 16) {
				throw false;
			}
			if(td.tables[col->table_id].fd == NOTOPEN) {
				throw false;
			}
			if(col->col_num > table->header->num_columns) {
				throw false;
			}
		}

		is_valid = true;

	} catch(bool e) {
		destroy_operators();
		is_valid = false;
	}
}

void Join::set_operators() {
	make_operators();
	check_operators();
}

JoinOperator* Join::find_operator(int tid1, int tid2) {
	vector<JoinOperator*>::iterator itr;
	for(itr = opers.begin() ; itr != opers.end() ; itr++) {
		if((*itr)->left->table_id == tid1 && (*itr)->right->table_id == tid2) {
			return *itr;
		}
		if((*itr)->left->table_id == tid2 && (*itr)->right->table_id == tid1) {
			return *itr;
		}
	}
	return NULL;
}

void Join::erase_operator(JoinOperator* oper) {
	vector<JoinOperator*>::iterator itr;
	for(itr = opers.begin() ; itr != opers.end() ; itr++) {
		if(oper == *itr) {
			// fields will be deallocated in other function
			opers.erase(itr);
			return;
		}
	}
}

JoinTargetTable* Join::find_target(int table_id) {
	vector<JoinTargetTable*>::iterator itr;
	for(itr = targets.begin() ; itr != targets.end() ; itr++) {
		if((*itr)->table_id == table_id) {
			return *itr;
		}
	}
	return NULL;
}

bool Join::col_exists(JoinTargetTable* table, int col_num) {
	vector<int>::iterator itr;
	for(itr = table->col_nums->begin() ; itr != table->col_nums->end() ; itr++) {
		if((*itr) == col_num) {
			return true;
		}
	}
	return false;
}

void Join::add_target() {
	vector<JoinOperator*>::iterator itr;
	JoinTargetTable* table = NULL;
	int col_num;

	for(itr = opers.begin() ; itr != opers.end() ; itr++) {

		table = find_target((*itr)->left->table_id);
		if(table == NULL) {
			table = (JoinTargetTable*)malloc(sizeof(JoinTargetTable));
			if(table == NULL) {
				PANIC("failed to allocate JoinTargetTable");
			}
			table->table_id = (*itr)->left->table_id;
			table->col_nums = new vector<int>();
			table->size = td.tables[table->table_id].num_records;
			targets.push_back(table);
		}
		col_num = (*itr)->left->col_num;
		if(!col_exists(table, col_num)) {
			table->col_nums->push_back(col_num);
		}

		table = find_target((*itr)->right->table_id);
		if(table == NULL) {
			table = (JoinTargetTable*)malloc(sizeof(JoinTargetTable));
			if(table == NULL) {
				PANIC("failed to allocate JoinTargetTable");
			}
			table->table_id = (*itr)->right->table_id;
			table->size = td.tables[table->table_id].num_records;
			table->col_nums = new vector<int>();
			targets.push_back(table);
		}
		col_num = (*itr)->right->col_num;
		if(!col_exists(table, col_num)) {
			table->col_nums->push_back(col_num);
		}
	}
}

void Join::sort_targets() {
	vector<JoinTargetTable*>::iterator itr;

	for(itr = targets.begin() ; itr != targets.end() ; itr++) {
		sort((*itr)->col_nums->begin(), (*itr)->col_nums->end());
	}

	sort(targets.begin(), targets.end(), compare_targets);
}

void Join::set_targets() {
	add_target();
	sort_targets();
}

void Join::destroy_targets() {
	vector<JoinTargetTable*>::iterator itr;
	for(itr = targets.begin() ; itr != targets.end() ; itr++) {
		delete (*itr)->col_nums;
		free(*itr);
	}
}

int Join::get_idx_on_targets(int table_id) {
	vector<JoinTargetTable*>::iterator itr;
	int idx = 0;

	for(itr = targets.begin() ; itr != targets.end() ; itr++) {
		if((*itr)->table_id == table_id) {
			break;
		}
		idx++;
	}
	if(idx == targets.size()) {
		PANIC("The target table is not on the graph");
	}

	return idx;
}

int Join::get_tid_on_targets(int idx) {
	vector<JoinTargetTable*>::iterator itr;
	int table_id;

	if(idx >= targets.size()) {
		PANIC("idx must be less than the number of targets");
	}

	itr = targets.begin();
	for(int i = 0 ; i < idx ; i++) {
		itr++;
	}
	return (*itr)->table_id;
}

void Join::make_graph() {
	int num_targets;

	num_targets = targets.size();
	graph = (int**)malloc(sizeof(int*) * num_targets);
	if(graph == NULL) {
		PANIC("failed to allocate join_graph");
	}
	for(int i = 0 ; i < num_targets ; i++) {
		graph[i] = (int*)malloc(sizeof(int) * num_targets);
		if(graph[i] == NULL) {
			PANIC("failed to allocate join_graph");
		}
		memset(graph[i], 0, sizeof(int) * num_targets);
	}
}

void Join::draw_graph() {
	int row;
	int col;
	int tmp;
	vector<JoinOperator*>::iterator itr;

	for(itr = opers.begin() ; itr != opers.end() ; itr++) {
		row = get_idx_on_targets((*itr)->left->table_id);
		col = get_idx_on_targets((*itr)->right->table_id);
		if(row < col) {
			// swap
			tmp = col;
			col = row;
			row = tmp;
		}
		graph[row][col]++;
	}
}

void Join::check_graph() {
	int num_targets;
	num_targets = targets.size();

	try {
		for(int i = 0 ; i < num_targets ; i++) {
			for(int j = 0 ; j <= i ; j++) {
				// no selft join
				if(i == j && graph[i][j] != 0) {
					throw false;
				}
				// TODO: check cycle: graph must be acyclic
				/* check cycle routine */
			}
		}
	} catch(bool e) {
		destroy_operators();
		destroy_targets();
		destroy_graph();
		is_valid = false;
	}
}

void Join::erase_edge(JoinOperator* oper) {
	int row;
	int col;
	int tmp;

	row = get_idx_on_targets(oper->left->table_id);
	col = get_idx_on_targets(oper->right->table_id);

	if(row < col) {
		// swap
		tmp = row;
		row = col;
		col = tmp;
	}

	graph[row][col]--;
}

void Join::destroy_graph() {
	int num_targets;

	num_targets = targets.size();

	for(int i = 0 ; i < num_targets ; i++) {
		free(graph[i]);
	}
	free(graph);
	graph = NULL;
}

void Join::set_graph() {
	make_graph();
	draw_graph();
	check_graph();
}


void Join::parse() {

	set_operators();
	if(is_valid == false) {
		return;
	}
	set_targets();
	set_graph();
	if(is_valid == false) {
		return;
	}
}

JoinColumn* Join::find_column(int table_id, int col_num) {
	vector<JoinColumn*>::iterator itr;
	for(itr = columns.begin() ; itr != columns.end() ; itr++) {
		if((*itr)->table_id == table_id && (*itr)->col_num == col_num) {
			return *itr;
		}
	}
	return NULL;
}

void Join::enqueue_operator(JoinOperator* oper) {
	int ltid;
	int lcol;
	int rtid;
	int rcol;
	JoinColumn* column = NULL;

	ltid = oper->left->table_id;
	lcol = oper->left->col_num;
	rtid = oper->right->table_id;
	rcol = oper->right->col_num;

	erase_operator(oper);
	erase_edge(oper);
	sequence.push(oper);

	if(find_column(ltid, lcol) == NULL) {
		column = (JoinColumn*)malloc(sizeof(JoinColumn));
		if(column == NULL) {
			PANIC("failed to allocate left join column in eneque_operator");
		}
		column->table_id = ltid;
		column->col_num = lcol;
		columns.push_back(column);
	}

	if(find_column(rtid, rcol) == NULL) {
		column = (JoinColumn*)malloc(sizeof(JoinColumn));
		if(column == NULL) {
			PANIC("failed to allocate left join column in eneque_operator");
		}
		column->table_id = rtid;
		column->col_num = rcol;
		columns.push_back(column);
	}
	sort(columns.begin(), columns.end(), compare_columns);
}

int Join::select_first_left_table() {
	JoinTargetTable* table = NULL;
	vector<JoinTargetTable*>::iterator itr;
	uint64_t min = 0xFFFFFFFFFFFFFFFF;

	for(itr = targets.begin() ; itr != targets.end() ; itr++) {
		if((*itr)->size < min) {
			table = *itr;
			min = (*itr)->size;
		}
	}
	first_table_id = table->table_id;
	return table->table_id;
}

JoinOperator* Join::select_first_right_table(int ltid) {
	JoinTargetTable* ptr = NULL;
	JoinTargetTable* table = NULL;
	int rtid;
	int idx, i, j;
	int num_targets = targets.size();
	uint64_t min = 0xFFFFFFFFFFFFFFFF;
	idx = get_idx_on_targets(ltid);
	i = idx;
	j = 0;

	while(i != num_targets) {

		if(graph[i][j] > 0) {
			rtid = get_tid_on_targets(j);
			if(rtid == ltid) {
				rtid = get_tid_on_targets(i);
			}
			ptr = find_target(rtid);

			if(ptr->size < min) {
				table = ptr;
				min = ptr->size;
			}
		}

		(j != idx) ? j++ : i++;
	}

	return find_operator(ltid, table->table_id);
}

JoinOperator* Join::select_first_operator() {
	return select_first_right_table(select_first_left_table());
}

JoinOperator* Join::select_operator() {
	vector<JoinColumn*>::iterator itr;
	JoinTargetTable* ptr = NULL;
	JoinTargetTable* table = NULL;
	int num_targets = targets.size();
	int tid = 0;
	int ltid = 0;
	int rtid;
	int idx, i, j;

	for(itr = columns.begin() ; itr != columns.end() ; itr++) {
		if(tid != (*itr)->table_id) {
			tid = (*itr)->table_id;
			idx = get_idx_on_targets(tid);
			i = idx;
			j = 0;
			
			while(i != num_targets) {

				if(graph[i][j] > 0) {
					rtid = get_tid_on_targets(j);
					if(rtid == tid) {
						rtid = get_tid_on_targets(i);
					}
					ptr = find_target(rtid);

					table = ptr;
					ltid = tid;
					break;
				}

				(j != idx) ? j++ : i++;
			}
		}
	}
	return find_operator(ltid, table->table_id);
}

void Join::destroy_columns() {
	vector<JoinColumn*>::iterator itr;
	for(itr = columns.begin() ; itr != columns.end() ; ) {
		free(*itr);
		itr = columns.erase(itr);
	}
}

void Join::schedule() {
	JoinOperator* oper;
	oper = select_first_operator();
	enqueue_operator(oper);
	while(!opers.empty()) {
		oper = select_operator();
		enqueue_operator(oper);
	}
}

Join::Join(const char* query) {
	is_valid = false;
	strcpy(this->query, query);
	graph = NULL;

	parse();
	schedule();
}

Join::~Join() {
	if(is_valid) {
		destroy_targets();
		destroy_graph();
		destroy_columns();
		// TODO: after join_thread, JoinOperators must be deallocated!
	}
}

int64_t Join::analysis_join_result(JoinRelation* result) {
	vector<int> idxs;
	int idx = 0;
	vector<int>::iterator iitr;
	vector<JoinColumn>::iterator citr;
	vector<vector<int64_t> >::iterator ritr;
	int64_t sum = 0;

	for(citr = result->column.begin() ; citr != result->column.end() ; citr++) {
		if(citr->col_num == 1) {
			idxs.push_back(idx);
		}
		idx++;
	}

	for(iitr = idxs.begin() ; iitr != idxs.end() ; iitr++) {
		for(ritr = result->records.begin() ; ritr != result->records.end() ; ritr++) {
			sum+=(*ritr)[*iitr];
		}
	}

	delete result;

	return sum;
}

int64_t Join::run() {
	JoinOperator* oper;
	SingleJoinProc* single;
	JoinRelation* result;
	int i = 0;

	if(is_valid == false) {
		return 0;
	}

	oper = sequence.front();
	sequence.pop();
	single = new SingleJoinProc(this, oper, NULL);
	result = single->run();
	delete single;
	while(!sequence.empty()) {
		oper = sequence.front();
		sequence.pop();
		single = new SingleJoinProc(this, oper, result);
		result = single->run();
		delete single;
	}

	return analysis_join_result(result);
}

bool compare_targets(JoinTargetTable* table1, JoinTargetTable* table2) {
	return table1->table_id < table2->table_id;
}

static bool compare_columns(JoinColumn* col1, JoinColumn* col2) {
	return (col1->table_id == col2->table_id) ?
		col1->col_num < col2->col_num :
		col1->table_id < col2->table_id;
}
