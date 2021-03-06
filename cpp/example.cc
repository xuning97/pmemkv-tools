#include <iostream>
#include "libpmemkv.h"

#define LOG(msg) std::cout << msg << "\n"

using namespace pmemkv;

int main() {
    LOG("Starting engine");
    KVEngine* kv = KVEngine::Start("vsmap", "{\"path\":\"/dev/shm/\"}");

    LOG("Putting new key");
    KVStatus s = kv->Put("key1", "value1");
    assert(s == OK && kv->Count() == 1);

    LOG("Reading key back");
    string value;
    s = kv->Get("key1", &value);
    assert(s == OK && value == "value1");

    LOG("Iterating existing keys");
    kv->Put("key2", "value2");
    kv->Put("key3", "value3");
    kv->All([](const string& k) {
        LOG("  visited: " << k);
    });

    LOG("Removing existing key");
    s = kv->Remove("key1");
    assert(s == OK && !kv->Exists("key1"));

    LOG("Stopping engine");
    delete kv;
    return 0;
}
