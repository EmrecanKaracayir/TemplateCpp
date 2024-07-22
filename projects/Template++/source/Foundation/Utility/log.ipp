#pragma once

#include "Foundation/types.hpp"

#include <cassert>
#include <iostream>

namespace fn::Utility
{
  /**
   * @brief    A @c noexcept wrapper around @c std::cerr.
   * @param    message The message to log.
   * @remark   Inserts a newline character after the message.
   * @internal A proper logging library will surpass this function.
   */
  inline auto elog(const auto& message) noexcept -> none;
} // namespace fn::Utility

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

namespace fn::Utility
{
  // NOLINTBEGIN(bugprone-exception-escape)

  inline auto elog(const auto& message) noexcept -> none
  {
    // Ensure that the stream is in a non-throwing state
    assert(std::cout.exceptions() == std::ios_base::iostate{0});

#pragma warning(push)
#pragma warning(disable : 26'447)

    // NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay,
    // hicpp-no-array-decay)

    // Log the exception
    std::cerr << message << '\n';

    // NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay,
    // hicpp-no-array-decay)

#pragma warning(pop)
  }

  // NOLINTEND(bugprone-exception-escape)
} // namespace fn::Utility

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Promotes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

// NOLINTBEGIN(misc-unused-using-decls)

namespace fn
{
  using Utility::elog;
} // namespace fn

// NOLINTEND(misc-unused-using-decls)
