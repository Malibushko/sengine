#include "Identifiable.h"

Identifiable::Identifiable()
{
    static uuids::uuid_system_generator Generator;
    m_ID = Generator();

    assert( !m_ID.is_nil() );
}
