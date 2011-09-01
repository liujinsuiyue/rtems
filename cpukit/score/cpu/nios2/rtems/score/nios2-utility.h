/*
 * Copyright (c) 2011 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 *
 * $Id$
 */

#ifndef _RTEMS_SCORE_NIOS2_UTILITY_H
#define _RTEMS_SCORE_NIOS2_UTILITY_H

#define NIOS2_CTLREG_INDEX_STATUS 0
#define NIOS2_CTLREG_INDEX_ESTATUS 1
#define NIOS2_CTLREG_INDEX_BSTATUS 2
#define NIOS2_CTLREG_INDEX_IENABLE 3
#define NIOS2_CTLREG_INDEX_IPENDING 4
#define NIOS2_CTLREG_INDEX_CPUID 5
#define NIOS2_CTLREG_INDEX_EXCEPTION 7
#define NIOS2_CTLREG_INDEX_PTEADDR 8
#define NIOS2_CTLREG_INDEX_TLBACC 9
#define NIOS2_CTLREG_INDEX_TLBMISC 10
#define NIOS2_CTLREG_INDEX_BADADDR 12
#define NIOS2_CTLREG_INDEX_CONFIG 13
#define NIOS2_CTLREG_INDEX_MPUBASE 14
#define NIOS2_CTLREG_INDEX_MPUACC 15

#define NIOS2_CONTEXT_OFFSET_R16 0
#define NIOS2_CONTEXT_OFFSET_R17 4
#define NIOS2_CONTEXT_OFFSET_R18 8
#define NIOS2_CONTEXT_OFFSET_R19 12
#define NIOS2_CONTEXT_OFFSET_R20 16
#define NIOS2_CONTEXT_OFFSET_R21 20
#define NIOS2_CONTEXT_OFFSET_R22 24
#define NIOS2_CONTEXT_OFFSET_R23 28
#define NIOS2_CONTEXT_OFFSET_FP 32
#define NIOS2_CONTEXT_OFFSET_STATUS 36
#define NIOS2_CONTEXT_OFFSET_SP 40
#define NIOS2_CONTEXT_OFFSET_RA 44
#define NIOS2_CONTEXT_OFFSET_TDD 48

#define NIOS2_ISR_STATUS_MASK_IIC 0xfffffffe
#define NIOS2_ISR_STATUS_BITS_IIC 0x00000000

#define NIOS2_ISR_STATUS_MASK_EIC_IL 0xfffffc0f
#define NIOS2_ISR_STATUS_BITS_EIC_IL 0x000003f0

#define NIOS2_ISR_STATUS_MASK_EIC_RSIE 0xf7ffffff
#define NIOS2_ISR_STATUS_BITS_EIC_RSIE 0x00000000

#define NIOS2_STATUS_RSIE (1 << 23)
#define NIOS2_STATUS_NMI (1 << 22)
#define NIOS2_STATUS_PRS_OFFSET 16
#define NIOS2_STATUS_PRS_MASK (0x3f << NIOS2_STATUS_PRS_OFFSET)
#define NIOS2_STATUS_CRS_OFFSET 10
#define NIOS2_STATUS_CRS_MASK (0x3f << NIOS2_STATUS_CRS_OFFSET)
#define NIOS2_STATUS_IL_OFFSET 4
#define NIOS2_STATUS_IL_MASK (0x3f << NIOS2_STATUS_IL_OFFSET)
#define NIOS2_STATUS_IH (1 << 3)
#define NIOS2_STATUS_EH (1 << 2)
#define NIOS2_STATUS_U (1 << 1)
#define NIOS2_STATUS_PIE (1 << 0)

#define NIOS2_EXCEPTION_CAUSE_OFFSET 2
#define NIOS2_EXCEPTION_CAUSE_MASK (0x1f << NIOS2_EXCEPTION_CAUSE_OFFSET)

#define NIOS2_PTEADDR_PTBASE_OFFSET 22
#define NIOS2_PTEADDR_PTBASE_MASK (0x3ff << NIOS2_PTEADDR_PTBASE_OFFSET)
#define NIOS2_PTEADDR_VPN_OFFSET 2
#define NIOS2_PTEADDR_VPN_MASK (0xfffff << NIOS2_PTEADDR_VPN_OFFSET)

#define NIOS2_TLBACC_IG_OFFSET 25
#define NIOS2_TLBACC_IG_MASK (0x3ff << NIOS2_TLBACC_IG_OFFSET)
#define NIOS2_TLBACC_C (1 << 24)
#define NIOS2_TLBACC_R (1 << 23)
#define NIOS2_TLBACC_W (1 << 22)
#define NIOS2_TLBACC_X (1 << 21)
#define NIOS2_TLBACC_G (1 << 20)
#define NIOS2_TLBACC_PFN_OFFSET 2
#define NIOS2_TLBACC_PFN_MASK (0xfffff << NIOS2_TLBACC_PFN_OFFSET)

#define NIOS2_TLBMISC_WAY_OFFSET 20
#define NIOS2_TLBMISC_WAY_MASK (0xf << NIOS2_TLBMISC_WAY_OFFSET)
#define NIOS2_TLBMISC_RD (1 << 19)
#define NIOS2_TLBMISC_WE (1 << 18)
#define NIOS2_TLBMISC_PID_OFFSET 5
#define NIOS2_TLBMISC_PID_MASK (0x3fff << NIOS2_TLBMISC_PID_OFFSET)
#define NIOS2_TLBMISC_DBL (1 << 3)
#define NIOS2_TLBMISC_BAD (1 << 2)
#define NIOS2_TLBMISC_PERM (1 << 1)
#define NIOS2_TLBMISC_D (1 << 0)

#define NIOS2_CONFIG_ANI (1 << 1)
#define NIOS2_CONFIG_PE (1 << 0)

#define NIOS2_MPUBASE_BASE_OFFSET 5
#define NIOS2_MPUBASE_BASE_MASK (0x1ffffff << NIOS2_MPUBASE_BASE_OFFSET)
#define NIOS2_MPUBASE_INDEX_OFFSET 1
#define NIOS2_MPUBASE_INDEX_MASK (0x1f << NIOS2_MPUBASE_INDEX_OFFSET)
#define NIOS2_MPUBASE_D (1 << 0)

#define NIOS2_MPUACC_MASK_OFFSET 6
#define NIOS2_MPUACC_MASK_MASK (0x1ffffff << NIOS2_MPUACC_MASK_OFFSET)
#define NIOS2_MPUACC_LIMIT_OFFSET 6
#define NIOS2_MPUACC_LIMIT_MASK (0x3ffffff << NIOS2_MPUACC_LIMIT_OFFSET)
#define NIOS2_MPUACC_C (1 << 5)
#define NIOS2_MPUACC_PERM_OFFSET 2
#define NIOS2_MPUACC_PERM_MASK (0x7 << NIOS2_MPUACC_PERM_OFFSET)
#define NIOS2_MPUACC_RD (1 << 1)
#define NIOS2_MPUACC_WR (1 << 0)

#ifndef ASM

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Nios II specific thread dispatch disabled indicator.
 *
 * This global variable is used by the interrupt dispatch support for the
 * external interrupt controller (EIC) with shadow registers.  This makes it
 * possible to do the thread dispatch after an interrupt without disabled
 * interrupts and thus probably reduce the maximum interrupt latency.  Its
 * purpose is to prevent unbounded stack usage of the interrupted thread.
 */
extern uint32_t _Nios2_Thread_dispatch_disabled;

/**
 * @brief This global symbol specifies the status register mask used to disable
 * interrupts.
 *
 * The board support package must provide a global symbol with this name to
 * specifiy the status register mask used in _CPU_ISR_Disable().
 */
extern char _Nios2_ISR_Status_mask [];

/**
 * @brief This symbol specifies the status register bits used to disable
 * interrupts.
 *
 * The board support package must provide a global symbol with this name to
 * specifiy the status register bits used in _CPU_ISR_Disable().
 */
extern char _Nios2_ISR_Status_bits [];

static inline uint32_t _Nios2_Get_ctlreg_status( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_STATUS );
}

static inline void _Nios2_Set_ctlreg_status( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_STATUS, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_estatus( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_ESTATUS );
}

static inline void _Nios2_Set_ctlreg_estatus( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_ESTATUS, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_bstatus( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_BSTATUS );
}

static inline void _Nios2_Set_ctlreg_bstatus( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_BSTATUS, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_ienable( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_IENABLE );
}

static inline void _Nios2_Set_ctlreg_ienable( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_IENABLE, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_ipending( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_IPENDING );
}

static inline uint32_t _Nios2_Get_ctlreg_cpuid( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_CPUID );
}

static inline uint32_t _Nios2_Get_ctlreg_exception( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_EXCEPTION );
}

static inline uint32_t _Nios2_Get_ctlreg_pteaddr( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_PTEADDR );
}

static inline void _Nios2_Set_ctlreg_pteaddr( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_PTEADDR, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_tlbacc( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_TLBACC );
}

static inline void _Nios2_Set_ctlreg_tlbacc( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_TLBACC, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_tlbmisc( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_TLBMISC );
}

static inline void _Nios2_Set_ctlreg_tlbmisc( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_TLBMISC, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_badaddr( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_BADADDR );
}

static inline uint32_t _Nios2_Get_ctlreg_config( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_CONFIG );
}

static inline void _Nios2_Set_ctlreg_config( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_CONFIG, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_mpubase( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_MPUBASE );
}

static inline void _Nios2_Set_ctlreg_mpubase( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_MPUBASE, (int) value );
}

static inline uint32_t _Nios2_Get_ctlreg_mpuacc( void )
{
  return (uint32_t) __builtin_rdctl( NIOS2_CTLREG_INDEX_MPUACC );
}

static inline void _Nios2_Set_ctlreg_mpuacc( uint32_t value )
{
  __builtin_wrctl( NIOS2_CTLREG_INDEX_MPUACC, (int) value );
}

static inline uint32_t _Nios2_Get_ISR_status_mask( void )
{
  return (uint32_t) &_Nios2_ISR_Status_mask [0];
}

static inline uint32_t _Nios2_Get_ISR_status_bits( void )
{
  return (uint32_t) &_Nios2_ISR_Status_bits [0];
}

static inline bool _Nios2_Has_internal_interrupt_controller( void )
{
  uint32_t isr_status_mask = _Nios2_Get_ISR_status_mask();

  return isr_status_mask == NIOS2_ISR_STATUS_MASK_IIC;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !ASM */

#endif /* _RTEMS_SCORE_NIOS2_UTILITY_H */
