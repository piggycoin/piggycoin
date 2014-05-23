// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // Yo dawg, this is the secret. Checkpoint 0 hash == Genesis block hash.
        (     0, uint256("0x17123d76375bf82f6d28f7351eefc80565e91dbc6fef61549e6704a31e2d90b1"))
        (  9979, uint256("0x2c901bd7cb792a8a20f55b6c11a387ce40833b563bc1efd7bac799725de67e86"))
        ( 11267, uint256("0xdc84f77dfeddbd31214d0e4b101e575ee7948eca51cd47debe1945bdf4783218"))
        ( 15000, uint256("0xe816c4900711efb90e329e2be1c559da26b860c781c2205a618839c0ab30d950"))
        ( 21886, uint256("0xa439f10001a38aa9834b3868dc1092326b1971209bbee00a5eab551b211cf7a7"))
        ( 30000, uint256("0x31aeac59fc41e7b4d6c7e84b89f38593adf83bda059755e459864fd82cf88023"))
        ( 43100, uint256("0x249392f38e74acc0047b7ffb2d1703816dd45dc9d16bb91177f28daa6cb3d39b"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
