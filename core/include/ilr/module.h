// TODO rename, describe the file

#ifndef ILR_MODULE_H
#define ILR_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

/// Module (unit of compilation)
typedef struct ilr_module_ ilr_module_t;

/// Initialize empty module
ilr_module_t * ilr_new_module(void);

/// Free module's memory
void ilr_free_module(ilr_module_t ** module);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ILR_MODULE_H
