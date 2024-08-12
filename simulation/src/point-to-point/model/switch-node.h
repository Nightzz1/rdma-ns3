#ifndef SWITCH_NODE_H
#define SWITCH_NODE_H

#include <map>
#include <unordered_map>
#include <ns3/node.h>
#include "ns3/qbb-net-device.h"
#include "ns3/switch-mmu.h"
#include "ns3/pint.h"
#include "ns3/custom-header.h"

namespace ns3 {

class Packet;

class flow_key {
public:
    flow_key() {};
    flow_key(CustomHeader& ch) {
        sip = ch.sip;
        dip = ch.dip;
        sport = ch.udp.sport;
        dport = ch.udp.dport;
    }
    uint32_t sip, dip;
    uint16_t sport, dport;

    bool operator==(const flow_key& a) const {
        if (a.sip == this->sip && a.dip == this->dip && a.sport == this->sport && a.dport == this->dport) return true;
        return false;
    }
};

struct FlowKeyHash {
    std::size_t operator()(const flow_key& key) const {
        // 使用 std::hash 对多个成员进行哈希并结合
        return ((std::hash<uint32_t>()(key.sip) ^ (std::hash<uint32_t>()(key.dip) << 1)) >> 1) ^
               (std::hash<uint16_t>()(key.sport) ^ (std::hash<uint16_t>()(key.dport) << 1));
    }
};

class SwitchNode : public Node{
	static const uint32_t pCnt = 257;	// Number of ports used
	static const uint32_t qCnt = 8;	// Number of queues/priorities used
	uint32_t m_ecmpSeed;
	std::unordered_map<uint32_t, std::vector<int> > m_rtTable; // map from ip address (u32) to possible ECMP port (index of dev)

	// monitor of PFC
	uint32_t m_bytes[pCnt][pCnt][qCnt]; // m_bytes[inDev][outDev][qidx] is the bytes from inDev enqueued for outDev at qidx
	
	uint64_t m_txBytes[pCnt]; // counter of tx bytes

	uint32_t m_lastPktSize[pCnt];
	uint64_t m_lastPktTs[pCnt]; // ns
	double m_u[pCnt];

protected:
	bool m_ecnEnabled;
	uint32_t m_ccMode;
	uint64_t m_maxRtt;

	uint32_t m_ackHighPrio; // set high priority for ACK/NACK    

private:
	int GetOutDev(Ptr<const Packet>, CustomHeader &ch);
	void SendToDev(Ptr<Packet>p, CustomHeader &ch);
	static uint32_t EcmpHash(const uint8_t* key, size_t len, uint32_t seed);
	void CheckAndSendPfc(uint32_t inDev, uint32_t qIndex);
	void CheckAndSendResume(uint32_t inDev, uint32_t qIndex);
public:
	Ptr<SwitchMmu> m_mmu;
    std::unordered_map<flow_key, int, FlowKeyHash> m_flow_table[pCnt];

	static TypeId GetTypeId (void);
	SwitchNode();
	void SetEcmpSeed(uint32_t seed);
	void AddTableEntry(Ipv4Address &dstAddr, uint32_t intf_idx);
	void ClearTable();
	bool SwitchReceiveFromDevice(Ptr<NetDevice> device, Ptr<Packet> packet, CustomHeader &ch);
	void SwitchNotifyDequeue(uint32_t ifIndex, uint32_t qIndex, Ptr<Packet> p);

	// for approximate calc in PINT
	int logres_shift(int b, int l);
	int log2apprx(int x, int b, int m, int l); // given x of at most b bits, use most significant m bits of x, calc the result in l bits
};

} /* namespace ns3 */

#endif /* SWITCH_NODE_H */
