#include <iostream>
#include "L1TopoRDO/Fibre.h"
#include "L1TopoRDO/Helpers.h"
#include "L1TopoRDO/BlockTypes.h"

namespace L1Topo {

  Fibre::Fibre(const std::vector<uint32_t> status, const std::vector<uint32_t> count)
    :m_status(status), m_count(count), m_word(0) {
    this->encode();
  }

  Fibre::Fibre(const uint32_t word)
    :m_status(5,0), m_count(5,0), m_word(word) {
    this->decode();
  }
  
  // assume the vectors are correctly ordered - no way to know what they mean nor what order they should be in
  // will read vector from left to right and pack word left to right, unusually.
  void Fibre::encode(){
     m_word = static_cast<int>(L1Topo::BlockTypes::FIBRE) << 28;
     // assert(status.size()<=5);
     // assert(status.size()==count.size());
     for (unsigned int i=0; i<5 && i<m_status.size() && i<m_count.size(); ++i){
       // assert(m_count[i]<0x10); // should not exceed 4 bits
       uint32_t fibre = (m_status[i] & 0x1) << 4 | (m_count[i] & 0xf) ;
       m_word |= (fibre << (((4-i)*5)+3) );
     }
  }

  void Fibre::decode(){
    for (unsigned int i=0; i<5; ++i){
      uint32_t fibre = m_word >> (((4-i)*5)+3) & 0x1f;
      m_status[i] = (fibre >> 4) & 0x1;
      m_count[i] = fibre & 0xf;
    }
  }
  
  uint32_t Fibre::word() const{
    return m_word;
  }
  
  const std::vector<uint32_t>& Fibre::status() const{
    return m_status;
  }
  
  const std::vector<uint32_t>& Fibre::count() const{
    return m_count;
  }
    
} // namespace L1Topo

std::ostream& operator<<(std::ostream& os, const L1Topo::Fibre& f) {

  os << "     Fibre status,sizes: ";
  for (unsigned int i=0; i<5 && i<f.status().size() && i<f.count().size(); ++i){
    os << "(" << f.status()[i] << "," << f.count()[i] << ") ";
  }
  return os;
}
