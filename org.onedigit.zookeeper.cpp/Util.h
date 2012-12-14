#ifndef UTIL_H
#define UTIL_H

#pragma warning(disable : 4996)

class Util
{
public:

    static const char* state2String(int state){
        if (state == 0)
            return "CLOSED_STATE";
        if (state == ZOO_CONNECTING_STATE)
            return "CONNECTING_STATE";
        if (state == ZOO_ASSOCIATING_STATE)
            return "ASSOCIATING_STATE";
        if (state == ZOO_CONNECTED_STATE)
            return "CONNECTED_STATE";
        if (state == ZOO_EXPIRED_SESSION_STATE)
            return "EXPIRED_SESSION_STATE";
        if (state == ZOO_AUTH_FAILED_STATE)
            return "AUTH_FAILED_STATE";

        return "INVALID_STATE";
    }

    static const char* type2String(int state){
        if (state == ZOO_CREATED_EVENT)
            return "CREATED_EVENT";
        if (state == ZOO_DELETED_EVENT)
            return "DELETED_EVENT";
        if (state == ZOO_CHANGED_EVENT)
            return "CHANGED_EVENT";
        if (state == ZOO_CHILD_EVENT)
            return "CHILD_EVENT";
        if (state == ZOO_SESSION_EVENT)
            return "SESSION_EVENT";
        if (state == ZOO_NOTWATCHING_EVENT)
            return "NOTWATCHING_EVENT";

        return "UNKNOWN_EVENT_TYPE";
    }

    static const char* errorString(int error)
    {
        const char* default = "UNKNOWN";

        if(error == ZOK) {
            return "OK";
        } else if (error == ZSYSTEMERROR) {
            return "ZSYSTEMERROR";
        } else if (error == ZRUNTIMEINCONSISTENCY) {
            return "ZRUNTIMEINCONSISTENCY";
        } else if (error == ZDATAINCONSISTENCY) {
            return "ZDATAINCONSISTENCY";
        } else if (error == ZCONNECTIONLOSS) {
            return "ZCONNECTIONLOSS";
        } else if (error == ZMARSHALLINGERROR) {
            return "ZMARSHALLINGERROR";
        } else if (error == ZUNIMPLEMENTED) {
            return "ZUNIMPLEMENTED";
        } else if (error == ZOPERATIONTIMEOUT) {
            return "ZOPERATIONTIMEOUT";
        } else if (error == ZBADARGUMENTS) {
            return "ZBADARGUMENTS";
        } else if (error == ZINVALIDSTATE) {
            return "ZINVALIDSTATE";
        } else if (error == ZAPIERROR) {
            return "ZAPIERROR";
        } else if (error == ZNONODE) {
            return "ZNONODE";
        } else if (error == ZNOAUTH) {
            return "ZNOAUTH";
        } else if (error == ZBADVERSION) {
            return "ZBADVERSION";
        } else if (error == ZNOCHILDRENFOREPHEMERALS) {
            return "ZNOCHILDRENFOREPHEMERALS";
        } else if (error == ZNODEEXISTS) {
            return "ZNODEEXISTS";
        } else if (error == ZNOTEMPTY) {
            return "ZNOTEMPTY";
        } else if (error == ZSESSIONEXPIRED) {
            return "ZSESSIONEXPIRED";
        } else if (error == ZINVALIDCALLBACK) {
            return "ZINVALIDCALLBACK";
        } else if (error == ZINVALIDACL) {
            return "ZINVALIDACL";
        } else if (error == ZAUTHFAILED) {
            return "ZAUTHFAILED";
        } else if (error == ZCLOSING) {
            return "ZCLOSING";
        } else if (error == ZNOTHING) {
            return "ZNOTHING";
        } else if (error == ZSESSIONMOVED) {
            return "ZSESSIONMOVED";
        }
        else {
            return default;
        }
    }
};

#endif /* UTIL_H */