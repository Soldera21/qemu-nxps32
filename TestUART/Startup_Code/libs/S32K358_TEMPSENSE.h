/*
** ###################################################################
**     Processor:           S32K358_M7
**     Compiler:            Keil ARM C/C++ Compiler
**     Reference manual:    S32K3xx RM Rev.8
**     Version:             rev. 1.2, 2024-02-12
**     Build:               b240212
**
**     Abstract:
**         Peripheral Access Layer for S32K358_M7
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**
**     NXP Confidential and Proprietary. This software is owned or controlled
**     by NXP and may only be used strictly in accordance with the applicable
**     license terms. By expressly accepting such terms or by downloading,
**     installing, activating and/or otherwise using the software, you are
**     agreeing that you have read, and that you agree to comply with and are
**     bound by, such license terms. If you do not agree to be bound by the
**     applicable license terms, then you may not retain, install, activate
**     or otherwise use the software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/*!
 * @file S32K358_TEMPSENSE.h
 * @version 1.2
 * @date 2024-02-12
 * @brief Peripheral Access Layer for S32K358_TEMPSENSE
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
* The SoC header defines typedef for all modules.
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
* The SoC header defines macros for all modules and registers.
*
* @section [global]
* Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
* These are generated macros used for accessing the bit-fields from registers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.1, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.2, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.4, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.5, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
* This type qualifier is needed to ensure correct I/O access and addressing.
*/

/* Prevention from multiple including the same memory map */
#if !defined(S32K358_TEMPSENSE_H_)  /* Check if memory map has not been already included */
#define S32K358_TEMPSENSE_H_

#include "S32K358_COMMON.h"

/* ----------------------------------------------------------------------------
   -- TEMPSENSE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TEMPSENSE_Peripheral_Access_Layer TEMPSENSE Peripheral Access Layer
 * @{
 */

/** TEMPSENSE - Register Layout Typedef */
typedef struct {
  __IO uint32_t ETSCTL;                            /**< ETS Control, offset: 0x0 */
  uint8_t RESERVED_0[4];
  __I  uint32_t TCA0;                              /**< Temperature Coefficient, offset: 0x8 */
  __I  uint32_t TCA1;                              /**< Temperature Coefficient, offset: 0xC */
  __I  uint32_t TCA2;                              /**< Temperature Coefficient, offset: 0x10 */
} TEMPSENSE_Type, *TEMPSENSE_MemMapPtr;

/** Number of instances of the TEMPSENSE module. */
#define TEMPSENSE_INSTANCE_COUNT                 (1u)

/* TEMPSENSE - Peripheral instance base addresses */
/** Peripheral TEMPSENSE base address */
#define IP_TEMPSENSE_BASE                        (0x4037C000u)
/** Peripheral TEMPSENSE base pointer */
#define IP_TEMPSENSE                             ((TEMPSENSE_Type *)IP_TEMPSENSE_BASE)
/** Array initializer of TEMPSENSE peripheral base addresses */
#define IP_TEMPSENSE_BASE_ADDRS                  { IP_TEMPSENSE_BASE }
/** Array initializer of TEMPSENSE peripheral base pointers */
#define IP_TEMPSENSE_BASE_PTRS                   { IP_TEMPSENSE }

/* ----------------------------------------------------------------------------
   -- TEMPSENSE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TEMPSENSE_Register_Masks TEMPSENSE Register Masks
 * @{
 */

/*! @name ETSCTL - ETS Control */
/*! @{ */

#define TEMPSENSE_ETSCTL_ETS_EN_MASK             (0x1U)
#define TEMPSENSE_ETSCTL_ETS_EN_SHIFT            (0U)
#define TEMPSENSE_ETSCTL_ETS_EN_WIDTH            (1U)
#define TEMPSENSE_ETSCTL_ETS_EN(x)               (((uint32_t)(((uint32_t)(x)) << TEMPSENSE_ETSCTL_ETS_EN_SHIFT)) & TEMPSENSE_ETSCTL_ETS_EN_MASK)

#define TEMPSENSE_ETSCTL_GNDSEL_MASK             (0x2U)
#define TEMPSENSE_ETSCTL_GNDSEL_SHIFT            (1U)
#define TEMPSENSE_ETSCTL_GNDSEL_WIDTH            (1U)
#define TEMPSENSE_ETSCTL_GNDSEL(x)               (((uint32_t)(((uint32_t)(x)) << TEMPSENSE_ETSCTL_GNDSEL_SHIFT)) & TEMPSENSE_ETSCTL_GNDSEL_MASK)
/*! @} */

/*! @name TCA0 - Temperature Coefficient */
/*! @{ */

#define TEMPSENSE_TCA0_TCA0_MASK                 (0xFFFFU)
#define TEMPSENSE_TCA0_TCA0_SHIFT                (0U)
#define TEMPSENSE_TCA0_TCA0_WIDTH                (16U)
#define TEMPSENSE_TCA0_TCA0(x)                   (((uint32_t)(((uint32_t)(x)) << TEMPSENSE_TCA0_TCA0_SHIFT)) & TEMPSENSE_TCA0_TCA0_MASK)
/*! @} */

/*! @name TCA1 - Temperature Coefficient */
/*! @{ */

#define TEMPSENSE_TCA1_TCA1_MASK                 (0xFFFFU)
#define TEMPSENSE_TCA1_TCA1_SHIFT                (0U)
#define TEMPSENSE_TCA1_TCA1_WIDTH                (16U)
#define TEMPSENSE_TCA1_TCA1(x)                   (((uint32_t)(((uint32_t)(x)) << TEMPSENSE_TCA1_TCA1_SHIFT)) & TEMPSENSE_TCA1_TCA1_MASK)
/*! @} */

/*! @name TCA2 - Temperature Coefficient */
/*! @{ */

#define TEMPSENSE_TCA2_TCA2_MASK                 (0xFFFFU)
#define TEMPSENSE_TCA2_TCA2_SHIFT                (0U)
#define TEMPSENSE_TCA2_TCA2_WIDTH                (16U)
#define TEMPSENSE_TCA2_TCA2(x)                   (((uint32_t)(((uint32_t)(x)) << TEMPSENSE_TCA2_TCA2_SHIFT)) & TEMPSENSE_TCA2_TCA2_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group TEMPSENSE_Register_Masks */

/*!
 * @}
 */ /* end of group TEMPSENSE_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K358_TEMPSENSE_H_) */
