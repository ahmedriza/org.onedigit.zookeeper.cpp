#include <iostream>

#include "Connection.h"
#include "Util.h"

const char *Connection::clientIdFile_ = 0;
clientid_t Connection::myid_;
zhandle_t *Connection::zh_;

Connection::Connection()
{
}

Connection::~Connection()
{
}

void Connection::watcher(zhandle_t *zzh, int type, int state, const char *path, void* context)
{
    // Be careful using zh here rather than zzh - as this may be mt code
    // the client lib may call the watcher before zookeeper_init returns 

    fprintf(stderr, "Watcher %s state = %s", Util::type2String(type), Util::state2String(state));
    if (path && strlen(path) > 0) {
        fprintf(stderr, " for path %s", path);
    }
    fprintf(stderr, "\n");

    if (type == ZOO_SESSION_EVENT) {
        if (state == ZOO_CONNECTED_STATE) {
            const clientid_t *id = zoo_client_id(zzh);
            if (myid_.client_id == 0 || myid_.client_id != id->client_id) {
                myid_ = *id;
                fprintf(stderr, "Got a new session id: 0x%llx\n", (long long)myid_.client_id);
                if (clientIdFile_) {
                    FILE *fh = fopen(clientIdFile_, "w");
                    if (!fh) {
                        perror(clientIdFile_);
                    } else {
                        int rc = fwrite(&myid_, sizeof(myid_), 1, fh);
                        if (rc != sizeof(myid_)) {
                            perror("writing client id");
                        }
                        fclose(fh);
                    }
                }
            }
        } else if (state == ZOO_AUTH_FAILED_STATE) {
            fprintf(stderr, "Authentication failure. Shutting down...\n");
            zookeeper_close(zzh);
            zh_ = 0;
        } else if (state == ZOO_EXPIRED_SESSION_STATE) {
            fprintf(stderr, "Session expired. Shutting down...\n");
            zookeeper_close(zzh);
            zh_ = 0;
        }
    }
}

void Connection::my_string_completion(int rc, const char *name, const void *data) {
    fprintf(stderr, "[%s]: rc = %s\n", (char*)(data==0?"null":data), Util::errorString(rc));
    if (!rc) {
        fprintf(stderr, "\tname = %s\n", name);
    }
}

void Connection::my_strings_completion(int rc, const struct String_vector *strings,
        const void *data) 
{
    int i;
    if (strings) {
        for (i=0; i < strings->count; i++) {
            fprintf(stderr, "\t%s\n", strings->data[i]);
        }
    }
    free((void*)data);
}

void Connection::my_void_completion(int rc, const void *data) 
{
    fprintf(stderr, "%s: rc = %s\n", (char*)data, Util::errorString(rc));
    free((void*)data);
}

void Connection::connect()
{
    std::string hostPortList = "c0155.daiwaeurope.local:2181,dvdevln2.daiwa.global:2181,dvdevln4.daiwa.global:2181";
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    zoo_deterministic_conn_order(1);
    zh_ = zookeeper_init(hostPortList.c_str(), &Connection::watcher, 30000, &myid_, 0, 0); 
    if (zh_) {
        std::cout << "zookeeper client connected" << std::endl;
    } else {
        throw std::exception("Could not connect with zookeeper");
    }
}

void Connection::create(const std::string& line)
{
    int flags = 0;
    char* data = strdup(line.c_str());
    int rc = zoo_acreate(zh_, data, "new", 3, &ZOO_OPEN_ACL_UNSAFE, flags,
        my_string_completion, data);
    if (rc) {
        fprintf(stderr, "create: error %s for %s\n", Util::errorString(rc), data);
    }
}

void Connection::remove(const std::string& line)
{
    char* data = strdup(line.c_str());
    int rc = zoo_adelete(zh_, data, -1, my_void_completion, data);
    // rc = zoo_delete(zh, line, -1);
    if (rc) {
        fprintf(stderr, "remove: error %s for %s\n", Util::errorString(rc), line);
    }
}

void Connection::getChildren(const std::string& line)
{
    std::cout << "path = " << line << std::endl;
    int rc = zoo_aget_children(zh_, line.c_str(), 1, my_strings_completion, strdup(line.c_str()));
    if (rc) {
        fprintf(stderr, "getChildren: error %s for %s\n", Util::errorString(rc), line);
    }
}
