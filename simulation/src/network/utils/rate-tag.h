#ifndef RATE_TAG_H
#define RATE_TAG_H

#include "ns3/tag.h"

namespace ns3 {

class RateTag : public Tag
{
public:
    static TypeId GetTypeId (void);
    virtual TypeId GetInstanceTypeId (void) const;
    virtual uint32_t GetSerializedSize (void) const;
    virtual void Serialize (TagBuffer buf) const;
    virtual void Deserialize (TagBuffer buf);
    virtual void Print (std::ostream &os) const;
    RateTag ();
    RateTag (uint32_t rate, uint32_t id);
    uint32_t GetRate();
    uint32_t GetId();
private:
    uint32_t m_rate;
    uint32_t m_id;
};

}

#endif