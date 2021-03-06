#ifndef LIBATAPP_BINDING_C_LIBATAPP_C_H_
#define LIBATAPP_BINDING_C_LIBATAPP_C_H_

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "config/compile_optimize.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *libatapp_c_context;

typedef const void *libatapp_c_message;

typedef void *libatapp_c_module;

enum LIBATAPP_C_ATBUS_PROTOCOL_CMD {
    LIBATAPP_C_ATBUS_CMD_INVALID = 0,

    //  数据协议
    LIBATAPP_C_ATBUS_CMD_DATA_TRANSFORM_REQ = 1,
    LIBATAPP_C_ATBUS_CMD_DATA_TRANSFORM_RSP,
    LIBATAPP_C_ATBUS_CMD_CUSTOM_CMD_REQ,

    // 节点控制协议
    LIBATAPP_C_ATBUS_CMD_NODE_SYNC_REQ = 9,
    LIBATAPP_C_ATBUS_CMD_NODE_SYNC_RSP,
    LIBATAPP_C_ATBUS_CMD_NODE_REG_REQ,
    LIBATAPP_C_ATBUS_CMD_NODE_REG_RSP,
    LIBATAPP_C_ATBUS_CMD_NODE_CONN_SYN,
    LIBATAPP_C_ATBUS_CMD_NODE_PING,
    LIBATAPP_C_ATBUS_CMD_NODE_PONG,

    LIBATAPP_C_ATBUS_CMD_MAX
};

// =========================== callbacks ===========================
typedef int32_t (*libatapp_c_on_msg_fn_t)(libatapp_c_context, libatapp_c_message, const void *msg_data, uint64_t msg_len, void *priv_data);
typedef int32_t (*libatapp_c_on_send_fail_fn_t)(libatapp_c_context, uint64_t src_pd, uint64_t dst_pd, libatapp_c_message, void *priv_data);
typedef int32_t (*libatapp_c_on_connected_fn_t)(libatapp_c_context, uint64_t pd, int32_t status, void *priv_data);
typedef int32_t (*libatapp_c_on_disconnected_fn_t)(libatapp_c_context, uint64_t pd, int32_t status, void *priv_data);
typedef int32_t (*libatapp_c_on_all_module_inited_fn_t)(libatapp_c_context, void *priv_data);
typedef int32_t (*libatapp_c_on_cmd_option_fn_t)(libatapp_c_context, const char *buffer[], uint64_t buffer_len[], uint64_t sz, void *priv_data);

UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_set_on_msg_fn(libatapp_c_context context, libatapp_c_on_msg_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_set_on_send_fail_fn(libatapp_c_context context, libatapp_c_on_send_fail_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_set_on_connected_fn(libatapp_c_context context, libatapp_c_on_connected_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_set_on_disconnected_fn(libatapp_c_context context, libatapp_c_on_disconnected_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_set_on_all_module_inited_fn(libatapp_c_context context, libatapp_c_on_all_module_inited_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_add_cmd(libatapp_c_context context, const char *cmd, libatapp_c_on_cmd_option_fn_t fn, const char *help_msg,
                                                   void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_add_option(libatapp_c_context context, const char *opt, libatapp_c_on_cmd_option_fn_t fn, const char *help_msg,
                                                      void *priv_data);


// =========================== create/destory ===========================
UTIL_SYMBOL_EXPORT libatapp_c_context __cdecl libatapp_c_create();
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_destroy(libatapp_c_context context);

// =========================== actions ===========================
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_run(libatapp_c_context context, int32_t argc, const char **argv, void *priv_data);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_reload(libatapp_c_context context);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_stop(libatapp_c_context context);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_tick(libatapp_c_context context);

// =========================== basic ===========================
UTIL_SYMBOL_EXPORT uint64_t __cdecl libatapp_c_get_id(libatapp_c_context context);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_get_app_version(libatapp_c_context context, const char **verbuf, uint64_t *bufsz);

// =========================== configures ===========================
UTIL_SYMBOL_EXPORT uint64_t __cdecl libatapp_c_get_configure_size(libatapp_c_context context, const char *path);
UTIL_SYMBOL_EXPORT uint64_t __cdecl libatapp_c_get_configure(libatapp_c_context context, const char *path, const char *out_buf[], uint64_t out_len[],
                                                             uint64_t arr_sz);

// =========================== flags ===========================
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_is_running(libatapp_c_context context);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_is_stoping(libatapp_c_context context);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_is_timeout(libatapp_c_context context);

// =========================== bus actions ===========================
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_listen(libatapp_c_context context, const char *address);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_connect(libatapp_c_context context, const char *address);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_disconnect(libatapp_c_context context, uint64_t app_id);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_send_data_msg(libatapp_c_context context, uint64_t app_id, int32_t type, const void *buffer, uint64_t sz,
                                                            int32_t require_rsp = 0);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_send_custom_msg(libatapp_c_context context, uint64_t app_id, const void *arr_buf[], uint64_t arr_size[],
                                                              uint64_t arr_count);

// =========================== message ===========================
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_msg_get_cmd(libatapp_c_message msg);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_msg_get_type(libatapp_c_message msg);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_msg_get_ret(libatapp_c_message msg);
UTIL_SYMBOL_EXPORT uint32_t __cdecl libatapp_c_msg_get_sequence(libatapp_c_message msg);
UTIL_SYMBOL_EXPORT uint64_t __cdecl libatapp_c_msg_get_src_bus_id(libatapp_c_message msg);
UTIL_SYMBOL_EXPORT uint64_t __cdecl libatapp_c_msg_get_forward_from(libatapp_c_message msg);
UTIL_SYMBOL_EXPORT uint64_t __cdecl libatapp_c_msg_get_forward_to(libatapp_c_message msg);

// =========================== module ===========================
UTIL_SYMBOL_EXPORT libatapp_c_module __cdecl libatapp_c_module_create(libatapp_c_context context, const char *mod_name);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_module_get_name(libatapp_c_module mod, const char **namebuf, uint64_t *bufsz);
UTIL_SYMBOL_EXPORT libatapp_c_context __cdecl libatapp_c_module_get_context(libatapp_c_module mod);
typedef int32_t (*libatapp_c_module_on_init_fn_t)(libatapp_c_module, void *priv_data);
typedef int32_t (*libatapp_c_module_on_reload_fn_t)(libatapp_c_module, void *priv_data);
typedef int32_t (*libatapp_c_module_on_stop_fn_t)(libatapp_c_module, void *priv_data);
typedef int32_t (*libatapp_c_module_on_timeout_fn_t)(libatapp_c_module, void *priv_data);
typedef int32_t (*libatapp_c_module_on_tick_fn_t)(libatapp_c_module, void *priv_data);

UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_module_set_on_init(libatapp_c_module mod, libatapp_c_module_on_init_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_module_set_on_reload(libatapp_c_module mod, libatapp_c_module_on_reload_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_module_set_on_stop(libatapp_c_module mod, libatapp_c_module_on_stop_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_module_set_on_timeout(libatapp_c_module mod, libatapp_c_module_on_timeout_fn_t fn, void *priv_data);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_module_set_on_tick(libatapp_c_module mod, libatapp_c_module_on_tick_fn_t fn, void *priv_data);

// =========================== utilities ===========================
UTIL_SYMBOL_EXPORT int64_t __cdecl libatapp_c_get_unix_timestamp();
/**
 * write log using atapp engine
 * @param tag tag, 0 for default
 * @param level log level
 * @param level_name log level name
 * @param file_path related file path
 * @param func_name related function name
 * @param line_number related line number
 * @param content log data
 */
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_log_write(uint32_t tag, uint32_t level, const char *level_name, const char *file_path, const char *func_name,
                                                     uint32_t line_number, const char *content);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_log_update();

UTIL_SYMBOL_EXPORT uint32_t __cdecl libatapp_c_log_get_level(uint32_t tag);
UTIL_SYMBOL_EXPORT int32_t __cdecl libatapp_c_log_check_level(uint32_t tag, uint32_t level);
UTIL_SYMBOL_EXPORT void __cdecl libatapp_c_log_set_project_directory(const char *project_dir, uint64_t dirsz);

#ifdef __cplusplus
}
#endif

#endif
