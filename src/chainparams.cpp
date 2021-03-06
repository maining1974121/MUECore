// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2014-2017 The MonetaryUnit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

#include "stdio.h"
#include "pow.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    return genesis;
}


static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "18/06/2017 respn to trump the Castro gov said Trump's US is in no condition to lecture us";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";

              consensus.nSubsidyHalvingInterval = -1;
              consensus.nMasternodePaymentsStartBlock = 322;
              consensus.nMasternodePaymentsIncreaseBlock = -1;
              consensus.nMasternodePaymentsIncreasePeriod = -1;
              consensus.nInstantSendKeepLock = 94;
              consensus.nBudgetPaymentsStartBlock = 65123;
              consensus.nBudgetPaymentsCycleBlocks = 64800;
              consensus.nBudgetPaymentsWindowBlocks = 390;
              consensus.nBudgetProposalEstablishingTime = 86400;
              consensus.nSuperblockStartBlock = 69023;
              consensus.nSuperblockCycle = 64800;
              consensus.nGovernanceMinQuorum = 10;
              consensus.nGovernanceFilterElements = 20000;
              consensus.nMasternodeMinimumConfirmations = 20;

              consensus.nMajorityEnforceBlockUpgrade = 750;
              consensus.nMajorityRejectBlockOutdated = 950;

              consensus.nMajorityWindow = 3900;
              consensus.BIP34Height = -1;
              consensus.BIP34Hash = uint256S("0x0");
              consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
              consensus.nPowTargetTimespan = 120;
              consensus.nPowTargetSpacing = 40;
              consensus.fPowAllowMinDifficultyBlocks = false;
              consensus.fPowNoRetargeting = false;
              consensus.nRuleChangeActivationThreshold = 2;
              consensus.nMinerConfirmationWindow = 3;

              consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
              consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
              consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
              // Deployment of BIP68, BIP112, and BIP113.
              consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
              consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1486252800; // Feb 5th, 2017
              consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517788800; // Feb 5th, 2018

              /**
               * The message start string is designed to be unlikely to occur in normal data.
               * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
               * a large 32-bit integer with any alignment.
               */

              pchMessageStart[0] = 0xb5;
              pchMessageStart[1] = 0xcc;
              pchMessageStart[2] = 0xcd;
              pchMessageStart[3] = 0xa7;

              vAlertPubKey = ParseHex("042736aa94dcc46a596d1f42a5402261b6d9d8a72de40ace5a8856f9e5f7bab96f837f926a8ab8d1e2f8d6d7ef59732d99b55352c4fdf775bdb9690c42851609bd");
              nDefaultPort = 19683;
              nMaxTipAge = 28800;
              nPruneAfterHeight = 100000;


              genesis = CreateGenesisBlock(1498253423, 932796, 0x1e0ffff0, 1, 50 * COIN);
              consensus.hashGenesisBlock = genesis.GetHash();
              assert(consensus.hashGenesisBlock == uint256S("0x000002acd994a815401fbaae0e52404b32857efd0b7b0c77b8e0715ccdd6d437"));
              assert(genesis.hashMerkleRoot == uint256S("0x69bb62a0f72c83b38ef6539987cf6c4da5b8e57ac7ecede490a7cefc171e7421"));

              vSeeds.push_back(CDNSSeedData("nodes.muex.io","nodes.muex.io"));
              vSeeds.push_back(CDNSSeedData("nodes.monetaryunit.org","nodes.monetaryunit.org"));
              vSeeds.push_back(CDNSSeedData("nodes.mymue.com","nodes.mymue.com"));
              vSeeds.push_back(CDNSSeedData("nodes.cryptophi.com","nodes.cryptophi.com"));

        // MonetaryUnit addresses start with '7'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,16);
        // MonetaryUnit script addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,76);
        // MonetaryUnit private keys start with 's' or 't'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,126);

        // MonetaryUnit BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // MonetaryUnit BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // MonetaryUnit BIP44 coin type is '5' <== Should be migrated to 31 SLIP-44 MonetaryUnit
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 950;
        strSporkPubKey = "04251df9125d968a5efeac89f08be613621ae19d3d9ca4818485d2405a994b6164d9f26c5ad3e7a19a99dc36fa7dd03f05e968b4bdd1dc39e5b25c0dc60a441506";
        strMasternodePaymentsPubKey = "0483bbc11d4c6a0cb4361da2a234912a7e174e2b9ecfb7685920c24a58fa32205d73f272540032ec7f4dd9d7d865bf171268dcacaa1184675cb2ed2361eb93218f";

        checkpointData = (CCheckpointData) {
                boost::assign::map_list_of
                (0, uint256S("0x000002acd994a815401fbaae0e52404b32857efd0b7b0c77b8e0715ccdd6d437"))
                (1, uint256S("0x0000017ec32860e36fc3cb05c21913b50545757f5617a301f33737c511281a4d"))
                (161, uint256S("0x0000000023c2152b45c51919f349ee9bfb0fdca48428eb340de7056cdb1cf2dc"))
                (228, uint256S("0x000000002516606a20c5788142b5f9912c078325b66f224e185402e89dea42d5"))
                (260, uint256S("0x00000000017ec822f590e0bc6fa703fc615c1afe16b163cfbab49131d4760c76"))
                (500, uint256S("0x0000000007f129a02b3cd71baa3b9c4b0f5d33853648a4afa5ba3193ee967f1e"))
                (600, uint256S("0x0000000000e90fc3ba2070dbae096f16537589f23fee6263d1eced54f6642617"))
                (700, uint256S("0x000000000309573e3f20c1eec45a1c334e976d6748e4f17a5a9f3dfc5f29ba0b"))
                (800, uint256S("0x0000000002cf6221167b3c8fa5e5fe769b57b135d229939160a47d5e85dee6ab"))
                (900, uint256S("0x00000000022ff8f902a6cf52e1ba7286572b158d34998df9d1fc7bcedfe79335"))
                (1000, uint256S("0x00000000005525752de45ac2bcd51df2fafc322a6c69e37381f5b2a7c9218dcc"))
                (1500, uint256S("0x0000000000498b101e2bc7fa81e39f8fc51cca0359df6cb1285ff86171721fd1"))
                (1750, uint256S("0x0000000000c479cfe3b71650ed8f0f02579c7e649a7a5d5c58fe65979dcfb22c")),
                1498541029,
                       197,   //   (the tx=... number in the SetBestChain debug.log lines)
                      2160    // * estimated number of transactions per day after checkpoint
       };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v1)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = -1;
        consensus.nMasternodePaymentsStartBlock = 121;
        consensus.nMasternodePaymentsIncreaseBlock = -1;
        consensus.nMasternodePaymentsIncreasePeriod = -1;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 2282;
        consensus.nBudgetPaymentsCycleBlocks = 90;
        consensus.nBudgetPaymentsWindowBlocks = 39;
        consensus.nBudgetProposalEstablishingTime = 720;
        consensus.nSuperblockStartBlock = 2432;
        consensus.nSuperblockCycle = 90;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;

        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;

        consensus.nMajorityWindow = 390;
        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256S("0x0");
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 60;
        consensus.nPowTargetSpacing = 40;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 8;
        consensus.nMinerConfirmationWindow = 11;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1456790400; // March 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800; // May 1st, 2017

        pchMessageStart[0] = 0xbd;
        pchMessageStart[1] = 0xa3;
        pchMessageStart[2] = 0xc8;
        pchMessageStart[3] = 0xb1;

        vAlertPubKey = ParseHex("042736aa94dcc46a596d1f42a5402261b6d9d8a72de40ace5a8856f9e5f7bab96f837f926a8ab8d1e2f8d6d7ef59732d99b55352c4fdf775bdb9690c42851609bd");
        nDefaultPort = 18683;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1498253504, 879253, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c4e1485ee323e0dfab3c8afa871ceceff8822b9abe68005e22576d47a6f"));
        assert(genesis.hashMerkleRoot == uint256S("0x69bb62a0f72c83b38ef6539987cf6c4da5b8e57ac7ecede490a7cefc171e7421"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("nodes.muex.io","nodes.muex.io"));
        vSeeds.push_back(CDNSSeedData("nodes.monetaryunit.org","nodes.monetaryunit.org"));
        vSeeds.push_back(CDNSSeedData("nodes.mymue.com","nodes.mymue.com"));
        vSeeds.push_back(CDNSSeedData("nodes.cryptophi.com","nodes.cryptophi.com"));



        // MonetaryUnit addresses start with 'G'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,38);
        // MonetaryUnit script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // MonetaryUnit private keys start with 'S' or 'T'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,64);

        // Testnet MonetaryUnit BIP32 pubkeys
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet MonetaryUnit BIP32 prvkeys
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Testnet MonetaryUnit BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60;
        strSporkPubKey = "04251df9125d968a5efeac89f08be613621ae19d3d9ca4818485d2405a994b6164d9f26c5ad3e7a19a99dc36fa7dd03f05e968b4bdd1dc39e5b25c0dc60a441506";
        strMasternodePaymentsPubKey = "0483bbc11d4c6a0cb4361da2a234912a7e174e2b9ecfb7685920c24a58fa32205d73f272540032ec7f4dd9d7d865bf171268dcacaa1184675cb2ed2361eb93218f";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x0")),

            1483076495, // * UNIX timestamp of last checkpoint block
            168590,     // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            500         // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = -1;
        consensus.nMasternodePaymentsStartBlock = 121;
        consensus.nMasternodePaymentsIncreaseBlock = -1;
        consensus.nMasternodePaymentsIncreasePeriod = -1;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 212;
        consensus.nBudgetPaymentsCycleBlocks = 90;
        consensus.nBudgetPaymentsWindowBlocks = 39;
        consensus.nBudgetProposalEstablishingTime = 720;
        consensus.nSuperblockStartBlock = 318;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;

        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;

        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256S("0x0");
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60;
        consensus.nPowTargetSpacing = 40;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;
        consensus.nMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0xe6;
        pchMessageStart[1] = 0xce;
        pchMessageStart[2] = 0xa3;
        pchMessageStart[3] = 0xba;
        nMaxTipAge = 1 * 60 * 60;
        nDefaultPort = 17683;
        nPruneAfterHeight = 1000;


        genesis = CreateGenesisBlock(1498253597, 633385 , 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000014536730b6914fb4ce0f3f53c3d204b6602d2637ac83a17eacb13725b53"));
        assert(genesis.hashMerkleRoot == uint256S("0x69bb62a0f72c83b38ef6539987cf6c4da5b8e57ac7ecede490a7cefc171e7421"));

        vFixedSeeds.clear();
        vSeeds.clear();

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x0")),
            0,
            0,
            0
        };

        // MonetaryUnit addresses start with 'R'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);
        // MonetaryUnit script addresses start with 'U' or 'V'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,69);
        // MonetaryUnit private keys start with 'Q' or 'R'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,59);

        // Regtest MonetaryUnit BIP32 pubkeys start with
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest MonetaryUnit BIP32 prvkeys start with
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        // Regtest MonetaryUnit BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
