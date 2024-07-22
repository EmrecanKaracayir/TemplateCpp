#pragma once

#include "Foundation/types.hpp"

#include <exception>

namespace fn::Utility
{
  /**
   * @brief    A @c noexcept wrapper around @c std::exception::what.
   * @param    exception The exception to get the message of.
   * @internal When MSVC decides to conform to the standard by making
   *           @c std::exception::what @c noexcept, this function will be
   *           removed.
   * @return   The message of the exception.
   */
  constexpr auto WHAT(const std::exception& exception) noexcept -> cstr;
} // namespace fn::Utility

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

namespace fn::Utility
{
  constexpr auto WHAT(const std::exception& exception) noexcept -> cstr
  {
#pragma warning(push)
#pragma warning(disable : 26'447)

    // Return the exception message
    return exception.what();

#pragma warning(pop)
  }
} // namespace fn::Utility

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Promotes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

// NOLINTBEGIN(misc-unused-using-decls)

namespace fn
{
  using Utility::WHAT;
} // namespace fn

// NOLINTEND(misc-unused-using-decls)
