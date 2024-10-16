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
/*!        \file  vac/language/detail/copy_enabler.h
 *        \brief  Helper template for enabling/disabling copy constructor/assignment.
 *
 *********************************************************************************************************************/

#ifndef LIB_VAC_INCLUDE_VAC_LANGUAGE_DETAIL_COPY_ENABLER_H_
#define LIB_VAC_INCLUDE_VAC_LANGUAGE_DETAIL_COPY_ENABLER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

namespace vac {
namespace language {
namespace detail {

// VECTOR Next Construct AutosarC++17_10-A12.4.1: MD_VAC_A12.4.1_noVirtualDtor
/*!
 * \brief   Helper template for enabling/disabling copy constructor/assignment.
 * \details Defaulting copy constructor/assignment in a class with the CopyEnabler as base class will automatically
 *          enable/disable copy constructor/assignment depending on compile time flag.
 * \remark  This helper should only be used in case of private inheritance.
 * \tparam  enable Switch for enabling/disabling copy constructor/assignment.
 */
template <bool enable>
struct CopyEnabler {};

// VECTOR Next Construct AutosarC++17_10-A12.4.2: MD_VAC_A12.4.2_ifAPublicDestructorIsNotVirtual
/*!
 * \brief Specialization disabling copy constructor/assignment.
 */
template <>
class CopyEnabler<false> {
 public:
  /*! \brief Default constructor. */
  constexpr CopyEnabler() noexcept = default;

  /*! \brief Default copy constructor deleted. */
  constexpr CopyEnabler(CopyEnabler const&) noexcept = delete;

  // VECTOR Next Construct AutosarC++17_10-A12.8.6:MD_VAC_A12.8.6_copyMoveConstructorAssignmentShallBeProtectedOrDeleted
  /*! \brief Move constructor. */
  constexpr CopyEnabler(CopyEnabler&&) noexcept = default;

  /*!
   * \brief  Default copy assignment operator deleted.
   * \return
   */
  CopyEnabler& operator=(CopyEnabler const&) & noexcept = delete;

  // VECTOR Next Construct AutosarC++17_10-A12.8.6:MD_VAC_A12.8.6_copyMoveConstructorAssignmentShallBeProtectedOrDeleted
  /*!
   * \brief  Move assignment.
   * \return A reference to the assigned-to object.
   */
  CopyEnabler& operator=(CopyEnabler&&) & noexcept = default;

  // VECTOR Next Construct AutosarC++17_10-A12.4.1: MD_VAC_A12.4.1_noVirtualDtor
  /*! \brief Default destructor. */
  ~CopyEnabler() noexcept = default;
};

}  // namespace detail
}  // namespace language
}  // namespace vac

#endif  // LIB_VAC_INCLUDE_VAC_LANGUAGE_DETAIL_COPY_ENABLER_H_
