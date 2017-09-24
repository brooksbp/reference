#ifndef BASE_SYS_INFO_H
#define BASE_SYS_INFO_H

#ifdef __cplusplus
extern "C" {
#endif

int64 sys_info_amount_of_physical_memory(void);
int64 sys_info_amount_of_available_physical_memory(void);

#ifdef __cplusplus
}
#endif

#endif /* BASE_SYS_INFO_H */
