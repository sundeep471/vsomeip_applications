/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  phase_managed_allocator.h
 *        \brief  The header file is related to the memory allocation in different phases.
 *
 *      \details  The template of phase-checked allocators and non-phase-checked allocators are introduced.
 *                If the phase check result is true, PhaseManagedAllocator is mapped to the three phase allocator,
 *                otherwise it is mapped directly to DelegateAllocator.
 *                NOTE: ThreePhaseAllocator has been removed, PhaseManagedAllocator will always be mapped to
 *                DelegateAllocator.
 *
 *********************************************************************************************************************/

#ifndef LIB_VAC_INCLUDE_VAC_MEMORY_PHASE_MANAGED_ALLOCATOR_H_
#define LIB_VAC_INCLUDE_VAC_MEMORY_PHASE_MANAGED_ALLOCATOR_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <memory>

namespace vac {
namespace memory {

namespace internal {

/*!
 * \brief Wrapper template to differentiate between deterministic mode allocators with allocation phase check and
 *        non-deterministic mode allocators without allocation phase check.
 */
template <typename T, typename DelegateAllocator, bool is_deterministic_mode>
class PhaseManagedAllocator;

/*!
 * \brief Wrapper template for phase-checked allocators.
 */
template <typename T, typename DelegateAllocator>
class PhaseManagedAllocator<T, DelegateAllocator, true> {
 public:
  /*!
   * \brief Allocator type.
   */
  using type = DelegateAllocator;
};

/*!
 * \brief Wrapper template for non-phase-checked allocators.
 */
template <typename T, typename DelegateAllocator>
class PhaseManagedAllocator<T, DelegateAllocator, false> {
 public:
  /*!
   * \brief Allocator type.
   */
  using type = DelegateAllocator;
};

}  // namespace internal

/*!
 * \brief   Wrapper template to differentiate between phase-checked allocators and non-phase-checked allocators.
 */
template <typename T, typename DelegateAllocator = std::allocator<T>>
using PhaseManagedAllocator = typename internal::PhaseManagedAllocator<T, DelegateAllocator, false>::type;

}  // namespace memory
}  // namespace vac

#endif  // LIB_VAC_INCLUDE_VAC_MEMORY_PHASE_MANAGED_ALLOCATOR_H_
