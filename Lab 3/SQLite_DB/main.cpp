#define _CRT_SECURE_NO_WARNINGS
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;



static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	printf("{\n");
	for (i = 0; i<argc; i++)
	{
		printf("'%s': '%s'%s\n", azColName[i], argv[i] ? argv[i] : "NULL", i != argc - 1 ? "," : "");
	}
	printf("}\n");
	return 0;
}

void check_request(string request_type, int rc, char* zErrMsg)
{
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		cout << request_type << ": OK\n";
	}
}

void exececute_sql(sqlite3* db, char* sql_code)
{
	const char* data = "Callback function called";
	char *zErrMsg = 0;
	int rc = sqlite3_exec(db, sql_code, callback, (void*)data, &zErrMsg);
	check_request("request", rc, zErrMsg);
}

void create_all_tables(sqlite3* db)
{
	char* sql = "CREATE TABLE tg_osu_id("  \
		"tg_id INT NOT NULL," \
		"osu_id INT NOT NULL," \
		"PRIMARY KEY(tg_id, osu_id));";
	exececute_sql(db, sql);

	sql = "CREATE TABLE osu_users("  \
		"osu_id INT PRIMARY KEY NOT NULL," \
		"username VARCHAR(255) NOT NULL," \
		"join_date DATETIME NOT NULL,"\
		"country VARCHAR(255) NOT NULL);";
	exececute_sql(db, sql);

	sql = "CREATE TABLE osu_stats("  \
		"osu_id INT NOT NULL," \
		"update_time DATETIME NOT NULL,"\
		"count300 VARCHAR(255) NOT NULL,"\
		"count100 VARCHAR(255) NOT NULL,"\
		"count50 VARCHAR(255) NOT NULL,"\
		"playcount VARCHAR(255) NOT NULL,"\
		"ranked_score VARCHAR(255) NOT NULL,"\
		"total_score VARCHAR(255) NOT NULL,"\
		"pp_rank VARCHAR(255) NOT NULL,"\
		"level VARCHAR(255) NOT NULL,"\
		"pp_raw VARCHAR(255) NOT NULL,"\
		"accuracy VARCHAR(255) NOT NULL,"\
		"count_rank_ss VARCHAR(255) NOT NULL,"\
		"count_rank_ssh VARCHAR(255) NOT NULL,"\
		"count_rank_s VARCHAR(255) NOT NULL,"\
		"count_rank_sh VARCHAR(255) NOT NULL,"\
		"count_rank_a VARCHAR(255) NOT NULL,"\
		"total_seconds_played VARCHAR(255) NOT NULL,"\
		"pp_country_rank VARCHAR(255) NOT NULL,"\
		"PRIMARY KEY(osu_id, update_time));";
	exececute_sql(db, sql);

	sql = "CREATE TABLE watchlist("  \
		"user_osu_id INT NOT NULL," \
		"watched_player_id INT NOT NULL,"\
		"PRIMARY KEY(user_osu_id, watched_player_id));";
	exececute_sql(db, sql);
}

void add_user(sqlite3* db, char* tg_id, char* osu_id)
{
	char sql[255];
	sprintf(sql, "INSERT INTO tg_osu_id(tg_id, osu_id) VALUES(%s, %s);", tg_id, osu_id);
	exececute_sql(db, sql);

}

void add_user_info(sqlite3* db, char* osu_id, char* username, char* join_date, char* country)
{
	char sql[255];
	sprintf(sql, "INSERT INTO osu_users(osu_id, username, join_date, country) VALUES(%s, %s, %s, %s);", osu_id, username, join_date, country);
	exececute_sql(db, sql);
}

void add_user_stats(
	sqlite3* db,
	char* osu_id,
	char* update_time,
	char* count300,
	char* count100,
	char* count50,
	char* playcount,
	char* ranked_score,
	char* total_score,
	char* pp_rank,
	char* level,
	char* pp_raw,
	char* accuracy,
	char* count_rank_ss,
	char* count_rank_ssh,
	char* count_rank_s,
	char* count_rank_sh,
	char* count_rank_a,
	char* total_seconds_played,
	char* pp_country_rank)
{
	char sql[10000];
	sprintf(sql, "INSERT INTO osu_stats(osu_id, update_time, count300, count100, count50, playcount, ranked_score, total_score, pp_rank, level, pp_raw, accuracy, count_rank_ss, count_rank_ssh, count_rank_s, count_rank_sh, count_rank_a, total_seconds_played, pp_country_rank) " \
	"VALUES(%s, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",  osu_id, update_time, count300, count100, count50, playcount, ranked_score, total_score, pp_rank, level, pp_raw, accuracy, count_rank_ss, count_rank_ssh, count_rank_s, count_rank_sh, count_rank_a, total_seconds_played, pp_country_rank);
	printf(sql);
	exececute_sql(db, sql);	
}


void select_all_users(sqlite3* db)
{
	char* sql = "SELECT * FROM 'tg_osu_id';";
	exececute_sql(db, sql);
}

void select_all_info(sqlite3* db)
{
	char* sql = "SELECT * FROM 'osu_users';";
	exececute_sql(db, sql);
}

void select_all_stats(sqlite3* db)
{
	char* sql = "SELECT * FROM 'osu_stats';";
	exececute_sql(db, sql);
}

void get_user_info(sqlite3* db, char* tg_id)
{
	char sql[10000];
	sprintf(sql, "SELECT osu_users.* FROM osu_users INNER JOIN tg_osu_id ON (tg_osu_id.osu_id = osu_users.osu_id AND tg_id = %s);", tg_id);
	exececute_sql(db, sql);
}


int main()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("test.db", &db);

	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}
	create_all_tables(db);


	add_user(db, "12345", "54321");
	add_user_info(db, "54321", "'hjkj'", "'2015-07-29 19:05:11'", "'UA'");
	//add_user(db, "2334", "524321");
	//add_user(db, "12122345", "543241");
	//add_user(db, "123345", "545321");
	add_user_stats(db, "54321", "2015-07-29 19:05:11", "100", "100", "100", "100", "100", "100", "100", "100", "100", "100%", "100", "100", "100", "100", "100", "100", "100");
	select_all_users(db);
	select_all_info(db);
	get_user_info(db, "12345");
	get_user_info(db, "12355");
	select_all_stats(db);

	sqlite3_close(db);
	system("pause");
}