#define _CRT_SECURE_NO_WARNINGS
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;
string response("");

bool empty(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {

	response += "{";
	for (int i = 0; i<argc; i++)
	{
		char str[10000];
		sprintf(str, "'%s': '%s'%s ", azColName[i], argv[i] ? argv[i] : "NULL", i != argc - 1 ? "," : "");
		response += str;
	}
	response += "}\n";
	return 0;
}

void check_request(string request_type, int rc, char* zErrMsg)
{
	if (rc != SQLITE_OK)
	{
		response += "{'ok': false, 'error': '" + string(zErrMsg) + "'}\n";
		sqlite3_free(zErrMsg);
	}
	else
	{
		response += "{'ok': true}\n";
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
		"PRIMARY KEY(tg_id));";
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

void add_user(sqlite3* db, const char* tg_id, const char* osu_id)
{
	char sql[255];
	sprintf(sql, "INSERT INTO tg_osu_id(tg_id, osu_id) VALUES(%s, %s);", tg_id, osu_id);
	exececute_sql(db, sql);

}

void add_user_info(sqlite3* db, const char* osu_id, const char* username, const char* join_date, const char* country)
{
	char sql[255];
	sprintf(sql, "INSERT INTO osu_users(osu_id, 'username', 'join_date', 'country') VALUES(%s, '%s', '%s', '%s');", osu_id, username, join_date, country);
	exececute_sql(db, sql);
}

void add_user_stats(
	sqlite3* db,
	const char* osu_id,
	const char* update_time,
	const char* count300,
	const char* count100,
	const char* count50,
	const char* playcount,
	const char* ranked_score,
	const char* total_score,
	const char* pp_rank,
	const char* level,
	const char* pp_raw,
	const char* accuracy,
	const char* count_rank_ss,
	const char* count_rank_ssh,
	const char* count_rank_s,
	const char* count_rank_sh,
	const char* count_rank_a,
	const char* total_seconds_played,
	const char* pp_country_rank)
{
	char sql[10000];
	sprintf(sql, "INSERT INTO osu_stats(osu_id, update_time, count300, count100, count50, playcount, ranked_score, total_score, pp_rank, level, pp_raw, accuracy, count_rank_ss, count_rank_ssh, count_rank_s, count_rank_sh, count_rank_a, total_seconds_played, pp_country_rank) " \
	"VALUES(%s, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');",  osu_id, update_time, count300, count100, count50, playcount, ranked_score, total_score, pp_rank, level, pp_raw, accuracy, count_rank_ss, count_rank_ssh, count_rank_s, count_rank_sh, count_rank_a, total_seconds_played, pp_country_rank);
	exececute_sql(db, sql);	
}

void add_to_watchlist(sqlite3* db, char* user_id, char* watched_player_id)
{
	char sql[255];
	sprintf(sql, "INSERT INTO watchlist(user_osu_id, watched_player_id) VALUES(%s, %s);", user_id, watched_player_id);
	exececute_sql(db, sql);
}


void select_all_users(sqlite3* db)
{
	char* sql = "SELECT tg_osu_id.tg_id, osu_users.* FROM osu_users INNER JOIN tg_osu_id ON (tg_osu_id.osu_id = osu_users.osu_id);";
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

void get_user_info(sqlite3* db, const char* tg_id)
{
	char sql[10000];
	sprintf(sql, "SELECT tg_osu_id.tg_id, osu_users.* FROM osu_users INNER JOIN tg_osu_id ON (tg_osu_id.osu_id = osu_users.osu_id AND tg_id = %s);", tg_id);
	exececute_sql(db, sql);
}

void get_user_stats(sqlite3* db, const char* tg_id)
{
	char sql[10000];
	sprintf(sql, "SELECT osu_stats.* FROM osu_stats INNER JOIN tg_osu_id ON (tg_osu_id.osu_id = osu_stats.osu_id AND tg_id = %s);", tg_id);
	exececute_sql(db, sql);
}

void get_watched_list(sqlite3* db, const char* tg_id)
{
	char sql[10000];
	sprintf(sql, "SELECT watched_player_id FROM watchlist WHERE (user_osu_id = (SELECT osu_id FROM tg_osu_id WHERE tg_id = %s) );", tg_id);
	exececute_sql(db, sql);
}

void get_lastest_stats(sqlite3* db, const char* tg_id)
{
	char sql[10000];
	sprintf(sql, "SELECT osu_stats.* FROM osu_stats INNER JOIN tg_osu_id ON (tg_osu_id.osu_id = osu_stats.osu_id ) WHERE (tg_osu_id.tg_id = %s and osu_stats.update_time = (SELECT MAX(update_time) from osu_stats));", tg_id);
	exececute_sql(db, sql);
}

void execute_func(sqlite3* db, ifstream &ifstr)
{
	string type;
	ifstr >> type;
	if (type == "add_user")
	{
		string tg_id, osu_id, username, join_date, join_time, country;
		ifstr >> tg_id >> osu_id >> username >> join_date >> join_time >> country;
		join_date += " " + join_time;
		add_user(db, tg_id.c_str(), osu_id.c_str());
		add_user_info(db, osu_id.c_str(), username.c_str(), join_date.c_str(), country.c_str());
	}
	else if (type == "add_stats")
	{
		string osu_id,
			update_date,
			update_time,
			count300,
			count100,
			count50,
			playcount,
			ranked_score,
			total_score,
			pp_rank,
			level,
			pp_raw,
			accuracy,
			count_rank_ss,
			count_rank_ssh,
			count_rank_s,
			count_rank_sh,
			count_rank_a,
			total_seconds_played,
			pp_country_rank;
			ifstr >> osu_id >> update_date >> update_time >> count300 >> count100 >> count50 >> playcount >> ranked_score >> total_score >> pp_rank >> level >> pp_raw >> accuracy >> count_rank_ss >> count_rank_ssh >> count_rank_s >> count_rank_sh >> count_rank_a >> total_seconds_played >> pp_country_rank;
			update_time = update_date + ' ' + update_time;
			add_user_stats(db, osu_id.c_str(), update_time.c_str(), count300.c_str(), count100.c_str(), count50.c_str(), playcount.c_str(), ranked_score.c_str(), total_score.c_str(), pp_rank.c_str(), level.c_str(), pp_raw.c_str(), accuracy.c_str(), count_rank_ss.c_str(), count_rank_ssh.c_str(), count_rank_s.c_str(), count_rank_sh.c_str(), count_rank_a.c_str(), total_seconds_played.c_str(), pp_country_rank.c_str());
	}
	else if(type == "get_stats")
	{
		string tg_id;
		ifstr >> tg_id;
		get_user_stats(db, tg_id.c_str());
	}
	else if(type == "get_info")
	{
		string tg_id = "";
		ifstr >> tg_id;
		get_user_info(db, tg_id.c_str());
	}
	else if(type == "watchlist")
	{
		string tg_id;
		ifstr >> tg_id;
		get_watched_list(db, tg_id.c_str());
	}
	else if (type == "get_users")
	{
		select_all_users(db);
	}
	else if (type == "lastest_stats")
	{
		string tg_id;
		ifstr >> tg_id;
		get_lastest_stats(db, tg_id.c_str());
	}

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
	//trying to make missing tables
	create_all_tables(db);
	//get_user_stats(db, "12345");
	//add_user_info(db, "1", "1", "2015-12-31 14:48:12", "US");

	//system("python http_server.py");
	cout << response << endl;
	response = "";
	while (true)
	{
		ifstream ifstr("requests.in");

		if (!empty(ifstr))
		{
			execute_func(db, ifstr);

			ofstream callback("callback.out");
			callback << response;
			cout << response << endl;
			response = "";
			ofstream ofstr("requests.in");
			ofstr.close();
		}

		ifstr.close();
	}

	sqlite3_close(db);
	system("pause");
}