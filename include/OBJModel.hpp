#ifndef INCLUDE_INCLUDE_OBJMODEL_HPP_
#define INCLUDE_INCLUDE_OBJMODEL_HPP_

#include "types.hpp"

#include <map>
#include <string>
#include <vector>

class OBJModel {
public:
  OBJModel();
  OBJModel(OBJModel &&) = default;
  OBJModel(const OBJModel &) = default;
  OBJModel &operator=(OBJModel &&) = default;
  OBJModel &operator=(const OBJModel &) = default;
  ~OBJModel();

  void LoadFromFile(const std::string &filename);

  [[nodiscard]] std::vector<f32> getVertexData() const;
  [[nodiscard]] i32 getVertexCount() const;

private:
  struct Color {
    f32 r;
    f32 g;
    f32 b;
  };
  struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
  };

  std::map<std::string, Color> mMaterialMap;
  std::vector<f32> mVertexData;

  void LoadMaterialFile(const std::string &filename);
  bool StartWith(const std::string &line, const char *text);
  void addVertexData(const i32 vIdx, const i32 nIdx, const char *const mtl,
                     const std::vector<Vec3> &vertices,
                     const std::vector<Vec3> &normals);
};

#endif // INCLUDE_INCLUDE_OBJMODEL_HPP_
