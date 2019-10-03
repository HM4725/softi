#ifndef __JOIN_H__
#define __JOIN_H__

#include "table.h"
#include <vector>
#include <queue>

using namespace std;

struct JoinColumn {
	int table_id;
	int col_num;
};

// Used for join query parse
struct JoinTargetTable {
	int table_id;
	vector<int>* col_nums;
	uint64_t size;
};

struct JoinOperator {
	JoinColumn* left;
	JoinColumn* right;
};

// Used for join processing

struct JoinRelation {
	vector<JoinColumn> column;
	vector<vector<int64_t> > records;
};

// Join
class Join {
	friend class SingleJoinProc;
private:
	bool is_valid;
	char query[FILENAME_MAX_LENGTH + 1];
	vector<JoinOperator*> opers;
	vector<JoinTargetTable*> targets;
	int** graph;
	vector<JoinColumn*> columns;
	queue<JoinOperator*> sequence;

	int first_table_id;
//	vector<SingleJoinProc*> join_opers;
/* 1. parse */
	// opers
	void make_operators();
	void destroy_operators();
	void check_operators();
	void set_operators();
	JoinOperator* find_operator(int tid1, int tid2);
	void erase_operator(JoinOperator* oper);
	
	// targets
	JoinTargetTable* find_target(int table_id);
	bool col_exists(JoinTargetTable* table, int col_num);
	void add_target();
	void sort_targets();
	void set_targets();
	void destroy_targets();
	int get_idx_on_targets(int table_id);
	int get_tid_on_targets(int idx);

	// graph
	void make_graph();
	void draw_graph();
	void check_graph();
	void erase_edge(JoinOperator* oper);
	void destroy_graph();
	void set_graph();
	
	// parse
	void parse();

/* 2. schedule */

	JoinColumn* find_column(int table_id, int col_num);
	void enqueue_operator(JoinOperator* oper);
	int select_first_left_table();
	JoinOperator* select_first_right_table(int ltid);
	JoinOperator* select_first_operator();
	JoinOperator* select_operator();
	void destroy_columns();

	// schedule
	void schedule();

/* 3. analysis result */
	int64_t analysis_join_result(JoinRelation* result);

public:
	Join(const char* query);
	~Join();
	int64_t run();
};

class SingleJoinProc {
private:
	Join* join;
	JoinOperator* oper;
	//vector<int> left_table_ids;
	JoinRelation* left;
	JoinRelation* right;
	//SingleJoinProc* next;

	JoinRelation* single_join();
	JoinRelation* load_relation(JoinTargetTable* table);
	void load_left_relation();
	void set_oper_direction();
	void load_right_relation();
	void link_prev(SingleJoinProc* prev);

public:
	SingleJoinProc(Join* join, JoinOperator* oper, JoinRelation* left);
	~SingleJoinProc();
	JoinRelation* run();
};

static bool compare_targets(JoinTargetTable* table1, JoinTargetTable* table2);
static bool compare_columns(JoinColumn* col1, JoinColumn* col2);

#endif /* JOIN_H */
