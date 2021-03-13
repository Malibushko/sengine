#include <uuid.h>

class Identifiable
{
 public:
    using id_t = uuids::uuid;

    Identifiable();

    uuids::uuid GetId() const noexcept;

 private:
    uuids::uuid m_ID;
};
