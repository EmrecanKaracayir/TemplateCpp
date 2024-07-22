#pragma once

#include "Foundation/_internal/Exception/_internal/concepts.hpp"
#include "Foundation/_internal/Exception/Name.ipp"
#include "Foundation/types.hpp"

#include <concepts>
#include <exception>
#include <optional>
#include <ostream>
#include <source_location>
#include <string>
#include <utility>

namespace fn::_internal::Exception
{
  /**
   * @brief  A foundation class for exceptions.
   * @tparam name The name of the exception.
   * @tparam Context The context of the exception.
   */
  template <Name name, _internal::IsContext Context>
  class Exception final : public std::exception
  {
  public:
    /*------------------------------------------------------------------------*\
    *| [public]: Constructors                                                 |*
    \*------------------------------------------------------------------------*/

    /**
     * @brief Constructs an exception by copying another exception.
     * @param other Other exception to copy from.
     */
    Exception(const Exception& other) noexcept = default;

    /**
     * @brief Constructs an exception by moving another exception.
     * @param other Other exception to move from.
     */
    Exception(Exception&& other) noexcept = default;

    /**
     * @brief Constructs an exception without any message or context.
     */
    explicit Exception(
      const std::source_location& location = std::source_location::current()
    ) noexcept;

    /**
     * @brief Constructs an exception with a message.
     * @param message The message.
     */
    explicit Exception(
      std::string&&               message,
      const std::source_location& location = std::source_location::current()
    ) noexcept;

    /**
     * @brief Constructs an exception with a message and a context.
     * @param message The message.
     * @param context The context.
     */
    Exception(
      std::string&&               message,
      Context&&                   context,
      const std::source_location& location = std::source_location::current()
    ) noexcept;

    /*------------------------------------------------------------------------*\
    *| [public]: Destructor                                                   |*
    \*------------------------------------------------------------------------*/

    /**
     * @brief Destructs the exception.
     */
    ~Exception() override = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Operators                                                    |*
    \*------------------------------------------------------------------------*/

    /**
     * @brief   Assigns another exception to this exception by copying.
     * @param   other The other exception to copy from.
     * @returns The reference to this exception.
     */
    auto operator=(const Exception& other) noexcept -> Exception& = default;

    /**
     * @brief   Assigns another exception to this exception by moving.
     * @param   other The other exception to move from.
     * @returns The reference to this exception.
     */
    auto operator=(Exception&& other) noexcept -> Exception& = default;

    /*------------------------------------------------------------------------*\
    *| [public]: Methods                                                      |*
    \*------------------------------------------------------------------------*/

    /**
     * @brief   Accessor for the name of the exception.
     * @returns The name of the exception.
     */
    [[nodiscard]]
    auto what() const noexcept -> cstr override;

    /*------------------------------------------------------------------------*\
    *| [public]: Accessors                                                    |*
    \*------------------------------------------------------------------------*/

    /**
     * @brief   Accessor for the message of the exception.
     * @returns The message of the exception.
     */
    [[nodiscard]]
    auto getMessage() const noexcept -> const std::optional<std::string>&;

    /**
     * @brief   Accessor for the context of the exception.
     * @returns The context of the exception.
     */
    [[nodiscard]]
    auto getContext() const noexcept -> const std::optional<Context>&;

    /**
     * @brief   Accessor for the location of the exception.
     * @returns The location of the exception.
     */
    [[nodiscard]]
    auto getLocation() const noexcept -> const std::source_location&;

  private:
    /*------------------------------------------------------------------------*\
    *| [private]: Fields                                                      |*
    \*------------------------------------------------------------------------*/

    std::optional<std::string> m_message;
    std::optional<Context>     m_context;
    std::source_location       m_location;

    /*------------------------------------------------------------------------*\
    *| [private]: Friends                                                     |*
    \*------------------------------------------------------------------------*/

    /**
     * @brief   Prints the exception to an output stream.
     * @param   os The output stream.
     * @param   exception The exception.
     * @returns The output stream.
     */
    friend auto operator<<(
      std::ostream& os, const Exception& exception
    ) noexcept -> std::ostream&
    {
#pragma warning(push)
#pragma warning(disable : 26'447 26'485)

      // Print exception name
      os << '\n' << name.value << '\n';

      // Print message if available
      if (const auto message{exception.m_message}; message.has_value())
      {
        os << "  Message: " << message.value() << '\n';
      }

      // Print context if available and not unit
      if (const auto context{exception.m_context}; context.has_value())
      {
        // Print context if not unit
        if constexpr (not std::same_as<Context, unit>)
        {
          os << "  Context: " << context.value() << '\n';
        }
      }

      // Print address
      os << "  Address: " << exception.m_location.file_name() << "("
         << exception.m_location.line() << ":" << exception.m_location.column()
         << ")\n";

      // Print routine
      os << "  Routine: " << exception.m_location.function_name() << '\n';

#pragma warning(pop)

      // Return output stream
      return os;
    }
  };
} // namespace fn::_internal::Exception

/*----------------------------------------------------------------------------*\
*| <<<<<<<<<<<<<<<<<<<<<<<<<<<<< Implementation >>>>>>>>>>>>>>>>>>>>>>>>>>>>> |*
\*----------------------------------------------------------------------------*/

namespace fn::_internal::Exception
{
  /*--------------------------------------------------------------------------*\
  *| [public]: Constructors                                                   |*
  \*--------------------------------------------------------------------------*/

  template <Name name, _internal::IsContext Context>
  Exception<name, Context>::Exception(const std::source_location& location
  ) noexcept
    : m_location{location}
  {}

  template <Name name, _internal::IsContext Context>
  Exception<name, Context>::Exception(
    std::string&& message, const std::source_location& location
  ) noexcept
    : m_message{std::move(message)}
    , m_location{location}
  {}

  template <Name name, _internal::IsContext Context>
  Exception<name, Context>::Exception(
    std::string&&               message,
    Context&&                   context,
    const std::source_location& location
  ) noexcept
    : m_message{std::move(message)}
    , m_context{std::move(context)}
    , m_location{location}
  {}

  /*--------------------------------------------------------------------------*\
  *| [public]: Methods                                                        |*
  \*--------------------------------------------------------------------------*/

  template <Name name, _internal::IsContext Context>
  auto Exception<name, Context>::what() const noexcept -> cstr
  {
#pragma warning(push)
#pragma warning(disable : 26'485)

    return name.value;

#pragma warning(pop)
  }

  /*--------------------------------------------------------------------------*\
  *| [public]: Accessors                                                      |*
  \*--------------------------------------------------------------------------*/

  template <Name name, _internal::IsContext Context>
  [[nodiscard]]
  auto Exception<name, Context>::getMessage() const noexcept
    -> const std::optional<std::string>&
  {
    return m_message;
  }

  template <Name name, _internal::IsContext Context>
  [[nodiscard]]
  auto Exception<name, Context>::getContext() const noexcept
    -> const std::optional<Context>&
  {
    return m_context;
  }

  template <Name name, _internal::IsContext Context>
  [[nodiscard]]
  auto Exception<name, Context>::getLocation() const noexcept
    -> const std::source_location&
  {
    return m_location;
  }
} // namespace fn::_internal::Exception
