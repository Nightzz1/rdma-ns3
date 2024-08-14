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
    return sizeof(uint32_t) * 2;
}

void
RateTag::Serialize (TagBuffer buf) const 
{
    buf.WriteU32(m_rate);
    buf.WriteU32(m_id);
}

void
RateTag::Deserialize (TagBuffer buf)
{
    m_rate = buf.ReadU32();
    m_id = buf.ReadU32();
}

void
RateTag::Print (std::ostream &os) const
{
    os << "Rate = " << m_rate << " Id = " << m_id;
}

RateTag::RateTag ()
    : Tag()
{
}

RateTag::RateTag(uint32_t rate, uint32_t id)
    : Tag(),
      m_rate (rate), m_id(id)
{
}

uint32_t RateTag::GetRate() {
    return m_rate;
}

uint32_t RateTag::GetId() {
    return m_id;
}

}