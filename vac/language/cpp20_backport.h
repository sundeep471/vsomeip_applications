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
/*!      \file  cpp20_backport.h
 *      \brief  Contains useful backports of features from C++20.
 *
 *********************************************************************************************************************/
#ifndef LIB_VAC_INCLUDE_VAC_LANGUAGE_CPP20_BACKPORT_H_
#define LIB_VAC_INCLUDE_VAC_LANGUAGE_CPP20_BACKPORT_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <type_traits>
#include "vac/language/cpp14_backport.h"

namespace vac {
namespace language {

/*!
 * \brief  Returns the size of the given container.
 * \tparam Container The type of container.
 * \param  c The container.
 * \return The size of the given container.
 * */
template <typename Container>
constexpr auto ssize(Container const& c) noexcept -> common_type_t<std::ptrdiff_t, make_signed_t<decltype(c.size())>> {
  /*! \brief Type alias. */
  using SignedType = common_type_t<std::ptrdiff_t, make_signed_t<decltype(c.size())>>;
  return static_cast<SignedType>(c.size());
}

// VECTOR Next Construct AutosarC++17_10-A12.4.1: MD_VAC_A12.4.1_compileTimeResolution
// VECTOR Next Construct VectorC++-V11-0-3: MD_VAC_V11-0-3_structShallContainOnlyPublicMember
/*! \brief Type identity. Useful for inheritance and for blocking template argument deduction. */
template <typename T>
struct type_identity {
  /*! \brief Identity type. */
  using type = T;
};

/*! \brief Type identity helper alias. */
template <typename T>
using type_identity_t = typename type_identity<T>::type;

/*!
 * \brief  Implementation of C++20 std::remove_cvref.
 * \tparam T The type to remove top-level cv-qualifiers and references from.
 */
template <typename T>
class remove_cvref {
 public:
  /*! \brief The type of T without cv-qualifiers or reference. */
  using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

/*! \brief Alias for remove_cvref<T>::type */
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

}  // namespace language
}  // namespace vac

#endif  // LIB_VAC_INCLUDE_VAC_LANGUAGE_CPP20_BACKPORT_H_
