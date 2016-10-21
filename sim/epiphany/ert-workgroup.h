#ifndef __ERT_WORKGROUP_H__
#define __ERT_WORKGROUP_H__

#include <stdint.h>

/* Chip types */
#define E_E16G301 0
#define E_E64G401 1
/* Not in 'upstream' e-lib yet */
#define E_E1KG501 2

/* Object types */
#define E_EPI_GROUP 3

/* structs */
typedef struct {
  uint32_t  objtype;    /* 0x28 */
  uint32_t  chiptype;   /* 0x2c */
  uint32_t  group_id;   /* 0x30 */
  uint32_t  group_row;  /* 0x34 */
  uint32_t  group_col;  /* 0x38 */
  uint32_t  group_rows; /* 0x3c */
  uint32_t  group_cols; /* 0x40 */
  uint32_t  core_row;   /* 0x44 */
  uint32_t  core_col;   /* 0x48 */
  uint32_t  __pad;      /* 0x4c */
} __attribute__((packed)) e_group_config_t;

#endif
