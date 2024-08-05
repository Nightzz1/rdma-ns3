#include "rate-tag.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (RateTag);

TypeId
RateTag::GetTypeId (void)
{
    static TypeId tid = TypeId ("ns3::RateTag")
        .SetParent<Tag> ()
        .AddConstructor<RateTag> ()
    ;
    return tid;
}

TypeId
RateTag::GetInstanceTypeId (void) const
{
    return GetTypeId();
}

uint32_t
RateTag::GetSerializedSize (void) const
{
    return sizeof(double);
}

void
RateTag::Serialize (TagBuffer buf) const 
{
    buf.WriteDouble(m_rate);
}

void
RateTag::Deserialize (TagBuffer buf)
{
    m_rate = buf.ReadDouble();
}

void
RateTag::Print (std::ostream &os) const
{
    os << "Rate=" << m_rate;
}

RateTag::RateTag ()
    : Tag()
{
}

RateTag::RateTag(double rate)
    : Tag(),
      m_rate (rate)
{
}

void
RateTag::SetRate (double rate)
{
    m_rate = rate;
}

double 
RateTag::GetRate (void) const
{
    return m_rate;
}

}