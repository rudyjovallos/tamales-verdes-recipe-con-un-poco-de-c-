#ifndef CORD_HPP
#define CORD_HPP

#include <cstddef>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "cs128referencelist.hpp"

class Cord : public std::enable_shared_from_this<Cord> {
public:
  Cord(const std::string& dat);
  Cord(const std::shared_ptr<Cord>& left_cord,
       const std::shared_ptr<Cord>& right_cord);

  ~Cord() = default;
  Cord(const Cord&) = delete;
  Cord& operator=(const Cord&) = delete;

  // Getters
  size_t Length() const;
  const std::string& GetData() const;
  std::shared_ptr<Cord> GetLeft() const;
  std::shared_ptr<Cord> GetRight() const;

  // Cord Operations
  std::string ToString() const;
  std::shared_ptr<Cord> SubString(
      size_t lower_idx, size_t upper_idx);  // lower inclusive, upper exclusive
  char At(size_t idx) const;

  void ToStringRecursive(std::string& string, const Cord& cord) const;
  void AtRecursive(size_t& idx, const Cord& cord, char& val) const;
  void ExtractCordsRec(size_t lower_idx,
                       size_t upper_idx,
                       int& index,
                       const Cord& cord) const;
  void CheckCords(std::map<std::string, std::shared_ptr<Cord>>& visited,
                  std::shared_ptr<Cord>& cord) const;

  bool IsInternalNode() const;
  bool IsLeafNode() const;

  // Friend functions
  friend std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord,
                                           std::shared_ptr<Cord> right_cord);
  friend void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords);

private:
  std::shared_ptr<Cord> left_ = nullptr;
  std::shared_ptr<Cord> right_ = nullptr;
  size_t length_;
  std::string data_;

  bool IsValidCord() const;
};

#endif
