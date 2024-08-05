#ifndef RATE_TAG_H
#define RATE_TAG_H

#include "ns3/tag.h"

namespace ns3 {

class RateTag : public Tag
{
public:
    static TypeId GetTypeId (void);
    virtual TypeId GetInstanceTypeId (void) const;
    virtual utint32_t GetSerializedSize (void) const;
    virtual void Serialize (TagBuffer buf) const;
    virtual void Deserialize (TagBuffer buf);
    virtual void Print (std::ostream &os) const;
    RateTag ();
    RateTag (double rate);
    void SetRate (double rate);
    double GetRate (void) const;
private:
    double m_rate;
};

}

#endif