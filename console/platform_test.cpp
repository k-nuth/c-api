// // Copyright (c) 2016-2024 Knuth Project developers.
// // Distributed under the MIT software license, see the accompanying
// // file COPYING or http://www.opensource.org/licenses/mit-license.php.


// // Copyright (c) 2016-2024 Knuth Project developers.
// // Distributed under the MIT software license, see the accompanying
// // file COPYING or http://www.opensource.org/licenses/mit-license.php.

// #include <cstdio>

// #include <algorithm>
// #include <chrono>
// #include <stdexcept>
// #include <thread>

// #include <kth/capi.h>
// #include <kth/infrastructure.hpp>

// #include <kth/capi/config/settings.h>
// #include <kth/capi/helpers.hpp>
// #include <kth/capi/platform.h>

// int main(int argc, char* argv[]) {

//     kth_bool_t ok;
//     char* error_message = nullptr;
//     // auto settings = kth_config_settings_get_from_file("/home/fernando/dev/kth/cs-api/console/node.cfg", &ok, &error_message);
//     // auto settings = kth_config_settings_get_from_file("/home/fernando/dev/kth/cs-api/console/node_error.cfg", &ok, &error_message);
//     auto settings = kth_config_settings_get_from_file("/home/fernando/dev/kth/cs-api/console/asdasdasds.cfg", &ok, &error_message);

//     if ( ! ok) {
//         printf("%s\n", error_message);
//     }


//     // auto array = kth_platform_allocate_array_of_strings(3);

//     // // kth_platform_allocate_string_at(&array[0], 6);
//     // // strcpy(array[0], "hello");

//     // // kth_platform_allocate_string_at(&array[1], 6);
//     // // strcpy(array[1], "world");

//     // // kth_platform_allocate_string_at(&array[2], 6);
//     // // strcpy(array[2], "knuth");


//     // auto hello = kth_platform_allocate_and_copy_string_at(array, 0, "hello");
//     // auto world = kth_platform_allocate_and_copy_string_at(array, 1, "world");
//     // auto knuth = kth_platform_allocate_and_copy_string_at(array, 2, "knuth");

//     // printf("%s\n", hello);
//     // printf("%s\n", world);
//     // printf("%s\n", knuth);

//     // printf("%s\n", array[0]);
//     // printf("%s\n", array[1]);
//     // printf("%s\n", array[2]);


//     return 0;
// }
