#include <stdio.h>

#include <kth/capi/config/settings.h>
// #include <kth/capi/primitives.h>

int main() {

    kth_settings config = kth_config_settings_default(kth_network_mainnet);

    auto node = kth_node_construct(&config, stdout, stderr);

    kth_node_destruct(node);
    return 0;
}

