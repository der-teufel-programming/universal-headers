// $FreeBSD: releng/12.3/lib/libomp/omp.h 356460 2020-01-07 18:08:09Z dim $
/*
 * include/omp.h.var
 */


//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//


#ifndef __OMP_H
#   define __OMP_H

#   include <stdlib.h>
#   include <stdint.h>

#   define KMP_VERSION_MAJOR    5
#   define KMP_VERSION_MINOR    0
#   define KMP_VERSION_BUILD    20140926
#   define KMP_BUILD_DATE       "No_Timestamp"

#   ifdef __cplusplus
    extern "C" {
#   endif

#   define omp_set_affinity_format   ompc_set_affinity_format
#   define omp_get_affinity_format   ompc_get_affinity_format
#   define omp_display_affinity      ompc_display_affinity
#   define omp_capture_affinity      ompc_capture_affinity

#   if defined(_WIN32)
#       define __KAI_KMPC_CONVENTION __cdecl
#       ifndef __KMP_IMP
#           define __KMP_IMP __declspec(dllimport)
#       endif
#   else
#       define __KAI_KMPC_CONVENTION
#       ifndef __KMP_IMP
#           define __KMP_IMP
#       endif
#   endif

    /* schedule kind constants */
    typedef enum omp_sched_t {
        omp_sched_static  = 1,
        omp_sched_dynamic = 2,
        omp_sched_guided  = 3,
        omp_sched_auto    = 4,
        omp_sched_monotonic = 0x80000000
    } omp_sched_t;

    /* set API functions */
    extern void   __KAI_KMPC_CONVENTION  omp_set_num_threads (int);
    extern void   __KAI_KMPC_CONVENTION  omp_set_dynamic     (int);
    extern void   __KAI_KMPC_CONVENTION  omp_set_nested      (int);
    extern void   __KAI_KMPC_CONVENTION  omp_set_max_active_levels (int);
    extern void   __KAI_KMPC_CONVENTION  omp_set_schedule          (omp_sched_t, int);

    /* query API functions */
    extern int    __KAI_KMPC_CONVENTION  omp_get_num_threads  (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_dynamic      (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_nested       (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_max_threads  (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_thread_num   (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_num_procs    (void);
    extern int    __KAI_KMPC_CONVENTION  omp_in_parallel      (void);
    extern int    __KAI_KMPC_CONVENTION  omp_in_final         (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_active_level        (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_level               (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_ancestor_thread_num (int);
    extern int    __KAI_KMPC_CONVENTION  omp_get_team_size           (int);
    extern int    __KAI_KMPC_CONVENTION  omp_get_thread_limit        (void);
    extern int    __KAI_KMPC_CONVENTION  omp_get_max_active_levels   (void);
    extern void   __KAI_KMPC_CONVENTION  omp_get_schedule            (omp_sched_t *, int *);
    extern int    __KAI_KMPC_CONVENTION  omp_get_max_task_priority   (void);

    /* lock API functions */
    typedef struct omp_lock_t {
        void * _lk;
    } omp_lock_t;

    extern void   __KAI_KMPC_CONVENTION  omp_init_lock    (omp_lock_t *);
    extern void   __KAI_KMPC_CONVENTION  omp_set_lock     (omp_lock_t *);
    extern void   __KAI_KMPC_CONVENTION  omp_unset_lock   (omp_lock_t *);
    extern void   __KAI_KMPC_CONVENTION  omp_destroy_lock (omp_lock_t *);
    extern int    __KAI_KMPC_CONVENTION  omp_test_lock    (omp_lock_t *);

    /* nested lock API functions */
    typedef struct omp_nest_lock_t {
        void * _lk;
    } omp_nest_lock_t;

    extern void   __KAI_KMPC_CONVENTION  omp_init_nest_lock    (omp_nest_lock_t *);
    extern void   __KAI_KMPC_CONVENTION  omp_set_nest_lock     (omp_nest_lock_t *);
    extern void   __KAI_KMPC_CONVENTION  omp_unset_nest_lock   (omp_nest_lock_t *);
    extern void   __KAI_KMPC_CONVENTION  omp_destroy_nest_lock (omp_nest_lock_t *);
    extern int    __KAI_KMPC_CONVENTION  omp_test_nest_lock    (omp_nest_lock_t *);

    /* OpenMP 5.0  Synchronization hints*/
    typedef enum omp_sync_hint_t {
        omp_sync_hint_none           = 0,
        omp_lock_hint_none           = omp_sync_hint_none,
        omp_sync_hint_uncontended    = 1,
        omp_lock_hint_uncontended    = omp_sync_hint_uncontended,
        omp_sync_hint_contended      = (1<<1),
        omp_lock_hint_contended      = omp_sync_hint_contended,
        omp_sync_hint_nonspeculative = (1<<2),
        omp_lock_hint_nonspeculative = omp_sync_hint_nonspeculative,
        omp_sync_hint_speculative    = (1<<3),
        omp_lock_hint_speculative    = omp_sync_hint_speculative,
        kmp_lock_hint_hle            = (1<<16),
        kmp_lock_hint_rtm            = (1<<17),
        kmp_lock_hint_adaptive       = (1<<18)
    } omp_sync_hint_t;

    /* lock hint type for dynamic user lock */
    typedef omp_sync_hint_t omp_lock_hint_t;

    /* hinted lock initializers */
    extern void __KAI_KMPC_CONVENTION omp_init_lock_with_hint(omp_lock_t *, omp_lock_hint_t);
    extern void __KAI_KMPC_CONVENTION omp_init_nest_lock_with_hint(omp_nest_lock_t *, omp_lock_hint_t);

    /* time API functions */
    extern double __KAI_KMPC_CONVENTION  omp_get_wtime (void);
    extern double __KAI_KMPC_CONVENTION  omp_get_wtick (void);

    /* OpenMP 4.0 */
    extern int  __KAI_KMPC_CONVENTION  omp_get_default_device (void);
    extern void __KAI_KMPC_CONVENTION  omp_set_default_device (int);
    extern int  __KAI_KMPC_CONVENTION  omp_is_initial_device (void);
    extern int  __KAI_KMPC_CONVENTION  omp_get_num_devices (void);
    extern int  __KAI_KMPC_CONVENTION  omp_get_num_teams (void);
    extern int  __KAI_KMPC_CONVENTION  omp_get_team_num (void);
    extern int  __KAI_KMPC_CONVENTION  omp_get_cancellation (void);

    /* OpenMP 4.5 */
    extern int   __KAI_KMPC_CONVENTION  omp_get_initial_device (void);
    extern void* __KAI_KMPC_CONVENTION  omp_target_alloc(size_t, int);
    extern void  __KAI_KMPC_CONVENTION  omp_target_free(void *, int);
    extern int   __KAI_KMPC_CONVENTION  omp_target_is_present(void *, int);
    extern int   __KAI_KMPC_CONVENTION  omp_target_memcpy(void *, void *, size_t, size_t, size_t, int, int);
    extern int   __KAI_KMPC_CONVENTION  omp_target_memcpy_rect(void *, void *, size_t, int, const size_t *,
                                            const size_t *, const size_t *, const size_t *, const size_t *, int, int);
    extern int   __KAI_KMPC_CONVENTION  omp_target_associate_ptr(void *, void *, size_t, size_t, int);
    extern int   __KAI_KMPC_CONVENTION  omp_target_disassociate_ptr(void *, int);

    /* OpenMP 5.0 */
    extern int   __KAI_KMPC_CONVENTION  omp_get_device_num (void);
    typedef void * omp_depend_t;

    /* kmp API functions */
    extern int    __KAI_KMPC_CONVENTION  kmp_get_stacksize          (void);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_stacksize          (int);
    extern size_t __KAI_KMPC_CONVENTION  kmp_get_stacksize_s        (void);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_stacksize_s        (size_t);
    extern int    __KAI_KMPC_CONVENTION  kmp_get_blocktime          (void);
    extern int    __KAI_KMPC_CONVENTION  kmp_get_library            (void);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_blocktime          (int);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_library            (int);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_library_serial     (void);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_library_turnaround (void);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_library_throughput (void);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_defaults           (char const *);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_disp_num_buffers   (int);

    /* Intel affinity API */
    typedef void * kmp_affinity_mask_t;

    extern int    __KAI_KMPC_CONVENTION  kmp_set_affinity             (kmp_affinity_mask_t *);
    extern int    __KAI_KMPC_CONVENTION  kmp_get_affinity             (kmp_affinity_mask_t *);
    extern int    __KAI_KMPC_CONVENTION  kmp_get_affinity_max_proc    (void);
    extern void   __KAI_KMPC_CONVENTION  kmp_create_affinity_mask     (kmp_affinity_mask_t *);
    extern void   __KAI_KMPC_CONVENTION  kmp_destroy_affinity_mask    (kmp_affinity_mask_t *);
    extern int    __KAI_KMPC_CONVENTION  kmp_set_affinity_mask_proc   (int, kmp_affinity_mask_t *);
    extern int    __KAI_KMPC_CONVENTION  kmp_unset_affinity_mask_proc (int, kmp_affinity_mask_t *);
    extern int    __KAI_KMPC_CONVENTION  kmp_get_affinity_mask_proc   (int, kmp_affinity_mask_t *);

    /* OpenMP 4.0 affinity API */
    typedef enum omp_proc_bind_t {
        omp_proc_bind_false = 0,
        omp_proc_bind_true = 1,
        omp_proc_bind_master = 2,
        omp_proc_bind_close = 3,
        omp_proc_bind_spread = 4
    } omp_proc_bind_t;

    extern omp_proc_bind_t __KAI_KMPC_CONVENTION omp_get_proc_bind (void);

    /* OpenMP 4.5 affinity API */
    extern int  __KAI_KMPC_CONVENTION omp_get_num_places (void);
    extern int  __KAI_KMPC_CONVENTION omp_get_place_num_procs (int);
    extern void __KAI_KMPC_CONVENTION omp_get_place_proc_ids (int, int *);
    extern int  __KAI_KMPC_CONVENTION omp_get_place_num (void);
    extern int  __KAI_KMPC_CONVENTION omp_get_partition_num_places (void);
    extern void __KAI_KMPC_CONVENTION omp_get_partition_place_nums (int *);

    extern void * __KAI_KMPC_CONVENTION  kmp_malloc  (size_t);
    extern void * __KAI_KMPC_CONVENTION  kmp_aligned_malloc  (size_t, size_t);
    extern void * __KAI_KMPC_CONVENTION  kmp_calloc  (size_t, size_t);
    extern void * __KAI_KMPC_CONVENTION  kmp_realloc (void *, size_t);
    extern void   __KAI_KMPC_CONVENTION  kmp_free    (void *);

    extern void   __KAI_KMPC_CONVENTION  kmp_set_warnings_on(void);
    extern void   __KAI_KMPC_CONVENTION  kmp_set_warnings_off(void);

    /* OpenMP 5.0 Tool Control */
    typedef enum omp_control_tool_result_t {
        omp_control_tool_notool = -2,
        omp_control_tool_nocallback = -1,
        omp_control_tool_success = 0,
        omp_control_tool_ignored = 1
    } omp_control_tool_result_t;

    typedef enum omp_control_tool_t {
        omp_control_tool_start = 1,
        omp_control_tool_pause = 2,
        omp_control_tool_flush = 3,
        omp_control_tool_end = 4
    } omp_control_tool_t;

    extern int __KAI_KMPC_CONVENTION omp_control_tool(int, int, void*);

    /* OpenMP 5.0 Memory Management */
    typedef uintptr_t omp_uintptr_t;

    typedef enum {
        OMP_ATK_THREADMODEL = 1,
        OMP_ATK_ALIGNMENT = 2,
        OMP_ATK_ACCESS = 3,
        OMP_ATK_POOL_SIZE = 4,
        OMP_ATK_FALLBACK = 5,
        OMP_ATK_FB_DATA = 6,
        OMP_ATK_PINNED = 7,
        OMP_ATK_PARTITION = 8
    } omp_alloctrait_key_t;

    typedef enum {
        OMP_ATV_FALSE = 0,
        OMP_ATV_TRUE = 1,
        OMP_ATV_DEFAULT = 2,
        OMP_ATV_CONTENDED = 3,
        OMP_ATV_UNCONTENDED = 4,
        OMP_ATV_SEQUENTIAL = 5,
        OMP_ATV_PRIVATE = 6,
        OMP_ATV_ALL = 7,
        OMP_ATV_THREAD = 8,
        OMP_ATV_PTEAM = 9,
        OMP_ATV_CGROUP = 10,
        OMP_ATV_DEFAULT_MEM_FB = 11,
        OMP_ATV_NULL_FB = 12,
        OMP_ATV_ABORT_FB = 13,
        OMP_ATV_ALLOCATOR_FB = 14,
        OMP_ATV_ENVIRONMENT = 15,
        OMP_ATV_NEAREST = 16,
        OMP_ATV_BLOCKED = 17,
        OMP_ATV_INTERLEAVED = 18
    } omp_alloctrait_value_t;

    typedef struct {
        omp_alloctrait_key_t key;
        omp_uintptr_t value;
    } omp_alloctrait_t;

#   if defined(_WIN32)
    // On Windows cl and icl do not support 64-bit enum, let's use integer then.
    typedef omp_uintptr_t omp_allocator_handle_t;
    extern __KMP_IMP omp_allocator_handle_t const omp_null_allocator;
    extern __KMP_IMP omp_allocator_handle_t const omp_default_mem_alloc;
    extern __KMP_IMP omp_allocator_handle_t const omp_large_cap_mem_alloc;
    extern __KMP_IMP omp_allocator_handle_t const omp_const_mem_alloc;
    extern __KMP_IMP omp_allocator_handle_t const omp_high_bw_mem_alloc;
    extern __KMP_IMP omp_allocator_handle_t const omp_low_lat_mem_alloc;
    extern __KMP_IMP omp_allocator_handle_t const omp_cgroup_mem_alloc;
    extern __KMP_IMP omp_allocator_handle_t const omp_pteam_mem_alloc;
    extern __KMP_IMP omp_allocator_handle_t const omp_thread_mem_alloc;
    typedef omp_uintptr_t omp_memspace_handle_t;
    extern __KMP_IMP omp_memspace_handle_t const omp_default_mem_space;
    extern __KMP_IMP omp_memspace_handle_t const omp_large_cap_mem_space;
    extern __KMP_IMP omp_memspace_handle_t const omp_const_mem_space;
    extern __KMP_IMP omp_memspace_handle_t const omp_high_bw_mem_space;
    extern __KMP_IMP omp_memspace_handle_t const omp_low_lat_mem_space;
#   else
#       if __cplusplus >= 201103
    typedef enum omp_allocator_handle_t : omp_uintptr_t
#       else
    typedef enum omp_allocator_handle_t
#       endif
    {
      omp_null_allocator = 0,
      omp_default_mem_alloc = 1,
      omp_large_cap_mem_alloc = 2,
      omp_const_mem_alloc = 3,
      omp_high_bw_mem_alloc = 4,
      omp_low_lat_mem_alloc = 5,
      omp_cgroup_mem_alloc = 6,
      omp_pteam_mem_alloc = 7,
      omp_thread_mem_alloc = 8,
      KMP_ALLOCATOR_MAX_HANDLE = UINTPTR_MAX
    } omp_allocator_handle_t;
#       if __cplusplus >= 201103
    typedef enum omp_memspace_handle_t : omp_uintptr_t
#       else
    typedef enum omp_memspace_handle_t
#       endif
    {
      omp_default_mem_space = 0,
      omp_large_cap_mem_space = 1,
      omp_const_mem_space = 2,
      omp_high_bw_mem_space = 3,
      omp_low_lat_mem_space = 4,
      KMP_MEMSPACE_MAX_HANDLE = UINTPTR_MAX
    } omp_memspace_handle_t;
#   endif
    extern omp_allocator_handle_t __KAI_KMPC_CONVENTION omp_init_allocator(omp_memspace_handle_t m,
                                                       int ntraits, omp_alloctrait_t traits[]);
    extern void __KAI_KMPC_CONVENTION omp_destroy_allocator(omp_allocator_handle_t allocator);

    extern void __KAI_KMPC_CONVENTION omp_set_default_allocator(omp_allocator_handle_t a);
    extern omp_allocator_handle_t __KAI_KMPC_CONVENTION omp_get_default_allocator(void);
#   ifdef __cplusplus
    extern void *__KAI_KMPC_CONVENTION omp_alloc(size_t size, omp_allocator_handle_t a = omp_null_allocator);
    extern void __KAI_KMPC_CONVENTION omp_free(void * ptr, omp_allocator_handle_t a = omp_null_allocator);
#   else
    extern void *__KAI_KMPC_CONVENTION omp_alloc(size_t size, omp_allocator_handle_t a);
    extern void __KAI_KMPC_CONVENTION omp_free(void *ptr, omp_allocator_handle_t a);
#   endif

    /* OpenMP 5.0 Affinity Format */
    extern void __KAI_KMPC_CONVENTION omp_set_affinity_format(char const *);
    extern size_t __KAI_KMPC_CONVENTION omp_get_affinity_format(char *, size_t);
    extern void __KAI_KMPC_CONVENTION omp_display_affinity(char const *);
    extern size_t __KAI_KMPC_CONVENTION omp_capture_affinity(char *, size_t, char const *);

    /* OpenMP 5.0 events */
#   if defined(_WIN32)
    // On Windows cl and icl do not support 64-bit enum, let's use integer then.
    typedef omp_uintptr_t omp_event_handle_t;
#   else
    typedef enum omp_event_handle_t { KMP_EVENT_MAX_HANDLE = UINTPTR_MAX } omp_event_handle_t;
#   endif
    extern void __KAI_KMPC_CONVENTION omp_fulfill_event ( omp_event_handle_t event );

    /* OpenMP 5.0 Pause Resources */
    typedef enum omp_pause_resource_t {
      omp_pause_resume = 0,
      omp_pause_soft = 1,
      omp_pause_hard = 2
    } omp_pause_resource_t;
    extern int __KAI_KMPC_CONVENTION omp_pause_resource(omp_pause_resource_t, int);
    extern int __KAI_KMPC_CONVENTION omp_pause_resource_all(omp_pause_resource_t);

    extern int __KAI_KMPC_CONVENTION omp_get_supported_active_levels(void);

#   undef __KAI_KMPC_CONVENTION
#   undef __KMP_IMP

    /* Warning:
       The following typedefs are not standard, deprecated and will be removed in a future release.
    */
    typedef int     omp_int_t;
    typedef double  omp_wtime_t;

#   ifdef __cplusplus
    }
#   endif

#endif /* __OMP_H */
