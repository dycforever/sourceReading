
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>

static void
ngx_destroy_cycle_pools(ngx_conf_t *conf)
{
    ngx_destroy_pool(conf->temp_pool);
    ngx_destroy_pool(conf->pool);
}

void* parse_conf () {
    ngx_cycle_t      *cycle, init_cycle;
    ngx_conf_t           conf;
    ngx_pool_t          *pool;
    ngx_log_t           *log;
    ngx_core_module_t   *module;
    void                *rv;
    int i;
    char* conf_file = "nginx.conf";

    // dyc: init ngx_sys_errlist for log
    if (ngx_strerror_init() != NGX_OK) {
        return NULL;
    }

    ngx_time_init();
    log = ngx_log_init(".");
    if (log == NULL) {
        return NULL;
    }

    ngx_memzero(&init_cycle, sizeof(ngx_cycle_t));
    init_cycle.log = log;
    ngx_cycle = &init_cycle;

    init_cycle.pool = ngx_create_pool(1024, log);
    if (init_cycle.pool == NULL) {
        return NULL;
    }

    pool = ngx_create_pool(NGX_CYCLE_POOL_SIZE, log);
    if (pool == NULL) {
        return NULL;
    }
    pool->log = log;

    cycle = ngx_pcalloc(pool, sizeof(ngx_cycle_t));
    if (cycle == NULL) {
        ngx_destroy_pool(pool);
        return NULL;
    }
    cycle->pool = pool;
    cycle->log = log;
    cycle->new_log.log_level = NGX_LOG_ERR;
    cycle->old_cycle = &init_cycle;

    ngx_memzero(&conf, sizeof(ngx_conf_t));
    conf.args = ngx_array_create(pool, 10, sizeof(ngx_str_t));
    if (conf.args == NULL) {
        ngx_destroy_pool(pool);
        return NULL;
    }

    conf.temp_pool = ngx_create_pool(NGX_CYCLE_POOL_SIZE, log);
    if (conf.temp_pool == NULL) {
        ngx_destroy_pool(pool);
        return NULL;
    }

    cycle->conf_ctx = ngx_pcalloc(pool, ngx_max_module * sizeof(void *));
    if (cycle->conf_ctx == NULL) {
        ngx_destroy_pool(pool);
        return NULL;
    }

    for (i = 0; ngx_modules[i]; i++) {
        if (ngx_modules[i]->type != NGX_CORE_MODULE) {
            continue;
        }

        module = ngx_modules[i]->ctx;

        if (module->create_conf) {
            rv = module->create_conf(cycle);
            if (rv == NULL) {
                ngx_destroy_pool(pool);
                return NULL;
            }
            cycle->conf_ctx[ngx_modules[i]->index] = rv;
        }
    }

    conf.ctx = cycle->conf_ctx;
    conf.cycle = cycle;
    conf.pool = pool;
    conf.log = log;
    conf.module_type = NGX_CORE_MODULE;
    conf.cmd_type = NGX_MAIN_CONF;

    if (ngx_conf_param(&conf) != NGX_CONF_OK) {
        ngx_destroy_cycle_pools(&conf);
        return NULL;
    }
    printf("after ngx_conf_param()\n");

    cycle->conf_file.data = conf_file;
    cycle->conf_file.len = sizeof(conf_file);
    if (ngx_conf_parse(&conf, &cycle->conf_file) != NGX_CONF_OK) {
        ngx_destroy_cycle_pools(&conf);
        return NULL;
    }

    return NULL;
}

int main() {
    parse_conf();
    return 0;
}

