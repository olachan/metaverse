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
#include <metaverse/explorer/commands/mnemonic-new.hpp>

#include <iostream>
#include <metaverse/bitcoin.hpp>
#include <metaverse/explorer/define.hpp>


namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;

console_result mnemonic_new::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const dictionary_list& language = get_language_option();
    const data_chunk& entropy = get_seed_argument();

    const auto entropy_size = entropy.size();

    if ((entropy_size % bc::wallet::mnemonic_seed_multiple) != 0)
    {
        error << BX_EC_MNEMONIC_NEW_INVALID_ENTROPY << std::flush;
        return console_result::failure;
    }

    // If 'any' default to first ('en'), otherwise the one specified.
    const auto dictionary = language.front();
    const auto words = create_mnemonic(entropy, *dictionary);

    output << join(words) << std::flush;
    return console_result::okay;
}

} //namespace commands 
} //namespace explorer 
} //namespace libbitcoin 
