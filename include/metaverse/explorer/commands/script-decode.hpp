/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2017 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse-explorer.
 *
 * metaverse-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BX_SCRIPT_DECODE_HPP
#define BX_SCRIPT_DECODE_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <metaverse/bitcoin.hpp>
#include <metaverse/explorer/command.hpp>
#include <metaverse/explorer/define.hpp>
#include <metaverse/explorer/generated.hpp>
#include <metaverse/explorer/config/address.hpp>
#include <metaverse/explorer/config/algorithm.hpp>
#include <metaverse/explorer/config/btc.hpp>
#include <metaverse/explorer/config/byte.hpp>
#include <metaverse/explorer/config/cert_key.hpp>
#include <metaverse/explorer/config/ec_private.hpp>
#include <metaverse/explorer/config/encoding.hpp>
#include <metaverse/explorer/config/endorsement.hpp>
#include <metaverse/explorer/config/hashtype.hpp>
#include <metaverse/explorer/config/hd_key.hpp>
#include <metaverse/explorer/config/header.hpp>
#include <metaverse/explorer/config/input.hpp>
#include <metaverse/explorer/config/language.hpp>
#include <metaverse/explorer/config/output.hpp>
#include <metaverse/explorer/config/raw.hpp>
#include <metaverse/explorer/config/script.hpp>
#include <metaverse/explorer/config/signature.hpp>
#include <metaverse/explorer/config/transaction.hpp>
#include <metaverse/explorer/config/wrapper.hpp>
#include <metaverse/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Class to implement the script-decode command.
 */
class BCX_API script_decode 
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "script-decode";
    }

    /**
     * The symbolic (not localizable) former command name, lower case.
     */
    static const char* formerly()
    {
        return "showscript";
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return script_decode::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "TRANSACTION";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Decode a script to plain text tokens.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("BASE16", 1);
    }

	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        const auto raw = requires_raw_input();
        load_input(get_base16_argument(), "BASE16", variables, input, raw);
    }

    /**
     * Load program option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    virtual options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
        (
            BX_HELP_VARIABLE ",h",
            value<bool>()->zero_tokens(),
            "Get a description and instructions for this command."
        )
        (
            BX_CONFIG_VARIABLE ",c",
            value<boost::filesystem::path>(),
            "The path to the configuration settings file."
        )
        (
            "BASE16",
            value<bc::config::base16>(&argument_.base16),
            "The Base16 script. If not specified the script is read from STDIN."
        );

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the BASE16 argument.
     */
    virtual bc::config::base16& get_base16_argument()
    {
        return argument_.base16;
    }

    /**
     * Set the value of the BASE16 argument.
     */
    virtual void set_base16_argument(
        const bc::config::base16& value)
    {
        argument_.base16 = value;
    }

private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
          : base16()
        {
        }

        bc::config::base16 base16;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
        {
        }

    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif