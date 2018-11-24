from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib import parse
import json, os, time

class DB:

    def __init__(self):
        self.__add_user_list = ["tg_id", "osu_id", "username", "join_date", "country"]
        self.__add_stats_list = ["osu_id", "update_time", "count300", "count100", "count50", "playcount", "ranked_score", "total_score", "pp_rank", "level", "pp_raw", "accuracy", "count_rank_ss", "count_rank_ssh", "count_rank_s", "count_rank_sh", "count_rank_a", "total_seconds_played", "pp_country_rank"]
    def get_data(self, method, arguments):
        print(method, arguments)
        open('callback.out', 'w').close()

        db_file = open("requests.in", "w")

        db_file.write(method + ' ')
        if method == "add_user":
            for arg in self.__add_user_list:
                db_file.write(arguments[arg] + ' ')
        elif method == "add_stats":
            for arg in self.__add_stats_list:
                db_file.write(arguments[arg] + ' ')
        elif method in ["get_stats", "get_info", "watchlist", "lastest_stats"]:
            db_file.write(arguments["tg_id"])
        db_file.close()

        result = []
        response = {"ok" : True}
        i = 0
        while os.stat("callback.out").st_size == 0 and i < 2:
            time.sleep(0.25)
            i += 0.25
        if(i >= 2):
            response["ok"] = False
            response["error"] = "Wrong method: " + method
        with open("callback.out", "r") as callback:
            for line in callback:
                print(line)
                print(type(line))
                if(line != ""):
                    json_line = json.loads(line.replace("'", "\""))
                    if("ok" in json_line):
                        if(not json_line["ok"]):
                            if(response["ok"]):
                                response["ok"] = False
                                response["error"] = []
                            response["error"].append(json_line["error"])
                    else:
                        result.append(json_line)
        if(response["ok"]):
            response["result"] = result
        return response

db = DB()
class S(BaseHTTPRequestHandler):
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        self._set_headers()
        self.wfile.write(b"123")

    def do_HEAD(self):
        self._set_headers()
        
    def do_POST(self):
        # Doesn't do anything with posted data
        self._set_headers()
        post_str_data = b'?' + self.rfile.read(int(self.headers['Content-Length']))
        post_data = dict(parse.parse_qsl(parse.urlsplit(post_str_data.decode("utf-8")).query))
        self.wfile.write(json.dumps(db.get_data(self.path[1:], post_data)).encode("utf-8"))
        
def run(server_class=HTTPServer, handler_class=S, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print ('Starting httpd...')
    httpd.serve_forever()


open('callback.out', 'w').close()
run()