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
/*!        \file  vac/include/ara/core/exception.h
 *        \brief  SWS core type ara::core::Exception. Base type for all AUTOSAR exception types.
 *
 *********************************************************************************************************************/

#ifndef LIB_VAC_INCLUDE_ARA_CORE_EXCEPTION_H_
#define LIB_VAC_INCLUDE_ARA_CORE_EXCEPTION_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <exception>
#include <utility>

#include "ara/core/error_code.h"

namespace ara {
namespace core {

/*!
 * \brief Base type for all AUTOSAR exception types
 * \trace CREQ-166594
 * \trace SPEC-7552399
 * \vpublic
 */
class Exception : public std::exception {
 public:
  // VECTOR Disable AutosarC++17_10-A15.5.1: MD_VAC_A15.5.1_explicitNoexceptIfAppropriate
  /*!
   * \brief Construct a new Exception object with a specific ErrorCode.
   * \param error_code The ErrorCode.
   * \trace SPEC-7552400
   * \vpublic
   */
  explicit Exception(ErrorCode error_code) noexcept : error_code_{error_code} {}

  /*!
   * \brief Destructor.
   * \vpublic
   */
  ~Exception() noexcept override = default;

  /*!
   * \brief   Return the explanatory string.
   * \details This function overrides the virtual function std::exception::what.
   *          All guarantees about the lifetime of the returned pointer
   *          that are given for std::exception::what are preserved.
   * \returns A null-terminated string.
   * \trace   SPEC-7552401
   * \vpublic
   */
  char const* what() const noexcept override { return this->Error().Message().data(); }

  /*!
   * \brief   Return the embedded ErrorCode that was given to the constructor.
   * \returns A reference to the embedded ErrorCode.
   * \trace   SPEC-7552402
   * \vpublic
   */
  ErrorCode const& Error() const noexcept { return error_code_; }

 protected:
  /*!
   * \brief Default Move Constructor.
   * \vpublic
   */
  Exception(Exception&&) noexcept = default;

  /*!
   * \brief Default Copy Constructor.
   * \vpublic
   */
  Exception(Exception const&) noexcept = default;

  /*!
   * \brief  Default Move assignment.
   * \return A reference to the assigned-to object.
   */
  Exception& operator=(Exception&&) & noexcept = default;

  /*!
   * \brief  Default Copy assignment.
   * \return A reference to the assigned-to object.
   */
  Exception& operator=(Exception const&) & noexcept = default;
  // VECTOR Enable AutosarC++17_10-A15.5.1

 private:
  /*!
   * \brief  the embedded ErrorCode
   */
  ErrorCode error_code_;
};

}  // namespace core
}  // namespace ara

#endif  // LIB_VAC_INCLUDE_ARA_CORE_EXCEPTION_H_
