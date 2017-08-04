/**
 * Copyright (c) 2017 Bitprim developers (see AUTHORS)
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BITPRIM_NODECINT_PARSER_HPP_
#define BITPRIM_NODECINT_PARSER_HPP_

#include <ostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/node/define.hpp>
#include <bitcoin/node/configuration.hpp>

namespace bitprim { namespace nodecint {

using variables_map = boost::program_options::variables_map;

/// Parse configurable values from environment variables, settings file, and
/// command line positional and non-positional options.
class BCN_API parser
  : public libbitcoin::config::parser
{
public:
    explicit
    parser(libbitcoin::config::settings const& context);

    explicit
    parser(libbitcoin::node::configuration const& defaults);

    /// Parse all configuration into member settings.
//    virtual bool parse(int argc, char const* argv[], std::ostream& error);
    virtual bool parse(boost::filesystem::path const& config_path, std::ostream& error);

    /// Load configuration file settings.
    libbitcoin::options_metadata load_settings() override;



    /// Load command line options (named).
    libbitcoin::options_metadata load_options() override;
    /// Load command line arguments (positional).
    libbitcoin::arguments_metadata load_arguments() override;
    /// Load environment variable settings.
    libbitcoin::options_metadata load_environment() override;


    //virtual bool load_configuration_variables(variables_map& variables, std::string const& option_name);
    bool load_configuration_variables(variables_map& variables, boost::filesystem::path const& config_path);


    /// The populated configuration settings values.
    libbitcoin::node::configuration configured;
};

} // namespace nodecint
} // namespace bitprim

#endif /* BITPRIM_NODECINT_PARSER_HPP_ */
