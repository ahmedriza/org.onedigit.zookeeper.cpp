#pragma once
#include <string>
#include <zookeeper.h>

class Connection
{
public:
    Connection();
    ~Connection();

    void connect();
    void create(const std::string& line);
    void remove(const std::string& line);
    void getChildren(const std::string& line);

private:
    static void watcher(zhandle_t *zzh, int type, int state, const char *path, void* context);
    static void my_string_completion(int rc, const char *name, const void *data);
    static void my_strings_completion(int rc, const struct String_vector *strings, const void *data);
    static void my_void_completion(int rc, const void *data);

    static const char *clientIdFile_;
    static clientid_t myid_;
    static zhandle_t *zh_;
};
