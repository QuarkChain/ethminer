/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_GETWORK_H_
#define JSONRPC_CPP_STUB_GETWORK_H_

#include <jsonrpccpp/client.h>
#include <mutex>



class JsonrpcGetwork
{
public:
	std::mutex getWork_submitWork_mutex;
    JsonrpcGetwork(jsonrpc::IClientConnector* conn) { this->client = new jsonrpc::Client(*conn); }

    Json::Value eth_getWork(const std::string& shard, const std::string& coinbase_adr)
    {
    	std::lock_guard<std::mutex> guard(getWork_submitWork_mutex);
        Json::Value p;
        p.append(shard);
        p.append(coinbase_adr);
        Json::Value result = this->client->CallMethod("getWork", p);
        if (result.isArray())
            return result;
        else
            throw jsonrpc::JsonRpcException(
                jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
    }
    bool eth_submitWork( const std::string& param1,
        const std::string& param2, const std::string& param3, const std::string& param4)
    {
    	std::lock_guard<std::mutex> guard(getWork_submitWork_mutex);
        Json::Value p;
        p.append(param1);
        p.append(param2);
        p.append(param3);
        p.append(param4);
        Json::Value result = this->client->CallMethod("submitWork", p);
        if (result.isBool())
            return result.asBool();
        else
            throw jsonrpc::JsonRpcException(
                jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
    }
    /*
    bool eth_submitHashrate(const std::string& param1, const std::string& param2)
    {
        Json::Value p;
        p.append(param1);
        p.append(param2);
        Json::Value result = this->client->CallMethod("eth_submitHashrate", p);
        if (result.isBool())
            return result.asBool();
        else
            throw jsonrpc::JsonRpcException(
                jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
    }
    */

private:
    jsonrpc::Client* client;
};

#endif  // JSONRPC_CPP_STUB_GETWORK_H_
