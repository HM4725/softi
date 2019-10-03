#include "join.h"
#include <stdlib.h>
#include <unordered_map>

JoinRelation* SingleJoinProc::single_join() {
	int ltid;
	int lcol;
	int rtid;
	int rcol;
	int idx = 0;
	int lidx = 0;
	int ridx = 0;
	size_t i;
	vector<int64_t> tmp;
	vector<JoinColumn>::iterator lcitr;
	vector<JoinColumn>::iterator rcitr;
	JoinRelation* result;
	unordered_multimap<int64_t, size_t> hashmap;
	
	// 1. find position (index)
	ltid = oper->left->table_id;
	lcol = oper->left->col_num;
	rtid = oper->right->table_id;
	rcol = oper->right->col_num;
	for(lcitr = left->column.begin() ; lcitr != left->column.end() ; lcitr++) {
		if(lcitr->table_id == ltid && lcitr->col_num == lcol) {
			break;
		}
		lidx++;
	}

	for(rcitr = right->column.begin() ; rcitr != right->column.end() ; rcitr++) {
		if(rcitr->table_id == rtid && rcitr->col_num == rcol) {
			break;
		}
		ridx++;
	}
	// 2. set column
	result = new JoinRelation();
	for(lcitr = left->column.begin() ; lcitr != left->column.end() ; lcitr++) {
		result->column.push_back(*lcitr);
	}
	for(rcitr = right->column.begin() ; rcitr != right->column.end() ; rcitr++) {
		result->column.push_back(*rcitr);
	}

	for( ; lcitr != left->column.end() ; lcitr++) {
		result->column.push_back(*lcitr);
	}

	// 3. insert records
	for(i = 0 ; i < right->records.size() ; i++) {
		hashmap.insert(make_pair(right->records[i][ridx],i));
	}
	for(i = 0 ; i < left->records.size() ; i++) {
		auto range = hashmap.equal_range(left->records[i][lidx]);
		for(auto it = range.first; it != range.second ; ++it) {
			tmp.insert(tmp.end(), left->records[i].begin(), left->records[i].end());
			tmp.insert(tmp.end(), right->records[it->second].begin(), right->records[it->second].end());
			result->records.push_back(move(tmp));
		}
	}

	return result;
}

JoinRelation* SingleJoinProc::load_relation(JoinTargetTable* target) {
	vector<int>::iterator itr;
	int table_id;
	Table* table;
	JoinRelation* relation;
	JoinColumn tmp_col;
	vector<int64_t> tmp_rec;
	off_t root_offset;
	InternalPage* internal_node;
	LeafPage* leaf_node;
	NodePage page;
	int i;

	table_id = target->table_id;
	table = &td.tables[table_id];

	relation = new JoinRelation();

	// 1. relation->column
	tmp_col.table_id = table_id;
	tmp_col.col_num = 1;
	relation->column.push_back(tmp_col);
	for(itr = target->col_nums->begin() ; itr != target->col_nums->end(); itr++) {
		if(*itr != 1) {
			tmp_col.table_id = table_id;
			tmp_col.col_num = *itr;
			relation->column.push_back(tmp_col);
		}
	}
	// end if no record
	root_offset = table->header->root_offset;
	if(root_offset == 0) {
		return relation;
	}

	// 2. relation->records;
	file_read_page(table_id, FILEOFF_TO_PAGENUM(root_offset), (Page*)&page);
	while(!page.is_leaf) {
		internal_node = (InternalPage*)&page;
		file_read_page(table_id, FILEOFF_TO_PAGENUM(INTERNAL_OFFSET(internal_node, 0)), (Page*)&page);
	}
	leaf_node = (LeafPage*)&page;

	while(true) {
		for(i = 0 ; i < leaf_node->num_keys ; i++) {
			tmp_rec.push_back(LEAF_KEY(leaf_node, i));
			for(itr = target->col_nums->begin() ; itr != target->col_nums->end() ; itr++) {
				if(*itr != 1) {
					tmp_rec.push_back(LEAF_VALUE(leaf_node, i)[*itr - 2]);
				}
			}
			// TODO: emplace??
			relation->records.push_back(tmp_rec);
			tmp_rec.clear();
		}
		if(leaf_node->sibling == 0) {
			break;
		}
		file_read_page(table_id, FILEOFF_TO_PAGENUM(leaf_node->sibling), (Page*)&page);
	}
	return relation;
}

// If oper is first oper, call load_left_relation
void SingleJoinProc::load_left_relation() {
	JoinColumn* tmp;

	left = load_relation(join->find_target(join->first_table_id));

//	left_table_ids.push_back(join->first_table_id);
}

void SingleJoinProc::set_oper_direction() {
	int left_table_id;
//	vector<int>::iterator itr;
	vector<JoinColumn>::iterator itr;
	bool correct = false;
	JoinColumn* tmp;
/*
	left_table_id = oper->left->table_id;
	for(itr = left_table_ids.begin() ; itr != left_table_ids.end() ; itr++) {
		if(*itr == left_table_id) {
			correct = true;
		}
	}*/
	left_table_id = oper->left->table_id;
	for(itr = left->column.begin() ; itr != left->column.end() ; itr++) {
		if(itr->table_id == left_table_id) {
			correct = true;
		}
	}
	if(correct == false) {
		tmp = oper->left;
		oper->left = oper->right;
		oper->right = tmp;
	}
}

void SingleJoinProc::load_right_relation() {
	int table_id;
	JoinTargetTable* target;

	set_oper_direction();
	table_id = oper->right->table_id;
	right = load_relation(join->find_target(table_id));
}
/*
void SingleJoinProc::link_prev(SingleJoinProc* prev) {
	if(prev !=NULL) {
		prev->next = this;
	}
}*/

SingleJoinProc::SingleJoinProc(Join* join, JoinOperator* oper,/* SingleJoinProc* prev*/ JoinRelation* left) {
	this->join = join;
	this->oper = oper;
	/*
	if(prev != NULL) {
		link_prev(prev);
	}
	if(prev == NULL) {
		load_left_relation();
	}*/
	if(left == NULL) {
		load_left_relation();
	} else {
		this->left = left;
	}
	load_right_relation();
	//next = NULL;
}

SingleJoinProc::~SingleJoinProc() {
	free(oper->left);
	free(oper->right);
	free(oper);
	delete left;
	delete right;
}

JoinRelation* SingleJoinProc::run() {
	return single_join();
}
