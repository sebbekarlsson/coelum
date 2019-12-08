#ifndef COELUM_CONFIG_H
#define COELUM_CONFIG_H

#define CONFIG_FILENAME "config.json"

typedef struct CONFIG_STRUCT
{
    unsigned int window_resizable;
} config_T;

config_T* init_config();

void config_free(config_T* config);

void load_config_from_file_if_exists(config_T* config);
#endif
