// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2023 The Dinartether Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>
#include "chainparamsseeds.h"

//TODO: Take these out
extern double algoHashTotal[16];
extern int algoHashHits[16];


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Date 19/Nov/2023 This is Dinartether";
    const CScript genesisOutputScript = CScript() << ParseHex("04216d0a8ad92e0bd982ece9c41b6705271f7a28250006bb6f0e68320db614aa20f8cde382c72407d997f3162d6d47d1a3668327626e0b217886134c77b1384fe0") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

void CChainParams::TurnOffSegwit() {
	consensus.nSegwitEnabled = true;
}

void CChainParams::TurnOffCSV() {
	consensus.nCSVEnabled = true;
}

void CChainParams::TurnOffBIP34() {
	consensus.nBIP34Enabled = true;
}

void CChainParams::TurnOffBIP65() {
	consensus.nBIP65Enabled = true;
}

void CChainParams::TurnOffBIP66() {
	consensus.nBIP66Enabled = true;
}

bool CChainParams::BIP34() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP65() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP66() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::CSVEnabled() const{
	return consensus.nCSVEnabled;
}


/**
 * Main network
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 1051200;  
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; 
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.powLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60; 
	consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1613; 
        consensus.nMinerConfirmationWindow = 2016; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;  
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1698710400; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1730332800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1736773200; 
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1768309200; 
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1714; 
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1746554400; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1778090400;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1714;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1751220000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1782756000;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1755108000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1786644000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411; 
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;


        // The best chain should have at least this much work
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000004eb8068"); 

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00000164339b4d45907d900b1ad23af18fb7fb28e16e0bd66ec0627b3b4f8316"); 

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x62; // D
        pchMessageStart[1] = 0x31; // I
        pchMessageStart[2] = 0x26; // N
        pchMessageStart[3] = 0x4a; // T
        nDefaultPort = 12022;
        nPruneAfterHeight = 100000;


        genesis = CreateGenesisBlock(1700405567, 1424497, 0x1e00ffff, 4, 50 * COIN);

        consensus.hashGenesisBlock = genesis.GetX16RHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000000d4c1ddfc3fc8fcb8cf1379bf2707f67cf85350df4adda5c3325781e2e4"));
        assert(genesis.hashMerkleRoot == uint256S("0x9627afeed36b3010d597ea06d9ffde4ecc6ae9f9aee0f583ec12133f0a912d24"));

        vSeeds.emplace_back("seed01.dinartether.com", false);
        vSeeds.emplace_back("seed02.dinartether.com", false);
        vSeeds.emplace_back("seed03.dinartether.com", false);
        vSeeds.emplace_back("seed04.dinartether.com", false);
	vSeeds.emplace_back("seed05.dinartether.com", false);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,31);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};


        nExtCoinType = 175;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
                { 0, uint256S("0x000000d4c1ddfc3fc8fcb8cf1379bf2707f67cf85350df4adda5c3325781e2e4")},
                { 1, uint256S("0x000c14f6daf2ac48ce0a912a02cb0a4c114081aa662f09139679aef885ebdb62")},
                { 16, uint256S("0x00088761eedc8266575be357be126000f4145f5e0388db37a660bed05820d944")},
                { 101, uint256S("0x000001e0c06b1ff94a96c3e47bbb3f6b794794a84f74883918621399184178dc")},
                { 107, uint256S("0x00000164339b4d45907d900b1ad23af18fb7fb28e16e0bd66ec0627b3b4f8316")},
            }
        };

		
        chainTxData = ChainTxData{
            
            1700777566, // * UNIX timestamp of last known number of transactions
            108,    // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0.5118483412       // * estimated number of transactions per second after that timestamp
        };

        /** DINT Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "DXissueAssetXXXXXXXXXXXXXXXXXhhZGt";
        strReissueAssetBurnAddress = "DXReissueAssetXXXXXXXXXXXXXXVEFAWu";
        strIssueSubAssetBurnAddress = "DXissueSubAssetXXXXXXXXXXXXXWcwhwL";
        strIssueUniqueAssetBurnAddress = "DXissueUniqueAssetXXXXXXXXXXWEAe58";
        strIssueMsgChannelAssetBurnAddress = "DXissueMsgChanneLAssetXXXXXXSjHvAY";
        strIssueQualifierAssetBurnAddress = "DXissueQuaLifierXXXXXXXXXXXXUgEDbC";
        strIssueSubQualifierAssetBurnAddress = "DXissueSubQuaLifierXXXXXXXXXVTzvv5";
        strIssueRestrictedAssetBurnAddress = "DXissueRestrictedXXXXXXXXXXXXzJZ1q";
        strAddNullQualifierTagBurnAddress = "DXaddTagBurnXXXXXXXXXXXXXXXXZQm5ya";

            //Global Burn Address
        strGlobalBurnAddress = "DXBurnXXXXXXXXXXXXXXXXXXXXXXWUo9FV";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 200; // Asset activated block height
        nMessagingActivationBlock = 210; // Messaging activated block height
        nRestrictedActivationBlock = 210; // Restricted activated block height

        nKAAAWWWPOWActivationTime = 1700790000;
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
        /** DINT End **/
    }
};

/**
 * Testnet (v7)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 1051200;  //~ 4 yrs at 1 min block time
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; 
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;

        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60; 
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1310; 
        consensus.nMinerConfirmationWindow = 2016; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1723312800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1766646000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 6;  
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1759816800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1766646000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 1776276000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 1807812000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1782756000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1814292000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411; 
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 1786644000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 1818180000; 
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 1411; 
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 2016;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000001000100");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00000032a561fdbf3ef8f8ec34653b2258f9033a426428aca14b2adc026d448a");


        pchMessageStart[0] = 0x52; // D
        pchMessageStart[1] = 0x56; // I
        pchMessageStart[2] = 0x4E; // N
        pchMessageStart[3] = 0x54; // T
        nDefaultPort = 18770;
        nPruneAfterHeight = 1000;

        uint32_t nGenesisTime = 1700398954;  

 

        genesis = CreateGenesisBlock(nGenesisTime, 1705244, 0x1e00ffff, 2, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetX16RHash();

        //Test MerkleRoot and GenesisBlock
        assert(consensus.hashGenesisBlock == uint256S("0x00000032a561fdbf3ef8f8ec34653b2258f9033a426428aca14b2adc026d448a"));
        assert(genesis.hashMerkleRoot == uint256S("0x9627afeed36b3010d597ea06d9ffde4ecc6ae9f9aee0f583ec12133f0a912d24"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.emplace_back("seed01-testnet.dinartether.com", false);
        vSeeds.emplace_back("seed02-testnet.dinartether.com", false);
        vSeeds.emplace_back("seed03-testnet.dinartether.com", false);
        vSeeds.emplace_back("seed04-testnet.dinartether.com", false);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        // Dinartether BIP44 cointype in testnet
        nExtCoinType = 1;

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
                    { 0, uint256S("0x00000032a561fdbf3ef8f8ec34653b2258f9033a426428aca14b2adc026d448a")}
            }
        };

        chainTxData = ChainTxData{
            1700398954, // * UNIX timestamp of last known number of transactions
            0,     // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0        // * estimated number of transactions per second after that timestamp
        };

        /** DINT Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "DXissueAssetXXXXXXXXXXXXXXXXWdnemQ";
        strReissueAssetBurnAddress = "DXReissueAssetXXXXXXXXXXXXXXWG9NLd";
        strIssueSubAssetBurnAddress = "DXissueSubAssetXXXXXXXXXXXXXbNiH6v";
        strIssueUniqueAssetBurnAddress = "DXissueUniqueAssetXXXXXXXXXXS4695i";
        strIssueMsgChannelAssetBurnAddress = "DXissueMsgChanneLAssetXXXXXXT2PBdD";
        strIssueQualifierAssetBurnAddress = "DXissueQuaLifierXXXXXXXXXXXXUysLTj";
        strIssueSubQualifierAssetBurnAddress = "DXissueSubQuaLifierXXXXXXXXXYffPLh";
        strIssueRestrictedAssetBurnAddress = "DXissueRestrictedXXXXXXXXXXXXZVT9V";
        strAddNullQualifierTagBurnAddress = "DXaddTagBurnXXXXXXXXXXXXXXXXX5oLMH";

        // Global Burn Address
        strGlobalBurnAddress = "DXBurnXXXXXXXXXXXXXXXXXXXXXXU1qejP";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 6048; // Asset activated block height
        nMessagingActivationBlock = 10080; // Messaging activated block height
        nRestrictedActivationBlock = 10080; // Restricted activated block height

        nKAAAWWWPOWActivationTime = 1774461600; 
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
        /** DINT End **/
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; 
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.kawpowLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; 
        consensus.nMinerConfirmationWindow = 144; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;  // Assets (RIP5)
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 0; 
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 999999999999ULL; 
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideRuleChangeActivationThreshold = 208;
        consensus.vDeployments[Consensus::DEPLOYMENT_TRANSFER_SCRIPT_SIZE].nOverrideMinerConfirmationWindow = 288;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].bit = 10;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideRuleChangeActivationThreshold = 400;
        consensus.vDeployments[Consensus::DEPLOYMENT_COINBASE_ASSETS].nOverrideMinerConfirmationWindow = 500;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x43; // D
        pchMessageStart[1] = 0x52; // I
        pchMessageStart[2] = 0x4F; // N
        pchMessageStart[3] = 0x57; // T
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;


// This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
//        /////////////////////////////////////////////////////////////////
//
//
//        arith_uint256 test;
//        bool fNegative;
//        bool fOverflow;
//        test.SetCompact(0x207fffff, &fNegative, &fOverflow);
//        std::cout << "Test threshold: " << test.GetHex() << "\n\n";
//
//        int genesisNonce = 0;
//        uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
//        uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
//        for (int i=0;i<40000000;i++) {
//            genesis = CreateGenesisBlock(1533751200, i, 0x207fffff, 2, 5000 * COIN);
//            //genesis.hashPrevBlock = TempHashHolding;
//            consensus.hashGenesisBlock = genesis.GetHash();
//
//            arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
//            if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
//                BestBlockHash = consensus.hashGenesisBlock;
//                std::cout << BestBlockHash.GetHex() << " Nonce: " << i << "\n";
//                std::cout << "   PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
//            }
//
//            TempHashHolding = consensus.hashGenesisBlock;
//
//            if (BestBlockHashArith < test) {
//                genesisNonce = i - 1;
//                break;
//            }
//            //std::cout << consensus.hashGenesisBlock.GetHex() << "\n";
//        }
//        std::cout << "\n";
//        std::cout << "\n";
//        std::cout << "\n";
//
//        std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
//        std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
//        std::cout << "Genesis Merkle " << genesis.hashMerkleRoot.GetHex() << std::endl;
//
//        std::cout << "\n";
//        std::cout << "\n";
//        int totalHits = 0;
//        double totalTime = 0.0;
//
//        for(int x = 0; x < 16; x++) {
//            totalHits += algoHashHits[x];
//            totalTime += algoHashTotal[x];
//            std::cout << "hash algo " << x << " hits " << algoHashHits[x] << " total " << algoHashTotal[x] << " avg " << algoHashTotal[x]/algoHashHits[x] << std::endl;
//        }
//
//        std::cout << "Totals: hash algo " <<  " hits " << totalHits << " total " << totalTime << " avg " << totalTime/totalHits << std::endl;
//
//        genesis.hashPrevBlock = TempHashHolding;
//
//        return;

//        /////////////////////////////////////////////////////////////////


        genesis = CreateGenesisBlock(1700404903, 5, 0x207fffff, 4, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetX16RHash();

        assert(consensus.hashGenesisBlock == uint256S("0x50ebfbb2d2925934b7da3179eaeee017437fe52575585849204302a1b56bfd61"));
        assert(genesis.hashMerkleRoot == uint256S("0x9627afeed36b3010d597ea06d9ffde4ecc6ae9f9aee0f583ec12133f0a912d24"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,197);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        // Dinartether BIP44 cointype in regtest
        nExtCoinType = 1;

        /** DINT Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "DXissueAssetXXXXXXXXXXXXXXXXWdnemQ";
        strReissueAssetBurnAddress = "DXReissueAssetXXXXXXXXXXXXXXWG9NLd";
        strIssueSubAssetBurnAddress = "DXissueSubAssetXXXXXXXXXXXXXbNiH6v";
        strIssueUniqueAssetBurnAddress = "DXissueUniqueAssetXXXXXXXXXXS4695i";
        strIssueMsgChannelAssetBurnAddress = "DXissueMsgChanneLAssetXXXXXXT2PBdD";
        strIssueQualifierAssetBurnAddress = "DXissueQuaLifierXXXXXXXXXXXXUysLTj";
        strIssueSubQualifierAssetBurnAddress = "DXissueSubQuaLifierXXXXXXXXXYffPLh";
        strIssueRestrictedAssetBurnAddress = "DXissueRestrictedXXXXXXXXXXXXZVT9V";
        strAddNullQualifierTagBurnAddress = "DXaddTagBurnXXXXXXXXXXXXXXXXX5oLMH";

        // Global Burn Address
        strGlobalBurnAddress = "DXBurnXXXXXXXXXXXXXXXXXXXXXXU1qejP";

        // DGW Activation
        nDGWActivationBlock = 200;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 0; // Asset activated block height
        nMessagingActivationBlock = 0; // Messaging activated block height
        nRestrictedActivationBlock = 0; // Restricted activated block height


        nKAAAWWWPOWActivationTime = 3582830167;
        nKAWPOWActivationTime = nKAAAWWWPOWActivationTime;
        /** DINT End **/
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &GetParams() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network, bool fForceBlockNetwork)
{
    SelectBaseParams(network);
    if (fForceBlockNetwork) {
        bNetwork.SetNetwork(network);
    }
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

void TurnOffSegwit(){
	globalChainParams->TurnOffSegwit();
}

void TurnOffCSV() {
	globalChainParams->TurnOffCSV();
}

void TurnOffBIP34() {
	globalChainParams->TurnOffBIP34();
}

void TurnOffBIP65() {
	globalChainParams->TurnOffBIP65();
}

void TurnOffBIP66() {
	globalChainParams->TurnOffBIP66();
}
