#ifndef NET_CONFIG_MANAGER_H
#define NET_CONFIG_MANAGER_H

#ifndef NETWORK_DISABLED
#include "yaml-cpp/yaml.h"
#endif

/*

  Network preferences file reader/writer

*/

class NetConfigManager {
public:
    NetConfigManager() {}
    virtual ~NetConfigManager() {}

    void load();
    void save();

private:
#ifndef NETWORK_DISABLED
    bool load_file(YAML::Node&);
    void read_playername(YAML::Node&);
    void read_servers(YAML::Node&);
#endif
};

#endif // NET_CONFIG_MANAGER_H
