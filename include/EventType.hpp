#ifndef EVENTTYPE_H
#define EVENTTYPE_H
#include <string>
class EventType{
public:
  int type;

  EventType(int type);

  friend bool operator==(const EventType& a, const EventType& t) {
    return a.type == t.type;
  }

};

//hashing function for the EventType
namespace std {
template <> struct hash<EventType>
{
  std::size_t operator()(const EventType& k) const
  {
    using std::size_t;
    using std::hash;
    using std::string;

    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:

    return ((hash<int>()(k.type)));
  }
};
}

#endif
