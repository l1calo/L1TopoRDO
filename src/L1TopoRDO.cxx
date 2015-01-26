#include "L1TopoRDO/L1TopoRDO.h"

#include <cstdint>
#include <vector>

L1TopoRDO::L1TopoRDO():
  m_versionNumber(0),
  m_error(0)
{
  m_dataWords.push_back(0);
}

L1TopoRDO::~L1TopoRDO()
{
}

const std::vector<uint32_t>& L1TopoRDO::getDataWords () const
{
  return m_dataWords;
}

void L1TopoRDO::setDataWords (const std::vector<uint32_t> dataWords)
{
  m_dataWords = dataWords;
}

const std::vector<uint32_t>& L1TopoRDO::getStatusWords () const
{
  return m_statusWords;
}

void L1TopoRDO::setStatusWords (const std::vector<uint32_t> statusWords)
{
  m_statusWords = statusWords;
}

unsigned int L1TopoRDO::getError() const
{
  return m_error;
}

void L1TopoRDO::setError(const unsigned int error)
{
  m_error=error;
}


unsigned int L1TopoRDO::getSourceID() const
{
  return m_sourceID;
}

void L1TopoRDO::setSourceID(const unsigned int id)
{
  m_sourceID=id;
}