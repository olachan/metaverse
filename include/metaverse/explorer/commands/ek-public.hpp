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
#ifndef BX_EK_PUBLIC_HPP
#define BX_EK_PUBLIC_HPP

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
 * Various localizable strings.
 */
#define BX_EK_PUBLIC_SHORT_SEED \
    "The seed is less than 192 bits long."

/**
 * Class to implement the ek-public command.
 */
class BCX_API ek_public 
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "ek-public";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return ek_public::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "KEY_ENCRYPTION";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Create an encrypted public key from an intermediate passphrase token (BIP38).";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("TOKEN", 1)
            .add("SEED", 1);
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
        load_input(get_seed_argument(), "SEED", variables, input, raw);
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
            "uncompressed,u",
            value<bool>(&option_.uncompressed)->zero_tokens(),
            "Use the uncompressed public key format, as used to create the corresponding encrypted private key."
        )
        (
            "version,v",
            value<explorer::config::byte>(&option_.version)->default_value(0),
            "The desired payment address version used to create the corresponding encrypted private key."
        )
        (
            "TOKEN",
            value<bc::wallet::ek_token>(&argument_.token)->required(),
            "The intermediate passphrase token used to create the corresponding encrypted private key."
        )
        (
            "SEED",
            value<bc::config::base16>(&argument_.seed),
            "The Base16 entropy for the new encrypted public key. Must be at least 192 bits in length (only the first 192 bits are used). If not specified the seed is read from STDIN."
        );

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
        const auto& option_version = variables["version"];
        const auto& option_version_config = variables["wallet.pay_to_public_key_hash_version"];
        if (option_version.defaulted() && !option_version_config.defaulted())
        {
            option_.version = option_version_config.as<explorer::config::byte>();
        }
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
     * Get the value of the TOKEN argument.
     */
    virtual bc::wallet::ek_token& get_token_argument()
    {
        return argument_.token;
    }

    /**
     * Set the value of the TOKEN argument.
     */
    virtual void set_token_argument(
        const bc::wallet::ek_token& value)
    {
        argument_.token = value;
    }

    /**
     * Get the value of the SEED argument.
     */
    virtual bc::config::base16& get_seed_argument()
    {
        return argument_.seed;
    }

    /**
     * Set the value of the SEED argument.
     */
    virtual void set_seed_argument(
        const bc::config::base16& value)
    {
        argument_.seed = value;
    }

    /**
     * Get the value of the uncompressed option.
     */
    virtual bool& get_uncompressed_option()
    {
        return option_.uncompressed;
    }

    /**
     * Set the value of the uncompressed option.
     */
    virtual void set_uncompressed_option(
        const bool& value)
    {
        option_.uncompressed = value;
    }

    /**
     * Get the value of the version option.
     */
    virtual explorer::config::byte& get_version_option()
    {
        return option_.version;
    }

    /**
     * Set the value of the version option.
     */
    virtual void set_version_option(
        const explorer::config::byte& value)
    {
        option_.version = value;
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
          : token(),
            seed()
        {
        }

        bc::wallet::ek_token token;
        bc::config::base16 seed;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : uncompressed(),
            version()
        {
        }

        bool uncompressed;
        explorer::config::byte version;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
